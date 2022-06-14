#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
	printf("\n\n-------------------------Progetto di Calcolo Parallelo-------------------------\n\n");
	int N,M,id_thread,i,j,numT;
	double t0,t1,t;

	//Controllo del parametro di input
	if(argc>1 && (atoi(argv[1])))
		numT=atoi(argv[1]);
	else
	{
		printf("Attenzione! Il numero di thread e' assente o errato! Riprovare!\n");
		exit(EXIT_FAILURE);
	}

	//Generazione del seed
    	srand(time(0));

	//Lettura delle dimensioni della matrice A e conseguenti controlli
	do {
		printf("Inserisci il valore delle righe\n");
   		scanf("%d",&N);
		if(N==0)
			printf("\nAttenzione! La matrice deve avere almeno una riga!\n\n");
	}
	while(N==0);
	do {
		printf("\nInserisci il valore delle colonne\n");
   		scanf("%d",&M);
		if(M==N)
			printf("\nAttenzione! Il numero di colonne della matrice deve essere diverso dal numero di righe!\n\n");
		if(M==0)
			printf("\nAttenzione! La matrice deve avere almeno una colonna!!\n\n");
	}
	while(M==N || M==0);

	//Allocazione della memoria per la matrice A
    	int *A;
    	A=(int*)malloc(N*M*sizeof(int));

	//Generazione e stampa dei valori pseudo casuali della matrice A
	printf("\n\nStampa della matrice appena generata:\n");
	for(i=0;i<N;i++)
    	{
      	for(j=0;j<M;j++)
        	{
            	A[i*M+j]=1+rand()%100;
            	printf("%d\t",A[i*M+j]);
        	}
        	printf("\n");
    	}
	//Allocazione della memoria per il vettore c
    	int *c=calloc(M,sizeof(int));
	printf("\n\n");

	//Prima chiamata a omp_get_wtime
	t0=omp_get_wtime();

	//Regione parallela
    	#pragma omp parallel for schedule(static) shared(N,M,A,c) private(i,j) num_threads(numT)
    		for(j=0;j<M;j++)
    		{
			c[j]=101;
        		for(i=0;i<N;i++)
        		{
            		if(A[i*M+j]<c[j])
					c[j]=A[i*M+j];
        		}
			printf("Mi chiamo %d e ho calcolato il %d%c valore dell'array c e cioe' %d\n",omp_get_thread_num(),j+1,167,c[j]);
    		}

	//Seconda chiamata a omp_get_wtime()
	t1=omp_get_wtime();
	t=t1-t0;

	//Stampa dei risultati
	printf("\n\nSono stati necessari %lf secondi\n",t);
	printf("\n\nStampa del vettore risultato:\n");
    	for(i=0;i<M;i++)
      	printf("%d\t",c[i]);

	//Deallocazione della memoria
	free(A);
    free(c);
    return 0;
}
