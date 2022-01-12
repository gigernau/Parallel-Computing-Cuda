#include <stdio.h>
#include<stdlib.h>
#include<cuda_runtime.h>
#include <time.h>
#include <windows.h>
const int MAX_ROW_THREADS = 32; // 32x32 ---> 1024 thread su GPU
#define MAX 30


//eseguita da device e richiamabile da host e definisce funzione kernel
__global__ void cudamatmat(float * A,float * B,float * C, int N, int M, int P){
//sono matrici quadrate uso solo N

 int idy = blockIdx.y*blockDim.y+threadIdx.y;
 int idx = blockIdx.x*blockDim.x+threadIdx.x;

    float tmpSum = 0;

    if (idy < N && idx < N) {
        // each thread computes one element of the block sub-matrix
        for (int k = 0; k < N; k++) {
            tmpSum += A[idy * N + k] * B[k * N + idx];
        }
    }
    C[idy * N + idx] += tmpSum;
}




int main(){
	
	float *A, *B, *C;
	float *A_gpu= NULL, *B_gpu=NULL, *C_gpu=NULL;
	float total_t;
	int size = sizeof(float);
	float dim = 8000;
	int i;
	int numBlocks = dim / MAX_ROW_THREADS;
	clock_t start,stop;
	float gflops;

	//Imposta il dispositivo da utilizzare per le esecuzioni GPU.
	cudaSetDevice(0);

	//allocazione matrici
	A=(float*)malloc(size*dim*dim); 
	B=(float*)malloc(size*dim*dim);
	C=(float*)malloc(size*dim*dim);

	//popolamento matrici
	for(i=0;i<dim*dim;i++){
	 	A[i] = rand()*MAX;
	 	B[i] = rand()*MAX;
	 	C[i] = rand()*MAX;
	}

	//copia delle matrici sul device
    cudaMemcpy(A_gpu,A,size*dim*dim,cudaMemcpyHostToDevice);
	cudaMemcpy(B_gpu,B,size*dim*dim,cudaMemcpyHostToDevice);
	cudaMemcpy(C_gpu,C,size*dim*dim,cudaMemcpyHostToDevice);

	//Una configurazione definisce la griglia e il numero di threads per ogni blocco
	dim3 DimGrid(numBlocks, numBlocks);    //(dimensione / 32 )^2
	dim3 DimBlock(MAX_ROW_THREADS, MAX_ROW_THREADS, 1); //numero di threads per block (1024)

	printf("\nStart Time: \n\n");
	start=clock();

	//estensione sintassi c
	cudamatmat <<< DimGrid, DimBlock >>> (A_gpu, B_gpu, C_gpu, dim, dim, dim);
	
	//mettere la CPU in attesa della terminazione 
	//di tutte le operazioni in esecuzione sul device
	cudaThreadSynchronize();

	stop=clock();
	printf("\nStop Time: \n\n");
	total_t =((float)(stop-start))/CLOCKS_PER_SEC;
	gflops = 2.0 * dim * dim * dim /(total_t)/ 1.e9;
	cudaMemcpy(C,C_gpu,size*dim*dim,cudaMemcpyDeviceToHost);


	printf("\nRisultati:\n");
	printf("\nGflops: %f\n\n",gflops);
	printf("\nTime: %f\n\n",total_t);

	//deallocazione memoria device
	cudaFree(A_gpu);
	cudaFree(B_gpu);
	cudaFree(C_gpu);
	system("PAUSE");
	
}
