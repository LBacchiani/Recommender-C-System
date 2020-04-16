package semanticweb1920.rdf.serialization

import semanticweb1920.rdf.serialization.SerializationUtils.SEPARATOR

/**
 * Object that contains serialization utils constants
 */
internal object SerializationUtils {
    const val CREATED_RESOURCES_NAMESPACE = "http://semanticweb.example.com/c/code/"
    const val SEPARATOR = "-"
}

/**
 * Creates an RDF resource name concatenating a common name, a separator and a unique identifier
 *
 * Only [name] and [uid] are required.
 */
internal fun composeName(name: String, separator: String = SEPARATOR, uid: String) =
        name + separator + uid
