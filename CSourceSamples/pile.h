//Gestione delle pile - prototipi delle funzioni
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX 100
typedef int tipoNodo;

//pila indicizzata - statica
typedef struct pilaStatica {
    tipoNodo pila[MAX];
    int ultimoElementoPila;
} tipoPila;

//Funzioni di controllo
bool full (const tipoPila *lista); //Verifica se la lista è piena
bool isEmpty (const tipoPila *lista); //Verifica se la lista è vuota
bool push (tipoPila *pila, tipoNodo *elemento); //Inserisce l'elemento in cima alla pila
tipoNodo pop (tipoPila *pila); //Estrae l'elemento in cima alla pila
void stampaPilaIndicizzataStatica (tipoPila *pila); //Stampa la lista indicizzata statica


//Pila indicizzata - dinamica
typedef struct pilaDinamica {
    tipoNodo *pila;
    int dimensione;
    int ultimoElementoPila;
} tipoPilaDinamica;

//Funzioni di creazione e gestione della pila
tipoPilaDinamica creaPila (void); //Crea la pila indicizzata dinamica
void cancellaPila (tipoPilaDinamica *pila); //Cancella la pila indicizzata dinamica
void estendiPila (tipoPilaDinamica *pila); //Estende la pila indicizzata dinamica
void riduciPila (tipoPilaDinamica *pila); //Riduce la pila indicizzata dinamica
bool fullDinamic (const tipoPilaDinamica *pila); //Verifica se la pila è piena
bool isEmptyDinamic (const tipoPilaDinamica *pila); //Verifica se la pila è vuota
bool pushDinamic (tipoPilaDinamica *pila, tipoNodo *elementoDaAggiungere); //Inserisce l'elemento in cima alla pila
tipoNodo popDinamic (tipoPilaDinamica *pila); //Estrae l'elemento in cima alla pila
void stampaPilaIndicizzataDinamica (tipoPilaDinamica *pila); //Stampa la pila indicizzata dinamica


//Lista linkata
typedef struct s_nodo {
    int info;
    struct s_nodo *successivo;
} nodoPilaLinked;

nodoPilaLinked* creaTestaPilaLinked(int elemento); //Crea la testa della lista linkata
bool inizializzaLinkedList(nodoPilaLinked **testa); //Inizializza a una lista linkata vuota
bool isLinkedListEmpty (nodoPilaLinked **testa); //Verifica se la lista è vuota
bool pushPilaLinked(nodoPilaLinked **testa, int elemento); //Inserisce l'elemento in coda
tipoNodo popPilaLinked(nodoPilaLinked **testa); //Cancella l'elemento in coda
void stampaPilaLinked (nodoPilaLinked *testa); //Stampa la lista linkata
