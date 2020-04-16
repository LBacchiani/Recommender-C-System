import mu.KotlinLogging
import org.apache.jena.query.QueryExecutionFactory
import org.apache.jena.query.QueryFactory
import org.apache.jena.rdf.model.*
import org.apache.jena.rdf.model.ResourceFactory.createResource
import semanticweb1920.rdf.CEducationalOntology



object ConceptMaterialMapper {
    private val logger = KotlinLogging.logger {}
    private const val queryPrefix = "PREFIX  edu: <http://www.semanticweb.org/lori/ontologies/2020/3/C-Educational-Ontology#>\n " +
                      "PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>\nPREFIX skos:<http://www.w3.org/2004/02/skos/core#>\n"
    private val educationalModel = CEducationalOntology.model

    fun generateStudent(n: Int) {

        val names = listOf("Leonardo", "Francesco", "Alessandro", "Lorenzo", "Mattia", "Sofia", "Giulia", "Giorgia",
            "Martina", "Beatrice", "Luca", "Dario", "Sara", "Gaia", "Stefano", "Carla", "Giovanna", "Giovanni", "Andrea", "Stefano", "Mattia",
            "Alessia", "Marzia", "Luisa")

        val surnames = listOf("Bianchi", "Rossi", "Verdi", "Gialli", "Russo", "Costa", "Rizzo", "Conti", "Esposito", "Talamelli",
            "Bianco", "Storti", "Barbieri", "Tagliati", "Omiccioli", "Carnaroli", "Lazzarin", "Marzeri", "Bertarelli", "Abbruciati")
        val topics = educationalModel.listStatements(setSelector { s: Statement? -> s?.predicate?.localName == "hasTopic" }).toSet().map { x -> x.`object`.asResource()}.toSet()
        val educationalLevels = educationalModel.listStatements(setSelector { s: Statement? -> s?.predicate?.localName == "adaptTo"}).toSet().map { x -> x.`object`.asResource()}.toSet()
        val materialDifficultyLevels = educationalModel.listStatements(setSelector { s: Statement? -> s?.predicate?.localName == "hasDifficulty"}).toSet().map { x -> x.`object`.asResource()}.toSet()
        val materialTypes = educationalModel.listStatements(setSelector {s: Statement? -> s?.predicate?.localName == "hasType"}).toSet().map { x -> x.`object`.asResource()}.toSet()
        for(i in 1..n) {
            val student = createResource(CEducationalOntology.NAMESPACE + names.random() + surnames.random())
            val interestingTopics = topics.shuffled().subList(0, (2..5).random())
            val difficultyLevelsHandled = materialDifficultyLevels.shuffled().subList(0,materialDifficultyLevels.indices.random())
            val educationalLevel = educationalLevels.random()
            // to insert types in query change last subList parameter from 0 to materialTypes.indices.random()
            val types = materialTypes.shuffled().subList(0,0)
            with(educationalModel) {
                interestingTopics.forEach { topic -> add(createStatement(student, CEducationalOntology.HAS_INTEREST, topic))}
                add(createStatement(student, CEducationalOntology.HAS_EDUCATIONAL_LEVEL, educationalLevel))
                difficultyLevelsHandled.forEach { difficulty -> add(createStatement(student, CEducationalOntology.HANDLE_DIFFICULTY_LEVEL, difficulty))}
                types.forEach { type -> add(createStatement(student, CEducationalOntology.PREFERS, type)) }
            }
            logger.info { "-----------Material for ${student.localName}-----------" }
            logger.info { "Query parameter: \n- Topics: " + interestingTopics.map { x -> x.localName } + "\n- Educational level: ${educationalLevel.localName}\n- Difficulty level handled: " + difficultyLevelsHandled.map { x -> x.localName } + "\n- Preferred types: " + types.map { x -> x.localName } }
            logger.info { "Recommended material: " }
            val links: MutableMap<String,MutableSet<String>> =  mutableMapOf()
            recommend(buildMaterialQuery("",student.localName,difficultyLevelsHandled.isNotEmpty(),types.isNotEmpty()), links)
            niceoutput(links)
            logger.info { "You may be interested in: " }
            val recommendedLinks: MutableMap<String,MutableSet<String>> =  mutableMapOf()
            recommend(buildRelatedMaterialQuery("",student.localName,difficultyLevelsHandled.isNotEmpty(), types.isNotEmpty()), recommendedLinks, interestingTopics.map { x -> x.localName }.toSet())
            niceoutput(recommendedLinks)
        }
    }

