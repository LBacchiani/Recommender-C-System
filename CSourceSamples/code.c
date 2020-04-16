//Gestione delle liste - corpo delle funzioni

#include "code.h"

//Lista indicizzata - statica
bool full (const tipoCoda *coda) {
    return ((coda->ultimoElementoCoda == MAX-1)?true:false) ;
}

bool isEmpty (const tipoCoda *coda) {
    return ((coda->ultimoElementoCoda == 0)?true:false);
}

bool push (tipoCoda *coda, tipoNodo *elemento) {
    if (!full(coda)) { //Se la lista non è piena
        for (int i=coda->ultimoElementoCoda; i>=0; i--)
            coda->coda[i+1]=coda->coda[i]; //Shift a destra
        coda->coda[0]=(*elemento);
        coda->ultimoElementoCoda++;
        return true;
    } else
        printf("\tCoda piena!\n");
    return false;
}

tipoNodo pop (tipoCoda *coda) {
    if (!isEmpty(coda)) { //Se la lista non è vuota
        coda->ultimoElementoCoda--;
        return coda->coda[coda->ultimoElementoCoda];
    } else
        printf("\tCoda piena!\n");
    return -1;
}

void stampaCodaIndicizzataStatica (tipoCoda *coda) {
    if (!isEmpty(coda)) {
        for (int i=0; i<coda->ultimoElementoCoda; i++)
            printf("\t%d. Elemento: %d\n", i, coda->coda[i]);
        printf("\n");
    } else
        printf("\tCoda vuota!\n\n");
}


//Lista indicizzata - dinamica
tipoCodaDinamica creaCoda () {
    tipoCodaDinamica coda = {NULL, 0, 0};
    coda.coda = (tipoNodo*) malloc (MAX * sizeof (tipoNodo));
    if(coda.coda != NULL )
        coda.dimensione=MAX;
    return coda ;
}

void cancellaLista (tipoCodaDinamica *coda) {
    if (coda != NULL)
        free(coda->coda);
    coda->dimensione=0;
    coda->ultimoElementoCoda=-1;
}

void estendiCoda (tipoCodaDinamica *coda) {
    if (!fullDinamic(coda)) {
        tipoNodo *tmp = realloc(coda->coda, 2* (coda->dimensione) *sizeof(tipoNodo));
        if (tmp!= NULL) {
            coda->dimensione*=2;
            coda->coda=tmp;
            printf("\tDimensioni raddoppiate. Attuali dimensioni: %d\n\n", coda->dimensione);
        }
    }
}

void riduciCoda (tipoCodaDinamica *coda) {
    if (coda->dimensione/3 > coda->ultimoElementoCoda) {
        tipoNodo *tmp=realloc(coda->coda, coda->dimensione/2*sizeof(tipoNodo));
        if (tmp!= NULL) {
            coda->dimensione/=2;
            coda->coda=tmp;
            printf("\tDimensioni dimezzate. Attuali dimensioni: %d\n\n", coda->dimensione);
        }
    }
}

bool fullDinamic (const tipoCodaDinamica *pila) { //La lista è piena
    return ((pila->ultimoElementoCoda == MAX-1)?true:false) ;
}

bool isEmptyDinamic (const tipoCodaDinamica *pila) { //La lista è vuota
    return ((pila->ultimoElementoCoda == 0)?true:false);
}

bool pushDinamic (tipoCodaDinamica *coda, tipoNodo *elementoDaAggiungere) {
    if (!fullDinamic(coda)) { //Se la lista non è piena
        for (int i=coda->ultimoElementoCoda; i>=0; i--)
            coda->coda[i+1]=coda->coda[i]; //Shift a destra
        coda->coda[0]=(*elementoDaAggiungere);
        coda->ultimoElementoCoda++;
        return true;
    } else
        printf("\tLista piena!\n");
    return false;
}

tipoNodo popDinamic (tipoCodaDinamica *coda) {
    if (!isEmptyDinamic(coda)) { //Se la lista non è vuota
        coda->ultimoElementoCoda--;
        return coda->coda[coda->ultimoElementoCoda];;
    } else
        printf("\tCoda vuota!\n");
    return -1;
}

void stampaCodaIndicizzataDinamica (tipoCodaDinamica *coda) {
    if (!isEmptyDinamic(coda)) {
        for (int i=0; i<coda->ultimoElementoCoda; i++)
            printf("\t%d. Elemento: %d\n", i, coda->coda[i]);
        printf("\n");
    } else
        printf("\tCoda vuota!\n\n");
}


//Lista linkata
nodoCodaLinked* creaTestaCodaLinked(tipoNodo elemento) {
    nodoCodaLinked *testa = NULL;
    testa = malloc(sizeof(nodoCodaLinked));
   //Controlli malloc
    testa->info = elemento;
    testa->successivo = NULL;
    return testa;
}

bool inizializzaLinkedList(nodoCodaLinked **testa) {
    *testa=NULL;
    if (*testa==NULL)
        return true;
    else
        return false;
}

bool isLinkedListEmpty (nodoCodaLinked **testa) {
    return (*testa == NULL);
}

bool pushCodaLinked(nodoCodaLinked **testa, tipoNodo elemento) {
    nodoCodaLinked *nuovoNodo = malloc(sizeof(nodoCodaLinked));
    if (nuovoNodo==NULL)
        return false;
    nuovoNodo -> info = elemento;
    nuovoNodo -> successivo = *testa;
    *testa = nuovoNodo;
    return true;
}

tipoNodo popCodaLinked(nodoCodaLinked **testa) {
    nodoCodaLinked *current = *testa;
    while (current->successivo->successivo != NULL) {
        current = current->successivo;
    }
    tipoNodo returnValue = current->successivo->info;
    free(current->successivo);
    current->successivo=NULL;
    return returnValue;
}

void stampaCodaLinked (nodoCodaLinked *testa) {
    nodoCodaLinked *puntatore = testa;
    int i=0;
    while (puntatore!=NULL) {
        printf("\t%d. Stampa: %d\n", i++, puntatore->info);
        puntatore = puntatore -> successivo;
    }
    printf("\n");
}


