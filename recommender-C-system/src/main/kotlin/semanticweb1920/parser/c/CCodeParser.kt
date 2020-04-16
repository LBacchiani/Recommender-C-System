package semanticweb1920.parser.c

import semanticweb1920.parser.CodeParser
import semanticweb1920.parser.c.model.CRootASTNode
import semanticweb1920.parser.c.model.ProblemVisitor
import mu.KotlinLogging
import org.eclipse.cdt.core.dom.ast.gnu.c.GCCLanguage
import org.eclipse.cdt.core.index.IIndex
import org.eclipse.cdt.core.model.ILanguage
import org.eclipse.cdt.core.parser.DefaultLogService
import org.eclipse.cdt.core.parser.FileContent
import org.eclipse.cdt.core.parser.IncludeFileContentProvider
import org.eclipse.cdt.core.parser.ScannerInfo
import java.util.*

private val logger = KotlinLogging.logger {}

/**
 * A singleton class implementing the C Code Parser
 */
object CCodeParser : CodeParser {

    @Throws(Exception::class)
    override fun parse(toParse: String): CRootASTNode {
        val fileContent = FileContent.create("/FictionPath/ToParsedSource.cpp", toParse.toCharArray())

        val macroDefinitions = HashMap<String, String>()
        val includeSearchPaths = arrayOfNulls<String>(0)
        val scannerInfo = ScannerInfo(macroDefinitions, includeSearchPaths)

        val includeFileContentProvider = IncludeFileContentProvider.getEmptyFilesProvider()

        val idx: IIndex? = null

        val options = ILanguage.OPTION_NO_IMAGE_LOCATIONS

        val log = DefaultLogService()
        logger.info { "Creating C AST..." }
        return CRootASTNode(GCCLanguage.getDefault()
                .getASTTranslationUnit(fileContent, scannerInfo, includeFileContentProvider, idx, options, log))
                .also {
                    logger.info { "C code AST created, checking for problems..." }
                    it.translationUnit.accept(onProblemsIllegalArgumentExceptionVisitor)
                    logger.info { "Code checked." }
                }
    }

    /**
     * Problems handler
     */
    private val onProblemsIllegalArgumentExceptionVisitor = ProblemVisitor { problem ->
        throw IllegalArgumentException("${problem?.message
                ?: "unknown problem"} at line ${problem?.sourceLineNumber
                ?: "unknown"} => ${problem?.rawSignature}")
    }
}
