//  Settimana9-Esercizio1

#include "liste.h"

int main(void) {
    tipoNodo variabile=5;
    tipoNodo variabile1=3;
    
    //Lista statica
    tipoLista listaStatica;
    listaStatica.ultimoElementoLista=0;
    printf("Dopo creazione lista indicizzata statica\n\n");
    stampaListaIndicizzataStatica(&listaStatica);
    
    inserisciInTesta(&listaStatica, &variabile);
    printf("Dopo inserimento in testa (lista indicizzata statica)\n\n");
    stampaListaIndicizzataStatica(&listaStatica);
    
    inserisciInCoda(&listaStatica, &variabile1);
    printf("Dopo inserimento in coda (lista indicizzata statica)\n\n");
    stampaListaIndicizzataStatica(&listaStatica);
    
    inserisciDopoElemento(&listaStatica, 5, 20);
    printf("Dopo inserimento dopo un elemento (lista indicizzata statica)\n\n");
    stampaListaIndicizzataStatica(&listaStatica);
    
    cancellaDallaTesta(&listaStatica);
    printf("Dopo eliminazione in testa (lista indicizzata statica)\n\n");
    stampaListaIndicizzataStatica(&listaStatica);
    
    cancellaDallaCoda(&listaStatica);
    printf("Dopo eliminazione in coda (lista indicizzata statica)\n\n");
    stampaListaIndicizzataStatica(&listaStatica);
    
    cancellaPrimaOccorrenza(&listaStatica, &variabile1);
    printf("Dopo eliminazione prima occorrenza (lista indicizzata statica)\n\n");
    stampaListaIndicizzataStatica(&listaStatica);

    //Lista indicizzata dinamica
    printf("Dopo creazione lista indicizzata dinamica\n\n");
    tipoListaDinamica listaDinamica = creaLista();
    listaDinamica.ultimoElementoLista=0;
    stampaListaIndicizzataDinamica(&listaDinamica);
    
    inserisciInTestaDinamic(&listaDinamica, &variabile1);
    printf("Dopo inserimento in testa (lista indicizzata dinamica)\n\n");
    stampaListaIndicizzataDinamica(&listaDinamica);
    
    inserisciInCodaDinamic(&listaDinamica, &variabile);
    printf("Dopo inserimento in coda (lista indicizzata dinamica)\n\n");
    stampaListaIndicizzataDinamica(&listaDinamica);
    
    inserisciDopoElementoDinamic(&listaDinamica, 5, 20);
    printf("Dopo inserimento dopo un elemento (lista indicizzata dinamica)\n\n");
    stampaListaIndicizzataDinamica(&listaDinamica);
    
    cancellaDallaTestaDinamic(&listaDinamica);
    printf("Dopo eliminazione in testa (lista indicizzata dinamica)\n\n");
    stampaListaIndicizzataDinamica(&listaDinamica);
    
    cancellaDallaCodaDinamic(&listaDinamica);
    printf("Dopo eliminazione in coda (lista indicizzata dinamica)\n\n");
    stampaListaIndicizzataDinamica(&listaDinamica);
    
    cancellaPrimaOccorrenzaDinamic(&listaDinamica, &variabile1);
    printf("Dopo eliminazione prima occorrenza (lista indicizzata dinamica)\n\n");
    stampaListaIndicizzataDinamica(&listaDinamica);
    
    printf("Dopo estensione (lista indicizzata dinamica)\n\n");
    estendiLista(&listaDinamica);
    stampaListaIndicizzataDinamica(&listaDinamica);
    
    printf("Dopo riduzione (lista indicizzata dinamica)\n\n");
    riduciLista(&listaDinamica);
    stampaListaIndicizzataDinamica(&listaDinamica);
    
    //Lista linkata
    printf("Dopo creazione lista linkata con primo elemento\n\n");
    nodoLinkedList *testa = creaTestaLinkedList(2);
    stampaLinkedList(testa);
    
    inserisciInTestaLinkedList(&testa, 100);
    printf("Dopo inserimento in testa (lista linkata)\n\n");
    stampaLinkedList(testa);
    
    inserisciInCodaLinkedList(&testa, 10);
    printf("Dopo inserimento in coda (lista linkata)\n\n");
    stampaLinkedList(testa);
    
    inserisciDopoElementoLinkedList(&testa, 10, 50);
    printf("Dopo inserimento dopo un elemento (lista linkata)\n\n");
    stampaLinkedList(testa);
    
    cancellaDallaTestaLinkedList(&testa);
    printf("Dopo eliminazione in testa (lista linkata)\n\n");
    stampaLinkedList(testa);
    
    cancellaDallaCodaLinkedList(&testa);
    printf("Dopo eliminazione in coda (lista linkata)\n\n");
    stampaLinkedList(testa);
    
    cancellaPrimaOccorrenzaLinkedList(&testa, 10);
    printf("Dopo eliminazione prima occorrenza (lista linkata)\n\n");
    stampaLinkedList(testa);
    
    exit(EXIT_SUCCESS);
}
