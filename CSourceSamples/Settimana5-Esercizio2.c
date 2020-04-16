//  Settimana5-Esercizio2

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 200
#define E 0xFFFFFF8A
#define A 0XFFFFFF85
#define I 0XFFFFFF8D
#define O 0XFFFFFF95
#define U 0XFFFFFF97

int main(void) {
    //Dichiarazione variabili
    char fraseCanzone[MAX] = {};
    char fraseFinale[MAX] = {};
    int indexFraseFinale=0;

    //Variabili puntatori
    char *pFraseCanzone = fraseCanzone;
    char *pFraseFinale = fraseFinale;

    //a. Viene chiesto all'utente di digitare una frase di una canzone in italiano in cui siano presenti solo lettere, spazi e segni di punteggiatura (non devono quindi essere presenti numeri, ma possono essere presenti le seguenti 5 vocali accentate: à, è, ì, ò, ù
    do {
        printf("\nInserisci frase canzone (solo lettere, spazi e segni di punteggiatura, NON numeri): ");
        fgets(pFraseCanzone, MAX, stdin);
    } while (strcspn(*&pFraseCanzone, "0123456789")!=strlen(*&pFraseCanzone));
    //Ripeti inserimento finchè la frase non contiene un numeri

    //b. Frase visualizzata convertendo tutte le lettere in stampatello maiuscolo;
    printf("\nFrase in maiuscolo: ");
    for (int i=0; &pFraseCanzone[i]<&pFraseCanzone[MAX]; i++) {
        switch(*&pFraseCanzone[i]) {
            case A:
                printf("%c", 183);
                break;
            case E:
                printf("%c", 212);
                break;
            case I:
                printf("%c", 222);
                break;
            case O:
                printf("%c", 227);
                break;
            case U:
                printf("%c", 235);
                break;
            default:
                printf("%c", toupper(*&pFraseCanzone[i]));
                break;
        }
    }
   
    //c. Rimozione spazi e segni di punteggiatura;
    for (int i=0; &pFraseCanzone[i]<&pFraseCanzone[MAX]; i++) {
        if (isalpha(*&pFraseCanzone[i])) { //Se sono caratteri dell'alfabeto inserisco nella nuova stringa;
                *&pFraseFinale[indexFraseFinale]=*&fraseCanzone[i];
                indexFraseFinale++;
        }
    }
    
    //d. Ri-visualizzazione frase a monitor.
    printf("\nFrase senza punteggiatura e spazi: %s", *&pFraseFinale);

    //Messaggio di uscita
    puts("\nPremi un tasto per uscire...");
    getchar();
    return 0;
}
