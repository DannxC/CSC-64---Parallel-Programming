#include "Crivo.h"
#include <omp.h>

// Crivo: elimina os nao primos do marcador


void Crivo(ptrMarcador M) {

  // percorre bases primas
  // maior base limitada pela raiz quadrada do maior numero a marcar

  int maiorBase=(int)sqrtf((float)UltimoNumero(M));
  int base = PrimeiroPrimo(M);
  while(base <= maiorBase) {

      // elimina multiplos da base
      // a partir do quadrado da base

    #pragma omp parallel for
    for (int mult=base*base;
    mult<=UltimoNumero(M);
    mult+=base)
        MarcaMultiplo(M, mult);

      // avanca para a proxima base

      base = ProximoPrimo(M, base);
  }
}
