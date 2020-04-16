//Gestione delle liste - corpo delle funzioni

#include "myLbrary.h"

//Lista linkata

int menu(void) {
    int scelta=0;
    printf("Seleziona scelta:\n\n");
    printf("1. Aggiungi nuovo libro in coda;\n");
    printf("2. Cancella un libro;\n");
    printf("3. Visualizza tutti i libri;\n");
    printf("4. Visualizza i libri in base alla valutazione;\n");
    printf("5. Esci;\n\n");
    printf("Numero scelta: ");
    scanf("%d", &scelta);
    getchar();
    return scelta;
}

tipoNodo *creaNuovoLibro() {
    tipoNodo *nuovoLibro = (tipoNodo*) malloc(sizeof(tipoNodo));
    if (nuovoLibro==NULL)
        return NULL;
    printf("Titolo: ");
    fgets(nuovoLibro->titolo, MAX, stdin);
    printf("Autore: ");
    fgets(nuovoLibro->autore, MAX, stdin);
    printf("Casa editrice: ");
    fgets(nuovoLibro->casaEditrice, MAX, stdin);
    printf("Genere: ");
    fgets(nuovoLibro->genere, MAX, stdin);
    printf("Codice identificativo: ");
    fgets(nuovoLibro->codiceIdentificativo, MAX, stdin);
    printf("Anno di pubblicazione: ");
    scanf("%hu", &nuovoLibro->annoDiPubblicazione);
    printf("Lunghezza: ");
    scanf("%hu", &nuovoLibro->lunghezza);
    printf("Valutazione: ");
    scanf("%hu", &nuovoLibro->valutazione);
    getchar();
    
    
    nuovoLibro->titolo[strcspn(nuovoLibro->titolo, "\n")] = 0;
    nuovoLibro->autore[strcspn(nuovoLibro->autore, "\n")] = 0;
    nuovoLibro->casaEditrice[strcspn(nuovoLibro->casaEditrice, "\n")] = 0;
    nuovoLibro->genere[strcspn(nuovoLibro->genere, "\n")] = 0;
    nuovoLibro->codiceIdentificativo[strcspn(nuovoLibro->codiceIdentificativo, "\n")] = 0;
    return nuovoLibro;
}

nodoLinkedList* creaTestaLinkedList(tipoNodo elemento) {
    nodoLinkedList *testa = NULL;
    testa = malloc(sizeof(nodoLinkedList));
    if (testa==NULL)
        return NULL;
    strcpy(testa->info.titolo, elemento.titolo);
    strcpy(testa->info.autore, elemento.autore);
    strcpy(testa->info.casaEditrice, elemento.casaEditrice);
    strcpy(testa->info.genere, elemento.genere);
    strcpy(testa->info.codiceIdentificativo, elemento.codiceIdentificativo);
    testa->info.annoDiPubblicazione=elemento.annoDiPubblicazione;
    testa->info.lunghezza=elemento.lunghezza;
    testa->info.valutazione=elemento.valutazione;
    testa->successivo = NULL;
    return testa;
}

bool ricercaElemento(nodoLinkedList *puntatore, tipoNodo elemento) {
    if (puntatore->info.titolo==elemento.titolo && puntatore->info.autore==elemento.autore
        && puntatore->info.casaEditrice==elemento.casaEditrice && puntatore->info.genere==elemento.genere
        && puntatore->info.codiceIdentificativo==elemento.codiceIdentificativo
        && puntatore->info.annoDiPubblicazione==elemento.annoDiPubblicazione
        && puntatore->info.lunghezza==elemento.lunghezza
        && puntatore->info.valutazione==elemento.valutazione)
        return true;
    else
        return false;
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
    strcpy(nuovoNodo->info.titolo, elemento.titolo);
    strcpy(nuovoNodo->info.autore, elemento.autore);
    strcpy(nuovoNodo->info.casaEditrice, elemento.casaEditrice);
    strcpy(nuovoNodo->info.genere, elemento.genere);
    strcpy(nuovoNodo->info.codiceIdentificativo, elemento.codiceIdentificativo);
    nuovoNodo->info.annoDiPubblicazione=elemento.annoDiPubblicazione;
    nuovoNodo->info.lunghezza=elemento.lunghezza;
    nuovoNodo->info.valutazione=elemento.valutazione;
    nuovoNodo -> successivo = *testa;
    *testa = nuovoNodo;
    return true;
}

