package semanticweb1920.parser.c.model

import semanticweb1920.parser.c.model.CASTNode
import semanticweb1920.parser.model.ASTNode
import org.eclipse.cdt.core.dom.ast.IASTPreprocessorIncludeStatement
import org.eclipse.cdt.core.dom.ast.IASTPreprocessorMacroDefinition
import org.eclipse.cdt.core.dom.ast.IASTTranslationUnit

/**
 * A class representing the Root AST node for C code, using Eclipse CDT
 *
 * @property translationUnit The translation unit represents a compilable unit of source.
 */
class CRootASTNode(val translationUnit: IASTTranslationUnit) : ASTNode by CASTNode(translationUnit) {

    /**
     * Retrieves all macro definitions from root of AST
     */
    val macroDefinitions: Collection<IASTPreprocessorMacroDefinition>
        get() = translationUnit.macroDefinitions?.filterNotNull() ?: emptyList()

    /**
     * Retrieves all include statements from root of AST
     */
    val includeDirectives: Collection<IASTPreprocessorIncludeStatement>
        get() = translationUnit.includeDirectives?.filterNotNull() ?: emptyList()

}
