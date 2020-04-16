package semanticweb1920.rdf.serialization.mapping

import semanticweb1920.rdf.COntology
import semanticweb1920.rdf.serialization.composeName
import org.apache.jena.rdf.model.Model
import org.apache.jena.rdf.model.Resource
import org.apache.jena.rdf.model.ResourceFactory.createStatement
import org.apache.jena.rdf.model.ResourceFactory.createTypedLiteral
import org.apache.jena.rdf.model.Statement
import org.eclipse.cdt.core.dom.ast.IASTDeclSpecifier
import org.eclipse.cdt.core.dom.ast.IASTDeclarator
import org.eclipse.cdt.core.dom.ast.IASTNode

/////////////////////////
// Shorthand functions //
/////////////////////////

internal fun IASTNode.startLine() = this.fileLocation.startingLineNumber
internal fun IASTNode.endLine() = this.fileLocation.endingLineNumber

internal fun IASTDeclarator.declaredName() = this.name.rawSignature
internal fun IASTDeclarator.hasPointerType() = this.pointerOperators.isNotEmpty()
internal fun IASTDeclSpecifier.isTypedef() = this.storageClass == IASTDeclSpecifier.sc_typedef

/** Extracts type name from Eclipse CDT class name; defaults eliminating first four letters */
internal fun IASTNode.typeName(start: Int = 4, end: Int = this.javaClass.simpleName.length) =
        this.javaClass.simpleName.substring(start, end)

/** Creates the resource name composing a name and a uid; defaults to type name and the internal node offset concatenated with length */
internal fun IASTNode.resourceName(name: String = this.typeName(), uid: String = "${this.fileLocation.nodeOffset}-${this.fileLocation.nodeLength}") =
        composeName(name, uid = uid)

/** Creates or gets the resource with this name and type in the provided model with provided prefixUri */
internal fun IASTNode.toResource(prefixUri: String, model: Model,
                                 name: String = this.resourceName(),
                                 type: Resource = this.toOntologyEntity()): Resource =
        model.createResource(prefixUri + name, type)

///////////////////////
// Tagging functions //
///////////////////////

internal infix fun Resource.tagWithStartLineOf(correspondingAstNode: IASTNode): Statement =
        createStatement(this, COntology.LINE_PROPERTY, createTypedLiteral(correspondingAstNode.startLine()))

internal infix fun Resource.tagWithEndLineOf(correspondingAstNode: IASTNode): Statement =
        createStatement(this, COntology.END_LINE_PROPERTY, createTypedLiteral(correspondingAstNode.endLine()))

internal infix fun Resource.tagWithSourceCodeOf(correspondingAstNode: IASTNode): Statement =
        createStatement(this, COntology.SOURCE_CODE_PROPERTY, createTypedLiteral(correspondingAstNode.rawSignature))

internal infix fun Resource.tagWithNameOf(correspondingAstNode: IASTDeclarator): Statement =
        createStatement(this, COntology.NAME_PROPERTY, createTypedLiteral(correspondingAstNode.declaredName()))
