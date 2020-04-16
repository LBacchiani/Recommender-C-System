package semanticweb1920.parser

import semanticweb1920.parser.model.ASTNode

/**
 * An interface representing Code Parser abstraction
 */
interface CodeParser {

    /**
     * A function accepting a string for parsing
     */
    fun parse(toParse: String): ASTNode
}