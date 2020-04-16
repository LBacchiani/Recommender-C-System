//  Settimana10-Esercizio1

#include "pile.h"

int main(void) {
    tipoNodo variabile=5;
//    tipoNodo variabile1=3;
    
    //Pila indicizzata statica
    tipoPila pilaStatica;
    pilaStatica.ultimoElementoPila=0;
    printf("Dopo creazione pila indicizzata statica\n\n");
    stampaPilaIndicizzataStatica(&pilaStatica);
    
    push(&pilaStatica, &variabile);
    printf("Dopo push\n\n");
    stampaPilaIndicizzataStatica(&pilaStatica);
    
    printf("Popped item: %d\n", pop(&pilaStatica));
    printf("Dopo pop\n\n");
    stampaPilaIndicizzataStatica(&pilaStatica);
    
    //Lista indicizzata dinamica
    printf("Dopo creazione pila indicizzata dinamica\n\n");
    tipoPilaDinamica pilaDinamica = creaPila();
    pilaDinamica.ultimoElementoPila=0;
    stampaPilaIndicizzataDinamica(&pilaDinamica);
    
    pushDinamic(&pilaDinamica, &variabile);
    printf("Dopo push\n\n");
    stampaPilaIndicizzataDinamica(&pilaDinamica);
    
    printf("Popped item: %d\n", popDinamic(&pilaDinamica));
    printf("Dopo pop\n\n");
    stampaPilaIndicizzataDinamica(&pilaDinamica);

    printf("Dopo estensione (pila indicizzata dinamica)\n\n");
    estendiPila(&pilaDinamica);
    stampaPilaIndicizzataDinamica(&pilaDinamica);

    printf("Dopo riduzione (pila indicizzata dinamica)\n\n");
    riduciPila(&pilaDinamica);
    stampaPilaIndicizzataDinamica(&pilaDinamica);

    //Lista linkata
    printf("Dopo creazione pila linkata con primo elemento\n\n");
    nodoPilaLinked *testa = creaTestaPilaLinked(2);
    stampaPilaLinked(testa);
    
    pushPilaLinked(&testa, variabile);
    printf("Dopo push\n\n");
    stampaPilaLinked(testa);
    
    printf("Popped item: %d\n", popPilaLinked(&testa));
    printf("Dopo pop\n\n");
    stampaPilaLinked(testa);
    
    exit(EXIT_SUCCESS);
}
