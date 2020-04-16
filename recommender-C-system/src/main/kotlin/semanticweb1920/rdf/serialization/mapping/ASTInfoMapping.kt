package semanticweb1920.rdf.serialization.mapping

import semanticweb1920.parser.c.model.CRootASTNode
import semanticweb1920.rdf.COntology
import semanticweb1920.rdf.serialization.SerializationUtils.CREATED_RESOURCES_NAMESPACE
import semanticweb1920.rdf.serialization.composeName
import mu.KotlinLogging
import org.apache.jena.rdf.model.Model
import org.apache.jena.rdf.model.RDFNode
import org.apache.jena.rdf.model.Resource
import org.apache.jena.rdf.model.ResourceFactory.createTypedLiteral
import org.eclipse.cdt.core.dom.ast.*
import semanticweb1920.rdf.CEducationalOntology

private val logger = KotlinLogging.logger {}

/**
 * A singleton defining mappings for AST -> ontology triples transformation
 */
object ASTInfoMapping {

    val topics = mutableSetOf<String>()

    /**
     * A function implementing a mapping between the Eclipse AST classes and the Ontology classes
     */
    fun toRDF(pathMemory: StringBuilder, sourceAstNode: IASTNode, rdfModel: Model) {
        logger.trace { "${sourceAstNode.javaClass}: ${sourceAstNode.rawSignature}" }
        when {
            sourceAstNode is IASTTranslationUnit -> annotateTranslationUnit(pathMemory, CRootASTNode(sourceAstNode), rdfModel)

            sourceAstNode is IASTSimpleDeclaration && sourceAstNode.declarators.singleOrNull() is IASTFunctionDeclarator ->
                annotateFunctionDeclaration(pathMemory, sourceAstNode, rdfModel)

            sourceAstNode is IASTSimpleDeclaration &&
                    (sourceAstNode.declSpecifier.isTypedef() ||
                            sourceAstNode.declSpecifier is IASTCompositeTypeSpecifier ||
                            sourceAstNode.declSpecifier is IASTEnumerationSpecifier) ->
                annotateTypeDeclaration(pathMemory, sourceAstNode, rdfModel)

            sourceAstNode is IASTFunctionDefinition -> annotateFunctionDefinition(pathMemory, sourceAstNode, rdfModel)
            sourceAstNode is IASTDeclarationStatement -> annotateVariableDeclarationStatement(pathMemory, sourceAstNode, rdfModel)
            sourceAstNode is IASTReturnStatement -> annotateReturnStatement(pathMemory, sourceAstNode, rdfModel)
            sourceAstNode is IASTExpressionStatement -> annotateExpressionStatement(pathMemory, sourceAstNode, rdfModel)
            sourceAstNode is IASTForStatement -> annotateForStatement(pathMemory, sourceAstNode, rdfModel)
            sourceAstNode is IASTIfStatement -> annotateIfStatement(pathMemory, sourceAstNode, rdfModel)
            sourceAstNode is IASTSwitchStatement -> annotateSwitchStatement(pathMemory, sourceAstNode, rdfModel)
            sourceAstNode is IASTCaseStatement -> annotateSwitchSubStatement(pathMemory, sourceAstNode, rdfModel)
            sourceAstNode is IASTDefaultStatement -> annotateSwitchSubStatement(pathMemory, sourceAstNode, rdfModel)
            sourceAstNode is IASTBreakStatement -> annotateControlFlowStatement(pathMemory, sourceAstNode, rdfModel)
            sourceAstNode is IASTContinueStatement -> annotateControlFlowStatement(pathMemory, sourceAstNode, rdfModel)
            sourceAstNode is IASTDoStatement -> annotateDoStatement(pathMemory, sourceAstNode, rdfModel)
            sourceAstNode is IASTWhileStatement -> annotateWhileStatement(pathMemory, sourceAstNode, rdfModel)
            sourceAstNode is IASTGotoStatement -> annotateGotoStatement(pathMemory, sourceAstNode, rdfModel)
            sourceAstNode is IASTLabelStatement -> annotateLabelStatement(pathMemory, sourceAstNode, rdfModel)
        }
    }

