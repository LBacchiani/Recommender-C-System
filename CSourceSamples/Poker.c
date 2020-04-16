/*Sviluppare un programma che simuli un mescolatore (tramite un’apposita funzione) 
e un distributore (altra funzione) delle cinque carte di una mano di poker.

Implementare poi una funzione che determini se la mano contiene una coppia, una doppia coppia, un tris, un poker, un colore o una scala.

Utilizzare le funzioni per sviluppare un programma che gestisca un’intera partita 
il cui funzionamento è di seguito descritto: 
Il gioco richiede un mazzo di carte dal quale Il mazziere distribuisce cinque carte a ogni giocatore.
Ogni giocatore può cambiare da una a quattro carte, in modo da ottenere nuove combinazioni.
Ogni giocatore ha la facoltà di puntare una cifra o di abbandonare la mano.
Si procede alla verifica delle combinazioni e alla nomina del vincitore.

Vince chi ottiene la combinazione di maggiore valore o induce tutti gli altri giocatori ad abbandonare la partita.
Le combinazioni di maggior valore in ordine decrescente sono: 
• Poker • Colore • Full • Scala • Tris • Doppia Coppia • Coppia • La carta più alta

Ogni eventuale miglioria è, come sempre, bene accetta.*/

#include <stdlib.h>
#include <stdio.h>

#define NUM_CARTE 52
#define NUM_GIOC 4
#define TOT_FISH 400

enum DiverseMani{
	
	Carta_Alta,
	Coppia,
	Doppia_Coppia,
	Tris,
	Scala,
	Full,
	Colore,
	Poker
};

typedef struct{
	short int valore;
	short int seme;
}Carta;


typedef struct{
	Carta mano[5];
	enum DiverseMani tipoMano;
	int fishes;
	int puntata;
	int carteAlte;
	int folded;
	int allIn;
	int inGioco;
}Player;





void InizializzaMazzo(Carta m[]);

void InizializzaPartita(Carta m[], Player gioc[],int,int *,int *);

void MescolaMazzo(Carta m[]);

void DistribuisciCarte(Player gioc[],int, Carta m[],int *);

void OrdinaManiGiocatori(Player gioc[],int);

void ValutaManiGiocatori(Player gioc[],int);

void CambiaCarte(Player gioc[],int,Carta m[],int v[],int ,int *);

char SimboloValore(int);

void StampaMano(Carta v[]);

char DomandaSiNo (char v[],char);

void Puntate (Player gioc[],int,int *);

void GestisciPuntataSingola (Player gioc[],int ,int);

int ControlloGiocatori (Player gioc[],int);

void AssegnaVittoria(Player gioc[],int,int v[],int);



