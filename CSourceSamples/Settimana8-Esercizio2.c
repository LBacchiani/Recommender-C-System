//  Settimana8-Esercizio2 - v1.0

//Direttive preprocessore
#ifdef _WIN32
    #include <conio.h>
    #define pulisci system("cls");
#endif

#ifdef linux
    #include <curses.h>
    #define pulisci() system("clear");
#endif

#ifdef __APPLE__
    #include <curses.h>
    #define pulisci() system("clear");
#endif

//Direttive preprocessore
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define STR_LEN 50
#define NUM_ESAMI 3

//Definizione struttura studente
typedef struct s_studente {
    char nomeCognome[STR_LEN], nMatricola[STR_LEN];
    unsigned short int annoImmatricolazione;
    struct {
        char nomeInsegnamento[STR_LEN];
        unsigned short int voto;
    } pianoDiStudi[NUM_ESAMI];
} studente;

//Scope a livello di file sorgente
static int numStudentiInseriti=0;
static int dimensioneCorrente=10;

//Prototipi delle funzioni
short int menu (void);
bool aggiungiStudente (studente*);
bool stampaDatiMatricola (studente*);
bool stampaPianoDiStudi (studente*, int);
bool modificaPianoDiStudi (studente*);
bool numeroMatricolaTrovata (studente* , char*);

int main(void) {
    //Dichiarazione variabili
    studente *arrayStudenti=NULL;
    if ((arrayStudenti=malloc(dimensioneCorrente*sizeof(studente)))==NULL) //Allocazione dinamica vettore di strutture
        exit(EXIT_FAILURE);
    int scelta=0;
    
    for (;;) {
        scelta=menu();
        switch (scelta) { //Switch sulla scelta
            case 1:
                aggiungiStudente(arrayStudenti);
                break;
            case 2:
                stampaDatiMatricola(arrayStudenti);
                break;
            case 3:
                modificaPianoDiStudi(arrayStudenti);
                break;
            case 4:
                printf("\nPremi invio per uscire...\n\n");
                getchar();
                getchar();
                exit(EXIT_SUCCESS);
            default:
                printf("\n\nErrore, scelta non valida!");
        }
    }
}

short int menu (void) { //Funzione che stampa a video il menu, Restituisce il numero inserito dall'utente.
    short int scelta=4;
    do {
        if (scelta<1 || scelta>4)
            printf("\nErrore, scegliere numero corrispondente a una delle voci presenti!");
        printf("\n\nSeleziona scelta successiva:\n\n1. Aggiungi studente;\n"
               "2. Stampa informazioni studente;\n"
               "3. Modifica informazioni del piano di studi;\n"
               "4. Esci dal programma."
               "\n\nScelta (numero): ");
        scanf("%hi", &scelta);
    } while (scelta<1 || scelta>4); //Controllo sull'input
    getchar();
    return scelta;
}

bool aggiungiStudente (studente* arrayStudenti) { //Aggiunta studente. Ritorna vero/falso (operazione riuscita o no).
    
    char matricola[STR_LEN];
    studente *tempArray=NULL;
    printf("\nAggiungi matricola: "); //Inserimento matricola
    fgets(matricola, sizeof(matricola), stdin);
    
    if (numeroMatricolaTrovata(arrayStudenti, matricola)) { //Se è gia presente la matricola
        printf("\n\nErrore, matricola già presente!\n");
        return false;
    }
    if (numStudentiInseriti==dimensioneCorrente) { //Se il vettore è pieno, riallocazione della memoria
        dimensioneCorrente *= 2;
        tempArray = (studente*) realloc(arrayStudenti, dimensioneCorrente*sizeof(studente));
        if (tempArray!=NULL)
            arrayStudenti=tempArray;
        else
            return false;
        printf("\nVettore pieno, dopo la riallocazione di memoria il vettore ha dimensione %d!\n", dimensioneCorrente);
    }
    
    //Inserimento dati studente
    strcpy(arrayStudenti[numStudentiInseriti].nMatricola, matricola);
    printf("\nInserisci nome e cognome: ");
    fgets(arrayStudenti[numStudentiInseriti].nomeCognome, STR_LEN, stdin);
    printf("\nInserisci anno di immatricolazione: ");
    scanf("%hu", &arrayStudenti[numStudentiInseriti].annoImmatricolazione);
    printf("\nPer aggiungere insegnamenti e voti clicca su '3'.");
    getchar();
    
    //Eliminazione carattere newline
    arrayStudenti[numStudentiInseriti].nomeCognome[strcspn(arrayStudenti[numStudentiInseriti].nomeCognome, "\n")] = 0;
    
    //Inizializzazione insegnamenti
    for (int i=0; i<NUM_ESAMI; i++)
        strcpy(arrayStudenti[numStudentiInseriti].pianoDiStudi[i].nomeInsegnamento, "N/a");
    numStudentiInseriti++;
    return true;
}