    /**
     * Translation unit mapping function
     *
     * It updates pathMemory with current translationUnit identifier
     */
    private fun annotateTranslationUnit(pathMemory: StringBuilder, astRoot: CRootASTNode, rdfModel: Model) {
        pathMemory.append(composeName("file", uid = astRoot.translationUnit.filePath.hashCode().toString()) + "/")

        val currentFileResource = rdfModel.createResource(
                pathMemory.substring(0 until pathMemory.length - 1), // remove the final slash
                COntology.PROJECT_ENTITY)

        // Include Directive extraction
        if(astRoot.includeDirectives.isNotEmpty()) topics.add(CEducationalOntology.INCLUDE_DIRECTIVE.localName)
        astRoot.includeDirectives.forEach { include ->
            val includeResource = with(include) { toResource(pathMemory.toString(), rdfModel, resourceName(typeName(3))) }

            val includeLibraryRes = rdfModel.createResource(
                    CREATED_RESOURCES_NAMESPACE + composeName("library", uid = include.name.rawSignature),
                    COntology.LIBRARY_ENTITY)

            annotateCommonInfo(include, includeResource, rdfModel)

            with(rdfModel) {
                add(createStatement(currentFileResource, COntology.DEPENDENCY_PROPERTY, includeLibraryRes))
                add(createStatement(includeLibraryRes, COntology.NAME_PROPERTY, include.name.rawSignature))
                add(createStatement(includeResource, COntology.REFERENCES_PROPERTY, includeLibraryRes))
                add(includeResource tagWithSourceCodeOf include)
            }
        }

        // Macro extraction
        if(astRoot.macroDefinitions.isNotEmpty()) topics.add(CEducationalOntology.DEFINE_DIRECTIVE.localName)
        astRoot.macroDefinitions.forEach { macro ->
            val macroResource = with(macro) { toResource(pathMemory.toString(), rdfModel, resourceName(typeName(3))) }

            annotateCommonInfo(macro, macroResource, rdfModel)

            with(rdfModel) { add(macroResource tagWithSourceCodeOf macro) }
        }
    }

    /**
     * Mapping for custom types declarations
     */
    private fun annotateTypeDeclaration(pathMemory: StringBuilder, astNode: IASTSimpleDeclaration, rdfModel: Model) {
        val declaratorSpecifier = astNode.declSpecifier
        val declarator = astNode.declarators.singleOrNull()
        val declaredTypeRes = when (declaratorSpecifier) {
            is IASTCompositeTypeSpecifier, is IASTEnumerationSpecifier -> {

                val (typeDeclarationName, typeDeclarationTypeRes) = when {
                    (declaratorSpecifier as? IASTCompositeTypeSpecifier)?.key == IASTCompositeTypeSpecifier.k_union ->
                        Pair("UnionTypeDeclaration", COntology.UNION_ENTITY)
                    (declaratorSpecifier as? IASTCompositeTypeSpecifier)?.key == IASTCompositeTypeSpecifier.k_struct ->
                        Pair("StructTypeDeclaration", COntology.STRUCT_ENTITY)
                    declaratorSpecifier is IASTEnumerationSpecifier ->
                        Pair("EnumTypeDeclaration", COntology.ENUM_ENTITY)
                    else ->
                        Pair("GenericTypeDeclaration", COntology.TYPE_ENTITY).also {
                            logger.error { "Unmapped composite type declaration ${astNode.javaClass}: ${astNode.rawSignature} - defaulting to $it" }
                        }
                }

                // speicific sxtraction steps for union and struct

                // specific extraction steps for enum
                when {
                    (declaratorSpecifier as? IASTCompositeTypeSpecifier)?.key == IASTCompositeTypeSpecifier.k_union -> {
                        topics.add(CEducationalOntology.UNION.localName)
                    }
                    (declaratorSpecifier as? IASTCompositeTypeSpecifier)?.key == IASTCompositeTypeSpecifier.k_struct -> {
                        topics.add(CEducationalOntology.STRUCT.localName)
                    }
                    declaratorSpecifier is IASTEnumerationSpecifier -> {
                        topics.add(CEducationalOntology.ENUM.localName)
                    }

                    // common extraction steps for struct, enum and union types
                }

                // common extraction steps for struct, enum and union types
                val typeDeclarationStmtRes = with(declaratorSpecifier) { toResource(pathMemory.toString(), rdfModel, resourceName(typeDeclarationName)) }
                annotateCommonInfo(declaratorSpecifier, typeDeclarationStmtRes, rdfModel)

                val typeName = with(declaratorSpecifier) {
                    (this as? IASTCompositeTypeSpecifier)?.name
                            ?: (this as? IASTEnumerationSpecifier)?.name
                }
                val compositeTypeRes = with(declaratorSpecifier) {
                    toResource(pathMemory.toString(), rdfModel, resourceName("ElaboratedTypeSpecifier", typeName.toString()), typeDeclarationTypeRes)
                }

                with(rdfModel) {
                    add(typeDeclarationStmtRes tagWithSourceCodeOf declaratorSpecifier)
                    add(createStatement(compositeTypeRes, COntology.DECLARED_BY_PROPERTY, typeDeclarationStmtRes))
                    add(createStatement(compositeTypeRes, COntology.NAME_PROPERTY, typeName.toString()))
                }

                when (declaratorSpecifier) {
                    // speicific sxtraction steps for union and struct
                    is IASTCompositeTypeSpecifier -> declaratorSpecifier.members.forEach { fieldDeclaration ->
                        when (fieldDeclaration) {
                            is IASTSimpleDeclaration -> {
                                val declaredFieldRes = with(fieldDeclaration.declarators.single()) {
                                    toResource(pathMemory.toString(), rdfModel, resourceName("Field"), COntology.FIELD_ENTITY)
                                }
                                annotateVariableLikeDeclaration(pathMemory, fieldDeclaration, declaredFieldRes, rdfModel)

                                with(rdfModel) {
                                    add(declaredFieldRes tagWithSourceCodeOf fieldDeclaration)
                                    add(createStatement(compositeTypeRes, COntology.FIELD_PROPERTY, declaredFieldRes))
                                }
                            }
                            else -> logger.warn { "No mapping provided for ${fieldDeclaration.javaClass}: ${fieldDeclaration.rawSignature}" }
                        }
                    }

                    // specific extraction steps for enum
                    is IASTEnumerationSpecifier ->
                        declaratorSpecifier.enumerators.forEach { enumValue ->
                            val enumValueRes = enumValue.toResource(pathMemory.toString(), rdfModel)
                            with(rdfModel) {
                                add(enumValueRes tagWithSourceCodeOf enumValue)
                                add(createStatement(enumValueRes, COntology.NAME_PROPERTY, enumValue.name.rawSignature))
                                add(createStatement(enumValueRes, COntology.DECLARED_BY_PROPERTY, typeDeclarationStmtRes))
                            }
                        }
                }

                compositeTypeRes
            }
            else -> extractTypeResource(pathMemory, declaratorSpecifier, declarator, rdfModel)
        }

        if (declaratorSpecifier.isTypedef()) {
            val typeDeclarationStmtRes = with(astNode) { toResource(pathMemory.toString(), rdfModel, resourceName("TypeAliasDeclaration")) }
            annotateCommonInfo(astNode, typeDeclarationStmtRes, rdfModel)

            val aliasName = declarator!!.declaredName()
            val typeAliasRes = with(declarator) {
                toResource(pathMemory.toString(), rdfModel, resourceName("TypedefNameSpecifier", aliasName), COntology.TYPE_ENTITY)
            }

            with(rdfModel) {
                add(typeDeclarationStmtRes tagWithSourceCodeOf astNode)
                add(createStatement(typeAliasRes, COntology.DECLARED_BY_PROPERTY, typeDeclarationStmtRes))
                add(createStatement(typeAliasRes, COntology.ALIASES_PROPERTY, declaredTypeRes))
                add(createStatement(typeAliasRes, COntology.NAME_PROPERTY, aliasName))
            }
        }
    }

