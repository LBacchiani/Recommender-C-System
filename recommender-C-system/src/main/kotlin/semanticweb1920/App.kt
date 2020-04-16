package semanticweb1920


import ConceptMaterialMapper.generateStudent
import semanticweb1920.parser.c.CCodeParser
import semanticweb1920.parser.c.model.MapperVisitorWithMemory
import ConceptMaterialMapper.recommend
import semanticweb1920.rdf.COntology
import semanticweb1920.rdf.serialization.SerializationUtils
import semanticweb1920.rdf.serialization.mapping.ASTInfoMapping
import mu.KotlinLogging
import org.apache.jena.rdf.model.ModelFactory
import java.io.File
import java.nio.file.Files
import java.nio.file.Paths

private val logger = KotlinLogging.logger {}

fun main(args: Array<String>) {
    val outputModel = ModelFactory.createDefaultModel()
    if (args[0].isBlank()) {
        logger.error { "First argument should be the program's mode" }
        System.exit(1)
    }

    if(args[0] == "A") {
        logger.info { "Starting annotation mode..." }
        if (args[1].isBlank() || args[2].isBlank()) {
            logger.error { "Second argument should be the path to the file to parse" }
            logger.error { "Third argument should be the path to the annotation file" }
            //logger.error { "Fourth argument should be the path to the theory file" }
            System.exit(1)
        }
        val toParse: String? = try {
            String(Files.readAllBytes(Paths.get(args[1])))
        } catch (e: Exception) {
            logger.error(e) { "Cannot read file ${args[1]}" }
            System.exit(1)
            null
        }

        val annotationStream = try {
            File(args[2]).outputStream()
        } catch (e: Exception) {
            logger.error(e) { "Cannot write output file ${args[2]}" }
            System.exit(1)
            null
        }

//        val theoryStream = try {
//            File(args[3]).outputStream()
//        } catch (e: Exception) {
//            logger.error(e) { "Cannot write output file ${args[3]}" }
//            System.exit(1)
//            null
//        }

        val ast = CCodeParser.parse(toParse!!)

        ast.translationUnit.accept(
            MapperVisitorWithMemory(StringBuilder(SerializationUtils.CREATED_RESOURCES_NAMESPACE))
            { memory, currentNode ->
                ASTInfoMapping.toRDF(memory, currentNode, outputModel)
            })
        outputModel.setNsPrefixes(COntology.prefixes)
        outputModel.write(annotationStream!!)
        logger.info { "Created resulting annotation file at ${args[2]}" }
        logger.info { "--------Material recommended--------" }
        recommend(ASTInfoMapping.topics)
        //fromCodeToTheory(outputModel, theoryStream!!)
    }

    if(args[0] == "G") {
        logger.info { "Generating students..." }
        if(args[1].isBlank() || args[1].toIntOrNull() == null) {
            logger.error { "Second argument should be an integer" }
            System.exit(1)
        }
        generateStudent(args[1].toInt())
    }

}


