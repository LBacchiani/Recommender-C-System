//Gestione delle liste - corpo delle funzioni

#include "liste.h"

//Lista indicizzata - statica
bool full (const tipoLista *lista) {
    return ((lista->ultimoElementoLista == MAX-1)?true:false) ;
}

bool isEmpty (const tipoLista *lista) {
    return ((lista->ultimoElementoLista == 0)?true:false);
}

int indiceSuccessivo (const tipoLista *lista) {
    return (lista->ultimoElementoLista+1);
}

int indiceDaElemento (const tipoLista *lista, tipoNodo *elemento) {
    if (!isEmpty(lista))  //Se la lista non è piena
        for (int i=0; i<=lista->ultimoElementoLista; i++) //Scorro la lista dalla testa fino alla coda
            if (lista->lista[i]==(*elemento))  //Se ho trovato l'elemento restituisco
                return i;
    return -1; //Per qualsiasi errore la funzione restituisce -1
}

bool inserisciInTesta (tipoLista *lista, tipoNodo *elemento) {
    if (!full(lista)) { //Se la lista non è piena
        for (int i=lista->ultimoElementoLista; i>=0; i--)
            lista->lista[i+1]=lista->lista[i]; //Shift a destra
        lista->lista[0]=(*elemento);
        lista->ultimoElementoLista++;
        return true;
    } else
        printf("\tLista piena!\n");
    return false;
}

bool inserisciInCoda (tipoLista *lista, tipoNodo *elemento) {
    if (!full(lista)) { //Se la lista non è piena
        lista->lista[lista->ultimoElementoLista]=(*elemento);
        lista->ultimoElementoLista++;
        return true;
    } else
        printf("\tLista piena!\n");
    return false;
}

bool inserisciDopoElemento(tipoLista *lista, tipoNodo elementoDaRicercare, tipoNodo elementoDaInserire) {
    int indice = (indiceDaElemento(lista, &elementoDaRicercare)+1);
    if (!full(lista)) { //Se la lista non è piena
        if (indice>=0 && indice<=indiceSuccessivo(lista)) { //Se l'indice dove devo inserire l'elemento è sensato
            for (int i=lista->ultimoElementoLista; i>=indice; i--) //Partendo dall'ultimo elemento della lista shifto di una posizione a destra
                lista->lista[i+1]=lista->lista[i];
            lista->lista[indice]=elementoDaInserire;
            lista->ultimoElementoLista++;
            return true;
        } else
            printf("\tIndice errato!\n");
    } else
        printf("\tLista piena!\n");
    return true;
}

bool cancellaDallaTesta (tipoLista *lista) {
    if (!isEmpty(lista)) { //Se la lista non è vuota
        for (int i=0; i<lista->ultimoElementoLista; i++)
            lista->lista[i]=lista->lista[i+1]; //Shift a sinistra
        lista->ultimoElementoLista--;
        return true;
    } else
        printf("\tLista piena!\n");
    return false;
}

bool cancellaDallaCoda (tipoLista *lista) {
    if (!isEmpty(lista)) { //Se la lista non è vuota
        for (int i=lista->ultimoElementoLista; i<lista->ultimoElementoLista; i++)
            lista->lista[i]=lista->lista[i+1]; //Shift a sinistra
        lista->ultimoElementoLista--;
        return true;
    } else
        printf("\tLista piena!\n");
    return false;
}

bool cancellaPrimaOccorrenza (tipoLista *lista, tipoNodo *elemento) {
    int indice = indiceDaElemento(lista, elemento);
    if (indice==-1) {
        printf("\tElemento non trovato!\n");
        return false;
    }
    if (!isEmpty(lista)) { //Se la lista non è vuota
        if (indice>=0 && indice<=lista->ultimoElementoLista) { //Se l'indice di cui devo cancellare l'elemento è sensato
            for (int i=indice; i<lista->ultimoElementoLista; i++) //Partendo dall'ultimo elemento della lista shifto di una posizione a destra
                lista->lista[i]=lista->lista[i+1];
                lista->ultimoElementoLista--;
            return true;
        } else {
            printf("\tIndice errato!\n");
            return false;
        }
    } else {
        printf("\tLista vuota!\n");
        return false;
    }
}

void stampaListaIndicizzataStatica (tipoLista *lista) {
    if (!isEmpty(lista)) {
        for (int i=0; i<lista->ultimoElementoLista; i++)
            printf("\t%d. Elemento: %d\n", i, lista->lista[i]);
        printf("\n");
    } else
        printf("\tLista vuota!\n\n");
}


//Lista indicizzata - dinamica
tipoListaDinamica creaLista () {
    tipoListaDinamica lista = {NULL, 0, 0};
    lista.lista = (tipoNodo*) malloc (MAX * sizeof (tipoNodo));
    if(lista.lista != NULL )
        lista.dimensione=MAX;
    return lista ;
}