bool inserisciInCodaLinkedList(nodoLinkedList *testa, tipoNodo elemento) {
    nodoLinkedList *current = testa;
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
    if (ricercaElemento(current, elementoDaRicercare)) {
        inserisciInTestaLinkedList(testa, elementoDaInserire);
        return true;
    }
    while (!(ricercaElemento(current, elementoDaRicercare))) { //Finchè non trovo l'elemento desiderato
        current = current->successivo;
        if (current==NULL) {
            printf("Elemento non trovato!\n");
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
    printf("Elemento cancellato correttamente!\n");
    return true;
}

bool cancellaDallaCodaLinkedList(nodoLinkedList *testa) {
    nodoLinkedList *current = testa;
    while (current->successivo->successivo != NULL) {
        current = current->successivo;
    }
    free(current->successivo);
    current->successivo=NULL;
    return true;
}

bool cancellaPrimaOccorrenzaLinkedList(nodoLinkedList **testa) {
    nodoLinkedList *current = *testa;
    char codiceIdentificativo[MAX];
    printf("Inserisci il numero identificativo del libro da cancellare: ");
    fgets(codiceIdentificativo, MAX, stdin);
    codiceIdentificativo[strcspn(codiceIdentificativo, "\n")] = 0;
    if (strcmp(current->info.codiceIdentificativo, codiceIdentificativo)==0) { //Se l'elemento è in testa
        cancellaDallaTestaLinkedList(testa);
        return true;
    }
    while (current->successivo!=NULL && !(strcmp(current->successivo->info.codiceIdentificativo, codiceIdentificativo)==0)) {//Trovo quello precedente
        current = current->successivo;
        if (current==NULL) {
            printf("Elemento non trovato!\n");
            return false;
        }
    }
    nodoLinkedList *nodoTemp = current->successivo;
    current->successivo = current->successivo->successivo;
    free(nodoTemp);
    printf("Elemento cancellato correttamente!\n");
    return true;
}

void stampaLinkedList (nodoLinkedList *testa) {
    nodoLinkedList *puntatore = testa;
    int i=0;
    printf("Stampa lista linkata");
    while (puntatore!=NULL) {
        printf("\n\nElemento %d\n", ++i);
        printf("Titolo: %s\n", puntatore->info.titolo);
        printf("Autore: %s\n", puntatore->info.autore);
        printf("Casa editrice: %s\n", puntatore->info.casaEditrice);
        printf("Anno di pubblicazione: %hu\n", puntatore->info.annoDiPubblicazione);
        printf("Codice identificativo: %s\n", puntatore->info.codiceIdentificativo);
        printf("Genere: %s\n", puntatore->info.genere);
        printf("Lunghezza in pagine: %hu\n", puntatore->info.lunghezza);
        printf("Valutazione in decimi: %hu\n", puntatore->info.valutazione);
        puntatore = puntatore -> successivo;
    }
    printf("\n");
}

void stampaValutazione (nodoLinkedList *testa) {
    nodoLinkedList *puntatore = testa;
    unsigned short int valutazione=0;
    int i=0;
    do {
        if (valutazione<0 || valutazione>10)
            printf("Inserire una valutazione corretta!\n");
        printf("Inserisci valutazione minima: ");
        scanf("%hu", &valutazione);
    } while (valutazione<0 || valutazione>10);
    printf("Stampa lista linkata con valutazione >= %hu", valutazione);
    while (puntatore!=NULL) {
        if (puntatore->info.valutazione>=valutazione) {
            printf("\n\nElemento %d\n", ++i);
            printf("Titolo: %s\n", puntatore->info.titolo);
            printf("Autore: %s\n", puntatore->info.autore);
            printf("Casa editrice: %s\n", puntatore->info.casaEditrice);
            printf("Anno di pubblicazione: %hu\n", puntatore->info.annoDiPubblicazione);
            printf("Codice identificativo: %s\n", puntatore->info.codiceIdentificativo);
            printf("Genere: %s\n", puntatore->info.genere);
            printf("Lunghezza in pagine: %hu\n", puntatore->info.lunghezza);
            printf("Valutazione in decimi: %hu\n", puntatore->info.valutazione);
        }
        puntatore = puntatore -> successivo;
    }
    printf("\n");
}