int main ()
{
	int i,j,temp,n,cimaMazzo,puntataMax,giocAttivi,nPuntate=1,nMani=1,voglioVedere=0,numeroGioc;
	char r;
	Carta mazzo[NUM_CARTE];
	
	printf("\n\n    ---- GIOCO DEL POKER ----\n\n");
	InizializzaMazzo(mazzo);
	
	/*
	Stampa Mazzo inizializzato
	
	for(i=0;i<NUM_CARTE;i++)
	{
		if(i%13==0)
		printf("\n");
		printf("carta : %d\tseme : %c\n",mazzo[i].valore,mazzo[i].seme);
	}
	printf("\n\n\n\n");*/
	
	
	do
	{
		printf("\n\nInserire il numero di giocatori che parteciperanno (2-6) : ");
		fflush(stdin);
		temp = scanf("%d",&numeroGioc);
		if (!temp)
		{
			printf("Non hai inserito un numero!!\n\n");
			continue;
		}
		if(numeroGioc < 2 || numeroGioc > 6)
		{
			printf("Il numero di giocatori deve essere compreso tra 2 e 6!!\n\n");
		}
	}
	while (!temp || (numeroGioc < 2 || numeroGioc > 6));
	
	
	Player giocatore[numeroGioc];
	int pos[numeroGioc];
	
	//tutti i giocatori sono in gioco all'inizio... inGioco diventa 0 quando le fish a disposizione di un giocatore finiscono
	for(i=0;i<numeroGioc;i++)
	{
		giocatore[i].inGioco = 1;
		giocatore[i].fishes = TOT_FISH;
	}
	
	
	do
	{
      if(nMani != 1)
		{
			system("pause");
			printf("\n");
		}
		
		printf("\n\n   MANO   %d\n\n\n",nMani);
		
		
		MescolaMazzo(mazzo);
		
		/*
		Stampa Mazzo mescolato
		
		for(i=0;i<NUM_CARTE;i++)
		{
			
			if(i%13==0)
			printf("\n");
			if(mazzo[i].valore == 1 || mazzo[i].valore == 11 || mazzo[i].valore == 12 || mazzo[i].valore == 13)
			{
				temp = SimboloValore(mazzo[i].valore);
				printf(" %c ", temp);
			}
			else
			{
				printf(" %d ",mazzo[i].valore);
			}
			printf("\t%c  \n", mazzo[i].seme);
		}
		*/
		
		DistribuisciCarte(giocatore,numeroGioc,mazzo,&cimaMazzo);
		
		
		
		/*
		Stampa Mani giocatori
		
		for (i=0;i<numeroGioc;i++)
		{
			printf("\nMano Giocatore %d:\n\n",i+1);
			StampaMano(giocatore[i].mano);
			printf("\n");
		}
		*/
		
		OrdinaManiGiocatori(giocatore,numeroGioc);
		
		
		//stampo le carte del player 1 (l'utente)
		if (giocatore[0].inGioco)
		{
			printf("Mano Giocatore 1:\n\n");
			StampaMano(giocatore[0].mano);
			printf("\n");
		}
		else if (!giocatore[0].inGioco && !voglioVedere)
		{
			r=DomandaSiNo("\n\nNon sei piu' in gioco!!  Vuoi comunque vedere la partita?? (s/n)  ",r);
			
			if(r=='s')
			{
				voglioVedere=1;
			}
			else
			{
				r=DomandaSiNo("\n\nVuoi iniziarne una nuova?? (s/n)  ",r);
				if(r=='n')
				{
					exit(0);
				}
				else
				{
					InizializzaPartita(mazzo,giocatore,numeroGioc,&nMani,&nPuntate);
					temp=0;
					continue;
				}
			}
		}
		
		
		
		
		
		//diamo una dotazione di fish ai giocatori e inizializziamo le puntate a 0
		for(i=0;i<numeroGioc;i++)
		{
			giocatore[i].puntata = 0;
		}
		
		
		puntataMax = 0;
		
		nPuntate=1;
		//primo giro di puntate
		
		ValutaManiGiocatori(giocatore,numeroGioc);
		
		do
		{
			printf("\n\n  PUNTATA    %d",nPuntate);
			nPuntate++;
			giocAttivi = 0;
			Puntate(giocatore,numeroGioc,&puntataMax);
	   	
	   	
	   	//conto i giocatori ancora attivi (cioè i giocatori che possono eventualmente puntare nuovamente)
	   	for (i=0;i<numeroGioc;i++)
	   	{
	   		if(!giocatore[i].folded && giocatore[i].inGioco && !giocatore[i].allIn)
	   		{
	   			pos[giocAttivi] = i;
	   			giocAttivi++;
	   		}
	   	}
	   	
		   temp=0;
		   // conto quanti sono i giocatori che hanno la puntata attuale uguale alla puntata massima
		   for (i=0;i<giocAttivi;i++)
		   {
		   	if (giocatore[pos[i]].puntata == puntataMax)
		   	{
		   		temp++;
		   	}
		   }
		   sleep(2);
		}
		/* poi confronto i giocatori che potrebbero nuovamente puntare, col numero di quelli che hanno la puntata uguale a quella massima... se i numeri divergono
         significa che c'è almeno un giocatore che ha la puntata attuale minore di quella massima.... quindi bisogna fare un'altro giro di puntate*/
	   while (temp != giocAttivi);
	   
	   
	   
	   
	   temp=ControlloGiocatori(giocatore,numeroGioc);
	   
	   if(temp>1)
	   {
	   	printf("\n---Cambio delle carte!---\n");
	   	sleep(1);
	   }
	      
	   
	   if (temp != 0)
	   {
	   	if(!giocatore[0].folded && giocatore[0].inGioco && temp != 1)
	   	{
	   		
	   		printf("\n\nMano Giocatore 1\n");
				StampaMano(giocatore[0].mano);
	   		
		   	printf("\n\n");
				r=DomandaSiNo("Vuoi cambiare delle carte? (s/n)  ",r);
				
				if (r=='s')
				{
					do
					{
						printf("\nQuante carte vuoi cambiare? --> ");
						fflush(stdin);
						temp=scanf("%d",&n);
						if(!temp)
						{
							printf("Non hai inserito un numero!!\n\n");
							continue;
						}
						
						if(n<0)
						{
							printf("Non puoi inserire un numero negativo\n\n");
						}
						else if(n>4)
						{
							printf("Non puoi cambiare piu' di 4 carte!!\n\n");
						}
					}
					while(!temp || (n<0 || n>4));
					
					if(n!=0)
					{
			  		   //inizializzo pos
						for (i=0;i<4;i++)
						   pos[i]=0;
				  			
						
						printf("\nQuali ?\n");
						for(i=0;i<n;i++)
						{
							do
							{
								printf("(inserisci la posizione) --> ");
								fflush(stdin);
								temp=scanf("%d",(pos+i));
								if(!temp)
								{
									printf("Non hai inserito un numero!!\n\n");
									continue;
								}
								if(pos[i]<1 || pos[i]>5)
								{
									printf("La posizione devone essere compresa tra 1 e 5!!\n\n");
									continue;
								}
								
								//controllo che non si inserisca la stessa posizione più volte
								if(i!=0)
								{
									for(j=0;j<i;j++)
									{
										if(pos[i] == pos[j])
										{
											printf("La posizione %d e' gia' stata inserita!!\n\n",pos[i]);
											temp=0;
											break;
										}
									}
								}
									
								
							}
							while(!temp || (pos[i]<1 || pos[i]>5));
						}
						
						CambiaCarte(giocatore,numeroGioc,mazzo,pos,n,&cimaMazzo);
						
						OrdinaManiGiocatori(giocatore,numeroGioc);
				
						printf("\nMano Giocatore 1:\n");
						StampaMano(giocatore[0].mano);
					}
				}
			
		   }
			
			
			temp=ControlloGiocatori(giocatore,numeroGioc);
			
			if(temp>1)
			{
				//secondo giro di puntate
				
				ValutaManiGiocatori(giocatore,numeroGioc);
				
				do
				{
					temp=0;
					for(i=0;i<numeroGioc;i++)
					{
						if(!giocatore[i].folded && giocatore[i].inGioco && !giocatore[i].allIn)
						{
							temp++;
						}
					}
					
					if(temp != 0)
					{
						printf("\n\n  PUNTATA    %d",nPuntate);
					   nPuntate++;
					}
					
					giocAttivi = 0;
					Puntate(giocatore,numeroGioc,&puntataMax);
			   	
			   	//conto i giocatori ancora attivi (cioè i giocatori che possono eventualmente puntare nuovamente)
			   	for (i=0;i<numeroGioc;i++)
			   	{
			   		if(!giocatore[i].folded && giocatore[i].inGioco && !giocatore[i].allIn)
			   		{
			   			pos[giocAttivi] = i;
			   			giocAttivi++;
			   		}
			   	}
			   	
				   temp=0;
				   // conto quanti sono i giocatori che hanno la puntata attuale uguale alla puntata massima
				   for (i=0;i<giocAttivi;i++)
				   {
				   	if (giocatore[pos[i]].puntata == puntataMax)
				   	{
				   		temp++;
				   	}
				   }
				   sleep(2);
				}
				/* poi confronto i giocatori che potrebbero nuovamente puntare, col numero di quelli che hanno la puntata uguale a quella massima... se i numeri divergono
			      significa che c'è almeno un giocatore che ha la puntata attuale minore di quella massima.... quindi bisogna fare un'altro giro di puntate*/
			   while (temp != giocAttivi);
			}
			
		   
	   }
	   
	   
	   
	   giocAttivi = 0;
	   // conto il numero e prendo la posizione di quei giocatori che possono essere, passati alla funzione AssegnaVittoria (cioè i giocatori candidati alla vittoria)
		for (i=0;i<numeroGioc;i++)
		{
			if(!giocatore[i].folded && giocatore[i].inGioco)
			{
				pos[giocAttivi] = i;
				giocAttivi++;
			}
		}
	   
	   printf("\n\n");
	   for(i=0;i<numeroGioc;i++)
	   {
	   	if (giocatore[i].inGioco)
	   	{
   		 	printf("\n\nMano Giocatore %d:\n\n",i+1);
		   	StampaMano(giocatore[i].mano);
		   	sleep(1);
	   	}
	   }
	   
	   
	   AssegnaVittoria(giocatore,numeroGioc,pos,giocAttivi);
	   
	   temp=0;
	   //conto il numero di giocatori usciti dal tavolo del poker
	   for(i=0;i<numeroGioc;i++)   
	   {
	   	if(!giocatore[i].inGioco)
	   	{
	   		temp++;
	   	}
	   }
		
		//se questo numero corrisponde al numero totale di giocatori - 1 significa che abbiamo un vincitore, e la partita e' finita...
		if (temp == numeroGioc - 1)
		{
			printf("\n\nLa partita e' finita!!\n\n");
			
			sleep(2);
			
			r=DomandaSiNo("\n\nVuoi iniziarne una nuova?? (s/n)  ",r);
			
			if(r=='s')
			{
				InizializzaPartita(mazzo,giocatore,numeroGioc,&nMani,&nPuntate);
				nMani--;
				temp=0;
			}
		}
		nMani++;
   }
	while (temp != numeroGioc - 1);
	
	
	return 0;
}



















