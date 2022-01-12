# Parallel-Computing-Cuda
Parallel Computing Exercises with Cuda

## CASO DI STUDIO
date 3 matrici:
- A (N righe e M colonne)
- B (M righe e P colonne)
- C (N righe e P colonne)

![Schermata da 2022-01-12 18-50-20](https://user-images.githubusercontent.com/10176197/149194959-2beb1c96-8454-4104-8f4b-2eb6ee11ffc1.png)


## CALCOLO MATRICIALE
C = C + A*B

## DATI
- Leading Dimension:   1500
- Matrici A B e C

## ELABORATO 1: Mat * Mat (i,k,j index)
- Dimensioni ottimali: 100
- GFlops massimi: 7,244048 Gflops
- Step: 50


## ELABORATO 2: Mat * Mat in blocks
- Dimensioni Blocchi : 100
- GFlops costanti : 6,5 - 7,2 Gflops
- Step: 100


## ELABORATO 3: Mat * Mat with Multi Threads

Per la decomposizione del calcolo della matrice C tra i thread, si faccia riferimento alla
seguente figura con 4 thread (NTrow = 2 , NTcol = 2)

![Schermata da 2022-01-12 18-55-14](https://user-images.githubusercontent.com/10176197/149195466-1006829d-2d1d-45dc-9ef8-5026533808d8.png)

- Dimensioni Blocchi : 100
- Step: 200
- 1 Thread : Gflops costanti a punto 2
- 2 Thread : Gflops raddoppiano rispetto a 1 thread
			 Picco massimo : 13,75318 Gflops
			 SpeedUp(2) Max : 1,92
			 Efficienza Max : 0,96

- 4 Thread : Gflops raddoppiano rispetto a 2 thread
			 Picco massimo : 25,687102 Gflops
			 SpeedUp(4) Max : 3,96
			 Efficienza Max : 0,99
			 
