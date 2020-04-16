package semanticweb1920.rdf

import mu.KotlinLogging
import org.apache.jena.rdf.model.Model
import org.apache.jena.rdf.model.ModelFactory
import org.apache.jena.rdf.model.Property
import org.apache.jena.rdf.model.Resource
import org.apache.jena.shared.PrefixMapping

private val logger = KotlinLogging.logger {}

/**
 * Ontology model class
 */
object CEducationalOntology {

    private const val RDF = "http://www.w3.org/1999/02/22-rdf-syntax-ns#"
    private const val RDFS = "http://www.w3.org/2000/01/rdf-schema#"
    const val NAMESPACE = "http://www.semanticweb.org/lori/ontologies/2020/3/C-Educational-Ontology#"



    val prefixes: PrefixMapping = PrefixMapping.Factory.create()
        .setNsPrefix("CEducationalOntology", NAMESPACE)

    // load ontology model or empty model if not found
    val model: Model = ModelFactory.createDefaultModel().also { model ->
        javaClass.classLoader.getResourceAsStream("CEducationalOntology.owl")?.also {
            model.read(it, null)
        } ?: logger.warn { "CEducationalOntology.owl resource not found" }
    }



    private infix fun String.resource(resourceName: String): Resource = model.getResource(this + resourceName)
    private infix fun String.property(propertyName: String): Property = model.getProperty(this + propertyName)

    //////////////
    // Entities //
    /////////////

    //////////////ARGUMENT////////////////////
    val ARGUMENT = NAMESPACE resource "Argument"
    ////DIRECTIVE
    val CONDITIONAL_DIRECTIVE = NAMESPACE resource "ConditionalDirective"
    val DEFINE_DIRECTIVE = NAMESPACE resource "DefineDirective"
    val INCLUDE_DIRECTIVE = NAMESPACE resource "IncludeDirective"
    ////LOOP
    val DO_STATEMENT = NAMESPACE resource "DoStatement"
    val FOR_STATEMENT = NAMESPACE resource "ForStatement"
    val WHILE_STATEMENT = NAMESPACE resource "WhileStatement"
    ////TYPE
    val ARRAY_TYPE = NAMESPACE resource "ArrayType"
    val ENUM = NAMESPACE resource "Enum"
    val STRUCT = NAMESPACE resource "Struct"
    val UNION = NAMESPACE resource "Union"
    val POINTER = NAMESPACE resource "Pointer"
    //BRANCHING STATEMENT
    val BREAK = NAMESPACE resource "BreakStatement"
    val CONTINUE = NAMESPACE resource "ContinueStatement"
    val GOTO = NAMESPACE resource "GotoStatement"
    val RETURN = NAMESPACE resource "ReturnStatement"
    //DECISION MAKING STATEMENT
    val IF_THEN_ELSE = NAMESPACE resource "IfThenElseStatement"
    val SWITCH = NAMESPACE resource "SwitchStatement"
    //EXECUTABLE
    val FUNCTION = NAMESPACE resource "Function"
    //EXPRESSION
    val CAST = NAMESPACE resource "CastExpression"
    val DEREFERENCE = NAMESPACE resource "DereferencingExpression"
    val REFERENCE = NAMESPACE resource "ReferencingExpression"
    //STORAGE CLASS MODIFIER
    val AUTO = NAMESPACE resource "AutoModifier"
    val EXTERN = NAMESPACE resource "ExternModifier"
    val REGISTER = NAMESPACE resource "RegisterModifier"
    val STATIC = NAMESPACE resource "StaticModifier"
    //TYPE QUALIFIER
    val CONST = NAMESPACE resource "Const"
    val VOLATILE = NAMESPACE resource "Volatile"




    ////DIFFICULTY LEVEL//////
    val EASY = NAMESPACE resource "Easy"
    val MEDIUM = NAMESPACE resource "Medium"
    val HARD = NAMESPACE resource "Hard"

    ////EDUCATIONAL LEVEL //////

    val HIGH_SCHOOL = NAMESPACE resource "HighSchool"
    val UNIVERSITY = NAMESPACE resource "University"

    ////LEARNING OBJECT//////
    val LEARNING_OBJECT = NAMESPACE resource "LearningObject"

    ////LEARNING OBJECT TYPE//////
    val CODE_EXAMPLE = NAMESPACE resource "CodeExample"
    val EXERCISE = NAMESPACE resource "Exercise"
    val AUDIO = NAMESPACE resource "Audio"
    val IMAGE = NAMESPACE resource  "Image"
    val VIDEO = NAMESPACE resource "Video"
    val ARTICLE = NAMESPACE resource "Article"
    val LECTURE = NAMESPACE resource "Lecture"
    val SCHOOLAR_MATERIAL = NAMESPACE resource "SchoolarMaterial"
    val SUMMARY = NAMESPACE resource "Summary"
    val SURVEY = NAMESPACE resource "Survey"


    ///PROPERTY////

    val HAS_TOPIC = NAMESPACE property "hasTopic"
    val IS_TOPIC_OF = NAMESPACE property "isTopicOf"
    val HAS_TYPE = NAMESPACE property "hasType"
    val HAS_DIFFICULTY = NAMESPACE property "hasDifficulty"
    val HAS_EDUCATIONAL_LEVEL = NAMESPACE property "hasEducationalLevel"
    val HANDLE_DIFFICULTY_LEVEL = NAMESPACE property "handleMaterialDifficultyLevel"
    val HAS_INTEREST = NAMESPACE property "hasInterest"
    val PREFERS = NAMESPACE property "prefers"
}