void InizializzaMazzo(Carta m[NUM_CARTE])
{
	int i,j=0,k=3;
	for(i=0;i<NUM_CARTE;i++)
	{
		j++;
		m[i].valore=j;
		m[i].seme=k;
		
		
		if (j==13)
		{
		 	k++;
		   j=0;
		}
	}
}

void MescolaMazzo(Carta m[NUM_CARTE])
{
	srand(time(NULL));
	short int i,indice1,indice2;
	Carta temp;
	
	for(i=0;i<=NUM_CARTE;i++)
	{
		// calcolo un indice random per mescolare il mazzo
		indice1 = rand() % NUM_CARTE;
		indice2 = rand() % NUM_CARTE;
		
		
		temp=m[indice1];
		
		m[indice1] = m[indice2];
		
		m[indice2] = temp;
	}
}

void DistribuisciCarte(Player gioc[],int numGioc,Carta m[NUM_CARTE], int *cima)
//vengono distribuite le carte dall'inizio del mazzo, dando prima la prima carta a tutti, poi la seconda carta a tutti, ecc...
{
	int i,j,k=0;
	for (i=0;i<5;i++)
	{
		for (j=0;j<numGioc;j++)
		{
			if(gioc[j].inGioco)
			{
				gioc[j].mano[i] = m[k];
				k++;
			}
			
		}
	}
	for (j=0;j<numGioc;j++)
	{
		if(gioc[j].inGioco)
		{
			gioc[j].folded = 0;
			gioc[j].allIn = 0;
		}
	 	   
	}
	*cima=k;
}


void OrdinaManiGiocatori(Player gioc[], int numGioc)
{
	int i,j,flag,temp;

	for (i=0;i<numGioc;i++)
	{
		//ordino le mani di chi e' ancora in gioco.. e non ha foldato
		if (!gioc[i].folded && gioc[i].inGioco)
		{
			do
		   {
		   	flag=0;
		   	for(j=0;j<4;j++)
		   	{
		   		if(gioc[i].mano[j].valore > gioc[i].mano[j+1].valore)
		   		{
		   			temp = gioc[i].mano[j].valore;
		   			gioc[i].mano[j].valore = gioc[i].mano[j+1].valore;
		   			gioc[i].mano[j+1].valore = temp;
		   			
		   			temp = gioc[i].mano[j].seme;
		   			gioc[i].mano[j].seme = gioc[i].mano[j+1].seme;
		   			gioc[i].mano[j+1].seme = temp;
		   			
		   			flag=1;
		   		}
		   	}
		   }
		   while (flag==1);
		}
	}
}



