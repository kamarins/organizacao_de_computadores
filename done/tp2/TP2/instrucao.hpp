#ifndef INSTRUCAO_HPP
#define INSTRUCAO_HPP

#include <bits/stdc++.h>
using namespace std;

typedef struct instrucao Instrucao;
typedef struct endereco Endereco;

#define op_min 0
#define op_max 1
#define hault -1
#define TAM_FOR 10
#define REPETICOES 60
#define TAM_MEM 500 
#define NUM_INS 5000
#define QUANTIDADE_DE_ENDERECOS 2
#define ENDERECO_DE_PALAVRAS 1

#define TAM_INST_GERADOR 5000

Endereco* getEnd1(Instrucao* inst);
Endereco* getEnd2(Instrucao* inst);
int getEndBloco(Endereco* e);
int getEndPalavra(Endereco* e);
int getOpcode(Instrucao* inst);
void setEnd1(Instrucao* inst, Endereco* add1);
void setEnd2(Instrucao* inst, Endereco* add2);
void setEndBloco(Endereco* e, int endBloco);
void setEndPalavra(Endereco* e, int endPalavra);
void setOpcode(Instrucao* inst, int opcode);
void geraInstrucao();
Instrucao** alocaInstrucao(int tamanho);
void lerInstrucao(Instrucao** inst);
void deletarInstrucao(Instrucao** inst);

#endif