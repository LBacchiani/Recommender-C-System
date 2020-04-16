package semanticweb1920.parser.c.model

import org.eclipse.cdt.core.dom.ast.ASTGenericVisitor
import org.eclipse.cdt.core.dom.ast.ASTVisitor
import org.eclipse.cdt.core.dom.ast.IASTNode
import org.eclipse.cdt.core.dom.ast.IASTProblem


/**
 * An AST visitor that does something on problem encounter
 */
class ProblemVisitor(val onProblem: (IASTProblem?) -> Unit) : ASTVisitor() {

    init {
        shouldVisitProblems = true
    }

    override fun visit(problem: IASTProblem?): Int {
        onProblem(problem)
        return PROCESS_CONTINUE
    }
}

/**
 * An AST visitor that does some mapping over encountered nodes
 */
class MapperVisitor(private val mapper: (IASTNode) -> Unit) : ASTGenericVisitor(true) {

    override fun genericVisit(node: IASTNode): Int {
        mapper(node)
        return ASTVisitor.PROCESS_CONTINUE
    }
}

/**
 * An AST Visitor that does some mapping over encountered nodes and provides a memory to be used
 */
class MapperVisitorWithMemory(
        private val memory: StringBuilder = StringBuilder(),
        private val mapper: (StringBuilder, IASTNode) -> Unit
) : ASTGenericVisitor(true) {

    override fun genericVisit(node: IASTNode): Int {
        mapper(memory, node)
        return ASTVisitor.PROCESS_CONTINUE
    }
}
