//Gestione delle liste - prototipi delle funzioni
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX 100
typedef int tipoNodo;

//Lista indicizzata - statica
typedef struct listaStatica {
    tipoNodo lista[MAX];
    int ultimoElementoLista;
} tipoLista;

//Funzioni di controllo
bool full (const tipoLista *lista); //Verifica se la lista è piena
bool isEmpty (const tipoLista *lista); //Verifica se la lista è vuota
int indiceSuccessivo (const tipoLista *lista); //Verifica l'indice successivo all'ultimo
int indiceDaElemento (const tipoLista *lista, tipoNodo *elemento); //Restituisce l'indice dato l'elemento

//Funzioni di inserimento
bool inserisciInTesta (tipoLista *lista, tipoNodo *elemento); //Inserisce l'elemento in testa
bool inserisciInCoda (tipoLista *lista, tipoNodo *elemento); //Inserisce l'elemento in coda
bool inserisciDopoElemento(tipoLista *lista, tipoNodo elementoDaRicercare, tipoNodo elementoDaInserire); //Inserisce l'elemento dopo quello dato

////Funzioni di cancellazione
bool cancellaDallaTesta (tipoLista *lista); //Cancella l'elemento in testa
bool cancellaDallaCoda (tipoLista *lista);//Cancella l'elemento in coda
bool cancellaPrimaOccorrenza (tipoLista *lista, tipoNodo *elemento); //Cancella la prima occorrenza dell'elemento

//Funzione di stampa
void stampaListaIndicizzataStatica (tipoLista *lista); //Stampa la lista indicizzata statica


//Lista indicizzata - dinamica
typedef struct listaDinamica {
    tipoNodo *lista;
    int dimensione;
    int ultimoElementoLista;
} tipoListaDinamica;

//Funzioni di creazione e gestione della lista
tipoListaDinamica creaLista (void); //Crea la lista indicizzata dinamica
void cancellaLista (tipoListaDinamica *lista); //Cancella la lista indicizzata dinamica
void estendiLista (tipoListaDinamica *lista); //Estende la lista indicizzata dinamica
void riduciLista (tipoListaDinamica *lista); //Riduce la lista indicizzata dinamica

//Funzioni di controllo
bool fullDinamic (const tipoListaDinamica *lista); //Verifica se la lista è piena
bool isEmptyDinamic (const tipoListaDinamica *lista); //Verifica se la lista è vuota
int indiceSuccessivoDinamic (const tipoListaDinamica *lista); //Verifica l'indice successivo all'ultimo
int indiceDaElementoDinamic (const tipoListaDinamica *lista, tipoNodo *elemento); //Restituisce l'indice dato l'elemento

//Funzioni di inserimento
bool inserisciInTestaDinamic (tipoListaDinamica *lista, tipoNodo *elementoDaAggiungere); //Inserisce l'elemento in testa
bool inserisciInCodaDinamic (tipoListaDinamica *lista, tipoNodo *elementoDaAggiungere); //Inserisce l'elemento in coda
bool inserisciDopoElementoDinamic (tipoListaDinamica *lista, tipoNodo elementoDaRicercare, tipoNodo elementoDaInserire); //Inserisce l'elemento dopo quello dato

//Funzioni di cancellazione
bool cancellaDallaTestaDinamic (tipoListaDinamica *lista); //Cancella l'elemento in testa
bool cancellaDallaCodaDinamic (tipoListaDinamica *lista); //Cancella l'elemento in coda
bool cancellaPrimaOccorrenzaDinamic (tipoListaDinamica *lista, tipoNodo *elemento); //Cancella la prima occorrenza dell'elemento

//Funzione di stampa
void stampaListaIndicizzataDinamica (tipoListaDinamica *lista); //Stampa la lista indicizzata dinamica


//Lista linkata
typedef struct s_nodo {
    int info;
    struct s_nodo *successivo;
} nodoLinkedList;

//Funzione di creazione e gestione della lista
nodoLinkedList* creaTestaLinkedList(int elemento); //Crea la testa della lista linkata
bool inizializzaLinkedList(nodoLinkedList **testa); //Inizializza a una lista linkata vuota
bool isLinkedListEmpty (nodoLinkedList **testa); //Verifica se la lista è vuota

//Funzioni di inserimento
bool inserisciInTestaLinkedList(nodoLinkedList **testa, int elemento); //Inserisce l'elemento in testa
bool inserisciInCodaLinkedList(nodoLinkedList **testa, int elemento); //Inserisce l'elemento in coda
bool inserisciDopoElementoLinkedList(nodoLinkedList **testa, tipoNodo elementoDaRicercare, tipoNodo elementoDaInserire); //Inserisce l'elemento dopo quello dato

//Funzioni di cancellazione
bool cancellaDallaTestaLinkedList(nodoLinkedList **testa); //Cancella l'elemento in testa
bool cancellaDallaCodaLinkedList(nodoLinkedList **testa); //Cancella l'elemento in coda
bool cancellaPrimaOccorrenzaLinkedList(nodoLinkedList **testa, tipoNodo elemento); //Cancella la prima occorrenza dell'elemento

//Funzione di stampa
void stampaLinkedList (nodoLinkedList *testa); //Stampa la lista linkata
