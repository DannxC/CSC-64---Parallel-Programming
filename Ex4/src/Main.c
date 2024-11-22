#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include "WallTime.h"
#include "Pipe.h" 

int main(int argc, char *argv[]){

  // dados de entrada:
  // numero de estagios e numero de produtos

  if (argc != 3) {
    printf("requer argumentos nEsta e nProd\n");
    exit(1);
  }
  const int nEsta = atoi(argv[1]);
  if (nEsta <= 0) {
    printf("nEsta deve ser > 0 e nao %d\n", nEsta);
    exit(1);
  }
  const int nProd = atoi(argv[2]);
  if (nProd <= 0) {
    printf("nProd deve ser > 0 e nao %d\n", nProd);
    exit(1);
  }

  // quantas threads

  int nThreads = 1;
#ifdef _OPENMP
  nThreads = omp_get_max_threads();
  printf("OpenMP versao %d com %d threads\n", _OPENMP, nThreads);
#endif

  // instante inicial

  double tIni = WallTime();

  // matriz dummy para dependências
  int dummy[nProd + 1][nEsta + 1];

  // fabrica todos os produtos
#pragma omp parallel
  {
#pragma omp single
    {
      for (int prod = 1; prod <= nProd; prod++) {
        for (int esta = 1; esta <= nEsta; esta++) {
          // cria uma tarefa para cada estágio de cada produto
#pragma omp task depend(in: dummy[prod][esta - 1], dummy[prod - 1][esta]) depend(out: dummy[prod][esta])
          {
            // processamento do estágio
            Estagio(esta, prod, tIni);

            // imprime o tempo de fabricação quando o último estágio terminar
            if (esta == nEsta) {
              printf("produto %2.0d fabricado apos %2.0lf segundos com %d threads\n",
                     prod, WallTime() - tIni, nThreads);
            }
          }
        }
      }
    }
  }

  exit(0);
}