void cancellaLista (tipoListaDinamica *lista) {
    if (lista != NULL)
        free(lista->lista);
    lista->dimensione=0;
    lista->ultimoElementoLista=-1;
}

void estendiLista (tipoListaDinamica *lista) {
    if (!fullDinamic(lista)) {
        tipoNodo *tmp = realloc(lista->lista, 2* (lista->dimensione) *sizeof(tipoNodo));
        if (tmp!= NULL) {
            lista->dimensione*=2;
            lista->lista=tmp;
            printf("\tDimensioni raddoppiate. Attuali dimensioni: %d\n\n", lista->dimensione);
        }
    }
}

void riduciLista (tipoListaDinamica *lista) {
    if (lista->dimensione/3 > lista->ultimoElementoLista) {
        tipoNodo *tmp=realloc(lista->lista, lista->dimensione/2*sizeof(tipoNodo));
        if (tmp!= NULL) {
            lista->dimensione/=2;
            lista->lista=tmp;
            printf("\tDimensioni dimezzate. Attuali dimensioni: %d\n\n", lista->dimensione);
        }
    }
}

bool fullDinamic (const tipoListaDinamica *lista) { //La lista è piena
    return ((lista->ultimoElementoLista == MAX-1)?true:false) ;
}

bool isEmptyDinamic (const tipoListaDinamica *lista) { //La lista è vuota
    return ((lista->ultimoElementoLista == 0)?true:false);
}

int indiceSuccessivoDinamic (const tipoListaDinamica *lista) { //Restituisce l'indirizzo successivo all'ultimo elemento della lista
    return (lista->ultimoElementoLista+1);
}

int indiceDaElementoDinamic (const tipoListaDinamica *lista, tipoNodo *elemento) {
    if (!isEmptyDinamic(lista))  //Se la lista non è piena
        for (int i=0; i<=lista->ultimoElementoLista; i++) //Scorro la lista dalla testa fino alla coda
            if (lista->lista[i]==(*elemento))  //Se ho trovato l'elemento restituisco
                return i;
    return -1; //Per qualsiasi errore la funzione restituisce -1
}

bool inserisciInTestaDinamic (tipoListaDinamica *lista, tipoNodo *elementoDaAggiungere) {
    if (!fullDinamic(lista)) { //Se la lista non è piena
        for (int i=lista->ultimoElementoLista; i>=0; i--)
            lista->lista[i+1]=lista->lista[i]; //Shift a destra
        lista->lista[0]=(*elementoDaAggiungere);
        lista->ultimoElementoLista++;
        return true;
    } else
        printf("\tLista piena!\n");
    return false;
}

bool inserisciInCodaDinamic (tipoListaDinamica *lista, tipoNodo *elementoDaAggiungere) {
    if (!fullDinamic(lista)) { //Se la lista non è piena
        lista->lista[lista->ultimoElementoLista]=(*elementoDaAggiungere);
        lista->ultimoElementoLista++;
        return true;
    } else
        printf("\tLista piena!\n");
    return false;
}

bool inserisciDopoElementoDinamic (tipoListaDinamica *lista, tipoNodo elementoDaRicercare, tipoNodo elementoDaInserire) {
    int indice = (indiceDaElementoDinamic(lista, &elementoDaRicercare)+1);
    if (!fullDinamic(lista)) { //Se la lista non è piena
        if (indice>=0 && indice<=indiceSuccessivoDinamic(lista)) { //Se l'indice dove devo inserire l'elemento è sensato
            for (int i=lista->ultimoElementoLista; i>=indice; i--) //Partendo dall'ultimo elemento della lista shifto di una posizione a destra
                lista->lista[i+1]=lista->lista[i];
            lista->lista[indice]=elementoDaInserire;
            lista->ultimoElementoLista++;
            return true;
        } else
            printf("\tIndice errato!\n");
    } else
        printf("\tLista piena!\n");
    return true;
}

bool cancellaDallaTestaDinamic (tipoListaDinamica *lista) {
    if (!isEmptyDinamic(lista)) { //Se la lista non è vuota
        for (int i=0; i<lista->ultimoElementoLista; i++)
            lista->lista[i]=lista->lista[i+1]; //Shift a sinistra
        lista->ultimoElementoLista--;
        return true;
    } else
        printf("\tLista vuota!\n");
    return false;
}

bool cancellaDallaCodaDinamic (tipoListaDinamica *lista) {
    if (!isEmptyDinamic(lista)) { //Se la lista non è vuota
        for (int i=lista->ultimoElementoLista; i<lista->ultimoElementoLista; i++)
            lista->lista[i]=lista->lista[i+1]; //Shift a sinistra
        lista->ultimoElementoLista--;
        return true;
    } else
        printf("\tLista vuota!\n");
    return false;
}

