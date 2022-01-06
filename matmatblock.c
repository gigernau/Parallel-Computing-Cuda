#include "matmat.h"

/********************************************************

Studente: Gianluca De Lucia N97000311

********************************************************/

void matmatblock(int LDA, int LDB, int LDC, double *A, double *B, double *C, int N, int M, int P,int DBN, int DBM, int DBP){
    for (int i = 0; i <N/DBN ; i++)
    {
        for (int k = 0; k < P/DBM; k++)
        {
            for (int j = 0; j < M/DBP; j++)
            {
                matmatikj(LDA, LDB, LDC, (A+i*DBN*LDA+k*DBN), (B+k*DBM*LDB+j*DBM),(C+i*DBN*LDC+j*DBP), DBN,DBM,DBP);
   
            }
        }
    }
}
