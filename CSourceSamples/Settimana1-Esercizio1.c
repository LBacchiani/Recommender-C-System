//Settimana 1 - Esercizio 1
/* Testo esercizio:
 1. Scrivere un programma C che dichiari una variabile per ogni tipo studiato (usando anche i qualificatori short, long, signed e unsigned), ne stampi il valore e l’occupazione di memoria in byte;
 2. Utilizzare TUTTI gli argomenti della funzione printf() studiati e TUTTE le diverse varianti (modificatore, campoMinimo, precisione, modificatoreLunghezza);
 3. Per ogni chiamata alla funzione printf(), mostrare a video anche il numero di caratteri che quest’ultima ha stampato (Aiuto: la funzione printf() restituisce un valore);
 4. Stampare inoltre il valore minimo e il valore massimo ammissibile per ogni tipo utilizzato.
 */

#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void) {
    
    //Dichiarazione variabili di diversa tipologia con nomi autoesplicativi.
    
    char carattere = 'c';
    unsigned char carattereNonSegnato = 'c';
    int intero = 2540;
    short int interoCorto = -450;
    long int interoLungo = 21400000;
    unsigned int interoNonSegnato = 34000;
    unsigned long int interoLungoNonSegnato = 530456789;
    float numeroFloat = 1.4532;
    double numeroDouble = 0.000453;
    long double numeroDoubleLungo= 15000000000000;
    
    
    /*
     Per ogni variabile (ognuna di diversa tipologia) vengono stampate le seguenti informazioni:
     1. Valore;
     2. Dimensione in byte;
     3. Range ammissibile;
     4. Numero di caratteri stampati dalla funzione printf().
     */
    
    //NOTA: dato che ho usato un Mac, il valore di ritorno di sizeof() è di tipo long unsigned e non int. Non è da considerare warning
    printf("\nSettimana 1 - Esercizio 1\n\n");
    
    //Carattere
    printf("Numero di caratteri stampati: %2d.\n\n", (printf("Carattere. Range ammissibile: da %-4d a %-4d.\nValore: %c - Dimensione in byte: %lu.\n", CHAR_MIN, CHAR_MAX, carattere, sizeof(carattere))));
    
    //Carattere non segnato
    printf("Carattere non segnato. Range ammissibile: da %-4d a %-4d.\nValore: %c - Dimensione in byte: %lu.\n\n", 0, UCHAR_MAX, carattereNonSegnato, sizeof(carattereNonSegnato));
    
    //Intero
    printf("Intero. Range ammissibile: da %-4d a %-4d.\nValore: %d - Dimensione in byte: %lu.\n\n", INT_MIN, INT_MAX, intero, sizeof(intero));
    
    //Intero non segnato
    printf("Intero non segnato. Range ammissibile: da %-4d a %-4u.\nValore: %u - Dimensione in byte: %lu.\n\n", 0, UINT_MAX, interoNonSegnato, sizeof(interoNonSegnato));
    
    //Intero corto
   printf("Intero corto. Range ammissibile: da %-4d a %-4d.\nValore: %d - Dimensione in byte: %lu.\n\n", SHRT_MIN, SHRT_MAX, interoCorto, sizeof(interoCorto));
    
    //Intero lungo
    printf("Intero lungo. Range ammissibile: da %-4ld a %-4ld.\nValore: %ld - Dimensione in byte: %lu.\n\n", LONG_MIN, LONG_MAX, interoLungo, sizeof(interoLungo));
    
    //Intero lungo non segnato
    printf("Intero lungo non segnato. Range ammissibile: da %-4d a %-4ld.\nValore: %lu - Dimensione in byte: %lu.\n\n", 0, LONG_MAX, interoLungoNonSegnato, sizeof(interoLungoNonSegnato));
    
    //Float
    printf("Numero reale (float). Range ammissibile: da %-4e a %-4e.\nValore: %g - Dimensione in byte: %lu.\n\n", FLT_MIN, FLT_MAX, numeroFloat, sizeof(numeroFloat));
    
    //Double
    printf("Intero reale (double). Range ammissibile: da %-4e a %-4e.\nValore: %.6f - Dimensione in byte: %lu.\n\n", DBL_MIN, DBL_MAX, numeroDouble, sizeof(numeroDouble));
    
    //Long double
    printf("Intero reale (double) lungo. Range ammissibile: da %-4Le a %-4Le.\nValore: %-4.2Lf - Dimensione in byte: %lu.\n\n", LDBL_MIN, LDBL_MAX, numeroDoubleLungo, sizeof(numeroDoubleLungo));
    
    return 0;
}