    fun recommend(topics: Set<String>) {
        val links: MutableMap<String,MutableSet<String>> =  mutableMapOf()
        topics.forEach{topic -> recommend(buildMaterialQuery(topic), links)}
        niceoutput(links)
        logger.info { "--------Related material--------" }
        val recommendedLinks: MutableMap<String,MutableSet<String>> =  mutableMapOf()
        topics.forEach {topic -> recommend(buildRelatedMaterialQuery(topic), recommendedLinks, topics)}
        niceoutput(recommendedLinks)
    }


    private fun recommend(query: String, links: MutableMap<String,MutableSet<String>>, topics: Set<String> = setOf()) {
        val qe = QueryExecutionFactory.create(QueryFactory.create(query), educationalModel)
        val rs = qe.execSelect()
        while (rs.hasNext()) {
            val sol = rs.nextSolution()
            val arg = sol.get("arg").toString().substring(sol.get("source").toString().indexOf("#") + 1)
            val link = sol.get("source").toString().substring(sol.get("source").toString().indexOf("@") + 1)
            if (topics.isEmpty() || !topics.contains(arg)) {
                if (!links.containsKey(arg)) {
                    links[arg] = mutableSetOf(" - material at $link")
                } else {
                    links[arg]?.add(" - material at $link")
                }
            }
        }
        qe.close()
    }

    private fun niceoutput(links: MutableMap<String,MutableSet<String>>) {
        links.entries.forEach { (k,v) ->
            logger.info { "Material for --> $k" }
            v.forEach { s -> logger.info { s } }
        }
    }


    private fun buildMaterialQuery(topic: String = "", student: String = "", specifiedDiff: Boolean = false, specifiedType: Boolean = false):String {
        var query = queryPrefix +  "SELECT ?arg ?source\n" +
                "WHERE { \n" +
                "?material edu:hasSource ?source. \n" +
                "?material edu:hasTopic ?arg. \n"
        query += if(student != "") "?student edu:hasInterest ?arg. \n ?student edu:hasEducationalLevel ?eduLevel.\n ?material edu:adaptTo ?eduLevel.\n" else ""
        query += if(specifiedDiff) "?student edu:handleMaterialDifficultyLevel ?level.\n ?material edu:hasDifficulty ?level.\n" else ""
        query += if(specifiedType) "?student edu:prefers ?type. \n?material edu:hasType ?type." else ""
        query += if(student != "") "VALUES ?student {edu:$student}. \n }" else "VALUES ?arg  { edu:$topic}.\n }"
        return query
    }

    private fun buildRelatedMaterialQuery(topic: String = "", student: String = "", specifiedDiff: Boolean = false, specifiedType: Boolean = false): String {
        var query = queryPrefix + "SELECT ?arg ?source\n" +
                "WHERE {\n" +
                "      ?arg1 skos:related ?arg.\n" +
                "      ?relatedObj edu:hasTopic ?arg.\n" +
                "      ?relatedObj edu:hasSource ?source.\n"
        query += if(student != "") "?student edu:hasInterest ?arg1. \n?student edu:hasEducationalLevel ?eduLevel.\n?relatedObj edu:adaptTo ?eduLevel.\n" else ""
        query += if(specifiedDiff)  "?student  edu:handleMaterialDifficultyLevel ?level.\n?relatedObj edu:hasDifficulty ?level.\n" else ""
        query += if(specifiedType) "?student edu:prefers ?type. \n?relatedObj edu:hasType ?type." else ""
        query += if(student != "" ) "VALUES ?student {edu:$student}. \n }" else "VALUES ?arg1  { edu:$topic}.\n }"
        return query
    }

    //generic function for creating a selector
    private fun setSelector(select: (s: Statement?) -> Boolean): SimpleSelector {
        return object : SimpleSelector() {
            override fun selects(s: Statement?): Boolean {
                return select(s)
            }
        }
    }
}
