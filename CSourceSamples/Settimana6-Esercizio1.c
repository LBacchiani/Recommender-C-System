//Settimana6-Esercizio1
#include <stdio.h>
#include <stdlib.h>

#define elemento 7

short int *
cerca(const int[], const int, int);

short int *
cerca_vettore_ordinato(const int[], const int, int);

int main(void) {
    const int vettore[] = {3, 5, 7, 2, 8, 7, 9, 0, 10, 8};
    const int vettoreOrdinato[] = {3, 3, 4, 5, 6, 7, 7, 7, 9, 10};
    int dimensione = (sizeof(vettore)/sizeof(vettore[0]));

    //Ricerca e stampa degli indici delle occorrenze nel vettore non ordinato
    printf("\n\nIndici vettore NON ordinato");
    short int *indiciVettoreNonOrdinato = cerca(vettore, dimensione, elemento);
    for (int indice=0; indiciVettoreNonOrdinato[indice]!=-1; indice++)
        printf("\n%d. Indice: %d;", indice+1, indiciVettoreNonOrdinato[indice]);
    printf("\b.");
   
    //Ricerca e stampa degli indici delle occorrenze nel vettore ordinato
    printf("\n\nIndici vettore ordinato");
    short int *indiciVettoreOrdinato = cerca_vettore_ordinato(vettoreOrdinato, dimensione, elemento);
    for (int indice=0; indiciVettoreOrdinato[indice]!=-1; indice++)
        printf("\n%d. Indice: %d;", indice+1, indiciVettoreOrdinato[indice]);
    printf("\b.");
    
    //Libero l'area di memoria
    free(indiciVettoreNonOrdinato);
    free(indiciVettoreOrdinato);
    
    //Messaggio di uscita
    printf("\n\nPremi un tasto per uscire...");
    getchar();
    exit(EXIT_SUCCESS);
}

short int *
cerca(const int vettore[], const int dimensione, int elem) {
    unsigned short int numeroTrovati = 0;
    short int *indiciTrovati = calloc(dimensione, sizeof(short int));
    if (!indiciTrovati)
        exit(EXIT_FAILURE);

    //Controllo sull'occorrenza
    for (int indice=0; indice<dimensione; indice++)
        if (vettore[indice]==elem)
            indiciTrovati[numeroTrovati++] = indice;
    
    //Se non vi fossero riccorrenze
    indiciTrovati[numeroTrovati++]=-1;
    
    return indiciTrovati;
}

short int *
cerca_vettore_ordinato(const int vettore[], const int dimensione, int elem) {
    unsigned short int numeroTrovati = 0;
    short int *indiciTrovati = calloc(dimensione, sizeof(short int));
    if (!indiciTrovati)
        exit(EXIT_FAILURE);
    
    //Controllo sull'occorrenza
    for (int indice=0; indice<dimensione && vettore[indice]<=elem; indice++)
        if (vettore[indice]==elem)
            indiciTrovati[numeroTrovati++] = indice;
    
    //Se non vi fossero riccorrenze
    indiciTrovati[numeroTrovati++]=-1;
    
    return indiciTrovati;
}
