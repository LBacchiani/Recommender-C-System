//Settimana4-Esercizio2

#include <stdio.h>
#include <string.h>

int main(void) {
    
    //Dichiarazione variabili
    char fraseInput[31];
    char fraseMatch[31];
    char stringaFinale[30];
    char substring[30];
    unsigned short int lunghezzaInput=0, lunghezzaMatch=0;
    unsigned short int indexFraseInput=0, indexFraseFinale=0;
    
    //Chiedo in input le due frasi
    printf("Inserire frase da analizzare (senza spazi): ");
    scanf("%30s", fraseInput);
    printf("Inserire frase di match (senza spazi): ");
    scanf("%30s", fraseMatch);
    
    lunghezzaInput = strlen(fraseInput); //Calcolo la lunghezza della frase di input
    lunghezzaMatch = strlen(fraseMatch); //Calcolo la lunghezza della frase di match
    
    //Cicla finchè il contatore è minore della lunghezza della prima di input
    while(indexFraseInput<lunghezzaInput){
        //Inserisco nella substring dall'indirizzo dell'indice della frase di input a indirizzo+lunghezzaMatch
        strncpy(substring,&fraseInput[indexFraseInput],lunghezzaMatch);
        
        //Aggiungo carattere di fine stringa
        substring[lunghezzaMatch]='\0';
        
        if (strcmp(substring,fraseMatch) == 0){ //Se la substring e il match sono uguali
            stringaFinale[indexFraseFinale]='*'; //Aggiungo nella nuova stringa un *
            indexFraseInput += lunghezzaMatch; //Passo nella frase1 al primo carattere dopo l'occorrenza trovata
        } else { //Se non sono uguali
            stringaFinale[indexFraseFinale] = fraseInput[indexFraseInput]; //Aggiugno il carattere nella stringa finale
            indexFraseInput++; //Aggiorno l'indice della frase di input
        }
        indexFraseFinale++;
    }
    
    stringaFinale[indexFraseFinale]='\0'; //Aggiugno carattere di fine stringa
    printf("\nFrase ottenuta: %s", stringaFinale); //Stampo la nuova stringa ottenuta
    
    //Messaggio di uscita
    printf("\n\nPremi un tasto per uscire...");
    getchar();
    return 0;
}
