//  Settimana9-Esercizio2

#include "myLbrary.h"

int main(void) {
    printf("Stai per inserire il primo libro della lista!\n");
    nodoLinkedList *testa = creaTestaLinkedList(*creaNuovoLibro());
    if (testa!=NULL)
        printf("Lista creata correttamente!\n\n");
    else
        exit(EXIT_FAILURE);
    for (;;) {
        switch (menu()){
            case 1:
                inserisciInCodaLinkedList(testa, *creaNuovoLibro());
                break;
            case 2:
                cancellaPrimaOccorrenzaLinkedList(&testa);
                break;
            case 3:
                stampaLinkedList(testa);
                break;
            case 4:
                stampaValutazione(testa);
                break;
            case 5:
                exit(EXIT_SUCCESS);
            default:
                printf("Errore, numero non presente!");
        }
    }
    
    
}
