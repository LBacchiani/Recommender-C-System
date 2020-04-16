package semanticweb1920.parser.model

/**
 * Interface representing the abstraction of an Abstract Syntax Tree Node
 */
interface ASTNode {

    /**
     * The children of this AST Node
     */
    val children: Collection<ASTNode>

    /**
     * The parent of this AST Node; can be null if this is the top AST Node
     */
    val parent: ASTNode?
}