#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "c_timer.h"
#include <math.h>
#include <mpi.h>
#include "matmatthread.h"



void bCastMod(MPI_Comm newcomm, int proc, int lda, int n, int m, double* A){
    
    int myid,i,j;
    MPI_Comm_rank(newcomm, &myid);
    double tmp[n][m];

    if(proc==myid) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++) {
                tmp[i][j] = *(A+i*lda+j);
            }
        }
    }

    MPI_Bcast(tmp, n*m, MPI_DOUBLE,proc, newcomm);

    if(myid!=proc){
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                *(A+i*lda+j) = tmp[i][j];
            }
        }
    }
}

void matmatdist(int LDA, int LDB, int LDC, double *A, double *B, double *C, int M, int N, int P,int DBN, int DBM, int DBP, int NTrow, int NTcol, int SR, int SC){
 
   
    int rank,gridrank, size, dims[2], period[2], coord[2],Arow,Bcol;
    MPI_Comm gridComm, rowComm, colComm;
    int k,k2;
    double *Atmp, *Btmp;
    double *Acalc=NULL, *Bcalc=NULL;
    int LDAcalc, LDBcalc;
    
    //gestione partizioni delle matrici
    N=N/SR;
    M=M/SR/SC;
    P=P/SC;

    MPI_Comm_rank( MPI_COMM_WORLD, &rank);
    MPI_Comm_size( MPI_COMM_WORLD, &size);    
    

    //Creazione della griglia
    period[0]=1;
    period[1]=1;

    dims[0]=SR;
    dims[1]=SC;

    MPI_Cart_create(MPI_COMM_WORLD,2,dims,period,1,&gridComm);
    MPI_Cart_get(gridComm, 2, dims, period, coord);

    MPI_Comm_rank(gridComm,&rank);
    MPI_Cart_coords(gridComm,rank,2,coord);



    //Split in soottogriglie
    int stay[]={0,1};
    MPI_Cart_sub(gridComm,stay,&rowComm);
    stay[0]=1;
    stay[1]=0;
    MPI_Cart_sub(gridComm,stay,&colComm);

    MPI_Comm_size(rowComm, &k2);
    

    
    for(k=0; k<k2; k++){
        
        //broadcast A[coord[0]][k] su riga coord[0]
        if(k==coord[1]){
            //broadcast mia matrice verso gli altri
            bCastMod(rowComm, k, LDA, N, M, A);
            LDAcalc = LDA;
            Acalc = A;
        }else{
            //ricevo mia matrice da processore k di riga
            bCastMod(rowComm, k, LDA, N, M, Atmp);
            Acalc = Atmp;
            LDAcalc = M;

        }

        //broadcast B[k][coord[1]] su colonna coord[1]
        if(k==coord[0]){

            bCastMod(colComm, k, LDB, M, P, B);
            Bcalc = B;
            LDBcalc = LDB;

        }else{
            
            bCastMod(colComm, k, LDB, M, P, Btmp);
            Bcalc = Btmp;
            LDBcalc = P;

        }

        matmatthread(LDAcalc, LDBcalc, LDC, Acalc, Bcalc, C, N, M, P,DBN,DBM,DBP,NTrow,NTcol);
    }
    
}
