#ifndef instrucao_h
#define instrucao_h

#include <stdlib.h>
#include <stdio.h>
#include "endereco.h"

typedef struct instrucao Instrucao;

Instrucao** cria_ins(int tamanhoIns);
Instrucao* cria_uma_ins();
Endereco* getadd1(Instrucao* ins);
void setadd1(Instrucao* ins, Endereco* add1Aux);
Endereco* getAdd2(Instrucao* ins);
void setadd2(Instrucao* ins, Endereco* add2Aux);
Endereco* getAdd3(Instrucao* ins);
void setAdd3(Instrucao* ins, Endereco* add3Aux);
int getOpcode(Instrucao* ins);
void setOpcode(Instrucao* ins, int OpcodeAux);




#endif