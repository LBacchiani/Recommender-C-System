package semanticweb1920.parser.c.model

import semanticweb1920.parser.model.ASTNode
import org.eclipse.cdt.core.dom.ast.IASTNode

/**
 * Class wrapping an AST Node as of Eclipse CDT
 */
class CASTNode(val eclipseCDTNode: IASTNode) : ASTNode {

    override val children: Collection<ASTNode>
        get() = (eclipseCDTNode.children?.mapNotNull { CASTNode(it) }) ?: emptyList()

    override val parent: ASTNode?
        get() = eclipseCDTNode.parent?.let { CASTNode(it) }

}