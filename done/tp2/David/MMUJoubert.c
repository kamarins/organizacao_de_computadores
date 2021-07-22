#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "MMU.h"
#include "blocodememoria.h"
#include "endereco.h"
#include "instrucao.h"

BlocoMemoria* buscarNaMemoria(Endereco* endereco, BlocoMemoria** RAM, BlocoMemoria** cache1, BlocoMemoria** cache2, BlocoMemoria** cache3, int tamanhoCache1, int tamanhoCache2, int tamanhoCache3, int tamanhoRAM){
    int posicaoCache1 = tamanhoCache1;
    int posicaoCache2 = tamanhoCache2;
    int posicaoCache3 = tamanhoCache3;
    int custo = 0;

    if(getEndBloco(cache1[posicaoCache1])==getEndBlocoEnd(endereco)){
        custo+=10;
        setCusto(cache1[posicaoCache1], custo);
        setCacheHit(cache1[posicaoCache1], 1);
        //setAtualizado(cache1[posicaoCache1]);
        return cache1[posicaoCache1];
    }
    else{
        if(getEndBloco(cache2[posicaoCache2])==getEndBlocoEnd(endereco)){
            custo += 110;
            setCacheHit(cache2[posicaoCache2],2);
            //setAtualizado(cache2[posicaoCache2]);
            return testaCache1Cache2(posicaoCache1, posicaoCache2, )
        }
    }
}


BlocoMemoria testaCache1Cache2Cache3(int posicaoCache1, int posicaoCache2, int posicaoCache3, BlocoMemoria** cache1, BlocoMemoria** cache2, BlocoMemoria** cache3){
    if(!isAtualizado(cache1[posicaoCache1])){
        cache1[posicaoCache1] = cache2[posicaoCache2];
    }else{
        if(!isAtualizado())
    }
}