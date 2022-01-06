
/********************************************************

Studente: Gianluca De Lucia N97000311

********************************************************/

void matmatijk(int LDA, int LDB, int LDC, double *A, double *B, double *C, int N, int M, int P){

	for (int i = 0; i <N ; i++)
	{
		for (int j = 0; j < P; j++)
		{
			for (int k = 0; k < M; k++)
			{
				*(C+i*LDC +j) = *(C+i*LDC +j)+((*(A+i*LDA +k)) * (*(B+k*LDB +j)));
			}
		}

	}

}
void matmatjik(int LDA, int LDB, int LDC, double *A, double *B, double *C, int N, int M, int P){

	for (int j = 0; j < P; j++)
	{
		for (int i = 0; i < N ; i++)
		{
			for (int k = 0; k < M; k++)
			{
				*(C+i*LDC +j) = *(C+i*LDC +j)+((*(A+i*LDA +k)) * (*(B+k*LDB +j)));
			}
		}

	}

}
void matmatkij(int LDA, int LDB, int LDC, double *A, double *B, double *C, int N, int M, int P){

	for (int k = 0; k < M; k++)
	{	
		for (int i = 0; i < N ; i++)
		{
			for (int j = 0; j < P; j++)
			{

				*(C+i*LDC +j) = *(C+i*LDC +j)+((*(A+i*LDA +k)) * (*(B+k*LDB +j)));
			}
		}

	}
}
void matmatikj(int LDA, int LDB, int LDC, double *A, double *B, double *C, int N, int M, int P){

	for (int i = 0; i < N ; i++)
	{
		for (int k = 0; k < M; k++)
		{
			for (int j = 0; j < P; j++)
			{
				*(C+i*LDC +j) = *(C+i*LDC +j)+((*(A+i*LDA +k)) * (*(B+k*LDB +j)));
			}
		}

	}
}
void matmatkji(int LDA, int LDB, int LDC, double *A, double *B, double *C, int N, int M, int P){

	for (int k = 0; k < M; k++)
	{
		for (int j = 0; j < P; j++)
		{
			for (int i = 0; i <N ; i++)
			{
				*(C+i*LDC +j) = *(C+i*LDC +j)+((*(A+i*LDA +k)) * (*(B+k*LDB +j)));
			}
		}

	}
}


void matmatjki(int LDA, int LDB, int LDC, double *A, double *B, double *C, int N, int M, int P){

	for (int j = 0; j < P; j++)
	{
		for (int k = 0; k < M; k++)
		{
			for (int i = 0; i <N ; i++)
			{
				*(C+i*LDC +j) = *(C+i*LDC +j)+((*(A+i*LDA +k)) * (*(B+k*LDB +j)));
			}
		}

	}
}
