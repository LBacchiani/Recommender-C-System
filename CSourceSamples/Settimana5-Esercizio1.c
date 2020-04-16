//  Settimana5-Esercizio1

#include <stdio.h>
#define MAX 5

int main(void) {
    //Dichiarazione variabili
    int intero = 0;
    float conVirgola = 0.0;
    double conVirgolaPreciso = 0.0;
    char carattere;
    int vettoreInteri[MAX] = {10, 20, 30, 40, 50};
    
     //Variabili puntatori
    int *pIntero = &intero;
    float *pConVirgola = &conVirgola;
    double *pConVirgolaPreciso = &conVirgolaPreciso;
    char *pCarattere = &carattere;
    int *pVettoreInteri = vettoreInteri;
    
    //Inserimento valori
    printf("\nInserisci valori variabili.");
    printf("\n\nInserisci un valore intero: ");
    scanf("%d", &intero);
    printf("Inserisci un valore float: ");
    scanf("%f", &conVirgola);
    printf("Inserisci un valore double: ");
    scanf("%lf", &conVirgolaPreciso);
    printf("Inserisci un carattere: ");
    scanf(" %c", &carattere); //ci vuole uno spazio per non consideraro il tasto 'INVIO' precedente
    
    //Stampa valori delle variabili (accesso diretto e indiretto)
    printf("\n\nValori delle variabili (accesso diretto)\nIntero: %d\nFloat: %.3f\nDouble: %.3lf\nCarattere: %c\nVettore:", intero, conVirgola, conVirgolaPreciso, carattere);
    for (int i=0; i<MAX; i++) {
        printf("\nValore %d: %d", i, vettoreInteri[i]);
    }
    printf("\n\nValori delle variabili (accesso indiretto)\nIntero: %d\nFloat: %.3f\nDouble: %.3lf\nCarattere: %c", *pIntero, *pConVirgola, *pConVirgolaPreciso, *pCarattere);
    for(int i=0; *&pVettoreInteri[i]<*&pVettoreInteri[MAX]; i++) {
        printf("\nValore %d: %d", i, *&pVettoreInteri[i]);
    }
    
    //Stampa indirizzi di memoria delle variabili (accesso diretto e indiretto)
    printf("\n\nIndirizzi di memoria delle variabili (accesso diretto)\nIntero: %p\nFloat: %p\nDouble: %p\nCarattere: %p\nVettore: %p\n", &intero, &conVirgola, &conVirgolaPreciso, &carattere, vettoreInteri);
    printf("\n\nIndirizzi di memoria delle variabili (accesso indiretto)\nIntero: %p\nFloat: %p\nDouble: %p\nCarattere: %p\nVettore: %p", &*pIntero, &*pConVirgola, &*pConVirgolaPreciso, &*pCarattere, &*pVettoreInteri);
    
    //Stampa indirizzi di memoria dei puntatori
    printf("\n\nIndirizzi di memoria dei puntatori\npIntero: %p\npFloat: %p\npDouble: %p\npCarattere: %p\npVettoreInteri: %p", &pIntero, &pConVirgola, &pConVirgolaPreciso, &pCarattere, &pVettoreInteri);
    
    //Messaggio di uscita
    puts("\n\nPremi un tasto per uscire...");
    getchar();
    return 0;
}