    /**
     * Mapping for function declarations
     */
    private fun annotateFunctionDeclaration(pathMemory: StringBuilder, astNode: IASTSimpleDeclaration, rdfModel: Model): Resource {
        // Is assumed that function declarator is only the first
        val funDeclarator = astNode.declarators.single()
        val customFunctionResource = astNode.toResource(pathMemory.toString(), rdfModel, funDeclarator.resourceName())
        return extractFunction(pathMemory, astNode, astNode.declSpecifier, funDeclarator, rdfModel, customFunctionResource)
    }

    /**
     * Mapping for function definition
     */
    private fun annotateFunctionDefinition(pathMemory: StringBuilder, astNode: IASTFunctionDefinition, rdfModel: Model) {
        val functionResource = extractFunction(pathMemory, astNode, astNode.declSpecifier, astNode.declarator, rdfModel)
        // "scope" field information is ignored, maybe will be useful in future updates

        val functionBodyRes = extractBodyStatement(pathMemory, astNode.body, rdfModel)
        topics.add(CEducationalOntology.FUNCTION.localName)
        with(rdfModel) { add(createStatement(functionResource, COntology.BODY_PROPERTY, functionBodyRes)) }
    }

    /**
     * Generic mapping for body statements that could be compound or not; if they are, sub-statements are annotated to be sub-parts
     */
    private fun extractBodyStatement(pathMemory: StringBuilder, astNode: IASTStatement, rdfModel: Model) =
            astNode.toResource(pathMemory.toString(), rdfModel)
                    .also { if (astNode is IASTCompoundStatement) annotateCompoundStatement(pathMemory, astNode, rdfModel) }

    /**
     * Generic mapping for functions
     */
    private fun extractFunction(pathMemory: StringBuilder,
                                functionAstNode: IASTDeclaration,
                                declaratorSpecifier: IASTDeclSpecifier,
                                declarator: IASTDeclarator,
                                rdfModel: Model,
                                functionResource: Resource = functionAstNode.toResource(pathMemory.toString(), rdfModel)
    ): Resource {
        annotateCommonInfo(functionAstNode, functionResource, rdfModel)

        val returnTypeResource = extractTypeResource(pathMemory, declaratorSpecifier, declarator, rdfModel)

        annotateModifiers(declaratorSpecifier, functionResource, rdfModel)

        with(rdfModel) {
            add(createStatement(functionResource, COntology.RETURN_TYPE_PROPERTY, returnTypeResource))
            add(functionResource tagWithNameOf declarator)
            add(functionResource tagWithSourceCodeOf functionAstNode)

            val parametersDeclarations = declarator.children.filterIsInstance<IASTParameterDeclaration>()
            parametersDeclarations.map { param -> extractFunctionParameter(pathMemory, param, rdfModel, functionResource) }
                    .forEach { param -> add(createStatement(functionResource, COntology.PARAMETER_PROPERTY, param)) }
        }
        return functionResource
    }

