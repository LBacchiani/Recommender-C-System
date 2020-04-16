#include "code.h"

int main(void) {
    tipoNodo variabile=5;
    tipoNodo variabile1=3;
    
    //Pila indicizzata statica
    tipoCoda codaStatica;
    codaStatica.ultimoElementoCoda=0;
    printf("Dopo creazione coda indicizzata statica\n\n");
    stampaCodaIndicizzataStatica(&codaStatica);
    
    push(&codaStatica, &variabile);
    printf("Dopo push\n\n");
    stampaCodaIndicizzataStatica(&codaStatica);
    
    printf("Popped item: %d\n", pop(&codaStatica));
    printf("Dopo pop\n\n");
    stampaCodaIndicizzataStatica(&codaStatica);
    
    //Lista indicizzata dinamica
    printf("Dopo creazione pila indicizzata dinamica\n\n");
    tipoCodaDinamica codaDinamica = creaCoda();
    codaDinamica.ultimoElementoCoda=0;
    stampaCodaIndicizzataDinamica(&codaDinamica);
    
    pushDinamic(&codaDinamica, &variabile);
    printf("Dopo push\n\n");
    stampaCodaIndicizzataDinamica(&codaDinamica);
    
    printf("Popped item: %d\n", popDinamic(&codaDinamica));
    printf("Dopo pop\n\n");
    stampaCodaIndicizzataDinamica(&codaDinamica);
    
    printf("Dopo estensione (coda indicizzata dinamica)\n\n");
    estendiCoda(&codaDinamica);
    stampaCodaIndicizzataDinamica(&codaDinamica);
    
    printf("Dopo riduzione (coda indicizzata dinamica)\n\n");
    riduciCoda(&codaDinamica);
    stampaCodaIndicizzataDinamica(&codaDinamica);
    
    //Lista linkata
    printf("Dopo creazione coda linkata con primo elemento\n\n");
    nodoCodaLinked *testa = creaTestaCodaLinked(2);
    stampaCodaLinked(testa);
    
    pushCodaLinked(&testa, variabile);
    printf("Dopo push\n\n");
    stampaCodaLinked(testa);
    
    printf("Popped item: %d\n", popCodaLinked(&testa));
    printf("Dopo pop\n\n");
    stampaCodaLinked(testa);
    
    exit(EXIT_SUCCESS);
}
