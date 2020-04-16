//  Settimana7-Esercizio2

//Istruzioni per il preprocessore
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MIN 2
#define MAX 50000

//Prototipi delle funzioni
int *calcolaNumeriPrimi(int);
void stampaVettore(int *);
bool isPrime (int);

int main(void) {
    int numero=0;
    do {
         printf("\nInserisci range massimo per numeri primi (MIN 2 - MAX 50 000): ");
        scanf("%d", &numero);
    } while (numero<MIN || numero>MAX); //Inserimento e controllo input
    
    stampaVettore(calcolaNumeriPrimi(numero)); //Stampa i numeri primi
    printf("\n\nPremi un tasto per uscire...\n");
    exit(EXIT_SUCCESS);
}

bool isPrime (int numeroInput) { //Dato un numero in input, restituisce se il numero è primo o no
    bool isPrime=true;
    for (int divisore=2; divisore<numeroInput && isPrime==true; divisore++)
        if (numeroInput%divisore==0)
            return false;
    return isPrime;
}

//Calcola numeri primi precedenti al numero dato - restituisce puntatore al vettore
int *calcolaNumeriPrimi(int numero) {
    int contPrimi = 0;
    int *vettore = malloc(sizeof(int));
    int *vettoreTmp = NULL;
    if (vettore==NULL)
        exit(EXIT_FAILURE);
    vettore[contPrimi++]=2; //Il 2 è presente in ogni caso
    for (int contNumero=3; contNumero<=numero; contNumero++)
        if (contNumero%2!=0) //Controllo solo i numeri dispari
            if (isPrime(contNumero)==true) { //Se il numero è primo
                ++contPrimi;
                vettoreTmp = (int *) realloc (vettore, (contPrimi+1) * sizeof(int)); //Rialloca vettore
                if (vettoreTmp!=NULL)
                    vettore = vettoreTmp;
                vettore[contPrimi-1] = contNumero; //Inserisci numero
            }
    vettore[contPrimi]=-1; //Nell'ultima posizione inserisce -1
    return vettore;
}

void stampaVettore(int *vettore) { //Stampa vettore
    for (int i=0; vettore[i]!=-1; i++) {
        printf("\n%d. Numero: %d", i+1, vettore[i]);
    }
}