bool numeroMatricolaTrovata (studente* arrayStudenti, char* matricola) { //Restituisce vero/falso (matricola trovata o no).
    for (int i=0; i<numStudentiInseriti; i++)
        if ( strcmp (arrayStudenti[i].nMatricola, matricola)==0) //Se matricola trovata
            return true;
    return false;
}

bool stampaDatiMatricola(studente* arrayStudenti) { //Stampa i dati relativi alla matricola richiesta. Restituisce vero/falso (operazione riuscita o no).
    char matricola[STR_LEN];
    printf("\nInserisci numero matricola da ricercare: ");
    fgets(matricola, sizeof(matricola), stdin);
    
    for (int i=0; i<numStudentiInseriti; i++) {
        if (strcmp(arrayStudenti[i].nMatricola, matricola)==0) { //Se matricola trovata
            printf("\nRisultati ricerca\nNome e cognome: %s\nAnno di immatricolazione: %d\nNumero di matricola: %s\nPiano di studi:", arrayStudenti[i].nomeCognome, arrayStudenti[i].annoImmatricolazione, arrayStudenti[i].nMatricola);
            stampaPianoDiStudi(arrayStudenti, i);
            printf("\n\nPremi invio per continuare...");
            getchar();
            return true;
        }
    }
    printf("\nMatricola non trovata!");
    return false;
}

bool stampaPianoDiStudi (studente *arrayStudenti, int indice) { //Stampa voti del piano di studi. Restituisce true/false (operazione riuscita o no).
    for (int i=0; i<NUM_ESAMI; i++)
        printf("\nInsegnamento: %s   -   Voto: %d", arrayStudenti[indice].pianoDiStudi[i].nomeInsegnamento,
               arrayStudenti[indice].pianoDiStudi[i].voto);
    return true;
}

bool modificaPianoDiStudi (studente* arrayStudenti) { //Modifica il piano degli studi per lo studente
    char matricola[STR_LEN];
    printf("\nInserisci numero matricola di cui aggiungere un insegnamento/voto: ");
    fgets(matricola, sizeof(matricola), stdin);
    for (int i=0; i<numStudentiInseriti; i++)  //Scorro ogni studente
        if (strcmp(arrayStudenti[i].nMatricola, matricola)==0) { //Se matricola trovata
            printf("\nInserimento per %s - Matricola: %s", arrayStudenti[i].nomeCognome, arrayStudenti[i].nMatricola);
            for (int indiceInsegnamento=0; indiceInsegnamento<NUM_ESAMI; indiceInsegnamento++) {
                printf("\nInserisci nome insegnamento: ");
                fgets(arrayStudenti[i].pianoDiStudi[indiceInsegnamento].nomeInsegnamento, STR_LEN, stdin);
                
               /*Eliminazione carattere newline*/ arrayStudenti[i].pianoDiStudi[indiceInsegnamento].nomeInsegnamento[strcspn(arrayStudenti[i].pianoDiStudi[indiceInsegnamento].nomeInsegnamento, "\n")] = 0;
                
                printf("\nInserisci voto per '%s': ", arrayStudenti[i].pianoDiStudi[indiceInsegnamento].nomeInsegnamento);
                scanf("%hu", &arrayStudenti[i].pianoDiStudi[indiceInsegnamento].voto);
                getchar();
            }
            return true;
        }
    printf("\nMatricola non trovata!");
    return false;
}
