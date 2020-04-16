//  Settimana7-Esercizio1

#include <stdio.h>
#include <stdlib.h>
#define MAX 10

//Prototipi delle funzioni
unsigned long long fattorialeNumeroConTabulazione (int numeroInput, int nTab);
void tabulazione(int nTab, int partiDa);

int main(void) {
    int numero=0;
    do {
        printf("\nL'utente inserisca un valore (massimo %d): ", MAX);
        scanf("%d!", &numero); //Inserimento numero di cui calcolare il fattoriale
    } while (numero<0 || numero>MAX); //Controllo sull'input
    printf("\n\nRiassumendo, il fattoriale di %d è: %llu.\n\nPremi un tasto per uscire...", numero, fattorialeNumeroConTabulazione(numero, 0));
    getchar();
    exit(EXIT_SUCCESS);
}

unsigned long long fattorialeNumeroConTabulazione (int numeroInput, int nTab) { //Funzione ricorsiva per il fattoriale
    tabulazione(nTab++, 0);
    if (numeroInput==0 || numeroInput==1) { //Punto di uscita della ricorsione
        printf("Sapendo che il fattoriale di %d è %d, calcolo gli altri;", numeroInput, 1);
        return 1;
    }
    printf("Non sapendo il fattoriale di %d, calcolo il fattoriale di %d;", numeroInput, numeroInput-1); //Stampa chiamata ricorsiva
    numeroInput *= fattorialeNumeroConTabulazione(numeroInput-1, nTab); //Chiamata ricorsiva
    tabulazione(nTab++, 1);
    printf("Ricalcolo fattoriale precedente: %d;", numeroInput); //Stampa a ritroso
    return numeroInput;
}

void tabulazione(int nTab, int partiDa) { //Inserimento tabulazione per ricorsione
    putchar('\n');
    for (int index = partiDa; index < nTab; index++)
        putchar('\t');
}
