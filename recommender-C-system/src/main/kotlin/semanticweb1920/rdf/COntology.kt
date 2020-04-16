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
object COntology {

    private const val RDF = "http://www.w3.org/1999/02/22-rdf-syntax-ns#"
    private const val RDFS = "http://www.w3.org/2000/01/rdf-schema#"
    const val NAMESPACE = "https://gitlab.com/semantic-web-1819/c-owl-ontology/raw/master/COntology.owl#"
    // const val CODE_ONTOLOGY = "https://raw.githubusercontent.com/codeontology/parser/master/ontology/CodeOntology.owl#"

    val prefixes: PrefixMapping = PrefixMapping.Factory.create()
            .setNsPrefix("cOntology", NAMESPACE)

    // load ontology model or empty model if not found
    val model: Model = ModelFactory.createDefaultModel().also { model ->
        javaClass.classLoader.getResourceAsStream("COntology.owl")?.also {
            model.read(it, null)
        } ?: logger.warn { "COntology.owl resource not found" }
    }


    private infix fun String.resource(resourceName: String): Resource = model.getResource(this + resourceName)
    private infix fun String.property(propertyName: String): Property = model.getProperty(this + propertyName)

    //////////////
    // Entities //
    //////////////

    val LIBRARY_ENTITY = NAMESPACE resource "Library"

    val CODE_ELEMENT_ENTITY = NAMESPACE resource "CodeElement"

    // Directives
    val DIRECTIVE_ENTITY = NAMESPACE resource "Directive"
    val CONDITIONAL_DIRECTIVE_ENTITY = NAMESPACE resource "ConditionalDirective"
    val DEFINE_DIRECTIVE_ENTITY = NAMESPACE resource "DefineDirective"
    val INCLUDE_DIRECTIVE_ENTITY = NAMESPACE resource "IncludeDirective"

    // Executables
    val FUNCTION_ENTITY = NAMESPACE resource "Function"

    // Expression
    val EXPRESSION_ENTITY = NAMESPACE resource "Expression"
    val ACTUAL_ARGUMENT_ENTITY = NAMESPACE resource "ActualArgument"
    val ASSIGNMENT_EXPRESSION_ENTITY = NAMESPACE resource "AssignmentExpression"
    val CAST_EXPRESSION_ENTITY = NAMESPACE resource "CastExpression"
    val DEREFERENCING_EXPRESSION_ENTITY = NAMESPACE resource "DereferencingExpression"
    val FUNCTION_INVOCATION_EXPRESSION_ENTITY = NAMESPACE resource "FunctionInvocationExpression"
    val REFERENCING_EXPRESSION_ENTITY = NAMESPACE resource "ReferencingExpression"

    // Modifiers
    val STORAGE_CLASS_MODIFIER = NAMESPACE resource "StorageClassModifier"
    val TYPE_QUALIFIER = NAMESPACE resource "TypeQualifier"

    // Statement
    val STATEMENT_ENTITY = NAMESPACE resource "Statement"

    val BLOCK_ENTITY = NAMESPACE resource "BlockStatement"
    val CASE_ENTITY = NAMESPACE resource "CaseLabeledBlock"
    val DEFAULT_ENTITY = NAMESPACE resource "DefaultLabeledBlock"

    val BREAK_ENTITY = NAMESPACE resource "BreakStatement"
    val CONTINUE_ENTITY = NAMESPACE resource "ContinueStatement"
    val GOTO_ENTITY = NAMESPACE resource "GotoStatement"
    val RETURN_ENTITY = NAMESPACE resource "ReturnStatement"
    val IF_THEN_ELSE_ENTITY = NAMESPACE resource "IfThenElseStatement"
    val SWITCH_ENTITY = NAMESPACE resource "SwitchStatement"
    val DO_WHILE_ENTITY = NAMESPACE resource "DoStatement"
    val FOR_ENTITY = NAMESPACE resource "ForStatement"
    val WHILE_ENTITY = NAMESPACE resource "WhileStatement"

