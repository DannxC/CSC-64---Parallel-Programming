#include "Marcador.h"


// Cria marcador para inteiros <= ultimoNumero


ptrMarcador   CriaMarcador(const int ultimoNumero) {
  ptrMarcador M=NULL;
  M=(ptrMarcador)malloc(sizeof(Marcador));
  if (M==NULL) {
    printf("**CriaMarcador** falhou alocando ponteiro para marcador para ultimoNumero=%d\n",
	   ultimoNumero);
    exit(1);
  }
  
  // ultimo numero
  
  M->ultimoNum = ultimoNumero;
  
  // marcadores enderecam [0:ultimoNum+1]
  
  M->m=(bool*)malloc((M->ultimoNum+1)*sizeof(bool));
  if (M->m==NULL) {
    printf("**CriaMarcador** falhou alocando array marcador para ultimoNumero=%d\n",
	   ultimoNumero);
    exit(1);
  }
  
  return(M);
}


// Marca inteiros no intervalo [primeiroNumero : ultimoNumero] como primos


void MarcaTodosPrimos(ptrMarcador M, const int primeiroNumero, const int ultimoNumero) {
  for (int i=primeiroNumero; i<=ultimoNumero; i++) M->m[i]=true;
}


// Retorna o maior inteiro possivel no marcador


int UltimoNumero(ptrMarcador M) {
  return(M->ultimoNum);
}


// Marca o inteiro num como nao primo


int MarcaMultiplo(ptrMarcador M, const int num){
  M->m[num] = false;
}


// Retorna o primeiro primo 


int PrimeiroPrimo(ptrMarcador M){
  return(2);
}


// Retorna o menor primo maior que num


int ProximoPrimo(ptrMarcador M, const int num){
  for (int n=num+1; n<=M->ultimoNum; n++) {
    if (M->m[n])
      return(n);
  }
  return(0);
}


// Retorna quantos primos no marcador


int QuantosPrimos(ptrMarcador M){
  int cnt=0;
  for (int n=2; n<=M->ultimoNum; n++) {
    if (M->m[n]) cnt++;
  }
  return(cnt);
}


// Imprime primos no marcador


void DumpPrimos(ptrMarcador M) {
#define PRIMO_POR_LINHA 20
  int cnt=0;
  for (int n=2; n<=M->ultimoNum; n++) {
    if (M->m[n]) {
      if (++cnt == 1)
	printf("%d",n);
      else 
	printf("; %d",n);
      if (cnt == PRIMO_POR_LINHA) {
	cnt=0;
	printf("\n");
      }
    }
  }
  if (cnt != 0) printf("\n");
}


// Dealoca areas de memoria alocadas pelo marcador


void DestroiMarcador(ptrMarcador M){
  free(M->m);
}


