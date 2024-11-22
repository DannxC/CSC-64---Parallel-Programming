#ifndef __MARCADOR__
#define __MARCADOR__
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <omp.h>


typedef struct {
  bool * restrict m; // array de marcadores; primo sse "true"
  int ultimoNum;     // maior inteiro no marcador
} Marcador, *ptrMarcador;


// Cria marcador para inteiros <= ultimoNumero


ptrMarcador CriaMarcador(const int ultimoNumero);


// Marca inteiros no intervalo [primeiroNumero : ultimoNumero] como primos


void MarcaTodosPrimos(ptrMarcador M, const int primeiroNumero, const int ultimoNumero);


// Retorna o maior inteiro possivel no marcador


int UltimoNumero(ptrMarcador M);


// Marca o inteiro num como nao primo


int MarcaMultiplo(ptrMarcador M, const int num);


// Retorna o primeiro primo 


int PrimeiroPrimo(ptrMarcador M);


// Retorna o menor primo maior que num


int ProximoPrimo(ptrMarcador M, const int num);


// Retorna quantos primos no marcador


int QuantosPrimos(ptrMarcador M);


// Imprime primos no marcador


void DumpPrimos(ptrMarcador M);


// Dealoca areas de memoria alocadas pelo marcador


void DestroiMarcador(ptrMarcador M);

#endif