void ValutaManiGiocatori(Player gioc[], int numGioc)
{
	int i,j,y;
	for (i=0;i<numGioc;i++)
	{
		int kValore=0,perValore[5][2],kSeme=0,perSeme[4][2],flag;
		
		if(!gioc[i].folded && gioc[i].inGioco)
		{
			//inizializzo perValore, che mi serve per tenere i valori delle carte e il numero di volte che questi valori sono nella mano
			for(j=0;j<5;j++)
			{
				for(y=0;y<2;y++)
				{
					perValore[j][y]=0;
				}
			}
			//inizializzo perColore, che mi serve per tenere i semi delle carte e il numero di volte che questi semi sono nella mano
			for(j=0;j<4;j++)
			{
				for(y=0;y<2;y++)
				{
					perSeme[j][y]=0;
				}
			}
			
			
			//Raggruppo le carte per valore e le conto
			perValore[kValore][0] = gioc[i].mano[0].valore;
			perValore[kValore][1]++;
			kValore++;
	
	      for (j=1;j<5;j++)
	      {
	      	flag=0;
	      	for(y=0;y<kValore;y++)
	      	{
	      		if(gioc[i].mano[j].valore == perValore[y][0])
		      	{
		      		perValore[y][1]++;
		      		flag=1;
		      		break;
		      	}
	      	}
	      	if(flag==0)
	      	//se la carta non c'è tra quelle già incontrate, la aggiungio alla matrice
	      	{
	      		perValore[kValore][0] = gioc[i].mano[j].valore;
	      		perValore[kValore][1]++;
	      		kValore++;
	      	}
	      	
	      }
	      
	      
			//controllo se ha un poker in mano
	      flag=0;
	      for (j=0;j<kValore;j++)
	      {
	      	if(perValore[j][1] == 4)
		      {
		      	gioc[i].tipoMano = Poker;
		      	
		      	if (perValore[j][0] == 1)
		      	// se la carta alta e' l'asso bisogna assegnare un numero superiore a tutte le altre carte ( e non 1 !!)
		      	{
		      		gioc[i].carteAlte = 14;
		      	}
		      	else
		      	{
		      		gioc[i].carteAlte = perValore[j][0];
		      	}
		      	
		      	flag=1;
		      	break;
		      }
	      }
	      
	      if(flag==1)
	      //se abbiamo stabilito il tipo della mano possiamo passare al prox giocatore
	      {
	      	continue;
	      }
	      
	      
	      
	      //Raggruppo le carte per seme e le conto
	      perSeme[kSeme][0] = gioc[i].mano[0].seme;
			perSeme[kSeme][1]++;
			kSeme++;
	
	      for (j=1;j<5;j++)
	      {
	      	flag=0;
	      	for(y=0;y<kSeme;y++)
	      	{
	      		if(gioc[i].mano[j].seme == perSeme[y][0])
		      	{
		      		perSeme[y][1]++;
		      		flag=1;
		      		break;
		      	}
	      	}
	      	if(flag==0)
	      	//se la carta non c'è tra quelle già incontrate, la aggiungio alla matrice
	      	{
	      		perSeme[kSeme][0] = gioc[i].mano[j].seme;
	      		perSeme[kSeme][1]++;
	      		kSeme++;
	      	}
	      	
	      }
	      
	      
	      
	      
	      //controllo se ha un colore
	      if(perSeme[0][1] == 5)
	      {
	      	gioc[i].tipoMano = Colore;
	      	
	      	//stabilisco qual'è la carta più alta della mano del giocatore
		      gioc[i].carteAlte = gioc[i].mano[0].valore;
		      flag=0;
		      for (j=0;j<5;j++)
		      {
		      	if(gioc[i].carteAlte < gioc[i].mano[j].valore)
		      		gioc[i].carteAlte = gioc[i].mano[j].valore;
		      		
		      	if(gioc[i].mano[j].valore == 1)
		      	// se cercando la carta alta troviamo un asso, deve essere considerato la carta più alta
		      	   flag=1;
		      }
			
				if(flag)
				   gioc[i].carteAlte = 14;
			
	      	//avendo stabilito il tipo della mano... possiamo passare al prox giocatore
	      	continue;
	      }
	      
	      
	      //controllo se ha un full
	      if((perValore[0][1] == 3 && perValore[1][1] == 2) || (perValore[0][1] == 2 && perValore[1][1] == 3))
	      {
	      	gioc[i].tipoMano = Full;
	      	
	      	// per stabilire se una full supera un'altra, faccio la somma dei valori delle due carte che compaiono nella mano (ovviamente se sono assi, si trattano come sappiamo)
	      	gioc[i].carteAlte = (perValore[0][0] == 1 ? 14 : perValore[0][0]) + (perValore[1][0] == 1 ? 14 : perValore[1][0]);
	      	
	      	//avendo stabilito il tipo della mano... possiamo passare al prox giocatore
	      	continue;
	      }
	      
	      
	      //controllo se ha scala
	      if(perValore[0][0] == perValore[1][0]-1 && perValore[0][0] == perValore[2][0]-2 && perValore[0][0] == perValore[3][0]-3 && perValore[0][0] == perValore[4][0]-4)
	      {
	      	gioc[i].tipoMano = Scala;
	      	
	      	//in una scala la differenza la fa l'ultima carta della scala!
	      	gioc[i].carteAlte = perValore[4][0];
	      	
	      	//avendo stabilito il tipo della mano... possiamo passare al prox giocatore
	      	continue;
	      }
	      else if(perValore[0][0] == 1 && perValore[1][0] == perValore[2][0]-1 && perValore[1][0] == perValore[3][0]-2 && perValore[1][0] == perValore[4][0]-3)
	      //catturo il caso in cui ci sia la scala che termina con l'asso... che altrimenti verrebbe scartato
	      {
	      	gioc[i].tipoMano = Scala;
	      	
	      	//questo è il caso in cui abbiamo un asso in mano... e lui è la carta alta
	      	gioc[i].carteAlte = 14;
	      	
	      	//avendo stabilito il tipo della mano... possiamo passare al prox giocatore
	      	continue;
	      }
	      
	      
	      //controllo se ha tris
	      if(perValore[0][1] == 3 || perValore[1][1] == 3 || perValore[2][1] == 3)
	      {
	      	gioc[i].tipoMano = Tris;
	      	
	      	for (j=0;j<3;j++)
	      	{
	      		if(perValore[j][1] == 3)
	      		{
	      			gioc[i].carteAlte = (perValore[j][0] == 1 ? 14 : perValore[j][0]);
	      			break;
	      		}
	      	}
	      	
	      	//avendo stabilito il tipo della mano... possiamo passare al prox giocatore
	      	continue;
	      }
	      
	      
	      //controllo se ha doppia coppia
	      if((perValore[0][1] == 2 && perValore[1][1] == 2) || (perValore[0][1] == 2 && perValore[2][1] == 2) || (perValore[1][1] == 2 && perValore[2][1] == 2))
	      {
	      	gioc[i].tipoMano = Doppia_Coppia;
	      	
	      	//per stabilire se una doppia coppia supera un'altra, come nel full, devo sommare i numeri che compongono la doppia coppia...
	      	gioc[i].carteAlte = 0;
	      	for (j=0;j<3;j++)
	      	{
	      		if(perValore[j][1] == 2)
	      		{
	      			gioc[i].carteAlte += (perValore[j][0] == 1 ? 14 : perValore[j][0]);
	      		}
	      	}
	      	
	      	//avendo stabilito il tipo della mano... possiamo passare al prox giocatore
	      	continue;
	      }
	      
	      
	      //controllo se ha un coppia
	      if(perValore[0][1] == 2 || perValore[1][1] == 2 || perValore[2][1] == 2 || perValore[3][1] == 2)
	      {
	      	gioc[i].tipoMano = Coppia;
	      	
	      	for(j=0;j<4;j++)
	      	{
	      		if (perValore[j][1] == 2)
	      		{
	      			gioc[i].carteAlte = (perValore[j][0] == 1 ? 14 : perValore[j][0]);
	      		}
	      	}
	      	
	      	//avendo stabilito il tipo della mano... possiamo passare al prox giocatore
	      	continue;
	      }
	      
	      
	      //se non e' nessuna delle precedenti avrà una carta alta
	      gioc[i].tipoMano = Carta_Alta;
	      
	      //stabilisco qual'è la carta più alta della mano del giocatore
	      gioc[i].carteAlte = gioc[i].mano[0].valore;
	      flag=0;
	      for (j=0;j<5;j++)
	      {
	      	if(gioc[i].carteAlte < gioc[i].mano[j].valore)
	      		gioc[i].carteAlte = gioc[i].mano[j].valore;
	      		
	      	if(gioc[i].mano[j].valore == 1)
	      	// se cercando la carta alta troviamo un asso, deve essere considerato la carta più alta
	      	   flag=1;
	      }
		
			if(flag)
			   gioc[i].carteAlte = 14;
		}
	}
	
}



