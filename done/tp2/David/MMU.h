#ifndef MMU_h
#define MMU_h

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "blocodememoria.h"
#include "endereco.h"
#include "instrucao.h"

BlocoMemoria* MMU(Endereco* endereco, BlocoMemoria** RAM, BlocoMemoria** cache1, BlocoMemoria** cache2, BlocoMemoria** cache3, int tamanhoCache1, int tamanhoCache2,int tamanhoCache3);
int buscarNaMemoria(BlocoMemoria** memoria, Endereco* endereco, int tamanho);
int LFU(int tamanho, BlocoMemoria** cache);
BlocoMemoria* trocadeMemoria(int posicaoDeDestino, int posicaoDeSaida, BlocoMemoria** memoriaDeDestino, BlocoMemoria** memoriaDeSaida, int custo, Endereco* Endereco);

#endif