#include "ModVida.h"

// UmaVida: Executa uma iteracao do Jogo da Vida
//          em tabuleiros de tamanho tam. Produz o tabuleiro
//          de saida tabulOut a partir do tabuleiro de entrada
//          tabulIn. Os tabuleiros tem (tam, tam) celulas
//          internas vivas ou mortas. Tabuleiros sao orlados 
//          por celulas eternamente mortas.
//          Tabuleiros sao dimensionados tam+2 x tam+2.


void UmaVida(int* restrict tabulIn, int* restrict tabulOut, const int tam, 
	     const int tamLocal, const int procAntes, const int procDepois) {

  MPI_Request reqs[4];

  if (procAntes != MPI_PROC_NULL) {
    MPI_Irecv(&tabulIn[ind2d(0, 0)], tam + 2, MPI_INT, procAntes, 0, MPI_COMM_WORLD, &reqs[0]);
    MPI_Isend(&tabulIn[ind2d(1, 0)], tam + 2, MPI_INT, procAntes, 1, MPI_COMM_WORLD, &reqs[1]);
  } else {
    reqs[0] = MPI_REQUEST_NULL;
    reqs[1] = MPI_REQUEST_NULL;
  }

  if (procDepois != MPI_PROC_NULL) {
    MPI_Irecv(&tabulIn[ind2d(tamLocal + 1, 0)], tam + 2, MPI_INT, procDepois, 1, MPI_COMM_WORLD, &reqs[2]);
    MPI_Isend(&tabulIn[ind2d(tamLocal, 0)], tam + 2, MPI_INT, procDepois, 0, MPI_COMM_WORLD, &reqs[3]);
  } else {
    reqs[2] = MPI_REQUEST_NULL;
    reqs[3] = MPI_REQUEST_NULL;
  }

  MPI_Waitall(4, reqs, MPI_STATUSES_IGNORE);

  
  for (int i=1; i<=tamLocal; i++) {
    for (int j= 1; j<=tam; j++) {
      const int vizviv = 
	tabulIn[ind2d(i-1,j-1)] + 
	tabulIn[ind2d(i-1,j  )] +
	tabulIn[ind2d(i-1,j+1)] + 
	tabulIn[ind2d(i  ,j-1)] + 
	tabulIn[ind2d(i  ,j+1)] + 
	tabulIn[ind2d(i+1,j-1)] + 
	tabulIn[ind2d(i+1,j  )] + 
	tabulIn[ind2d(i+1,j+1)];
      if (tabulIn[ind2d(i,j)] && vizviv < 2) 
	tabulOut[ind2d(i,j)] = 0;
      else if (tabulIn[ind2d(i,j)] && vizviv > 3) 
	tabulOut[ind2d(i,j)] = 0;
      else if (!tabulIn[ind2d(i,j)] && vizviv == 3) 
	tabulOut[ind2d(i,j)] = 1;
      else
	tabulOut[ind2d(i,j)] = tabulIn[ind2d(i,j)];
    }
  }
}


// DumpTabul: Imprime trecho do tabuleiro entre
//            os indices globais (first,first) e (last,last)
//            X representa celula viva
//            . representa celula morta
//            Imprime mensagem "msg" antes do trecho do tabuleiro
//            para identificar cada invocacao 


void DumpTabul(int* restrict tabul, const int tam, 
	       const int first, const int last, char* restrict msg, 
	       const int myId, const int tamLocal, const int desloc){

  if (myId==0) {
    printf("%s; Dump posicoes [%d:%d, %d:%d] de tabuleiro %d x %d\n", 
	   msg, first, last, first, last, tam, tam);
    for (int i=first; i<=last; i++) printf("="); printf("=\n");
  }

  // para cada linha desejadas do tabuleiro global:
  //   se este processo for o dono da linha:
  //      se sou o processo 0, imprimo o trecho desejado
  //      senao, envio a linha para o processo 0
  //   se sou o processo 0 e nao sou o dono da linha:
  //      recebo a linha e imprimo o trecho desejado
  
  for (int indGlo=first; indGlo<=last; indGlo++) {
    const int indLoc=indGlo-desloc;
    if ((indLoc>0) & (indLoc<=tamLocal)) {
      if (myId == 0) {
	for (int ij=ind2d(indLoc,first); ij<=ind2d(indLoc,last); ij++)
	  printf("%c", tabul[ij]? 'X' : '.');
	printf("\n");
      }
      else {
	if (MPI_Send(tabul+ind2d(indLoc,first), last-first+1, MPI_INT,
		     0, indGlo, MPI_COMM_WORLD) != MPI_SUCCESS) {
          printf("Send no DumpTabul falhou\n"); MPI_Finalize(); exit(-1);
        } 
      }
    }
    else if (myId == 0) {
      MPI_Status status;
      int linha[tam+2];
      if (MPI_Recv(linha, tam+2, MPI_INT,
		   MPI_ANY_SOURCE, indGlo, MPI_COMM_WORLD, &status) != MPI_SUCCESS) {
        printf("Recv no DumpTabul falhou\n"); MPI_Finalize(); exit(-1);
      } 
      for (int ij=0; ij<last-first+1; ij++)
	printf("%c", linha[ij]? 'X' : '.');
      printf("\n");
    }
  }

  if (myId==0) {
    for (int i=first; i<=last; i++) printf("="); 
    printf("=\n");
  }
}