    /**
     * Mapping for modifiers (storage class and type qualifiers)
     */
    private fun annotateModifiers(declaratorSpecifier: IASTDeclSpecifier, toTagResource: Resource, rdfModel: Model) =
            extractModifierResources(declaratorSpecifier)
                    .forEach { with(rdfModel) { add(createStatement(toTagResource, COntology.MODIFIER_PROPERTY, it)) } }

    /**
     * Mapping for function parameters declaration
     */
    private fun extractFunctionParameter(
            pathMemory: StringBuilder,
            astNode: IASTParameterDeclaration,
            rdfModel: Model,
            declaredBy: Resource
    ): Resource {
        val paramDeclarationRes = astNode.toResource(pathMemory.toString(), rdfModel)
        val parameterTypeRes = extractTypeResource(pathMemory, astNode.declSpecifier, astNode.declarator, rdfModel)

        with(rdfModel) {
            add(createStatement(paramDeclarationRes, COntology.DECLARED_BY_PROPERTY, declaredBy))
            add(createStatement(paramDeclarationRes, COntology.TYPE_PROPERTY, parameterTypeRes))
            add(paramDeclarationRes tagWithNameOf astNode.declarator)
            add(paramDeclarationRes tagWithSourceCodeOf astNode)
        }
        return paramDeclarationRes
    }

    /**
     * Mapping for a compound statement
     */
    private fun annotateCompoundStatement(pathMemory: StringBuilder, compoundStatement: IASTCompoundStatement, rdfModel: Model) {
        val compoundStatementRes = compoundStatement.toResource(pathMemory.toString(), rdfModel)
        annotateCommonInfo(compoundStatement, compoundStatementRes, rdfModel)

        // scope field not used for now
        compoundStatement.statements.forEach {
            val statementRes = it.toResource(pathMemory.toString(), rdfModel)
            annotateCommonInfo(it, statementRes, rdfModel)

            with(rdfModel) { add(createStatement(compoundStatementRes, COntology.STATEMENT_PROPERTY, statementRes)) }
        }
    }

    /**
     * Mapping for an expression statement
     */
    private fun annotateExpressionStatement(pathMemory: StringBuilder, astNode: IASTExpressionStatement, rdfModel: Model) {
        val expressionStmtRes = astNode.toResource(pathMemory.toString(), rdfModel)
        annotateCommonInfo(astNode, expressionStmtRes, rdfModel)

        val expressionRes = extractExpression(pathMemory, astNode.expression, rdfModel)

        with(rdfModel) {
            add(createStatement(expressionStmtRes, COntology.EXPRESSION_PROPERTY, expressionRes))
            add(expressionStmtRes tagWithSourceCodeOf astNode)
        }
    }

    /**
     * Mapping for a return statement
     */
    private fun annotateReturnStatement(pathMemory: StringBuilder, astNode: IASTReturnStatement, rdfModel: Model) {
        val returnStmtRes = astNode.toResource(pathMemory.toString(), rdfModel)
        annotateCommonInfo(astNode, returnStmtRes, rdfModel)

        val returnedExpressionRes = extractExpression(pathMemory, astNode.returnValue, rdfModel)

        topics.add(CEducationalOntology.RETURN.localName)

        with(rdfModel) {
            add(createStatement(returnStmtRes, COntology.RETURNED_EXPRESSION_PROPERTY, returnedExpressionRes))
            add(returnStmtRes tagWithSourceCodeOf astNode)
        }
    }

    /**
     * Mapping for a for statement
     */
    private fun annotateForStatement(pathMemory: StringBuilder, astNode: IASTForStatement, rdfModel: Model) {
        val forStmtRes = astNode.toResource(pathMemory.toString(), rdfModel)
        annotateCommonInfo(astNode, forStmtRes, rdfModel)

        val forBodyRes = extractBodyStatement(pathMemory, astNode.body, rdfModel)

        val forInitializerStatementRes = astNode.initializerStatement?.run { toResource(pathMemory.toString(), rdfModel) }
        val forConditionExpressionRes = astNode.conditionExpression?.let { extractExpression(pathMemory, it, rdfModel) }
        val forIterationExpressionRes = astNode.iterationExpression?.let { extractExpression(pathMemory, it, rdfModel) }
        topics.add(CEducationalOntology.FOR_STATEMENT.localName)
        with(rdfModel) {
            add(createStatement(forStmtRes, COntology.BODY_PROPERTY, forBodyRes))
            forInitializerStatementRes?.let { add(createStatement(forStmtRes, COntology.FOR_INIT_PROPERTY, it)) }
            forConditionExpressionRes?.let { add(createStatement(forStmtRes, COntology.CONDITION_PROPERTY, it)) }
            forIterationExpressionRes?.let { add(createStatement(forStmtRes, COntology.FOR_UPDATE_PROPERTY, it)) }
            add(forStmtRes tagWithSourceCodeOf astNode)
        }
    }

