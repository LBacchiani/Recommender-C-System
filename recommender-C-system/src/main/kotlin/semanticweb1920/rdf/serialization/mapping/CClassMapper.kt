package semanticweb1920.rdf.serialization.mapping

import semanticweb1920.rdf.COntology
import org.apache.jena.rdf.model.Resource
import org.eclipse.cdt.core.dom.ast.*

/**
 * Mapping function from Eclipse AST classes to ontology entity classes
 */
fun IASTNode.toOntologyEntity(): Resource = when {
    // non exclusive cases must be evaluated before others, to prevent problems of overmatching
    this is IASTExpression && this.parent is IASTFunctionCallExpression -> COntology.ACTUAL_ARGUMENT_ENTITY
    this is IASTBinaryExpression && this.operator == IASTBinaryExpression.op_assign -> COntology.ASSIGNMENT_EXPRESSION_ENTITY
    this is IASTUnaryExpression && this.operator == IASTUnaryExpression.op_amper -> COntology.REFERENCING_EXPRESSION_ENTITY
    this is IASTUnaryExpression && this.operator == IASTUnaryExpression.op_star -> COntology.DEREFERENCING_EXPRESSION_ENTITY
    this is IASTFieldReference && this.isPointerDereference -> COntology.DEREFERENCING_EXPRESSION_ENTITY

    // those below are exclusive with each other
    this is IASTPreprocessorIncludeStatement -> COntology.INCLUDE_DIRECTIVE_ENTITY
    this is IASTPreprocessorMacroDefinition -> COntology.DEFINE_DIRECTIVE_ENTITY
    this is IASTSimpleDeclaration && this.declarators.singleOrNull() is IASTFunctionDeclarator -> COntology.FUNCTION_DECLARATION_ENTITY
    this is IASTSimpleDeclaration && this.declSpecifier.isTypedef() -> COntology.TYPE_ALIAS_DECLARATION_ENTITY
    this is IASTFunctionDefinition -> COntology.FUNCTION_ENTITY
    this is IASTParameterDeclaration -> COntology.PARAMETER_ENTITY
    this is IASTCompoundStatement -> COntology.BLOCK_ENTITY
    this is IASTReturnStatement -> COntology.RETURN_ENTITY
    this is IASTDeclarationStatement -> COntology.VARIABLE_DECLARATION_ENTITY
    this is IASTExpressionStatement -> COntology.EXPRESSION_STATEMENT_ENTITY
    this is IASTCastExpression -> COntology.CAST_EXPRESSION_ENTITY
    this is IASTFunctionCallExpression -> COntology.FUNCTION_INVOCATION_EXPRESSION_ENTITY
    this is IASTConditionalExpression -> COntology.IF_THEN_ELSE_ENTITY
    this is IASTIfStatement -> COntology.IF_THEN_ELSE_ENTITY
    this is IASTWhileStatement -> COntology.WHILE_ENTITY
    this is IASTDoStatement -> COntology.DO_WHILE_ENTITY
    this is IASTForStatement -> COntology.FOR_ENTITY
    this is IASTCompositeTypeSpecifier && this.key == IASTCompositeTypeSpecifier.k_struct -> COntology.STRUCT_TYPE_DECLARATION_ENTITY
    this is IASTCompositeTypeSpecifier && this.key == IASTCompositeTypeSpecifier.k_union -> COntology.UNION_TYPE_DECLARATION_ENTITY
    this is IASTEnumerationSpecifier -> COntology.ENUM_TYPE_DECLARATION_ENTITY
    this is IASTNamedTypeSpecifier -> COntology.TYPE_ENTITY
    this is IASTElaboratedTypeSpecifier && this.kind == IASTElaboratedTypeSpecifier.k_enum -> COntology.ENUM_ENTITY
    this is IASTElaboratedTypeSpecifier && this.kind == IASTElaboratedTypeSpecifier.k_struct -> COntology.STRUCT_ENTITY
    this is IASTElaboratedTypeSpecifier && this.kind == IASTElaboratedTypeSpecifier.k_union -> COntology.UNION_ENTITY
    this is IASTArrayDeclarator -> COntology.ARRAY_ENTITY
    this is IASTEnumerationSpecifier.IASTEnumerator -> COntology.PRIMITIVE_ENTITY
    this is IASTForStatement -> COntology.FOR_ENTITY
    this is IASTSwitchStatement -> COntology.SWITCH_ENTITY
    this is IASTCaseStatement -> COntology.CASE_ENTITY
    this is IASTDefaultStatement -> COntology.DEFAULT_ENTITY
    this is IASTBreakStatement -> COntology.BREAK_ENTITY
    this is IASTContinueStatement -> COntology.CONTINUE_ENTITY
    this is IASTGotoStatement -> COntology.GOTO_ENTITY
    this is IASTLabelStatement -> COntology.STATEMENT_ENTITY

    this is IASTBinaryExpression -> COntology.EXPRESSION_ENTITY
    this is IASTUnaryExpression -> COntology.EXPRESSION_ENTITY
    this is IASTFieldReference -> COntology.EXPRESSION_ENTITY
    this is IASTArraySubscriptExpression -> COntology.EXPRESSION_ENTITY
    this is IASTTypeIdExpression -> COntology.EXPRESSION_ENTITY

    else -> throw IllegalArgumentException("No class mapping for $this: ${this.rawSignature}")
}
