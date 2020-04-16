//  Esercizio1-Settimana4

//Direttive per il preprocessore (la definizione di macro non occupa posto in memoria)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define righe 10
#define colonne 10
#define numeroDirezioni 4
#define caratterePartenza 'A'

int main(void) {
    //Dichiarazioni variabili e array
    unsigned char matrice[righe][colonne];
    unsigned char carattere=caratterePartenza;
    unsigned short int numeroCasuale=0;
    unsigned short int rigaAttuale=0;
    unsigned short int colonnaAttuale=0;
    bool direzioneConsentita[numeroDirezioni] = {true}; //Imposta 'false' se non è accessibile. Su: [0] - Giu: [1] - Destra: [2] - Sinistra: [3]
    
    //Reset seme
    srand((unsigned) time(NULL));
    
    //Inizializzazione matrice
    for (int riga=0; riga<righe; riga++) {
        for (int colonna=0; colonna<colonne; colonna++)
            matrice[riga][colonna] = '.';
    }

    /*Applicazione algoritmo di cambiamento alla matrice
    Esegui ciclo finchè almeno un'opzione di spostamento cella è disponibile*/
    while(direzioneConsentita[0] || direzioneConsentita[1] || direzioneConsentita[2] || direzioneConsentita[3]) {
        //printf("\nNumero di volte di ciclo: %d", ++i);
        numeroCasuale = rand() % 4; //Generazione numero casuale da 0 a 3
        if (carattere>90)//Se si arriva alla 'Z' si esce dal ciclo
            break;
        switch (numeroCasuale) {
            case 0: //Mi sposto su di una riga
                rigaAttuale -= 1;
                /*Debug
                printf("\nSu - Sto valutando la cella [%d][%d]", rigaAttuale, colonnaAttuale);
                getchar();*/
                
                //Se è possibile visitare la cella
                if (rigaAttuale>=0 && rigaAttuale<righe && matrice[rigaAttuale][colonnaAttuale]=='.') {
                        matrice[rigaAttuale][colonnaAttuale]=carattere; //Imposto il carattere
                        carattere++; //Vado al carattere successivo
                        direzioneConsentita[0]=true; //Si può andare su
                        direzioneConsentita[1]=true; //Si può andare giu
                        direzioneConsentita[2]=true; //Si può andare a destra
                        direzioneConsentita[3]=true; //Si può andare a sinistra
                        /*Debug
                         printf(" - Valore cella attuale [%d][%d]: %c", rigaAttuale, colonnaAttuale, matrice[rigaAttuale][colonnaAttuale]);
                         getchar();*/
                } else {
                        rigaAttuale += 1; //Ripristino riga
                        direzioneConsentita[0]=false; //Non si può andare su
                        /*Debug
                        printf(" - Impossibile andare nella cella. Posizione attuale: [%d][%d], direzioneConsentita[%d]=%s", rigaAttuale, colonnaAttuale, 1, direzioneConsentita[1]?"true":"false");
                        getchar();*/
                }
                break;
            case 1: //Mi sposto giù di una riga
                rigaAttuale += 1;
                /*Debug
                 printf("\nSu - Sto valutando la cella [%d][%d]", rigaAttuale, colonnaAttuale);
                 getchar();*/
                
                //Se è possibile visitare la cella
                if (rigaAttuale>=0 && rigaAttuale<righe && matrice[rigaAttuale][colonnaAttuale]=='.') {
                    matrice[rigaAttuale][colonnaAttuale]=carattere; //Imposto il carattere
                    carattere++; //Vado al carattere successivo
                    direzioneConsentita[0]=true; //Si può andare su
                    direzioneConsentita[1]=true; //Si può andare giu
                    direzioneConsentita[2]=true; //Si può andare a destra
                    direzioneConsentita[3]=true; //Si può andare a sinistra
                    /*Debug
                    printf(" - Valore cella attuale [%d][%d]: %c", rigaAttuale, colonnaAttuale, matrice[rigaAttuale][colonnaAttuale]);
                    getchar();*/
                } else {
                    rigaAttuale -= 1; //Ripristino riga
                    direzioneConsentita[1]=false; //Non si può andare giù
                    /*Debug
                    printf(" - Impossibile andare nella cella. Posizione attuale: [%d][%d], direzioneConsentita[%d]=%s", rigaAttuale, colonnaAttuale, 1, direzioneConsentita[1]?"true":"false");
                    getchar();*/
                }
                break;
            case 2: //Mi sposto a destra di una colonna
                colonnaAttuale += 1;
                /*Debug
                 printf("\nSu - Sto valutando la cella [%d][%d]", rigaAttuale, colonnaAttuale);
                 getchar();*/
                
                //Se è possibile visitare la cella
                if (colonnaAttuale>=0 && colonnaAttuale<colonne && matrice[rigaAttuale][colonnaAttuale]=='.') {
                    matrice[rigaAttuale][colonnaAttuale]=carattere; //Imposto il carattere
                    carattere++; //Vado al carattere successivo
                    direzioneConsentita[0]=true; //Si può andare su
                    direzioneConsentita[1]=true; //Si può andare giu
                    direzioneConsentita[2]=true; //Si può andare a destra
                    direzioneConsentita[3]=true; //Si può andare a sinistra
                    /*Debug
                    printf(" - Valore cella attuale [%d][%d]: %c", rigaAttuale, colonnaAttuale, matrice[rigaAttuale [colonnaAttuale]);
                    getchar();*/
                } else {
                    colonnaAttuale -= 1; //Ripristino colonna
                    direzioneConsentita[2]=false; //Non si può andare a destra
                    /*Debug
                    printf(" - Impossibile andare nella cella. Posizione attuale: [%d][%d], direzioneConsentita[%d]=%s", rigaAttuale, colonnaAttuale, 1, direzioneConsentita[1]?"true":"false");
                    getchar();*/
                }
                break;
                
            case 3: //Mi sposto a sinistra di una colonna
                colonnaAttuale -= 1;
                /*Debug
                 printf("\nSu - Sto valutando la cella [%d][%d]", rigaAttuale, colonnaAttuale);
                 getchar();*/
                
                //Se è possibile visitare la cella
                if (colonnaAttuale>=0 && colonnaAttuale<colonne && matrice[rigaAttuale][colonnaAttuale]=='.') {
                    matrice[rigaAttuale][colonnaAttuale]=carattere; //Imposto il carattere
                    carattere++; //Vado al carattere successivo
                    direzioneConsentita[0]=true; //Si può andare su
                    direzioneConsentita[1]=true; //Si può andare giu
                    direzioneConsentita[2]=true; //Si può andare a destra
                    direzioneConsentita[3]=true; //Si può andare a sinistra
                    /*Debug
                    printf(" - Valore cella attuale [%d][%d]: %c", rigaAttuale, colonnaAttuale, matrice[rigaAttuale][colonnaAttuale]);
                    getchar();*/
                } else {
                    colonnaAttuale += 1; //Ripristino colonna
                    direzioneConsentita[3]=false; //Non si può andare a sinistra
                    /*Debug
                    printf(" - Impossibile andare nella cella. Posizione attuale: [%d][%d], direzioneConsentita[%d]=%s", rigaAttuale, colonnaAttuale, 1, direzioneConsentita[1]?"true":"false");
                    getchar();*/
                }
                break;
        }
    }
    
    if (!direzioneConsentita[0] && !direzioneConsentita[1] && !direzioneConsentita[2] && !direzioneConsentita[3]) {
        if (carattere=='A')
            printf("Matrice bloccata in partenza!\n");
        else
            printf("Ho raggiunto la lettera %c!\n", --carattere);
    }
    
    if (--carattere=='Z')
            printf("La matrice è arrivata alla lettera 'Z'!\n");
    
    
    //Stampa matrice
    printf("\nMatrice finale\n");
    for (int i=0; i<righe; i++) {
        printf("\n");
        for (int j=0; j<colonne; j++)
            printf(" %c ", matrice[i][j]);
    }
    
    //Messaggio di uscita
    printf("\n\nPremi un tasto per uscire...");
    getchar();

    return 0;
}

