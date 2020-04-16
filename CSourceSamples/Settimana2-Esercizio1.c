//Settimana 2 - Esercizio 1

#include <stdio.h>

void voloSuccessivo(unsigned short int oreArrivoAereoporto, unsigned short int minutiArrivoAereoporto, unsigned short int tabellaOre[], unsigned short int tabellaMinuti[], unsigned short int i) { //Funzione che stampa il volo successivo all'arivo in aereoporto
    
    unsigned short int flag=0; //Dichiarazione variabili
    
    for (i=0; i<16; i+=2) { //Scorre i due array (quello delle ore e quello dei minuti)
        if (oreArrivoAereoporto<tabellaOre[i]) { //Se l'ora di arrivo all'aereoporto è inferiore all'ora di partenza del volo
            flag=1;
        } else if (oreArrivoAereoporto==tabellaOre[i]) { //Se l'ora di arrivo all'aereoporto è la stessa dell'ora di partenza del volo
            flag=2;
        }
        switch (flag) {
            case 1: //Stampo gli orari senza senza effettuare ulteriori controlli
                printf("\n\nIl primo volo disponibile parte alle %.2hu:%.2hu ", tabellaOre[i], tabellaMinuti[i]); //Visualizza l'orario di partenza
                printf("e arriva alle %.2hu:", tabellaOre[++i]); //Visualizza l'ora di arrivo
                printf("%.2hu.", tabellaMinuti[i]); //Visualizza i minuti di arrivo
                break;
            case 2: //Controllo se i minuti dell'arrivo all'aereoporto siano inferiori ai minuti di partenza del volo
                if (minutiArrivoAereoporto<=tabellaMinuti[i]) {
                    printf("\n\nIl primo volo disponibile parte alle %.2hu:%.2hu ", tabellaOre[i], tabellaMinuti[i]); //Visualizza l'orario di partenza
                    printf("e arriva alle %.2hu:", tabellaOre[++i]); //Visualizza l'ora di arrivo
                    printf("%.2hu.", tabellaMinuti[i]); //Visualizza i minuti di arrivo
                } else {
                    flag=0; //Continua la ricerca con il volo successivo
                }
                break;
        }
        if (flag!=0) //Esce dal ciclo for nel caso sia stato trovato l'orario desiderato
            return;
    }
}
    
int main(void){
    //Dichiarazione variabili
    unsigned short int tabellaOre[16];
    unsigned short int tabellaMinuti[16];
    unsigned short int stampaTabella=0;
    unsigned short int i=0;
    unsigned short int oreArrivoAereoporto=0;
    unsigned short int minutiArrivoAereoporto=0;
    //Creazione tabella orari
    tabellaOre[0]=8;
    tabellaOre[1]=10;
    tabellaOre[2]=9;
    tabellaOre[3]=11;
    tabellaOre[4]=11;
    tabellaOre[5]=13;
    tabellaOre[6]=12;
    tabellaOre[7]=15;
    tabellaOre[8]=14;
    tabellaOre[9]=16;
    tabellaOre[10]=15;
    tabellaOre[11]=17;
    tabellaOre[12]=19;
    tabellaOre[13]=19;
    tabellaOre[14]=21;
    tabellaOre[15]=23;
    tabellaMinuti[0]=0;
    tabellaMinuti[1]=16;
    tabellaMinuti[2]=43;
    tabellaMinuti[3]=52;
    tabellaMinuti[4]=19;
    tabellaMinuti[5]=31;
    tabellaMinuti[6]=47;
    tabellaMinuti[7]=0;
    tabellaMinuti[8]=0;
    tabellaMinuti[9]=8;
    tabellaMinuti[10]=45;
    tabellaMinuti[11]=55;
    tabellaMinuti[12]=0;
    tabellaMinuti[13]=20;
    tabellaMinuti[14]=45;
    tabellaMinuti[15]=58;

    printf("\n\n---------------------------------\n");  //Stampa tabella degli orari
    printf("|\tSettimana 2 - Esercizio 1\t|\n");
    printf("---------------------------------\n");
    printf("|\tPartenze\t\tArrivi\t\t|\n");
    printf("---------------------------------\n");
    for (stampaTabella=0; stampaTabella<8; stampaTabella++) {
        printf("|\t%.2hu:", tabellaOre[i]);
        printf("%.2hu\t\t\t", tabellaMinuti[i]);
        printf("%.2hu:", tabellaOre[++i]);
        printf("%.2hu\t\t|\n", tabellaMinuti[i]);
        ++i;
    }
    
    printf("---------------------------------"); //Chisura della tabella
    printf("\n\nInserisci l'orario di arrivo all'aereoporto (hh:mm): "); //Titolo esercizio
    scanf("%hu:%hu", &oreArrivoAereoporto, &minutiArrivoAereoporto); //Inserimento orario di arrivo all'aereoporto
    voloSuccessivo(oreArrivoAereoporto, minutiArrivoAereoporto, tabellaOre, tabellaMinuti, i);  //Chiamata alla funzione
    printf(" Premi un tasto per uscire..."); //Messaggio di uscita dal programma
    getchar(); //Richiesta di un carattere da parte dell'utente
    return 0;
}
