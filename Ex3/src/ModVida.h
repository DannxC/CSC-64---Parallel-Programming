#ifndef _MODVIDA
#define _MODVIDA

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mpi.h>
#define ind2d(i,j) (i)*(tam+2)+(j)


// UmaVida: Executa uma iteracao do Jogo da Vida
//          em tabuleiros de tamanho tam. Produz o tabuleiro
//          de saida tabulOut a partir do tabuleiro de entrada
//          tabulIn. Os tabuleiros tem (tam, tam) celulas
//          internas vivas ou mortas. Tabuleiros sao orlados 
//          por celulas eternamente mortas.
//          Tabuleiros sao dimensionados tam+2 x tam+2.


void UmaVida(int* restrict tabulIn, int* restrict tabulOut, const int tam, 
             const int tamLocal, const int procAntes, const int procDepois);


// DumpTabul: Imprime trecho do tabuleiro entre
//            os indices globais (first,first) e (last,last)
//            X representa celula viva
//            . representa celula morta
//            Imprime mensagem "msg" antes do trecho do tabuleiro
//            para identificar cada invocacao 


void DumpTabul(int* restrict tabul, const int tam, 
	       const int first, const int last, char* restrict msg, 
	       const int myId, const int tamLocal, const int desloc);



// InitTabul: Inicializa os trechos locais dos dois tabuleiros:
//            tabulIn com um veleiro no canto superior esquerdo
//            tabulOut com celulas mortas



void InitTabul(int* restrict tabulIn, int* restrict tabulOut, const int tam, 
	       const int myId, const int tamLocal, const int desloc);

  
// Correto: Verifica se a configuracao final do tabuleiro
//          estah correta ou nao (veleiro no canto inferior direito)



bool Correto(int* restrict tabul, const int tam, const int myId,	\
	     const int tamLocal, const int desloc);

#endif
