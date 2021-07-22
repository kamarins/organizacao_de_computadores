#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "blocodememoria.h"

struct blocomemoria{
    int *palavras;
    int endBloco;
    bool atualizado;             //0 para false          e       1 para true
    int custo;
    int cacheHit;
    int numAcessos;
};

BlocoMemoria** cria_bloco(int tamanhoBloco){
    BlocoMemoria** bloco = malloc(tamanhoBloco*sizeof(BlocoMemoria));

    for(int i=0; i<=tamanhoBloco; i++){
        bloco[i] = malloc(sizeof(BlocoMemoria));
        bloco[i]->endBloco = -1;
        bloco[i]->atualizado = false;
        bloco[i]->custo = 0;
        bloco[i]->numAcessos = 0;
        setCacheHit(bloco[i],0);
    }

    return bloco;
}

BlocoMemoria* cria_um_bloco(){
    BlocoMemoria* um_bloco = malloc(sizeof(BlocoMemoria));
    um_bloco->endBloco = -1;
    um_bloco->atualizado = false;
    um_bloco->custo = 0;
    um_bloco->numAcessos = 0;
    setCacheHit(um_bloco,0);

    return um_bloco;
}

int getCusto(BlocoMemoria* bloco){
    return bloco->custo;
}
void setCusto(BlocoMemoria* bloco, int custoAux){
    bloco->custo = custoAux;
}
int getPalavras(BlocoMemoria* bloco, int i){
    return bloco->palavras[i];
}
void setPalavras(BlocoMemoria* bloco, int palavrasAux, int i){
    bloco->palavras[i] = palavrasAux;
}
int* getPalavrasVetor(BlocoMemoria* bloco){
    return bloco->palavras;
}
void setPalavrasVetor(BlocoMemoria* bloco, int* palavrasAux){
    bloco->palavras = palavrasAux;
}
int getEndBloco(BlocoMemoria* bloco){
    return bloco->endBloco;
}
void setEndBloco(BlocoMemoria* bloco, int endBlocoAux){
    bloco->endBloco = endBlocoAux;
}
bool isAtualizado(BlocoMemoria* bloco){
    return bloco->atualizado;
}
void setAtualizado(BlocoMemoria* bloco){
    bloco->atualizado = true;
}
void setDesatualizado(BlocoMemoria* bloco){
    bloco->atualizado = false;
}
int getCacheHit(BlocoMemoria* bloco){
    return bloco->cacheHit;
}
void setCacheHit(BlocoMemoria* bloco, int cacheHitAux){
    bloco->cacheHit = cacheHitAux;
}

int getNumAcessos(BlocoMemoria* bloco){
    return bloco->numAcessos;
}

void setNumAcessosAdd1(BlocoMemoria*bloco){
    bloco->numAcessos++;
}