    /**
     * Mapping for an if statement
     */
    private fun annotateIfStatement(pathMemory: StringBuilder, astNode: IASTIfStatement, rdfModel: Model) {
        val ifStmtRes = astNode.toResource(pathMemory.toString(), rdfModel)
        annotateCommonInfo(astNode, ifStmtRes, rdfModel)

        val conditionExpressionRes = extractExpression(pathMemory, astNode.conditionExpression, rdfModel)
        val thenClauseRes = extractBodyStatement(pathMemory, astNode.thenClause, rdfModel)
        val elseClauseRes = astNode.elseClause?.let { extractBodyStatement(pathMemory, it, rdfModel) }

        topics.add(CEducationalOntology.IF_THEN_ELSE.localName)

        with(rdfModel) {
            add(createStatement(ifStmtRes, COntology.CONDITION_PROPERTY, conditionExpressionRes))
            add(createStatement(ifStmtRes, COntology.THEN_PROPERTY, thenClauseRes))
            elseClauseRes?.let { add(createStatement(ifStmtRes, COntology.ELSE_PROPERTY, it)) }
            add(ifStmtRes tagWithSourceCodeOf astNode)
        }
    }

    /**
     * Mapping for a switch statement
     */
    private fun annotateSwitchStatement(pathMemory: StringBuilder, astNode: IASTSwitchStatement, rdfModel: Model) {
        val switchStmtRes = astNode.toResource(pathMemory.toString(), rdfModel)
        annotateCommonInfo(astNode, switchStmtRes, rdfModel)

        val controllerExprRes = extractExpression(pathMemory, astNode.controllerExpression, rdfModel)

        topics.add(CEducationalOntology.SWITCH.localName)

        with(rdfModel) {
            add(createStatement(switchStmtRes, COntology.EXPRESSION_PROPERTY, controllerExprRes))
            add(switchStmtRes tagWithSourceCodeOf astNode)

            // supposing that all direct sub-statements of a switch statement can be only labeled blocks or a default block
            astNode.body.children.map { it.toResource(pathMemory.toString(), rdfModel) }
                    .forEach { add(createStatement(switchStmtRes, COntology.SWITCH_LABEL_PROPERTY, it)) }
        }
    }

    /**
     * Mapping function for a switch sub-statement (namely case or default statements)
     */
    private fun annotateSwitchSubStatement(pathMemory: StringBuilder, astNode: IASTStatement, rdfModel: Model) {
        val switchSubStmtRes = astNode.toResource(pathMemory.toString(), rdfModel)
        annotateCommonInfo(astNode, switchSubStmtRes, rdfModel)

        // supposing that a case or default block has always none or single sub-statement
        val switchSubStatementBody = astNode.children.mapNotNull { it as? IASTStatement }.firstOrNull()
        val subStatementBodyRes = switchSubStatementBody?.let { extractBodyStatement(pathMemory, it, rdfModel) }

        with(rdfModel) {
            add(switchSubStmtRes tagWithSourceCodeOf astNode)
            subStatementBodyRes?.let { add(createStatement(switchSubStmtRes, COntology.BODY_PROPERTY, it)) }
            if (astNode is IASTCaseStatement) {
                val caseExprRes = extractExpression(pathMemory, astNode.expression, rdfModel)
                add(createStatement(switchSubStmtRes, COntology.EXPRESSION_PROPERTY, caseExprRes))
            }
        }
    }

    /**
     * Mapping for the break and continue statements
     */
    private fun annotateControlFlowStatement(pathMemory: StringBuilder, astNode: IASTStatement, rdfModel: Model) {
        val controlFlowStmtRes = astNode.toResource(pathMemory.toString(), rdfModel)
        if(controlFlowStmtRes.localName.contains("Continue")) {
            topics.add(CEducationalOntology.CONTINUE.localName)
        } else {
            topics.add(CEducationalOntology.BREAK.localName)
        }
        annotateCommonInfo(astNode, controlFlowStmtRes, rdfModel)
        with(rdfModel) { add(controlFlowStmtRes tagWithSourceCodeOf astNode) }
    }

    /**
     * Mapping for label statement
     */
    private fun annotateLabelStatement(pathMemory: StringBuilder, astNode: IASTLabelStatement, rdfModel: Model) {
        val labelStmtRes = astNode.toResource(pathMemory.toString(), rdfModel)
        annotateCommonInfo(astNode, labelStmtRes, rdfModel)
        with(rdfModel) {
            add(labelStmtRes tagWithSourceCodeOf astNode)
            add(labelStmtRes, COntology.NAME_PROPERTY, astNode.name.rawSignature)
        }
    }

