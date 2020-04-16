//Gestione delle liste - prototipi delle funzioni
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX 100

//Definizione tipo libro
typedef struct s_libro {
    char titolo[MAX];
    char autore[MAX];
    unsigned short int annoDiPubblicazione;
    char casaEditrice[MAX];
    unsigned short int lunghezza;
    char genere[MAX];
    char codiceIdentificativo[MAX];
    unsigned short int valutazione; //Valutazione del libro da 1 a 10
} tipoNodo;

//Lista linkata
typedef struct s_nodo {
    tipoNodo info;
    struct s_nodo *successivo;
} nodoLinkedList;

int menu(void);

//Funzione di creazione e gestione della lista
tipoNodo *creaNuovoLibro(void); //Crea nuova struct da inserire
nodoLinkedList* creaTestaLinkedList(tipoNodo elemento); //Crea la testa della lista linkata
bool inizializzaLinkedList(nodoLinkedList **testa); //Inizializza a una lista linkata vuota
bool isLinkedListEmpty (nodoLinkedList **testa); //Verifica se la lista è vuota
bool ricercaElemento(nodoLinkedList *puntatore, tipoNodo elemento); //Ricerca elemento

//Funzioni di inserimento
bool inserisciInTestaLinkedList(nodoLinkedList **testa, tipoNodo elemento); //Inserisce l'elemento in testa
bool inserisciInCodaLinkedList(nodoLinkedList *testa, tipoNodo elemento); //Inserisce l'elemento in coda
bool inserisciDopoElementoLinkedList(nodoLinkedList **testa, tipoNodo elementoDaRicercare, tipoNodo elementoDaInserire); //Inserisce l'elemento dopo quello dato

//Funzioni di cancellazione
bool cancellaDallaTestaLinkedList(nodoLinkedList **testa); //Cancella l'elemento in testa
bool cancellaDallaCodaLinkedList(nodoLinkedList *testa); //Cancella l'elemento in coda
bool cancellaPrimaOccorrenzaLinkedList(nodoLinkedList **testa); //Cancella la prima occorrenza dell'elemento

//Funzione di stampa
void stampaLinkedList (nodoLinkedList *testa); //Stampa la lista linkata
void stampaValutazione (nodoLinkedList *testa); //Stampa la lista linkata in base alla valutazione