    val DECLARATION_ENTITY = NAMESPACE resource "DeclarationStatement"
    val FUNCTION_DECLARATION_ENTITY = NAMESPACE resource "FunctionDeclaration"
    val STRUCT_TYPE_DECLARATION_ENTITY = NAMESPACE resource "StructTypeDeclaration"
    val TYPE_ALIAS_DECLARATION_ENTITY = NAMESPACE resource "TypeAliasDeclaration"
    val UNION_TYPE_DECLARATION_ENTITY = NAMESPACE resource "UnionTypeDeclaration"
    val ENUM_TYPE_DECLARATION_ENTITY = NAMESPACE resource "EnumTypeDeclaration"
    val VARIABLE_DECLARATION_ENTITY = NAMESPACE resource "VariableDeclarationStatement"
    val EXPRESSION_STATEMENT_ENTITY = NAMESPACE resource "ExpressionStatement"

    // Types
    val TYPE_ENTITY = NAMESPACE resource "Type"
    val ARRAY_ENTITY = NAMESPACE resource "ArrayType"
    val ENUM_ENTITY = NAMESPACE resource "Enum"
    val STRUCT_ENTITY = NAMESPACE resource "Struct"
    val UNION_ENTITY = NAMESPACE resource "Union"
    val POINTER_ENTITY = NAMESPACE resource "Pointer"
    val POINTER_DOC_ENTITY = NAMESPACE resource "PointerDoc"
    val PRIMITIVE_ENTITY = NAMESPACE resource "PrimitiveType"
    val FLOATING_POINT_TYPE = NAMESPACE resource "FloatingPointType"
    val INTEGER_TYPE = NAMESPACE resource "IntegerType"

    // Variables
    val FIELD_ENTITY = NAMESPACE resource "Field"
    val CELL_ENTITY = NAMESPACE resource "Cell"
    val LOCAL_VARIABLE_ENTITY = NAMESPACE resource "LocalVariable"
    val PARAMETER_ENTITY = NAMESPACE resource "Parameter"

    // Project
    val PROJECT_ENTITY = NAMESPACE resource "Project"
    val MAVEN_PROJECT_ENTITY = NAMESPACE resource "MavenProject"
    val GRADLE_PROJECT_ENTITY = NAMESPACE resource "GradleProject"

    ////////////////
    // Properties //
    ////////////////

    // Object properties
    val RDF_TYPE_PROPERTY = RDF property "type"

    val ARGUMENT_PROPERTY = NAMESPACE property "hasArgument"
    val DECLARATION_PROPERTY = NAMESPACE property "hasDeclaration"
    val FUNCTION_DECLARATION_PROPERTY = NAMESPACE property "hasFunctionDeclaration"
    val TYPE_DECLARATION_PROPERTY = NAMESPACE property "hasTypeDeclaration"
    val VARIABLE_DECLARATION_PROPERTY = NAMESPACE property "hasVariableDeclaration"
    val DEPENDENCY_PROPERTY = NAMESPACE property "hasDependency"
    val MODIFIER_PROPERTY = NAMESPACE property "hasModifier"
    val PARAMETER_PROPERTY = NAMESPACE property "hasParameter"
    val TYPE_PROPERTY = NAMESPACE property "hasType"
    val RETURN_TYPE_PROPERTY = NAMESPACE property "hasReturnType"
    val VARIABLE_PROPERTY = NAMESPACE property "hasVariable"
    val FIELD_PROPERTY = NAMESPACE property "hasField"
    val CELL_PROPERTY = NAMESPACE property "AccessTo"
    val EXPRESSION_PROPERTY = NAMESPACE property "hasSubExpression"
    val CONDITION_PROPERTY = NAMESPACE property "hasCondition"
    val FOR_INIT_PROPERTY = NAMESPACE property "hasForInit"
    val FOR_UPDATE_PROPERTY = NAMESPACE property "hasForUpdate"
    val INITIALIZER_PROPERTY = NAMESPACE property "hasInitializer"
    val LEFT_HAND_SIDE_PROPERTY = NAMESPACE property "hasLeftHandSide"
    val RETURNED_EXPRESSION_PROPERTY = NAMESPACE property "hasReturnedExpression"
    val TARGET_PROPERTY = NAMESPACE property "hasTarget"
    val SUBPROJECT_PROPERTY = NAMESPACE property "hasSubProject"
    val STATEMENT_PROPERTY = NAMESPACE property "hasSubStatement"
    val BODY_PROPERTY = NAMESPACE property "hasBody"
    val ELSE_PROPERTY = NAMESPACE property "hasElseBranch"
    val SWITCH_LABEL_PROPERTY = NAMESPACE property "hasSwitchLabel"
    val THEN_PROPERTY = NAMESPACE property "hasThenBranch"
    val INVOKES_PROPERTY = NAMESPACE property "invokes"
    val ARRAY_OF_PROPERTY = NAMESPACE property "isArrayOf"
    val PROJECT_PROPERTY = NAMESPACE property "hasProject"
    val DECLARED_BY_PROPERTY = NAMESPACE property "isDeclaredBy"
    val NEXT_PROPERTY = NAMESPACE property "hasNextStatement"
    val POINTS_TO_PROPERTY = NAMESPACE property "pointsTo"
    val REFERENCES_PROPERTY = NAMESPACE property "references"
    val ALIASES_PROPERTY = NAMESPACE property "aliases"
    val RETURNS_PROPERTY = NAMESPACE property "returns"
    val IMPLEMENTS_PROPERTY = NAMESPACE property "implements"
    val HAS_DOC_PROPERTY = NAMESPACE property "hasDoc"