    /**
     * Mapping for goto statement
     */
    private fun annotateGotoStatement(pathMemory: StringBuilder, astNode: IASTGotoStatement, rdfModel: Model) {
        val gotoStmtRes = astNode.toResource(pathMemory.toString(), rdfModel)
        annotateCommonInfo(astNode, gotoStmtRes, rdfModel)
        topics.add(CEducationalOntology.GOTO.localName)
        with(rdfModel) { add(gotoStmtRes tagWithSourceCodeOf astNode) }
    }


    /**
     * Mapping for do statements
     */
    private fun annotateDoStatement(pathMemory: StringBuilder, astNode: IASTDoStatement, rdfModel: Model) {
        val doStmtRes = astNode.toResource(pathMemory.toString(), rdfModel)
        annotateCommonInfo(astNode, doStmtRes, rdfModel)

        val doBodyRes = extractBodyStatement(pathMemory, astNode.body, rdfModel)
        val doConditionExprRes = extractExpression(pathMemory, astNode.condition, rdfModel)
        topics.add(CEducationalOntology.DO_STATEMENT.localName)
        with(rdfModel) {
            add(doStmtRes tagWithSourceCodeOf astNode)
            add(createStatement(doStmtRes, COntology.BODY_PROPERTY, doBodyRes))
            add(createStatement(doStmtRes, COntology.CONDITION_PROPERTY, doConditionExprRes))
        }
    }

    /**
     * Mapping for while statements
     */
    private fun annotateWhileStatement(pathMemory: StringBuilder, astNode: IASTWhileStatement, rdfModel: Model) {
        val whileStmtRes = astNode.toResource(pathMemory.toString(), rdfModel)
        annotateCommonInfo(astNode, whileStmtRes, rdfModel)

        val whileBodyRes = astNode.body?.let { extractBodyStatement(pathMemory, it, rdfModel) }
        val whileConditionExprRes = extractExpression(pathMemory, astNode.condition, rdfModel)
        topics.add(CEducationalOntology.WHILE_STATEMENT.localName)
        with(rdfModel) {
            add(whileStmtRes tagWithSourceCodeOf astNode)
            whileBodyRes?.let { add(createStatement(whileStmtRes, COntology.BODY_PROPERTY, it)) }
            add(createStatement(whileStmtRes, COntology.CONDITION_PROPERTY, whileConditionExprRes))
        }
    }

    /**
     * Mapping for a variable declaration statement
     */
    private fun annotateVariableDeclarationStatement(pathMemory: StringBuilder, astNode: IASTDeclarationStatement, rdfModel: Model) {
        val declarationStmtRes = astNode.toResource(pathMemory.toString(), rdfModel)
        annotateCommonInfo(astNode, declarationStmtRes, rdfModel)

        when (val astDeclaration = astNode.declaration) {
            is IASTSimpleDeclaration -> {
                astDeclaration.declarators.forEachIndexed { declaratorIndex, declarator ->
                    val declaredRes = with(declarator) {
                        toResource(pathMemory.toString(), rdfModel, resourceName("LocalVariable"), COntology.LOCAL_VARIABLE_ENTITY)
                    }

                    annotateVariableLikeDeclaration(pathMemory, astDeclaration, declaredRes, rdfModel, declaratorIndex)

                    with(rdfModel) {
                        add(createStatement(declarationStmtRes, COntology.VARIABLE_DECLARATION_PROPERTY, declaredRes))
                        add(declarationStmtRes tagWithSourceCodeOf astNode)
                    }
                }
            }
            else -> logger.warn { "No mapping provided for ${astDeclaration.javaClass}: ${astDeclaration.rawSignature}" }
        }
    }

    /**
     * Extracts and annotates a variable-declaration like statement; it can be a local variable declaration or a field declaration in structured type
     *
     * @param declaratorIndex Specifies which declarator is being annotated in multiple variable declarations
     */
    private fun annotateVariableLikeDeclaration(
            pathMemory: StringBuilder,
            astDeclaration: IASTSimpleDeclaration,
            declaredRes: Resource,
            rdfModel: Model,
            declaratorIndex: Int = 0
    ) {
        val declaratorSpecifier = astDeclaration.declSpecifier
        val declarator = astDeclaration.declarators[declaratorIndex]

        val declarationType = extractTypeResource(pathMemory, declaratorSpecifier, declarator, rdfModel)
        annotateModifiers(declaratorSpecifier, declaredRes, rdfModel)

        with(rdfModel) {
            add(createStatement(declaredRes, COntology.TYPE_PROPERTY, declarationType))
            add(declaredRes tagWithNameOf declarator)

            // if localVariableRes is initialized in place, add initialization expression
            ((declarator.initializer as? IASTEqualsInitializer)?.initializerClause as? IASTExpression)?.let { initExpr ->
                add(createStatement(declaredRes, COntology.INITIALIZER_PROPERTY, extractExpression(pathMemory, initExpr, rdfModel)))
            }
        }
    }

