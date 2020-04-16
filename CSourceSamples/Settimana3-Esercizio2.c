//Settimana3-Esercizio2

#include <stdio.h>
#include <stdbool.h>

int main(void) {
    
    //Dichiarazione e inizializzazione variabili
    bool disponibilitaPersonaUno[31] = {false}; //Inizializzo ogni elemento dell'array a zero
    bool disponibilitaPersonaDue[31] = {false}; //Inizializzo ogni elemento dell'array a zero
    bool flag=true;
    unsigned short int giornoDisponibile=0;
   
    //Messaggio di benvenuto
    printf("\nBenvenuto utente,\nprocedi inserendo le disponibilita' del primo collega, facendo cura di separare i giorni con un invio.\nQuando l'elenco e' terminato inserisci uno 0 (zero).\n");
    
    do {
        printf("\nGiorno del mese disponibile: ");
        scanf("%hu", &giornoDisponibile); //Inserimento disponibilità persona uno
        fflush(stdin);
        if (giornoDisponibile==0) //Se l'utente non intende immettere altre disponibilità.
            flag=false;
        else {
            if (giornoDisponibile>0 && giornoDisponibile<32) //Controllo sull'input errato.
                disponibilitaPersonaUno[giornoDisponibile]=true;
            else
                printf("Errore: inserire numeri esclusivamente tra 1 e 31. Riprovare!\n"); //Nel caso di errore.
        }
    } while (flag); //Ripeti il codice contenuto nel ciclo do-while finche l'utente non inserisce 0.
    
    
    ///Messaggio di inserimento del secondo utente
    printf("\n\nOra inserisci le disponibilita' del secondo collega, facendo cura di separare i giorni con un invio.\nQuando l'elenco e' terminato inserisci uno 0 (zero).\n");
    
    do {
        printf("\nGiorno del mese disponibile: ");
        scanf("%hu", &giornoDisponibile); //Inserimento disponibilità persona due
        fflush(stdin);
        if (giornoDisponibile==0) //Se l'utente non intende immettere altre disponibilità
            flag=true;
        else {
            if (giornoDisponibile>0 && giornoDisponibile<32) //Se l'utente non intende immettere altre disponibilità
                disponibilitaPersonaDue[giornoDisponibile]=true;
            else
                printf("Errore: inserire numeri esclusivamente tra 1 e 31. Riprovare!\n"); //Nel caso di errore
        }
    } while (!(flag)); //Ripeti il codice contenuto nel ciclo do-while finche l'utente non inserisce 0.
    

    //Ricerca elementi in comune
    printf("\nGiorni disponibili di entrambi i colleghi:");
    for (unsigned short int i=1; i<=31; i++) {
        if (disponibilitaPersonaUno[i] && disponibilitaPersonaDue[i]) {
            printf(" %hu", i); //Stampa disponibilità comune
            flag=false;
        }
    }
    
    if (flag) //Messaggio di nessuna disponibilità in comune
        printf(" nessuna disponiblita' in comune!");
    
    printf("\n\nCalendario\n\n\t"); //Stampa calendario grafico
    for (unsigned short int i=1; i<=31; i++) {
        if (!(i%8)) //Ricomincia la settimana
            printf("\n");
        printf("%4hu", i);
    }
    
    printf("\n\nPremi un tasto per uscire..."); //Messaggio di uscita
    getchar();
    return 0;
}
