#ifndef blocoMemoria_h
#define blocoMemoria_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct blocomemoria BlocoMemoria;

BlocoMemoria** cria_bloco(int tamanho);
BlocoMemoria* cria_um_bloco();
int getCusto(BlocoMemoria* bloco);
void setCusto(BlocoMemoria* bloco, int custoAux);
int getPalavras(BlocoMemoria* bloco, int i);
void setPalavras(BlocoMemoria* bloco, int palavrasAux, int i);
int* getPalavrasVetor(BlocoMemoria* bloco);
void setPalavrasVetor(BlocoMemoria* bloco, int* palavrasAux);
int getEndBloco(BlocoMemoria* bloco);
void setEndBloco(BlocoMemoria* bloco, int endBlocoAux);
bool isAtualizado(BlocoMemoria* bloco);
void setAtualizado(BlocoMemoria* bloco);
void setDesatualizado(BlocoMemoria* bloco);
int getCacheHit(BlocoMemoria* bloco);
void setCacheHit(BlocoMemoria* bloco, int cacheHitAux);
int getNumAcessos(BlocoMemoria* bloco);
void setNumAcessosAdd1(BlocoMemoria*bloco);



#endif 