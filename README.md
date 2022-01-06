# Parallel-Computing-Cuda
Parallel Computing Exercises with Cuda

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


## ELABORATO 3: Mat * Mat with Threads

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