void CambiaCarte(Player gioc[],int numGioc,Carta m[NUM_CARTE],int v[],int num, int *cima)
{
	int i,j;
	
	for(i=0;i<num;i++)
	{
		gioc[0].mano[v[i]-1].valore = m[*cima].valore;
		gioc[0].mano[v[i]-1].seme = m[*cima].seme;
		(*cima)++;
	}
}

char SimboloValore(int numero)
{
	if(numero==1)
      return 'A';
      
	else if(numero==11)
	   return 'J';
 	  
   else if(numero==12)
      return 'Q';
      
   else if(numero==13)
      return 'K';
}


void StampaMano(Carta v[5])
{
	int i;
	char temp;
	for (i=0;i<5;i++)
	{
		
		if(v[i].valore == 1 || v[i].valore == 11 || v[i].valore == 12 || v[i].valore == 13)
		{
			temp = SimboloValore(v[i].valore);
			printf("%c ", temp);
		}
		else
		{
			printf("%d ",v[i].valore);
		}
		printf("%c  ", v[i].seme);
	}
}


// funzione per chiedere una domanda e rispondere si o no
char DomandaSiNo(char v[],char risp)
{
     printf("%s",v);
     fflush(stdin);
     risp=getche();
     printf("\n");
     while(risp!='s' && risp!='n')
     {
        printf("Devi inserire o 's' o 'n' !\n\n");
        printf("%s",v);
        fflush(stdin);
        risp=getche();
        printf("\n");
     }
     return risp;
}


void GestisciPuntataSingola (Player gioc[],int numGioc,int puntata)
{
	if(puntata == -1)
	{
		gioc[numGioc].folded = 1;
		printf("\nGiocatore %d : ha lasciato la mano\n\n",numGioc+1);
	}
	else if (puntata == 0)
	{
		printf("\nGiocatore %d : passa il turno\n\n",numGioc+1);
	}
	else
	{
		printf("\nGiocatore %d : punta %d",numGioc+1,puntata);
		gioc[numGioc].puntata += puntata;
	 	gioc[numGioc].fishes -= puntata;
	   printf(" per un totale puntato di --> %d\n\n",gioc[numGioc].puntata);
	   if (gioc[numGioc].fishes == 0)
	   {
	   	gioc[numGioc].allIn = 1;
	   	printf("Giocatore %d ALL-IN\n",numGioc+1);
	   }
	}
	
}


int ControlloGiocatori (Player gioc[],int numGioc)
//funzione che controlla se ci sono ancora dei giocatori in gioco
{
	int i,n=0;
	for (i=0;i<numGioc;i++)
	{
		if(!gioc[i].folded && gioc[i].inGioco)
		{
			n++;
		}
	}
	return n;
}