bool cancellaPrimaOccorrenzaDinamic (tipoListaDinamica *lista, tipoNodo *elemento) {
    int indice = indiceDaElementoDinamic(lista, elemento);
    if (!isEmptyDinamic(lista)) { //Se la lista non è vuota
        if (indice>=0 && indice<=lista->ultimoElementoLista) { //Se l'indice di cui devo cancellare l'elemento è sensato
            for (int i=indice; i<lista->ultimoElementoLista; i++) //Partendo dall'ultimo elemento della lista shifto di una posizione a destra
                lista->lista[i]=lista->lista[i+1];
            lista->ultimoElementoLista--;
            return true;
        } else
            printf("\tIndice errato!\n");
    } else
        printf("\tLista vuota!\n\n");
    return false;
}

void stampaListaIndicizzataDinamica (tipoListaDinamica *lista) {
    if (!isEmptyDinamic(lista)) {
        for (int i=0; i<lista->ultimoElementoLista; i++)
            printf("\t%d. Elemento: %d\n", i, lista->lista[i]);
        printf("\n");
    } else
        printf("\tLista vuota!\n\n");
}


//Lista linkata
nodoLinkedList* creaTestaLinkedList(tipoNodo elemento) {
    nodoLinkedList *testa = NULL;
    testa = malloc(sizeof(nodoLinkedList));
   //Controlli malloc
    testa->info = elemento;
    testa->successivo = NULL;
    return testa;
}

bool inizializzaLinkedList(nodoLinkedList **testa) {
    *testa=NULL;
    if (*testa==NULL)
        return true;
    else
        return false;
}

bool isLinkedListEmpty (nodoLinkedList **testa) {
    return (*testa == NULL);
}

bool inserisciInTestaLinkedList(nodoLinkedList **testa, tipoNodo elemento) {
    nodoLinkedList *nuovoNodo = malloc(sizeof(nodoLinkedList));
    if (nuovoNodo==NULL)
        return false;
    nuovoNodo -> info = elemento;
    nuovoNodo -> successivo = *testa;
    *testa = nuovoNodo;
    return true;
}

bool inserisciInCodaLinkedList(nodoLinkedList **testa, tipoNodo elemento) {
    nodoLinkedList *current = *testa;
    while (current->successivo!= NULL) {
        current = current->successivo;
    }
    nodoLinkedList *nuovoNodo = malloc(sizeof(nodoLinkedList));
    current->successivo = nuovoNodo;
    current->successivo->info = elemento;
    current->successivo->successivo = NULL;
    return true;
}

bool inserisciDopoElementoLinkedList (nodoLinkedList **testa, tipoNodo elementoDaRicercare, tipoNodo elementoDaInserire) {
    nodoLinkedList *current = *testa;
    nodoLinkedList *temp = NULL;
    if (current->info==elementoDaRicercare) {
        inserisciInTestaLinkedList(testa, elementoDaInserire);
        return true;
    }
    while (current->info != elementoDaRicercare) { //Finchè non trovo l'elemento desiderato
        current = current->successivo;
        if (current==NULL) {
            printf("\tElemento non trovato!");
            return false;
        }
    }
    nodoLinkedList *nuovoNodo = (nodoLinkedList*) malloc(sizeof(nodoLinkedList));
    if (nuovoNodo==NULL)
        return false;
    temp=current->successivo;
    nuovoNodo->info=elementoDaInserire;
    nuovoNodo->successivo=temp;
    current->successivo=nuovoNodo;
    return true;
}

bool cancellaDallaTestaLinkedList(nodoLinkedList **testa) {
    if (testa==NULL)
        return false;
    nodoLinkedList *secondoNodo = NULL;
    secondoNodo = (*testa) -> successivo;
    free(*testa);
    *testa=secondoNodo;
    return true;
}

bool cancellaDallaCodaLinkedList(nodoLinkedList **testa) {
    nodoLinkedList *current = *testa;
    while (current->successivo->successivo != NULL) {
        current = current->successivo;
    }
    free(current->successivo);
    current->successivo=NULL;
    return true;
}

bool cancellaPrimaOccorrenzaLinkedList(nodoLinkedList **testa, tipoNodo elemento) {
    nodoLinkedList *current = *testa;
    if (current->info==elemento) { //Se l'elemento è in testa
        cancellaDallaTestaLinkedList(testa);
        return true;
    }
    while (current->successivo!=NULL && current->successivo->info != elemento) {//Trovo quello precedente
        current = current->successivo;
        if (current==NULL) {
            printf("\tElemento non trovato!\n\n");
            return false;
        }
    }
    nodoLinkedList *nodoTemp = current->successivo;
    current->successivo = current->successivo->successivo;
    free(nodoTemp);
    return true;
}

void stampaLinkedList (nodoLinkedList *testa) {
    nodoLinkedList *puntatore = testa;
    int i=0;
    while (puntatore!=NULL) {
        printf("\t%d. Stampa: %d\n", i++, puntatore->info);
        puntatore = puntatore -> successivo;
    }
    printf("\n");
}