    /**
     * Extracts expression resource
     */
    private fun extractExpression(pathMemory: StringBuilder, expression: IASTExpression, rdfModel: Model): RDFNode = when (expression) {
        is IASTLiteralExpression -> createTypedLiteral(expression.rawSignature)
        is IASTIdExpression -> createTypedLiteral(expression.name.rawSignature)
        is IASTTypeIdInitializerExpression -> createTypedLiteral(expression.rawSignature)
        is IASTBinaryTypeIdExpression -> createTypedLiteral(expression.rawSignature)
        else -> expression.toResource(pathMemory.toString(), rdfModel)
    }.also { expressionRdfNode ->
        with(rdfModel) {
            (expressionRdfNode as? Resource)?.run {
                // this runs only if computed expression is a Resource, i.e. not a literal
                add((expressionRdfNode tagWithSourceCodeOf expression))

                if (expression is IASTBinaryExpression) {
                    val leftExprRes = extractExpression(pathMemory, expression.operand1, rdfModel)
                    val rightExprRes = extractExpression(pathMemory, expression.operand2, rdfModel)
                    add(createStatement(expressionRdfNode, COntology.EXPRESSION_PROPERTY, leftExprRes))
                    add(createStatement(expressionRdfNode, COntology.EXPRESSION_PROPERTY, rightExprRes))
                }
                if (expression is IASTUnaryExpression) {
                    if(expression.operator == IASTUnaryExpression.op_star) topics.add(CEducationalOntology.DEREFERENCE.localName)
                    if(expression.operator == IASTUnaryExpression.op_amper) topics.add(CEducationalOntology.REFERENCE.localName)
                    add(createStatement(expressionRdfNode, COntology.EXPRESSION_PROPERTY,
                            extractExpression(pathMemory, expression.operand, rdfModel)))
                }
                if (expression is IASTFunctionCallExpression) {
                    expression.arguments.mapNotNull { it as? IASTExpression }
                            .forEach { argument ->
                                add(createStatement(expressionRdfNode, COntology.ARGUMENT_PROPERTY,
                                        extractExpression(pathMemory, argument, rdfModel)))
                            }
                }
                if (expression is IASTConditionalExpression) {
                    val conditionExpr = extractExpression(pathMemory, expression.logicalConditionExpression, rdfModel)
                    val thenExpr = extractExpression(pathMemory, expression.positiveResultExpression, rdfModel)
                    val elseExpr = extractExpression(pathMemory, expression.negativeResultExpression, rdfModel)
                    add(createStatement(expressionRdfNode, COntology.CONDITION_PROPERTY, conditionExpr))
                    add(createStatement(expressionRdfNode, COntology.THEN_PROPERTY, thenExpr))
                    add(createStatement(expressionRdfNode, COntology.ELSE_PROPERTY, elseExpr))
                }
                if (expression is IASTTypeIdExpression) {
                    val referencedType = expression.typeId
                    val referencedTypeRes = extractTypeResource(pathMemory, referencedType.declSpecifier, referencedType.abstractDeclarator, rdfModel)
                    add(createStatement(expressionRdfNode, COntology.REFERENCES_PROPERTY, referencedTypeRes))
                }
                if (expression is IASTCastExpression) {
                    topics.add(CEducationalOntology.CAST.localName)
                    val castType = expression.typeId
                    val castTypeRes = extractTypeResource(pathMemory, castType.declSpecifier, castType.abstractDeclarator, rdfModel)
                    val castedExpr = extractExpression(pathMemory, expression.operand, rdfModel)
                    add(createStatement(expressionRdfNode, COntology.TYPE_PROPERTY, castTypeRes))
                    add(createStatement(expressionRdfNode, COntology.EXPRESSION_PROPERTY, castedExpr))
                }
                if (expression is IASTArraySubscriptExpression) {
                    add(createStatement(expressionRdfNode, COntology.EXPRESSION_PROPERTY,
                            extractExpression(pathMemory, expression.arrayExpression, rdfModel)))
                }
                if (expression is IASTFieldReference) {
                    if(expression.isPointerDereference) topics.add(CEducationalOntology.DEREFERENCE.localName)
                    add(createStatement(expressionRdfNode, COntology.EXPRESSION_PROPERTY,
                            extractExpression(pathMemory, expression.fieldOwner, rdfModel)))
                }
            }
        }
    }


