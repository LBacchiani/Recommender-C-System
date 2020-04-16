//Settimana2-Esercizio2

#include <stdio.h>

int main(void) {

    //Dichiarazione variabili
    int numStudenti;
    int scelta=0;
    int i=1;
    float voto = 0.0;
    float sommaVoti = 0.0;
    float mediaVotiClasse = 0.0;
 
    //Titolo esercizio
    printf("Settimana 2 - Esercizio 2");
    
    //Inserimento numero degli studenti
    printf("\n\nInserisci un numero di studenti: ");
    scanf("%d", &numStudenti);

    do {
        //Inserimento voti
        printf("\n\nVuoi inserire i voti con un ciclo for (1) o un ciclo while(2)? ");
        scanf("%d", &scelta);

        //In base alla tipologia di ciclo scelta
        switch(scelta) {
            case 1:
                //Calcolo della media con ciclo for
                for (i=1; i<=numStudenti; i++) {
                    printf("\nInserisci il voto per lo studente numero %d: ", i);
                    scanf("%f", &voto);
                    sommaVoti += voto;
                }
                break;
            case 2:
                //Calcolo della media con ciclo while
                while (i<=numStudenti)  {
                    printf("\nInserisci il voto per lo studente numero %d: ", i);
                    scanf("%f", &voto);
                    sommaVoti += voto;
                    i++;
                }
                break;
            default:
                printf("\nErrore nella scelta!");
            }
    } while (scelta!=1 && scelta!=2); //Ripeti ciclo finche la variabile scelta è diversa da '1' e '2'

    //Calcolo della media
    mediaVotiClasse = sommaVoti/numStudenti;

    //Stampa della media
    printf("\nLa media dei voti della classe e' di %.2f --> ", mediaVotiClasse);

    //Stampa del commento relativo alla media
    if (mediaVotiClasse<6)
        printf("Media INSUFFICENTE!");
    else if (mediaVotiClasse>=6 && mediaVotiClasse<7)
        printf("Media SUFFICENTE!");
    else if (mediaVotiClasse>=7 && mediaVotiClasse<8)
        printf("Media DISCRETA!");
    else if (mediaVotiClasse>=8 && mediaVotiClasse<9)
        printf("Media BUONA!");
    else if (mediaVotiClasse>=9 && mediaVotiClasse<=10)
        printf("Media OTTIMA!");
    else if(mediaVotiClasse<0 && mediaVotiClasse>10)  //Media invalida
        printf("Errore nel calcolo della media!");
    
    //Messaggio di chiusura del programma
    printf("\n\n\nPremi un tasto per uscire...");
    getchar();
    return 0;
}
