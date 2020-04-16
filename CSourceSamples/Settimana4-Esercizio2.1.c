//  Settimana4-Esercizio2.1

//Direttive per il pre-processore
#include <stdio.h>
#define lunghezza 31

int main(void) {
    //Dichiarazione variabili
    char input[lunghezza]="default";
    char match[lunghezza]="default";
    unsigned short int numCaratteriTrovati=0;
    unsigned short int lunghezzaMatch=0;
    
    //Chiedo in input le due stringhe
    printf("\nInserisci la prima parola: ");
    fgets(input, 30, stdin);
    printf("\nInserisci la parola di match: ");
    fgets(match, 30, stdin);
    
    //Ottengo lunghezza stringa di match
    for (int z=1; match[z]!='\0'; z++) {
        lunghezzaMatch++;
    }
    
    //Algoritmo
    printf("\nStringa ottenuta: ");
    for (int i=0; input[i]!='\0'; i++) { //Scorro input finchè non è finita
        for (int j=0; match[j]!='\0'; j++) { //Scorro match finchè non è finita
            if (input[i]==match[j]) { //Se le lettere sono uguali
                numCaratteriTrovati++; //Aggiorno il contatore
                if (numCaratteriTrovati==lunghezzaMatch) {//Se vi è corrispondenza scrivo un *
                    printf("*");
                    numCaratteriTrovati=0; //Divengo pronto per cercare un'altra corrispondenza
                }
            } else {
                printf("%c", input[i-numCaratteriTrovati]); //Stampo il carattere iniziale di ricerca
                i -= numCaratteriTrovati; //Aggiorno l'indice
                numCaratteriTrovati=0; //Divengo pronto per cercare un'altra corrispondenza
                break;
            }
            i++; //Passo al prossimo elemento dell'input
        }
    }
    puts("\n\nPremi un tasto per uscire!");
    getchar();
    return 0;
}
