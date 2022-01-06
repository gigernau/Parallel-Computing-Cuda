#include "matmatblock.h"
#include <pthread.h>


/********************************************************

Studente: Gianluca De Lucia N97000311

********************************************************/

struct matrixStruct{
    double *A;
    double *B;
    double *C;
    int ldA;
    int ldB;
    int ldC;
    int rowsA;
    int colRowM;
    int colB;
    int blockDimR;
    int blockDimC;
    int blockDimtmp;
};

void* matBlockThread(void *arg){
    struct matrixStruct *args = (struct matrixStruct*)arg;
   
    matmatblock( args->ldA, args->ldB, args->ldC,
			args->A, args->B, args->C,
            args->rowsA, args->colB, args->colRowM,
            args->blockDimR, args->blockDimC,args->blockDimtmp);

    return 0;
}


void matmatthread (int LDA, int LDB, int LDC, double *A, double *B, double *C, int N, int M, int P,int DBN, int DBM, int DBP, int NTrow, int NTcol){
    int i=0, j=0;
    
    //Calcoliamo la dimensione del blocco delle righe da assegnare a ciascuna sottomatrice
    int step_i = N / NTrow;
    //Calcoliamo la dimensione del blocco delle colonne da assegnare a ciascuna sottomatrice.
    int step_j = P / NTcol;

    //Creiamo la griglia di thread
    pthread_t tid[NTrow][NTcol];

    //Creaimo una matrice di record che conterranno i dati che ciascun thread deve calcolare
    struct matrixStruct matThread[NTrow][NTcol];   

    //Suddividiamo ora le matrici, calcolando, per ciascun thread i dati che deve calcolare
    for(i=0; i<NTrow; i++){
        for(j=0; j<NTcol; j++){

            matThread[i][j].A = A + i*LDA*step_i; 			 //righe di A
            matThread[i][j].B = B + j*step_j;				 //colonne di B
            matThread[i][j].C = C + i*LDC*step_i + j*step_j;  //righe e colonne di C

            matThread[i][j].ldA = LDA;
            matThread[i][j].ldB = LDB;
            matThread[i][j].ldC = LDC;

            matThread[i][j].rowsA = step_i;
            matThread[i][j].colRowM = M;
            matThread[i][j].colB = step_j;

            matThread[i][j].blockDimR = DBN;
            matThread[i][j].blockDimC = DBP;
            matThread[i][j].blockDimtmp = DBN;
            
            //Lanciamo il processo
            //printf("\nProcesso %ld,",tid[i][j]);
            pthread_create(&tid[i][j], NULL, matBlockThread, &matThread[i][j]);
        }
    }
    
    //Aspettiamo che tutti i processi finiscano il loro calcolo prima di ritornare.
    for(i=0; i<NTrow; i++)
        for(j=0; j<NTcol; j++)
            pthread_join(tid[i][j], NULL);
            
}

