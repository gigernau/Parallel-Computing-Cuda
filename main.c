/********************************************************

Studente: Gianluca De Lucia N97000311

********************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"c_timer.h"
#include"matmat.h"
#include"matmatblock.h"
#include"matmatthread.h"



void stampaRis1(int, double, double, double, double, double, double);
void stampaRis2(int , double );
void stampaRis3(int ,int,double,double);
double Noptimal(double, double *, int, int);
void aggMatrixTmp (int , double *, double *);
void popolamentoMatrici (double *, double *, double *, int);
void IKJBlockThread(int, int , int ,double *, double *, double *, double *, int);

int main(){

	//Dichiarazione variabili
	double *A, *B, *C, *tmp;
	double t1, t2, flops1, flops2, flops3, flops4, flops5, flops6, flopsBlock, NN, absmax, maxdiff,optABS,optREL;
	int N, LD=1500, i, j, k, m = 50, Nopt=0,optFOR;
	

	//Allocazione di memoria per le matrici
	A=(double*)malloc(sizeof(double)*LD*LD);
	B=(double*)malloc(sizeof(double)*LD*LD);
	C=(double*)malloc(sizeof(double)*LD*LD);
	tmp=(double*)malloc(sizeof(double)*LD*LD);
	


	//popolamento matrici con valori random
	popolamentoMatrici(A,B,C,LD);
	
	optABS= 0.0;
	optREL=0.0;

	//Definizione tabella di stampa
	printf("\tN\t1) IJK\t\t2)JIK\t\t3)IKJ\t\t4)KIJ\t\t5)KJI\t\t6)JKI\n\n");

	//Step di 50 
	for (N=m; N<=1500 ; N+=m)
	{
		
		NN=N;

		//aggiornamento matrice temporanea di appoggio
		aggMatrixTmp (N,C,tmp);

		/**
		*
		*   INDICI:   IJK
		*
		**/
		t1=get_cur_time();
		matmatijk(LD, LD, LD, A, B, tmp, N, N, N);
		t2=get_cur_time()-t1;
		flops1=(2*NN*NN*NN)/t2/1.e9;

		//aggiornamento matrice temporanea di appoggio
		aggMatrixTmp (N,C,tmp);
		

		/**
		*
		*   INDICI:   JIK
		*
		**/
		t1=get_cur_time();
		matmatjik(LD, LD, LD, A, B, tmp, N, N, N);
		t2=get_cur_time()-t1;
		flops2=(2*NN*NN*NN)/t2/1.e9;

		//aggiornamento matrice temporanea di appoggio
		aggMatrixTmp (N,C,tmp);	



		/**
		*
		*   INDICI:   IKJ
		*
		**/
		t1=get_cur_time();
		matmatikj(LD, LD, LD, A, B, tmp, N, N, N);
		t2=get_cur_time()-t1;
		flops3=(2*NN*NN*NN)/t2/1.e9;

		//aggiornamento matrice temporanea di appoggio
		aggMatrixTmp (N,C,tmp);
		

		/**
		*
		*   INDICI:   KIJ
		*
		**/
		t1=get_cur_time();
		matmatkij(LD, LD, LD, A, B, tmp, N, N, N);
		t2=get_cur_time()-t1;
		flops4=(2*NN*NN*NN)/t2/1.e9;


		//aggiornamento matrice temporanea di appoggio
		aggMatrixTmp (N,C,tmp);
		


		/**
		*
		*   INDICI:   KJI
		*
		**/
		t1=get_cur_time();
		matmatkji(LD, LD, LD, A, B, tmp, N, N, N);
		t2=get_cur_time()-t1;
		flops5=(2*NN*NN*NN)/t2/1.e9;
		

		//aggiornamento matrice temporanea di appoggio
		aggMatrixTmp (N,C,tmp);



		/**
		*
		*   INDICI:   JKI
		*
		**/
		t1=get_cur_time();
		matmatjki(LD, LD, LD, A, B, tmp, N, N, N);
		t2=get_cur_time()-t1;
		flops6=(2*NN*NN*NN)/t2/1.e9;

		//aggiornamento matrice temporanea di appoggio
		aggMatrixTmp (N,C,tmp);


		//Stampa tabellare
		printf("\t%d\t%f\t%f\t%f\t%f\t%f\t%f\n",N,flops1,flops2,flops3,flops4,flops5,flops6);

		//Stampo su file
		stampaRis1(N,flops1,flops2,flops3,flops4,flops5,flops6);

		//aggiornamento valore massimo di N che massimizza i Gflops
		double fl[6] = {flops1,flops2,flops3,flops4,flops5,flops6};

		optREL = Noptimal(optABS,fl,Nopt,N);
		

		//AGGIONAMENTO MAX ABS
		if (optABS < optREL){
			optABS = optREL;
			Nopt = N;
		}
		
	}
		printf("\nGFopt: %f",optABS);
		printf("\nNopt: %d",Nopt);

		printf("\n\nDIMENSIONI OTTIMALI : %d\n", Nopt);



		//MATMATBLOCK

		printf("\n\nMAT MAT BLOCK\n\n");
		
		//Definizione tabella di stampa
		printf("\tN\t\tBlock IKJ\n\n");

		for (N=Nopt; N<=1500 ; N+=Nopt){

			NN=N;

			//aggiornamento matrice temporanea di appoggio
			aggMatrixTmp (N,C,tmp);

			t1=get_cur_time();
			matmatblock(LD, LD, LD, A, B, tmp, N, N, N,Nopt,Nopt,Nopt);
			t2=get_cur_time()-t1;
			flopsBlock=(2*NN*NN*NN)/t2/1.e9;
			printf("\n\t%d\t\t%f",N,flopsBlock);
			stampaRis2(N,flopsBlock);

		}
		printf("\n");


		//MATMATTHREAD

		printf("\n\nMAT MAT THREAD\n\n");
		
		

		//1 Thread
		IKJBlockThread(Nopt, 1, 1, A, B, C, tmp, LD);
		//2 Thread
		IKJBlockThread(Nopt, 1, 2, A, B, C, tmp, LD);
		//3 Thread
		IKJBlockThread(Nopt, 2, 2, A, B, C, tmp, LD);



}