    // Data properties
    val RDFS_LABEL_PROPERTY = RDFS property "label"
    val COMMENT_PROPERTY = RDFS property "comment"

    val BUILD_FILE_PROPERTY = NAMESPACE property "hasBuildFile"
    val DIMENSIONS_PROPERTY = NAMESPACE property "hasDimensions"
    val END_LINE_PROPERTY = NAMESPACE property "hasEndLine"
    val NAME_PROPERTY = NAMESPACE property "hasName"
    val VAR_ARGS_PROPERTY = NAMESPACE property "isVarArgs"
    val LABEL_LITERAL_PROPERTY = NAMESPACE property "hasLabel"
    val LINE_PROPERTY = NAMESPACE property "hasLine"
    val POSITION_PROPERTY = NAMESPACE property "hasPosition"
    val SOURCE_CODE_PROPERTY = NAMESPACE property "hasSourceCode"
    val TARGETED_LABEL_PROPERTY = NAMESPACE property "hasTargetedLabel"

    // Individuals
    val AUTO_INDIVIDUAL = NAMESPACE resource "AutoModifier"
    val EXTERN_INDIVIDUAL = NAMESPACE resource "ExternModifier"
    val REGISTER_INDIVIDUAL = NAMESPACE resource "RegisterModifier"
    val STATIC_INDIVIDUAL = NAMESPACE resource "StaticModifier"

    val CONST_INDIVIDUAL = NAMESPACE resource "Const"
    val VOLATILE_INDIVIDUAL = NAMESPACE resource "Volatile"

    val VOID_INDIVIDUAL = NAMESPACE resource "Void"

    val CHAR_INDIVIDUAL = NAMESPACE resource "Char"
    val SIGNED_CHAR_INDIVIDUAL = NAMESPACE resource "SignedChar"
    val UNSIGNED_CHAR_INDIVIDUAL = NAMESPACE resource "UnsignedChar"
    val SHORT_INDIVIDUAL = NAMESPACE resource "Short"
    val UNSIGNED_SHORT_INDIVIDUAL = NAMESPACE resource "UnsignedShort"
    val INT_INDIVIDUAL = NAMESPACE resource "Int"
    val UNSIGNED_INT_INDIVIDUAL = NAMESPACE resource "UnsignedInt"
    val LONG_INDIVIDUAL = NAMESPACE resource "Long"
    val UNSIGNED_LONG_INDIVIDUAL = NAMESPACE resource "UnsignedLong"

    val DOUBLE_INDIVIDUAL = NAMESPACE resource "Double"
    val LONG_DOUBLE_INDIVIDUAL = NAMESPACE resource "LongDouble"
    val FLOAT_INDIVIDUAL = NAMESPACE resource "Float"
}
