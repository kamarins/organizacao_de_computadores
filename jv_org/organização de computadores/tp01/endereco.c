#include "endereco.h"

struct endereco{
   int endereco_bloco;
   int endereco_palavra;
};

Endereco *Criar_Endereco(int endereco_bloco, int endereco_palavra){
    
   Endereco *endereco = malloc(sizeof(Endereco));
   
   endereco->endereco_bloco = endereco_bloco;
   endereco->endereco_palavra = endereco_palavra;
   
   return endereco;
}

int getEndereco_palavra(Endereco *enderecos){
    return enderecos->endereco_palavra;
}

int getEndereco_bloco_instrucao(Endereco *auxiliar){
     return auxiliar->endereco_bloco;
}