void AssegnaVittoria (Player gioc[],int numGioc,int v[],int num)
{
	int max,i,j,trovato,vincita=0,posVincitori[numGioc],posVincSparegg[numGioc],parita;
		
	ValutaManiGiocatori(gioc,numGioc);
	
	//inizializzo posVincitori e posVincSparegg
	for(i=0;i<numGioc;i++)
	{
		posVincitori[i] = -1;
		posVincSparegg[i] = -1;
	}
	
	
	// trovo, tra quelle dei giocatori ancora in gioco, la mano che ha più forza
	max = gioc[v[0]].tipoMano;
	
	for (i=1;i<num;i++)
	{
		if(max < gioc[v[i]].tipoMano)
		{
			max = gioc[v[i]].tipoMano;
		}
	}
	
	j = 0;
	
	//scopro se ci sono più mani dello stesso tipo, e salvo la posizione del giocatore nel vettore posVincitori[]
	for(i=0;i<num;i++)
	{
		if(max == gioc[v[i]].tipoMano)
		{
			posVincitori[j]=v[i];
			j++;
		}
	}
	
	parita = j;
	
	// se ci sono dei pareggi, prima di assegnare la vittoria, devo controllare se uno prevale sugli altri, grazie alla carta alta...
	if(j != 1)
	{
		// trovo, tra i pareggi, la carta più alta
		max = gioc[posVincitori[0]].carteAlte;
		
		for(i=1;i<j;i++)
		{
			if(gioc[posVincitori[i]].carteAlte > max)
			{
				max = gioc[posVincitori[i]].carteAlte;
			}
		}
		
		//scopro se tra i pareggi, ci sono anche pareggi di carta alta
		parita=0;
		for (i=0;i<j;i++)
		{
			if(max == gioc[posVincitori[i]].carteAlte)
			{
				posVincSparegg[parita] = posVincitori[i];
				parita++;
			}
		}
		
		//reinizializzo posVincitori
		for(i=0;i<numGioc;i++)
		   posVincitori[i] = -1;
		   
      // per poi ricopiarci dentro i veri vincitori, dopo lo spareggio
		for(i=0;i<parita;i++)   
		   posVincitori[i] = posVincSparegg[i];
	}
	
	
	
	//raccolgo le puntate dei giocatori in "vincita"
	for(i=0;i<numGioc;i++)
	{
		vincita += gioc[i].puntata;
		gioc[i].puntata = 0;
	}
	
	
	//comunico chi ha vinto la mano
	for (i=0;i<parita;i++)
	{
		gioc[posVincitori[i]].fishes += vincita / parita;
		printf("\n-----------------------------\nIl Giocatore %d vince %d fish\n-----------------------------\n",posVincitori[i]+1,vincita/parita);
	}
	
	
	//se ci sono dei giocatori che sono andati ALL IN e non sono tra i vincitori.... hanno esaurito le fish, e sono pertanto fuori dal gioco
	for (i=0;i<numGioc;i++)
	{
		trovato=0;
		for(j=0;j<parita;j++)
		{
			if(i == posVincitori[j])
			{
				trovato=1;
			}
		}
		if(!trovato && gioc[i].allIn == 1)
		{
			 gioc[i].inGioco = 0;
		}
	}
	
	sleep(2);
}

