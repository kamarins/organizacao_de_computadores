#include <stdio.h>
#include <stdlib.h>
#include "endereco.h"

struct endereco
{
    int endBloco;
    int endPalavra;
};

Endereco* cria_end(){
    Endereco* end = malloc(sizeof(Endereco));
}

int getEndBlocoEnd(Endereco* end){
    return end->endBloco;
}
void setEndBlocoEnd(Endereco* end, int endBlocoAux){
    end->endBloco = endBlocoAux;
}
int getEndPalavra(Endereco* end){
    return end->endPalavra;
}
void setEndPalavra(Endereco* end, int endPalavraAux){
    end->endPalavra = endPalavraAux;
}