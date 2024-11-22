#include "Marcador.h"
#include "Crivo.h"
#include "WallTime.h"


int main(int argc, char *argv[]) {

  // limite superior do intervalo de inteiros a investigar 

  //const int numMax=100, numPriCerto=25;
  const int numMax=1000000000, numPriCerto=50847534;

  // instante inicial da execucao

  double tStart=WallTime();
  
  // cria marcador
  // admite todos primos

  ptrMarcador M = CriaMarcador(numMax);
  MarcaTodosPrimos(M, 0, numMax);

  // executa Crivo de Eratostenes e mede tempo de execucao

  double t0=WallTime();
  Crivo(M);
  double t1=WallTime();

  // imprime numero de threads

#ifdef _OPENMP
#pragma omp parallel
  if (omp_get_thread_num() == 0)
    printf("Execucao OpenMP versao %d com %d threads\n",
	   _OPENMP, omp_get_num_threads());
#else
  printf("Execucao sequencial, compilado Sem OpenMP\n");
#endif

  // verifica correcao e imprime tempos

  const int numPriComp=QuantosPrimos(M);
  printf("achou %d primos em [2:%d]; ", numPriComp, numMax);
  if (numPriComp == numPriCerto) {
    printf("quantidade correta\n");
    const double tInit=t0-tStart;
    const double tComp=t1-t0;
    const double tFim=WallTime()-t1;
    printf("Tempos: init=%lf, comp=%lf, fim=%lf\n",
	   tInit, tComp, tFim);
  } else {
    printf("quantidade errada; correto seria %d\n", numPriCerto);
  }

  DestroiMarcador(M);
  exit(0);
}
