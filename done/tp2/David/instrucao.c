#include <stdio.h>
#include <stdlib.h>
#include "instrucao.h"
#include "endereco.h"


struct instrucao
{
    Endereco* add1;
    Endereco* add2;
    Endereco* add3;
    int opcode;
};

Instrucao** cria_ins(int tamanhoIns){
    Instrucao** inst = malloc(tamanhoIns*sizeof(Instrucao));
    for(int i=0; i<tamanhoIns; i++){
        inst[i]= malloc(sizeof(Instrucao));
    }
    return inst;
}

Instrucao* cria_uma_ins(){
    Instrucao* uma_inst = malloc(sizeof(Instrucao));

    return uma_inst;
}

Endereco* getadd1(Instrucao* ins){
    return ins->add1;
}
void setadd1(Instrucao* ins, Endereco* add1Aux){
    ins->add1 = add1Aux;
}
Endereco* getAdd2(Instrucao* ins){
    return ins->add2;
}
void setadd2(Instrucao* ins, Endereco* add2Aux){
    ins->add2 = add2Aux;
}
Endereco* getAdd3(Instrucao* ins){
    return ins->add3;
}
void setAdd3(Instrucao* ins, Endereco* add3Aux){
    ins->add3 = add3Aux;
}
int getOpcode(Instrucao* ins){
    return ins->opcode;
}
void setOpcode(Instrucao* ins, int OpcodeAux){
    ins->opcode = OpcodeAux;
}