/* Scrivere un programma C che realizzi il gioco della vita, l’automa cellulare di Conway.
 Gestire quindi la mappa di dimensione NxM tramite una matrice i cui valori 
 rappresentino la presenza o meno di un organismo nel mondo. Partendo da una 
 configurazione iniziale degli organismi a vostra scelta, far evolvere la popolazione 
 nel tempo secondo le tre seguenti regole genetiche: – un organismo sopravvive fino 
 alla generazione successiva se ha 2 o 3 vicini; – un organismo muore, lasciando la 
 cella vuota, se ha più di 3 o meno di 2 vicini; – ogni cella vuota con 3 vicini 
 diventa una cella di nascita e alla generazione successiva viene occupata da un 
 organismo. Si visualizzi l’evoluzione della popolazione nel tempo. */
 
#include <stdlib.h>
#include <stdio.h>
#define VIVA 254



int main ()
{
    int n,m,i,j,k,t,vive,scelta,scelta2,y,morte=0;
    char r,ch=13;
    do
    {
       printf("\n\n              ----- Il Gioco Della Vita -----\n\n");
       printf("Inserire la dimensione (altezza x larghezza) della tabella di gioco:\n");
       scanf("%d %d",&n,&m);
       while (n<3 || m<3)  //controllo delle grandezze inserite da tastiera
       {
          if(n<3)
          {
             printf("\nl'altezza della tabella non puo' essere inferiore a 3\n");
             printf("reinserisci l'altezza: ");
             fflush(stdin);
             scanf("%d",&n);
             if(n<3){continue;}
          }
          if(m<3)
          {
             printf("\nla larghezza della tabella non puo' essere inferiore a 3\n");
             printf("reinserisci la larghezza: ");
             fflush(stdin);
             scanf("%d",&m);
          }
       }
       
       unsigned char matr[n][m],temp[n][m];
                                            //inizializzazione matrici
       for (i=0;i<=n-1;i++)
       {
          for (j=0;j<=m-1;j++)
          {
              matr[i][j]=' ';
          }
       }
       for (i=0;i<=n-1;i++)
       {
          for (j=0;j<=m-1;j++)
          {
              temp[i][j]=' ';
          }
       }
   
       printf("\nOra inizializziamo la tabella (%dx%d) alla situazione di partenza desiderata.\n\n",n,m);
       do                                      // scegliamo il tipo di inizializzazzione del gioco
       {
          printf("In che modo si desidera inizializzare la tabella di gioco?\n\n");
          printf("1. Inserendo da tastiera le coordinate delle celle da rendere vive\n");
          printf("2. Inizializzando la tabella in maniera random (casuale)\n");
          fflush(stdin);
          scanf("%d",&scelta);
          switch (scelta)
          {
             case 1:
                  printf("\nSapendo che il modello di tabella e'\n\n");
                  printf("  0 1 2 3 ..\n0\n1\n2\n3\n..\n\ne che l'altezza puo' essere tra 0 e %d e la larghezza tra 0 e %d,\n",n-1,m-1);
          
                  printf("inserire le coordinate delle celle che si vogliono rendere vive\n");
           
                  do
                  {
                  	fflush(stdin);
                     scanf("%d %d",&i,&j);
                     while(i<0 || i>=n)
                     {
                        printf("la coordinata verticale deve restare tra 0 e %d\n",n-1);
                        fflush(stdin);
                        scanf("%d",&i);
                     }
                     while(j<0 || j>=m)
                     {
                        printf("la coordinata orizzontale deve restare tra 0 e %d\n",m-1);
                        fflush(stdin);
                        scanf("%d",&j);
                     }
                     matr[i][j]=VIVA;
                     printf("\nvuoi inserire altre celle vive? (s/n)  ");
                     do
                     {
                        fflush(stdin);
                        scanf("%c",&r);
                        if(r!='s' && r!='n')
                        {
                           printf("devi inserire o 's' o 'n'\n\n");
                        }
                     }
                     while(r!='s' && r!='n');
                     if(r=='s')
                     {
                        printf("inserisci coordinate:\n");
                     }
                  }
                  while (r=='s');
                  break;
             case 2:
                  srand(time(NULL));
                  do
                  {
                     printf("\nCome deve essere la tabella?\n\n");
                     printf("1. Molto popolata\n2. Mediamente popolata\n3. Poco popolata\n");
                     fflush(stdin);
                     scanf("%d",&scelta2);
                     switch (scelta2)
                     {
                        case 1:
                             for (i=0;i<=n-1;i++)
                             {
                                for (j=0;j<=m-1;j++)
                                {
                                   matr[i][j]=(rand()%2==1) ? VIVA : ' ';
                                }
                             }
                             break;
                        case 2:
                             for (i=0;i<=n-1;i++)
                             {
                                for (j=0;j<=m-1;j++)
                                {
                                   matr[i][j]=(rand()%5>3) ? VIVA : ' ';
                                }
                             }
                             break;
                        case 3:
                             for (i=0;i<=n-1;i++)
                             {
                                for (j=0;j<=m-1;j++)
                                {
                                   matr[i][j]=(rand()%10>8) ? VIVA : ' ';
                                }
                             }
                             break;
                        default:
                             printf("Non hai scelto nessuna delle tre opzioni!!!\n\n");
                             break;
                     }
                  }
                  while(scelta2!=1 && scelta2!=2 && scelta2!=3);
                  break;
             default:
                  printf("\nNon hai inserito nessuna delle due opzioni!!!\n\n");
                  break;
          }
       }
       while (scelta!=1 && scelta!=2);
       
                                                              //stampa situazione iniziale
       printf("\nLa situazione al Tempo 0 e' questa:\n\n");
       
       for (i=0;i<=n-1;i++)
       {
          if(i==0)
          {
             printf("%c",201);
             for (y=0;y<m*2;y++)
             {
                printf("%c",205);
             }
             printf("%c\n",187);
          }
          for (j=0;j<=m-1;j++)
          {
              if(j==0)
              {
                 printf("%c",186);
              }
              printf("%c ",matr[i][j]);
              if(j==m-1)
              {
                 printf("%c",186);
              }
          }
          if(i==n-1)
          {
             printf("\n%c",200);
             for (y=0;y<m*2;y++)
             {
                printf("%c",205);
             }
             printf("%c\n",188);
          }
          printf("\n");
       }
       
       
       do
       {   
          printf("\nA che tempo si desidera fare arrivare l'evoluzione?  [-1 --> infinito]  ");
          fflush(stdin);
          scanf("%d",&t);
          if(t==-1)
          {
             break;
          }
          else if(t<1)
          {
             printf("il tempo deve essere maggiore di 0\n\n");
          }
       }
       while (t<1);
       
       usleep(800*1000);  //ritardo prima dell'esecuzione
       system("cls");  //pulisce il cmd!
                                                      //iniziano i controlli sulle celle fatti per t volte
       for (k=1; t==-1 || k<=t ;k++)
       {
          morte=0;
          for (i=0;i<=n-1;i++)
          {
             for (j=0;j<=m-1;j++)
             {
                 vive=0;                               // inizializzo il contatore delle cellule vive a 0, per ogni cella esaminata
                 if(i==0 && j==0)                      // cella alto sx
                 {
                    if(matr[i+1][j]==VIVA)
                       vive++;
                    if(matr[i+1][j+1]==VIVA)
                       vive++;
                    if(matr[i][j+1]==VIVA)
                       vive++;
                    if(matr[n-1][j+1]==VIVA)
                       vive++;
                    if(matr[n-1][j]==VIVA)
                       vive++;
                    if(matr[n-1][m-1]==VIVA)
                       vive++;
                    if(matr[i][m-1]==VIVA)
                       vive++;
                    if(matr[i+1][m-1]==VIVA)
                       vive++;
                    if(vive<=1)
                    {
                       if (matr[i][j]==VIVA)
                          temp[i][j]=' ';
                    }
                    else if (vive==3)
                    {
                       if (matr[i][j]==' ')
                          temp[i][j]=VIVA;
                    }
                    else if (vive>=4)
                    {
                       if (matr[i][j]==VIVA)
                          temp[i][j]=' ';
                    }
                 }
                 else if(i==0 && (j>0 && j<m-1))       // celle bordo alto
                 {
                    if(matr[i+1][j]==VIVA)
                       vive++;
                    if(matr[i+1][j+1]==VIVA)
                       vive++;
                    if(matr[i][j+1]==VIVA)
                       vive++;
                    if(matr[n-1][j+1]==VIVA)
                       vive++;
                    if(matr[n-1][j]==VIVA)
                       vive++;
                    if(matr[n-1][j-1]==VIVA)
                       vive++;
                    if(matr[i][j-1]==VIVA)
                       vive++;
                    if(matr[i+1][j-1]==VIVA)
                       vive++;
                    if(vive<=1)
                    {
                       if (matr[i][j]==VIVA)
                          temp[i][j]=' ';
                    }
                    else if (vive==3)
                    {
                       if (matr[i][j]==' ')
                          temp[i][j]=VIVA;
                    }
                    else if (vive>=4)
                    {
                       if (matr[i][j]==VIVA)
                          temp[i][j]=' ';
                    }
                 }
                 else if (i==0 && j==m-1)              // cella alto dx
                 {
                    if(matr[i+1][j]==VIVA)
                       vive++;
                    if(matr[i+1][0]==VIVA)
                       vive++;
                    if(matr[i][0]==VIVA)
                       vive++;
                    if(matr[n-1][0]==VIVA)
                       vive++;
                    if(matr[n-1][j]==VIVA)
                       vive++;
                    if(matr[n-1][j-1]==VIVA)
                       vive++;
                    if(matr[i][j-1]==VIVA)
                       vive++;
                    if(matr[i+1][j-1]==VIVA)
                       vive++;
                    if(vive<=1)
                    {
                       if (matr[i][j]==VIVA)
                          temp[i][j]=' ';
                    }
                    else if (vive==3)
                    {
                       if (matr[i][j]==' ')
                          temp[i][j]=VIVA;
                    }
                    else if (vive>=4)
                    {
                       if (matr[i][j]==VIVA)
                          temp[i][j]=' ';
                    }
                 }
                 else if ((i>0 && i<n-1) && j==0)         //bordo sx
                 {
                    if(matr[i+1][j]==VIVA)
                       vive++;
                    if(matr[i+1][j+1]==VIVA)
                       vive++;
                    if(matr[i][j+1]==VIVA)
                       vive++;
                    if(matr[i-1][j+1]==VIVA)
                       vive++;
                    if(matr[i-1][j]==VIVA)
                       vive++;
                    if(matr[i-1][m-1]==VIVA)
                       vive++;
                    if(matr[i][m-1]==VIVA)
                       vive++;
                    if(matr[i+1][m-1]==VIVA)
                       vive++;
                    if(vive<=1)
                    {
                       if (matr[i][j]==VIVA)
                          temp[i][j]=' ';
                    }
                    else if (vive==3)
                    {
                       if (matr[i][j]==' ')
                          temp[i][j]=VIVA;
                    }
                    else if (vive>=4)
                    {
                       if (matr[i][j]==VIVA)
                          temp[i][j]=' ';
                    }
                 }
                 else if (i==n-1 && j==0)         //cella basso sx
                 {
                    if(matr[0][j]==VIVA)
                       vive++;
                    if(matr[0][j+1]==VIVA)
                       vive++;
                    if(matr[i][j+1]==VIVA)
                       vive++;
                    if(matr[i-1][j+1]==VIVA)
                       vive++;
                    if(matr[i-1][j]==VIVA)
                       vive++;
                    if(matr[i-1][m-1]==VIVA)
                       vive++;
                    if(matr[i][m-1]==VIVA)
                       vive++;
                    if(matr[0][m-1]==VIVA)
                       vive++;
                    if(vive<=1)
                    {
                       if (matr[i][j]==VIVA)
                          temp[i][j]=' ';
                    }
                    else if (vive==3)
                    {
                       if (matr[i][j]==' ')
                          temp[i][j]=VIVA;
                    }
                    else if (vive>=4)
                    {
                       if (matr[i][j]==VIVA)
                          temp[i][j]=' ';
                    }
                 }
                 else if (i==n-1 && (j>0 && j<m-1))                 //bordo basso
                 {
                    if(matr[0][j]==VIVA)
                       vive++;
                    if(matr[0][j+1]==VIVA)
                       vive++;
                    if(matr[i][j+1]==VIVA)
                       vive++;
                    if(matr[i-1][j+1]==VIVA)
                       vive++;
                    if(matr[i-1][j]==VIVA)
                       vive++;
                    if(matr[i-1][j-1]==VIVA)
                       vive++;
                    if(matr[i][j-1]==VIVA)
                       vive++;
                    if(matr[0][j-1]==VIVA)
                       vive++;
                    if(vive<=1)
                    {
                       if (matr[i][j]==VIVA)
                          temp[i][j]=' ';
                    }
                    else if (vive==3)
                    {
                       if (matr[i][j]==' ')
                          temp[i][j]=VIVA;
                    }
                    else if (vive>=4)
                    {
                       if (matr[i][j]==VIVA)
                          temp[i][j]=' ';
                    }
                 }   
                 else if (i==n-1 && j==m-1)                 //cella basso dx
                 {   
                    if(matr[0][j]==VIVA)
                       vive++;
                    if(matr[0][0]==VIVA)
                       vive++;
                    if(matr[i][0]==VIVA)
                       vive++;
                    if(matr[i-1][0]==VIVA)
                       vive++;
                    if(matr[i-1][j]==VIVA)
                       vive++;
                    if(matr[i-1][j-1]==VIVA)
                       vive++;
                    if(matr[i][j-1]==VIVA)
                       vive++;
                    if(matr[0][j-1]==VIVA)
                       vive++;
                    if(vive<=1)
                    {
                       if (matr[i][j]==VIVA)
                          temp[i][j]=' ';
                    }
                    else if (vive==3)
                    {
                       if (matr[i][j]==' ')
                          temp[i][j]=VIVA;
                    }
                    else if (vive>=4)
                    {
                       if (matr[i][j]==VIVA)
                          temp[i][j]=' ';
                    }
                 }
                 else if ((i>0 && i<n-1) && j==m-1)                 // bordo dx
                 {
                    if(matr[i+1][j]==VIVA)
                       vive++;
                    if(matr[i+1][0]==VIVA)
                       vive++;
                    if(matr[i][0]==VIVA)
                       vive++;
                    if(matr[i-1][0]==VIVA)
                       vive++;
                    if(matr[i-1][j]==VIVA)
                       vive++;
                    if(matr[i-1][j-1]==VIVA)
                       vive++;
                    if(matr[i][j-1]==VIVA)
                       vive++;
                    if(matr[i+1][j-1]==VIVA)
                       vive++;
                    if(vive<=1)
                    {
                       if (matr[i][j]==VIVA)
                          temp[i][j]=' ';
                    }
                    else if (vive==3)
                    {
                       if (matr[i][j]==' ')
                          temp[i][j]=VIVA;
                    }
                    else if (vive>=4)
                    {
                       if (matr[i][j]==VIVA)
                          temp[i][j]=' ';
                    }
                 }
                 else
                 {
                    if(matr[i+1][j]==VIVA)
                       vive++;
                    if(matr[i+1][j+1]==VIVA)
                       vive++;
                    if(matr[i][j+1]==VIVA)
                       vive++;
                    if(matr[i-1][j+1]==VIVA)
                       vive++;
                    if(matr[i-1][j]==VIVA)
                       vive++;
                    if(matr[i-1][j-1]==VIVA)
                       vive++;
                    if(matr[i][j-1]==VIVA)
                       vive++;
                    if(matr[i+1][j-1]==VIVA)
                       vive++;
                    if(vive<=1)
                    {
                       if (matr[i][j]==VIVA)
                          temp[i][j]=' ';
                    }
                    else if (vive==3)
                    {
                       if (matr[i][j]==' ')
                          temp[i][j]=VIVA;
                    }
                    else if (vive>=4)
                    {
                       if (matr[i][j]==VIVA)
                          temp[i][j]=' ';
                    }   
                 }
                 if (vive==0)
                 {
                     morte++;
                 }
             }
          }
          if (morte == m*n)
          {
             printf("\nAl tempo %d tutte le cellule sono morte... inutile proseguire l'esecuzione...\n",k-1);
             break;
          }
          printf("\n\n\nTempo %d\n\n",k);
          for (i=0;i<=n-1;i++)
          {
             if(i==0)
             {
                printf("%c",201);
                for (y=0;y<m*2;y++)
                {
                   printf("%c",205);
                }
                printf("%c\n",187);
             }
             for (j=0;j<=m-1;j++)
             {
                 if(j==0)
                 {
                    printf("%c",186);
                 }
                 matr[i][j]=temp[i][j];                             // trasferisco le modifiche avvenute, dalla matrice temp alla matrice principale
                 printf("%c ",matr[i][j]);
                 if(j==m-1)
                 {
                    printf("%c",186);
                 }
             }
             if(i==n-1)
             {
                printf("\n%c",200);
                for (y=0;y<m*2;y++)
                {
                   printf("%c",205);
                }
                printf("%c\n",188);
             }
             printf("\n");
          }
          if (t==-1)
          {
             usleep(80*1000);             // ritardo prima della prossima esecuzione
          }
          else
          {
             usleep(500*1000);            //ritardo prima della prossima esecuzione
          }
          if(k!=t)
          {
             system("cls");
          }
       }
       do
       {
          printf("\nVuoi rieseguire il gioco? (s/n)   ");
          fflush(stdin);
          scanf("%c",&r);
          if(r!='s' && r!='n')
          {
             printf("devi inserire o 's' o 'n'\n\n");
          }
       }
       while(r!='s' && r!='n');
       if(r=='s')
       {
          system("cls");
       }
    }
    while (r=='s');
    return 0;
}
              
              
              
              
              
              
              
              