//FUNZIONI

void stampaRis1(int N, double f1, double f2, double f3, double f4, double f5, double f6){

	FILE *fd;
    
    /* apre il file in scrittura */
    fd=fopen("MatMat.txt", "a");
    //Gestioni errori
    if( fd==NULL ) {
        perror("Errore in apertura del file");
    	exit(1);
    }

    /* scrive il numero */
    fprintf(fd,"\t%d\t\t%f\t%f\t%f\t%f\t%f\t%f\n",N,f1,f2,f3,f4,f5,f6);

    /* chiude il file */
    fclose(fd);
}

void stampaRis2(int N, double f1){

	FILE *fd;
    
    /* apre il file in scrittura */
    fd=fopen("matmatblock.txt", "a");
    //Gestioni errori
    if( fd==NULL ) {
        perror("Errore in apertura del file");
    	exit(1);
    }

    /* scrive il numero */
    fprintf(fd,"\t%d\t%f\n",N,f1);

    /* chiude il file */
    fclose(fd);
}

void stampaRis3(int nthread, int N, double f1, double time){

	FILE *fd;
	fd=fopen("matmatthread.txt", "a");
	if( fd==NULL ) {
		perror("Errore in apertura del file");
		exit(1);
	}

	fprintf(fd, "%d\t%d\t%f\t%f\n",nthread,N,f1,time);

	fclose(fd);
}

double Noptimal(double optABS, double *fl, int Nopt, int N){

	double optREL=0.0;
	
	//aggiornamento valore ottimale di N che massimizza i Gflops
	for(int i = 0 ; i < 6; i++){
		if(optREL < fl[i]){
			optREL = fl[i];
		}
	}

	
	return optREL;
		
}



void aggMatrixTmp (int LD, double *C, double *tmp){

	//aggiornamento matrice temporanea di appoggio
		for (int i = 0; i < LD; i++)
		{
			for (int j = 0; j < LD; j++)
			{
				*(tmp+i*LD +j)= *(C+i*LD +j);
			}

		}
}

void popolamentoMatrici(double *A, double *B, double *C, int LD){


	//Popolazione randomica delle matrici A B e C
	for ( int i = 0; i < LD; i++)
	{
		for ( int j = 0; j < LD; j++)
		{
			*(A+i*LD +j)=(float)rand()/RAND_MAX;
			*(B+i*LD +j)=(float)rand()/RAND_MAX;
			*(C+i*LD +j)=(float)rand()/RAND_MAX;
		}
		
	}

	printf("Popolamento delle matrici A B e C terminato con successo.\n" );
}



void IKJBlockThread(int Nopt, int NTrow, int NTcol,double *A, double *B, double *C, double *tmp, int LD){

		int nthread; 
		int N;
		double t1,t2,NN,flopsThread;

		//numero dei thread totali
		nthread = NTrow*NTcol;


		//Definizione tabella di stampa
		printf("\n\t%d Thread\n\n",nthread);

		for (N=Nopt; N<=1500 ; N+=Nopt){
					
			NN=N;

			//N tale che esso sia multiplo di entrambi i prodotti Nopt*NTrow e Nopt*NTcol
			if(N%(Nopt*NTcol) == 0){

				aggMatrixTmp(LD,C,tmp);
				t1 = get_cur_time();
				matmatthread(LD, LD, LD, A, B, tmp, N, N, N,Nopt,Nopt,Nopt,NTrow,NTcol);
				t2=get_cur_time()-t1;

				flopsThread=(2*NN*NN*NN)/t2/1.e9;
				printf("\n\t%d\t%f",N,flopsThread);


				stampaRis3(nthread,N,flopsThread,t2);


			}
		}

}


