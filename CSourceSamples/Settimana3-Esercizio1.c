//Settimana3-Esercizio1

#include <stdio.h>
#include <limits.h>

int main(void) {
    
    //Dichiarazione variabili
    long int numero=0;
    unsigned int i=0;
    long int numBinario[sizeof(long)*8];
    
   //Messaggio di benvenuto ed in serimento (valori compresi nel range del long int)
    printf("\nBenvenuto utente,\ndato il seguente range di valori: %d - %lu.", 1, ULONG_MAX);
    
    //Input numero
    do {
        printf("\nInserisci un numero intero da convertire in binario: ");
        scanf("%ld", &numero);
        if (numero<1)
            printf("\nErrore, inserire un numero compreso nel range!"); //Stampa messaggio di errore
    } while (numero<1); //Ripeti ciclo finche l'input è minore di 1
    
    printf("\nNumero (%ld) in binario: ", numero);
    
    //Conversione numero da decimale a binario
    while(numero>0) {
        numBinario[i]=numero%2;
        numero /= 2;
        i++;
    }
    
    //Stampa numero convertito in binario
    for (int j = i - 1; j >= 0; j--) {
        printf("%ld", numBinario[j]);
    }
    
    //Messaggio di uscita
    printf("\n\nPremi un tasto per continuare...");
    getchar();
    return 0;
}
