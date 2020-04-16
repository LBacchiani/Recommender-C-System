//Gestione delle liste - corpo delle funzioni

#include "pile.h"

//Lista indicizzata - statica
bool full (const tipoPila *pila) {
    return ((pila->ultimoElementoPila == MAX-1)?true:false) ;
}

bool isEmpty (const tipoPila *pila) {
    return ((pila->ultimoElementoPila == 0)?true:false);
}

bool push (tipoPila *pila, tipoNodo *elemento) {
    if (!full(pila)) { //Se la lista non è piena
        pila->pila[pila->ultimoElementoPila]=(*elemento);
        pila->ultimoElementoPila++;
        return true;
    } else
        printf("\tLista piena!\n");
    return false;
}

tipoNodo pop (tipoPila *pila) {
    if (!isEmpty(pila)) { //Se la lista non è vuota
        pila->ultimoElementoPila--;
        return pila->pila[pila->ultimoElementoPila];
    } else
        printf("\tPila piena!\n");
    return -1;
}

void stampaPilaIndicizzataStatica (tipoPila *pila) {
    if (!isEmpty(pila)) {
        for (int i=0; i<pila->ultimoElementoPila; i++)
            printf("\t%d. Elemento: %d\n", i, pila->pila[i]);
        printf("\n");
    } else
        printf("\tPila vuota!\n\n");
}


//Lista indicizzata - dinamica
tipoPilaDinamica creaPila () {
    tipoPilaDinamica pila = {NULL, 0, 0};
    pila.pila = (tipoNodo*) malloc (MAX * sizeof (tipoNodo));
    if(pila.pila != NULL )
        pila.dimensione=MAX;
    return pila ;
}

void cancellaLista (tipoPilaDinamica *pila) {
    if (pila != NULL)
        free(pila->pila);
    pila->dimensione=0;
    pila->ultimoElementoPila=-1;
}

void estendiPila (tipoPilaDinamica *pila) {
    if (!fullDinamic(pila)) {
        tipoNodo *tmp = realloc(pila->pila, 2* (pila->dimensione) *sizeof(tipoNodo));
        if (tmp!= NULL) {
            pila->dimensione*=2;
            pila->pila=tmp;
            printf("\tDimensioni raddoppiate. Attuali dimensioni: %d\n\n", pila->dimensione);
        }
    }
}

void riduciPila (tipoPilaDinamica *pila) {
    if (pila->dimensione/3 > pila->ultimoElementoPila) {
        tipoNodo *tmp=realloc(pila->pila, pila->dimensione/2*sizeof(tipoNodo));
        if (tmp!= NULL) {
            pila->dimensione/=2;
            pila->pila=tmp;
            printf("\tDimensioni dimezzate. Attuali dimensioni: %d\n\n", pila->dimensione);
        }
    }
}

bool fullDinamic (const tipoPilaDinamica *pila) { //La lista è piena
    return ((pila->ultimoElementoPila == MAX-1)?true:false) ;
}

bool isEmptyDinamic (const tipoPilaDinamica *pila) { //La lista è vuota
    return ((pila->ultimoElementoPila == 0)?true:false);
}

bool pushDinamic (tipoPilaDinamica *pila, tipoNodo *elementoDaAggiungere) {
    if (!fullDinamic(pila)) { //Se la lista non è piena
        pila->pila[pila->ultimoElementoPila]=(*elementoDaAggiungere);
        pila->ultimoElementoPila++;
        return true;
    } else
        printf("\tPila piena!\n");
    return false;
}

tipoNodo popDinamic (tipoPilaDinamica *pila) {
    if (!isEmptyDinamic(pila)) { //Se la lista non è vuota
        pila->ultimoElementoPila--;
        return pila->pila[pila->ultimoElementoPila];;
    } else
        printf("\tPila vuota!\n");
    return -1;
}

void stampaPilaIndicizzataDinamica (tipoPilaDinamica *pila) {
    if (!isEmptyDinamic(pila)) {
        for (int i=0; i<pila->ultimoElementoPila; i++)
            printf("\t%d. Elemento: %d\n", i, pila->pila[i]);
        printf("\n");
    } else
        printf("\tPila vuota!\n\n");
}


//Lista linkata
nodoPilaLinked* creaTestaPilaLinked(tipoNodo elemento) {
    nodoPilaLinked *testa = NULL;
    testa = malloc(sizeof(nodoPilaLinked));
   //Controlli malloc
    testa->info = elemento;
    testa->successivo = NULL;
    return testa;
}

bool inizializzaLinkedList(nodoPilaLinked **testa) {
    *testa=NULL;
    if (*testa==NULL)
        return true;
    else
        return false;
}

bool isLinkedListEmpty (nodoPilaLinked **testa) {
    return (*testa == NULL);
}

bool pushPilaLinked(nodoPilaLinked **testa, tipoNodo elemento) {
    nodoPilaLinked *current = *testa;
    while (current->successivo!= NULL) {
        current = current->successivo;
    }
    nodoPilaLinked *nuovoNodo = malloc(sizeof(nodoPilaLinked));
    current->successivo = nuovoNodo;
    current->successivo->info = elemento;
    current->successivo->successivo = NULL;
    return true;
}

tipoNodo popPilaLinked(nodoPilaLinked **testa) {
    nodoPilaLinked *current = *testa;
    while (current->successivo->successivo != NULL) {
        current = current->successivo;
    }
    tipoNodo returnValue = current->successivo->info;
    free(current->successivo);
    current->successivo=NULL;
    return returnValue;
}

void stampaPilaLinked (nodoPilaLinked *testa) {
    nodoPilaLinked *puntatore = testa;
    int i=0;
    while (puntatore!=NULL) {
        printf("\t%d. Stampa: %d\n", i++, puntatore->info);
        puntatore = puntatore -> successivo;
    }
    printf("\n");
}


