//Settimana 1 - Esercizio 2
/* Testo esercizio:
    1. Scrivere un programma C che usi TUTTI gli operatori studiati (lucido 4 - pagina 108);
    2. Stampare i valori delle variabili usate prima e dopo l’applicazione degli stessi.
 */

//Direttive di inclusione delle librerie
#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void){

    //Dichiarazione variabili di diversa tipologia con nomi autoesplicativi.
    char carattere='c';
    int intero1 = 2;
    int intero2 = 4;
    float float1 = 12.3;
    float float2 = 24.3;
    double reale=4.1;
    

    /*
     Per ogni operatore (ognuno di diversa tipologia) vengono stampate le seguenti informazioni:
         1. Valore prima dell'uso dell'operatore;
         2. Operatore usato;
         3. Valore dopo l'uso dell'operatore.
     */

    //Titolo esercizio
    printf("\nSettimana 1 - Esercizio 2\n\n");

    //++intero
    printf("Carattere = %c\t\t++carattere = ", carattere);
    printf("%c\n\n", ++carattere);

    //intero++
    printf("Intero = %d\t\tintero++ = ", intero1);
    printf("%d\n\n", intero1++);

    //--Reale
    printf("Reale = %.1f\t\t--reale = ", reale);
    printf("%.1f\n\n", --reale);

    //intero--
    printf("Intero = %d\t\tintero-- = ", intero2);
    printf("%d\n\n", intero2--);

    //+intero
    printf("Intero = %d\t\t+intero = %d\n\n", intero2, +intero1);

    //-intero
    printf("Intero = %d\t\t-intero = %d\n\n", intero1, -intero1);

    //float1 + float2
    printf("float1 = %.2f\t\tfloat2 = %.2f\t\tfloat1 + float2 = %3.2f\n\n", float1, float2, float1 + float2);

    //float1 - float2
    printf("float1 = %.2f\t\tfloat2 = %.2f\t\tfloat1 - float2 = %3.2f\n\n", float1, float2, float1 - float2);

    //float1 * float2
    printf("float1 = %.2f\t\tfloat2 = %.2f\t\tfloat1 * intero2 = %3.2f\n\n", float1, float2, float1 * float2);

    //float1 / float2
    printf("float1 = %.2f\t\tfloat2 = %.2f\t\tfloat1 / intero2 = %3.2f\n\n", float1, float2, float1 / float2);

    //intero1 % intero2
    printf("intero1 = %.2d\t\tintero2 = %.2d\t\tintero1 %% intero2 = %2d\n\n", intero1, intero2, intero1 % intero2);

    //intero1 = intero2
    printf("Intero1 = %2d\t\tIntero2 = %2d\t\tintero1 = intero2 = ", intero1, intero2);
    printf("%2d\n\n", intero1 = intero2);

    //intero1 += intero2
    printf("Intero1 = %2d\t\tIntero2 = %.2f\t\tintero1 += intero2 = ", intero1, float2);
    printf("%2d\n\n", intero1 += intero2);

    //float1 -= float2
    printf("Float1 = %.2f\t\tFloat2= %.2f\t\tfloat1 -= float2 = ", float1, float2);
    printf("%.2f\n\n", float1 -= float2);

    //intero1 *= intero2
    printf("Intero1 = %2d\t\tIntero2 = %2d\t\tintero1 *= intero2 = ", intero1, intero2);
    printf("%2d\n\n", intero1 *= intero2);

    //intero1 /= intero2
    printf("Intero1 = %2d\t\tIntero2 = %2d\t\tintero1 /= intero2 = ", intero1, intero2);
    printf("%2d\n\n", intero1 /= intero2);

    //intero1 % intero2
    printf("Intero1 = %2d\t\tIntero2 = %2d\t\tintero1 %%= intero2 = %.2d\n\n", intero1, intero2, (int) intero1 % (int) intero2);

    //intero1 > intero2
    printf("Intero1 = %2d\t\tIntero2 = %2d\t\tintero1 > intero2 = %s\n\n", intero1, intero2, ((intero1 > intero2) ? "Vero" : "Falso"));

    //intero1 < intero2
    printf("Intero1 = %2d\t\tIntero2 = %2d\t\tintero1 < intero2 = %s\n\n", intero1, intero2, ((intero1 < intero2) ? "Vero" : "Falso"));

    //intero1 >= intero2
    printf("Intero1 = %2d\t\tIntero2 = %2d\t\tintero1 >= intero2 = %s\n\n", intero1, intero2, ((intero1 >= intero2) ? "Vero" : "Falso"));

    //intero1 <= intero2
    printf("Intero1 = %2d\t\tIntero2 = %2d\t\tintero1 <= intero2 = %s\n\n", intero1, intero2, ((intero1 <= intero2) ? "Vero" : "Falso"));

    //intero1 == intero2
    printf("Intero1 = %2d\t\tIntero2 = %2d\t\tintero1 == intero2 = %s\n\n", intero1, intero2, ((intero1 == intero2) ? "Vero" : "Falso"));

    //intero1 != intero2
    printf("Intero1 = %2d\t\tIntero2 = %2d\t\tintero1 != intero2 = %s\n\n", intero1, intero2, ((intero1 != intero2) ? "Vero" : "Falso"));

    //intero1 AND intero2
    printf("Intero1 = %2d\t\tIntero2 = %2d\t\tintero1 AND intero2 = %s\n\n", intero1, intero2, ((intero1 && intero2) ? "Vero" : "Falso"));
    //intero1 OR intero2
    printf("Intero1 = %2d\t\tIntero2 = %2d\t\tintero1 OR intero2 = %s\n\n", intero1, intero2, ((intero1 || intero2) ? "Vero" : "Falso"));

    //NOT intero1
    printf("Intero1 = %2d\t\tNOT intero1 = %s\n\n", intero1, (!intero1 ? "Vero" : "Falso"));

    return 0;
}