// InitTabul: Inicializa os trechos locais dos dois tabuleiros:
//            tabulIn com um veleiro no canto superior esquerdo
//            tabulOut com celulas mortas



void InitTabul(int* restrict tabulIn, int* restrict tabulOut, const int tam, 
	       const int myId, const int tamLocal, const int desloc) {

  // nulifica os trechos locais dos dois tabuleiros, incluindo as ghost zone
  
  for (int ij=0; ij<(tamLocal+2)*(tam+2); ij++) {
    tabulIn[ij] = 0;
    tabulOut[ij] = 0;
  }

  // coloca o veleiro na posicao inicial do tabuleiro global
  // para cada linha global do veleiro:
  //   se a linha global estah representada neste processo:
  //      coloca o trecho do veleiro
  // PS: uma linha estah representada neste processo sse:
  //   este processo eh o dono da linha;
  //   a linha estah em uma das ghost zones deste processo
  
  int indGlo,indLoc;

  // primeira linha global

  indGlo=1; indLoc=indGlo-desloc;
  if ((indLoc>=0) & (indLoc<tamLocal+2)) {
    tabulIn[ind2d(indLoc,2)] = 1; 
  }

  // segunda linha global

  indGlo=2; indLoc=indGlo-desloc;
  if ((indLoc>=0) & (indLoc<tamLocal+2)) {
    tabulIn[ind2d(indLoc,3)] = 1; 
  }

  // terceira linha global

  indGlo=3; indLoc=indGlo-desloc;
  if ((indLoc>=0) & (indLoc<tamLocal+2)) {
    tabulIn[ind2d(indLoc,1)] = 1; 
    tabulIn[ind2d(indLoc,2)] = 1; 
    tabulIn[ind2d(indLoc,3)] = 1; 
  }
}

  
// Correto: Verifica se a configuracao final do tabuleiro
//          estah correta ou nao (veleiro no canto inferior direito)



bool Correto(int* restrict tabul, const int tam, const int myId,	\
	     const int tamLocal, const int desloc) {

  bool corrLocal=true; // correto neste processo

  // percorre todas as linhas do tabuleiro local
  // incluindo as duas ghost zone
  
  for (int linLoc=0; linLoc<tamLocal+2; linLoc++) {

    // conta celulas vivas na linha

    int cnt=0;
    for (int col=0; col<tam+2; col++)
      cnt += tabul[ind2d(linLoc,col)];

    // linha global correspondente

    const int linGlo=linLoc+desloc;

    // linhas globais acima da posicao final do veleiro
    // devem conter apenas celulas mortas

    if (linGlo <  tam-2)
      corrLocal &= (cnt == 0); 

    // confere a contagem das celulas vivas na primeira linha do veleiro
    // e se a posicao do veleiro estah correta

    else if (linGlo == tam-2)
      corrLocal &= (cnt == 1) &
	(tabul[ind2d(linLoc,tam-1)] == 1);

    // confere a contagem das celulas vivas na segunda linha do veleiro
    // e se a posicao do veleiro estah correta

    else if (linGlo == tam-1)
      corrLocal &= (cnt == 1) &
	(tabul[ind2d(linLoc,tam)] == 1);

    // confere a contagem das celulas vivas na terceira linha do veleiro
    // e se a posicao do veleiro estah correta

    else if (linGlo == tam )
      corrLocal &= (cnt == 3) &
	(tabul[ind2d(linLoc,tam-2)] == 1) &
	(tabul[ind2d(linLoc,tam-1)] == 1) &
	(tabul[ind2d(linLoc,tam  )] == 1);
  }

  // reduz o resultado dos processos

  bool corrGlobal; // correto em todos os processos
  
  if (MPI_Allreduce(&corrLocal, &corrGlobal, 1, 
                    MPI_C_BOOL, MPI_LAND, MPI_COMM_WORLD) != MPI_SUCCESS) {
    printf("Allreduce no Correto falhou\n"); MPI_Finalize(); exit(-1);
  } 
  
  return(corrGlobal);

}