void Puntate (Player gioc[],int numGioc,int *puntMax)
{
	int i,j,temp,incremento = *puntMax - gioc[0].puntata,flag;
	char r;
	
	srand(time(NULL));
	
	if (!gioc[0].allIn && !gioc[0].folded && gioc[0].inGioco)
	{
	   printf("\n\nGiocatore %d ha: %d fish\n",1,gioc[0].fishes);
	   
	   if (incremento >= gioc[0].fishes)
	   {
	   	r=DomandaSiNo("\nVuoi andare all-in ? (s/n)  ",r);
	   	if (r=='s')
	   	{
	   		gioc[0].allIn=1;
	   		gioc[0].puntata += gioc[0].fishes;
	   		gioc[0].fishes = 0;
	   	}
	   	else
	   	{
	   		incremento = -1;
	   		
	   		GestisciPuntataSingola(gioc,0,incremento);
	   	}
	   }
	   else
	   {
	   	do
			{
				printf("Quanto punti?  (-1 fold | 0 check) --> ");
				fflush(stdin);
				temp=scanf("%d",&incremento);
				if (!temp)
				{
					printf("Non hai inserito un numero!!\n\n");
					continue;
				}
				
				if(incremento == -1)
				{
					break;
				}
				
				if(incremento < -1)
				{
					printf("La puntata non puo' essere negativa!!\n\n");
					continue;
				}
				
				if (incremento > gioc[0].fishes)
				{
					printf("Non hai abbastanza fish!!\n\n");
					continue;
				}
				
				flag=0;
				for (i=1;i<numGioc;i++)
				{
					if(!gioc[i].folded && gioc[i].inGioco)
					{
						if(incremento + gioc[0].puntata < *puntMax)
						{
							flag=1;
							printf("\nLa tua puntata totale (%d) non raggiunge la puntata max degli altri (%d)\n\n",incremento + gioc[0].puntata,*puntMax);
							break;
						}
					}
				}
				
			}
			while (!temp || (gioc[0].puntata < -1 || incremento > gioc[0].fishes) || flag == 1);
			
			GestisciPuntataSingola(gioc,0,incremento);
			
			if(incremento != -1)
			{
				*puntMax = gioc[0].puntata;
			}
			
			sleep(2);
	   }
			
	}
		
	

	for(i=1;i<numGioc;i++)
	{
		if(!gioc[i].folded && !gioc[i].allIn)
		{
			temp=0;
			for (j=0;j<numGioc;j++)
			{
				if(gioc[j].folded || !gioc[j].inGioco)
				{
					temp++;
				}
			}
			if(temp == numGioc - 1)
			// se il numero di giocatori folded e anche non in gioco e' uguale a (numero giocatori - 1) significa che l'ultimo giocatore rimasto in gico ha diritto alla vittoria
			{
				incremento = 0;
				
				printf("\n\nGiocatore %d ha: %d fish\n",i+1,gioc[i].fishes);
				
				GestisciPuntataSingola(gioc,i,incremento);
				
				break;
			}
			printf("\n\nGiocatore %d ha: %d fish\n",i+1,gioc[i].fishes);
			switch(gioc[i].tipoMano)
			{
				case Poker:
					
					incremento = TOT_FISH/3;
					
					if (incremento > gioc[i].fishes)
					//se la puntata da fare supera il limite max di fish... si va ALL-IN
					{
						incremento = gioc[i].fishes;
						
						GestisciPuntataSingola(gioc,i,incremento);
						
						if(gioc[i].puntata > *puntMax )
						{
							// se l'incremento più la puntata precedente superano la puntata max, abbiamo una nuova puntata max
							// ( l'incremento e' gia stato aggiunto alla puntata attuale attraverso la funzione GestisciPuntataSingola !!!!! )
							*puntMax = gioc[i].puntata;
						}
						
					}
					else
					{
						if(incremento + gioc[i].puntata > *puntMax )
						{
							//se l'incremento più la puntata precedente superano la puntata max, abbiamo una nuova puntata max
							GestisciPuntataSingola(gioc,i,incremento);
							
							*puntMax = gioc[i].puntata;
						}
						else
						{
							//se l'incremento più la puntata precedente non superano la puntata max, puntiamo la differenza
							incremento = *puntMax - gioc[i].puntata;
							
							if (incremento > gioc[i].fishes)
							{
								incremento = gioc[i].fishes;
							}
							
							GestisciPuntataSingola(gioc,i,incremento);
						}
						
					}
					
					
					break;
					
				case Colore:
					
					
				   incremento = TOT_FISH/4;
					
					if (incremento > gioc[i].fishes)
					//se la puntata da fare supera il limite max di fish... si va ALL-IN
					{
						incremento = gioc[i].fishes;
						
						GestisciPuntataSingola(gioc,i,incremento);
						
						if(gioc[i].puntata > *puntMax )
						{
							//se l'incremento più la puntata precedente superano la puntata max, abbiamo una nuova puntata max
							*puntMax = gioc[i].puntata;
						}
					}
					else
					{
						if(incremento + gioc[i].puntata > *puntMax )
						{
							//se l'incremento più la puntata precedente superano la puntata max, abbiamo una nuova puntata max
							GestisciPuntataSingola(gioc,i,incremento);
							
							*puntMax = gioc[i].puntata;
						}
						else
						{
							//se l'incremento più la puntata precedente non superano la puntata max, puntiamo la differenza
							incremento = *puntMax - gioc[i].puntata;
							
							if (incremento > gioc[i].fishes)
							{
								incremento = gioc[i].fishes;
							}
							
							GestisciPuntataSingola(gioc,i,incremento);
						}
						
					}
					
					break;
				case Full:
					
					incremento = TOT_FISH/4;
					
					if (incremento  > gioc[i].fishes)
					//se la puntata da fare supera il limite max di fish... si va ALL-IN
					{
						incremento = gioc[i].fishes;
						
						GestisciPuntataSingola(gioc,i,incremento);
						
						if(gioc[i].puntata > *puntMax )
						{
							//se l'incremento più la puntata precedente superano la puntata max, abbiamo una nuova puntata max
							*puntMax = gioc[i].puntata;
						}
					}
					else
					{
						if(incremento + gioc[i].puntata > *puntMax )
						{
							//se l'incremento più la puntata precedente superano la puntata max, abbiamo una nuova puntata max
							GestisciPuntataSingola(gioc,i,incremento);
							
							*puntMax = gioc[i].puntata;
						}
						else
						{
							//se l'incremento più la puntata precedente non superano la puntata max, puntiamo la differenza
							incremento = *puntMax - gioc[i].puntata;
							
							if (incremento > gioc[i].fishes)
							{
								incremento = gioc[i].fishes;
							}
							
							GestisciPuntataSingola(gioc,i,incremento);
						}
						
					}
					
					break;
				case Scala:
					
					incremento = 0;
					
					if (incremento  > gioc[i].fishes)
					//se la puntata da fare supera il limite max di fish... si va ALL-IN
					{
						incremento = gioc[i].fishes;
						
						GestisciPuntataSingola(gioc,i,incremento);
						
						if(gioc[i].puntata > *puntMax )
						{
							//se l'incremento più la puntata precedente superano la puntata max, abbiamo una nuova puntata max
							*puntMax = gioc[i].puntata;
						}
					}
					else
					{
						if(incremento + gioc[i].puntata > *puntMax )
						{
							//se l'incremento più la puntata precedente superano la puntata max, abbiamo una nuova puntata max
							GestisciPuntataSingola(gioc,i,incremento);
							
							*puntMax = gioc[i].puntata;
						}
						else
						{
							if(rand() % 4 > 2)
							{
								incremento = -1;
								GestisciPuntataSingola(gioc,i,incremento);
							}
							else
							{
								//se l'incremento più la puntata precedente non superano la puntata max, puntiamo la differenza
								incremento = *puntMax - gioc[i].puntata;
								
								if (incremento > gioc[i].fishes)
								{
									incremento = gioc[i].fishes;
								}
								
								GestisciPuntataSingola(gioc,i,incremento);
							}
								
						}
						
					}
					
					break;
				case Tris:
					
					if(rand() % 3 > 1)
					{
						incremento=0;
					}
					else
					{
						incremento = TOT_FISH/5;
					}
					
					
					if (incremento  > gioc[i].fishes)
					//se la puntata da fare supera il limite max di fish... si va ALL-IN
					{
						incremento = gioc[i].fishes;
						
						GestisciPuntataSingola(gioc,i,incremento);
						
						if(gioc[i].puntata > *puntMax )
						{
							//se l'incremento più la puntata precedente superano la puntata max, abbiamo una nuova puntata max
							*puntMax = gioc[i].puntata;
						}
					}
					else
					{
						if(incremento + gioc[i].puntata > *puntMax )
						{
							//se l'incremento più la puntata precedente superano la puntata max, abbiamo una nuova puntata max
							GestisciPuntataSingola(gioc,i,incremento);
							
							*puntMax = gioc[i].puntata;
						}
						else
						{
							if(rand() % 3 > 1)
							{
								incremento = -1;
								GestisciPuntataSingola(gioc,i,incremento);
							}
							else
							{
								//se l'incremento più la puntata precedente non superano la puntata max, puntiamo la differenza
								incremento = *puntMax - gioc[i].puntata;
								
								if (incremento > gioc[i].fishes)
								{
									incremento = gioc[i].fishes;
								}
								
								GestisciPuntataSingola(gioc,i,incremento);
							}
								
						}
						
					}
					
					break;
				case Doppia_Coppia:
					
					if(rand() % 2 == 1)
					{
						incremento=0;
					}
					else
					{
						incremento = TOT_FISH/6;
					}
					
					
					if (incremento  > gioc[i].fishes)
					//se la puntata da fare supera il limite max di fish... si va ALL-IN
					{
						incremento = gioc[i].fishes;
						
						GestisciPuntataSingola(gioc,i,incremento);
						
						if(gioc[i].puntata > *puntMax )
						{
							//se l'incremento più la puntata precedente superano la puntata max, abbiamo una nuova puntata max
							*puntMax = gioc[i].puntata;
						}
					}
					else
					{
						if(incremento + gioc[i].puntata > *puntMax )
						{
							//se l'incremento più la puntata precedente superano la puntata max, abbiamo una nuova puntata max
							GestisciPuntataSingola(gioc,i,incremento);
							
							*puntMax = gioc[i].puntata;
						}
						else
						{
							if(rand() % 3 > 1)
							{
								incremento = -1;
								GestisciPuntataSingola(gioc,i,incremento);
							}
							else
							{
								//se l'incremento più la puntata precedente non superano la puntata max, puntiamo la differenza
								incremento = *puntMax - gioc[i].puntata;
								
								if (incremento > gioc[i].fishes)
								{
									incremento = gioc[i].fishes;
								}
								
								GestisciPuntataSingola(gioc,i,incremento);
							}
								
						}
						
					}
					
					
					break;
				case Coppia:
					
					if(rand() % 3 > 1)
					{
						incremento=0;
					}
					else if (rand() % 4 > 2)
					{
						incremento = -1;
					}
					else
					{
						incremento = TOT_FISH/7;
					}
					
					
					if(incremento == -1)
					{
						GestisciPuntataSingola(gioc,i,incremento);
						break;
					}
					
					
					if (incremento  > gioc[i].fishes)
					//se la puntata da fare supera il limite max di fish... si va ALL-IN
					{
						incremento = gioc[i].fishes;
						
						GestisciPuntataSingola(gioc,i,incremento);
						
						if(gioc[i].puntata > *puntMax )
						{
							//se l'incremento più la puntata precedente superano la puntata max, abbiamo una nuova puntata max
							*puntMax = gioc[i].puntata;
						}
					}
					else
					{
						if(incremento + gioc[i].puntata > *puntMax )
						{
							//se l'incremento più la puntata precedente superano la puntata max, abbiamo una nuova puntata max
							GestisciPuntataSingola(gioc,i,incremento);
							
							*puntMax = gioc[i].puntata;
						}
						else
						{
							if(rand() % 3 > 1)
							{
								incremento = -1;
								GestisciPuntataSingola(gioc,i,incremento);
							}
							else
							{
								//se l'incremento più la puntata precedente non superano la puntata max, puntiamo la differenza
								incremento = *puntMax - gioc[i].puntata;
								
								if (incremento > gioc[i].fishes)
								{
									incremento = gioc[i].fishes;
								}
								
								GestisciPuntataSingola(gioc,i,incremento);
							}
								
						}
						
					}
					
					
		         break;
				case Carta_Alta:
					
					
					if (rand() % 6 > 4)
					{
						incremento = TOT_FISH/8;
					}
					else
					{
						incremento = -1;
					}
					
					
					if(incremento == -1)
					{
						GestisciPuntataSingola(gioc,i,incremento);
						break;
					}
					
					
					if (incremento  > gioc[i].fishes)
					//se la puntata da fare supera il limite max di fish... si va ALL-IN
					{
						incremento = gioc[i].fishes;
						
						GestisciPuntataSingola(gioc,i,incremento);
						
						if(gioc[i].puntata > *puntMax )
						{
							//se l'incremento più la puntata precedente superano la puntata max, abbiamo una nuova puntata max
							*puntMax = gioc[i].puntata;
						}
					}
					else
					{
						if(incremento + gioc[i].puntata > *puntMax )
						{
							//se l'incremento più la puntata precedente superano la puntata max, abbiamo una nuova puntata max
							GestisciPuntataSingola(gioc,i,incremento);
							
							*puntMax = gioc[i].puntata;
						}
						else
						{
							if(rand() % 3 > 1)
							{
								incremento = -1;
								GestisciPuntataSingola(gioc,i,incremento);
							}
							else
							{
								//se l'incremento più la puntata precedente non superano la puntata max, puntiamo la differenza
								incremento = *puntMax - gioc[i].puntata;
								
								if (incremento > gioc[i].fishes)
								{
									incremento = gioc[i].fishes;
								}
								
								GestisciPuntataSingola(gioc,i,incremento);
							}
								
						}
						
					}
					
			}
			sleep(2);
		}
	}
	
}


void InizializzaPartita(Carta m[NUM_CARTE], Player gioc[],int numGioc, int *numMani , int *numPuntate)
{
	int i;
	system("cls");
	printf("\n\n    ---- GIOCO DEL POKER ----\n\n");
	InizializzaMazzo(m);
	
	for(i=0;i<numGioc;i++)
	{
		gioc[i].inGioco = 1;
		gioc[i].fishes = TOT_FISH;
	}
	
	*numMani=1;
	*numPuntate=1;
}