    /**
     * Extracts complete type information and returns a corresponding resource;
     * if a pointer type is encountered, the pointer resource and related RDF statement are added
     */
    private fun extractTypeResource(
            pathMemory: StringBuilder,
            declaratorSpecifier: IASTDeclSpecifier,
            declarator: IASTDeclarator?,
            rdfModel: Model
    ): Resource {
        /**
         * Extracts partial type information from declarator specifier node
         */
        fun extractType(declSpecifier: IASTDeclSpecifier): Resource = when (declSpecifier) {
            is IASTSimpleDeclSpecifier -> {
                with(declSpecifier) {
                    when (type) {
                        IASTSimpleDeclSpecifier.t_char -> if (isUnsigned) COntology.UNSIGNED_CHAR_INDIVIDUAL else COntology.CHAR_INDIVIDUAL
                        IASTSimpleDeclSpecifier.t_double -> COntology.DOUBLE_INDIVIDUAL
                        IASTSimpleDeclSpecifier.t_int -> if (isUnsigned) COntology.UNSIGNED_INT_INDIVIDUAL else COntology.INT_INDIVIDUAL
                        IASTSimpleDeclSpecifier.t_float -> COntology.FLOAT_INDIVIDUAL
                        IASTSimpleDeclSpecifier.t_void -> COntology.VOID_INDIVIDUAL
                        else -> {
                            logger.error { "Not recognized type: ${declSpecifier.rawSignature} - defaulting to generic type" }
                            COntology.TYPE_ENTITY
                        }
                    }
                }
            }
            else -> {
                logger.error { "No type recognized, ${declSpecifier.javaClass}: ${declSpecifier.rawSignature} - defaulting to generic type" }
                COntology.TYPE_ENTITY
            }
        }

        // Extract plain type, then if it is a pointer to that type add that information
        val plainTypeResource: Resource = when (declaratorSpecifier) {
            is IASTNamedTypeSpecifier, is IASTElaboratedTypeSpecifier -> with(declaratorSpecifier) {

                val typeName = (this as? IASTNamedTypeSpecifier)?.name
                        ?: (this as? IASTElaboratedTypeSpecifier)?.name

                toResource(pathMemory.toString(), rdfModel, resourceName(uid = typeName.toString()))
                        .also { with(rdfModel) { add(createStatement(it, COntology.NAME_PROPERTY, typeName!!.toString())) } }
            }

            else -> extractType(declaratorSpecifier)
        }

        if(declarator?.hasPointerType() == true) topics.add(CEducationalOntology.POINTER.localName)
        if(declarator is IASTArrayDeclarator) topics.add(CEducationalOntology.ARRAY_TYPE.localName)

        val partialTypeResource = when {
            declarator?.hasPointerType() == true ->
                with(declaratorSpecifier) {
                    toResource(pathMemory.toString(), rdfModel, resourceName("pointer"), COntology.POINTER_ENTITY)
                }.also { with(rdfModel) { add(createStatement(it, COntology.POINTS_TO_PROPERTY, plainTypeResource)) } }
            else -> plainTypeResource
        }
        return when (declarator) {
            is IASTArrayDeclarator -> declarator.toResource(pathMemory.toString(), rdfModel).also {
                with(rdfModel) {
                    add(createStatement(it, COntology.ARRAY_OF_PROPERTY, partialTypeResource))
                    add(createStatement(it, COntology.DIMENSIONS_PROPERTY, createTypedLiteral(declarator.arrayModifiers.size)))
                }
            }
            else -> partialTypeResource
        }
    }

    /**
     * Extracts the present modifier list as resources
     */
    private fun extractModifierResources(declaratorSpecifier: IASTDeclSpecifier): List<Resource> {
        val modifiersList = mutableListOf<Resource>()
        with(declaratorSpecifier) {
            if (isConst) {
                modifiersList += COntology.CONST_INDIVIDUAL
                topics.add(CEducationalOntology.CONST.localName)
            }
            if (isVolatile) {
                modifiersList += COntology.VOLATILE_INDIVIDUAL
                topics.add(CEducationalOntology.VOLATILE.localName)
            }
            when (storageClass) {
                IASTDeclSpecifier.sc_auto -> {
                    modifiersList += COntology.AUTO_INDIVIDUAL
                    topics.add(CEducationalOntology.AUTO.localName)
                }
                IASTDeclSpecifier.sc_extern -> {
                    modifiersList += COntology.EXTERN_INDIVIDUAL
                    topics.add(CEducationalOntology.EXTERN.localName)
                }
                IASTDeclSpecifier.sc_static -> {
                    modifiersList += COntology.STATIC_INDIVIDUAL
                    topics.add(CEducationalOntology.STATIC.localName)

                }
                IASTDeclSpecifier.sc_register -> {
                    modifiersList += COntology.REGISTER_INDIVIDUAL
                    topics.add(CEducationalOntology.REGISTER.localName)
                }
                else -> {}
            }
        }
        return modifiersList
    }

    /**
     * Extracts common info like:
     *
     * - Instruction start line
     * - Instruction end line
     */
    private fun annotateCommonInfo(relatedAstNode: IASTNode, subjectResource: Resource, rdfModel: Model) {
        with(rdfModel) {
            add(subjectResource tagWithStartLineOf relatedAstNode)
            add(subjectResource tagWithEndLineOf relatedAstNode)
        }
    }
}
