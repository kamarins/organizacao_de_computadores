#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "endereco.h"
//struct
typedef struct instrucao Instrucao;
//typedef struct cache Cache;
//typedef struct bloco Bloco;
//typedef struct endereco Endereco;

//funcoes
Instrucao *Criar_Instrucao (int opcode,
int endereco_bloco01, int endereco_palavra01, int endereco_bloco02, 
int endereco_palavra02, int endereco_bloco03, int endereco_palavra03);

Instrucao **Preencher_Instrucoes (int tamanho);


//Gets e Sets

Instrucao *getInstrucao_posicao(Instrucao **instrucao, int posicao);
void setInstrucao(Instrucao **instrucao, Instrucao *setInstrucao, int posicao);

int getOpcode (Instrucao *instrucao);
void setOpcode (Instrucao *instrucao, int opcode);


Endereco *getEndereco_01(Instrucao *instrucao);
Endereco *getEndereco_02(Instrucao *instrucao);
Endereco *getEndereco_03(Instrucao *instrucao);

void setEnd1 (Instrucao *aux, Endereco *end);
void setEnd2 (Instrucao *aux, Endereco *end);
void setEnd3 (Instrucao *aux, Endereco *end);

//-> Acessando as instruçoes
//Pega o endereco do bloco de qualquer um dos enderecos



//-> Acessando as memorias
//Retornar o bloco da cache


//Retornar o endereco do bloco. A variavel auxiliar se refere 
//tanto ao endereco_01, _02 ou _03,  quanto ao bloco da ram

