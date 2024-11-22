#include <stdio.h>
#include <stdlib.h>
#include <mpi.h> 
#include "ModVida.h"
#include "WallTime.h"

int main(int argc, char *argv[]) {
  
  // inscreve em MPI

  if (MPI_Init(&argc, &argv) != MPI_SUCCESS) {
    printf("MPI_Init falhou\n"); exit(0);
  }
  
  // tamanho do tabuleiro

#define POW 11
  const int tam = 1 << POW;

  // numero de processos, qual processo eu sou

  int numProc;
  if (MPI_Comm_size(MPI_COMM_WORLD, &numProc)!=MPI_SUCCESS) {
    printf("MPI_Comm_size falhou\n"); MPI_Finalize(); exit(0);
  }
  int myId;
  if (MPI_Comm_rank(MPI_COMM_WORLD, &myId)!=MPI_SUCCESS) {
    printf("MPI_Comm_rank falhou\n");; MPI_Finalize(); exit(0);
  }
  if (numProc > tam) {
    printf("Ha mais processos MPI (%d) do que linhas no tabuleiro (%d)\n",
           numProc, tam); ; MPI_Finalize(); exit(0);
  }

  // processos vizinhos antes e depois

  const int procAntes  = (myId==0)? MPI_PROC_NULL : myId-1;
  const int procDepois = (myId==numProc-1)? MPI_PROC_NULL : myId+1;

  // divisao de dominio do tabuleiro sem as bordas
  // tamLocal eh o tamanho do tabuleiro neste processo MPI sem as bordas
  // desloc eh o deslocamento a ser adicionado ao indice local para obter o indice global
  
  int tamLocal=tam/numProc;
  const int resto=tam%numProc;
  int desloc;
  if (myId < resto) {
    tamLocal++;
    desloc=tamLocal*myId;
  }
  else 
    desloc=tamLocal*myId+resto;

  // aloca e inicializa tabuleiros

  const double t0 = WallTime();
  int* restrict tabulIn  = (int *) malloc ((tamLocal+2)*(tam+2)*sizeof(int));
  int* restrict tabulOut = (int *) malloc ((tamLocal+2)*(tam+2)*sizeof(int));
  InitTabul(tabulIn, tabulOut, tam, myId, tamLocal, desloc);

  // percorre geracoes do tabuleiro
  
  const double t1 = WallTime();
  for (int i=0; i<2*(tam-3); i++) {
    UmaVida(tabulIn, tabulOut, tam, tamLocal, procAntes, procDepois);
    UmaVida(tabulOut, tabulIn, tam, tamLocal, procAntes, procDepois);
  }
  const double t2 = WallTime();
  
  // verifica correcao
  
  const bool corrTotal=Correto(tabulIn, tam, myId, tamLocal, desloc);
  if (myId == 0) {
    if (corrTotal)
      printf("**RESULTADO CORRETO** ");
    else {
      printf("**RESULTADO ERRADO**\n");
      fflush(stdout);
      MPI_Abort(MPI_COMM_WORLD, -1);
    }
  }
    
  // imprime resultado
    
  const double t3 = WallTime();
  if (myId == 0)
    printf("numProc=%d; tam=%d; tempos: init=%f, comp=%f, fim=%f, tot=%f \n", 
	   numProc, tam, t1-t0, t2-t1, t3-t2, t3-t0);

  // dealoca tabuleiros

  free(tabulIn);
  free(tabulOut);
  MPI_Finalize();
  exit(0);    
}
