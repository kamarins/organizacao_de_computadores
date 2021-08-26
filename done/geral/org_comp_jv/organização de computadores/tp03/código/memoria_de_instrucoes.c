#include "memoria_de_instrucoes.h"
#include "endereco.h"
#include "bloco_de_memoria.h"
#include "memoria_cache.h"
#include "define.h"

struct instrucao{
    int opcode;
    Endereco *endereco_01;
    Endereco *endereco_02;
    Endereco *endereco_03;
};


Instrucao *Criar_Instrucoes (int opcode,
    int endereco_bloco01, int endereco_palavra01, int endereco_bloco02, 
    int endereco_palavra02, int endereco_bloco03, int endereco_palavra03){

    Instrucao *instrucoes = malloc (sizeof(Instrucao));

    instrucoes->opcode = opcode;

    Endereco *endereco_01 = Criar_Endereco (endereco_bloco01, endereco_palavra01);
    Endereco *endereco_02 = Criar_Endereco (endereco_bloco02, endereco_palavra02);
    Endereco *endereco_03 = Criar_Endereco (endereco_bloco03, endereco_palavra03);

    
    setEnd1(instrucoes, endereco_01);
    setEnd2(instrucoes, endereco_02);
    setEnd3(instrucoes, endereco_03);

    return instrucoes;
}

Instrucao **Preencher_Instrucoes (int tamanho){
    
    FILE *arquivo = fopen ("instrucoes.txt", "r");

    int opcode;
    int endereco_bloco01;
    int endereco_palavra01;
    int endereco_bloco02; 
    int endereco_palavra02;
    int endereco_bloco03;
    int endereco_palavra03;

    Instrucao **preencher_instrucoes = malloc (tamanho * sizeof (Instrucao*));

    for (int i = 0; i < quantidade_instrucoes; i++){
        fscanf (arquivo, "%d", &opcode);
        fscanf (arquivo, "%d", &endereco_bloco01);
        fscanf (arquivo, "%d", &endereco_palavra01);
        fscanf (arquivo, "%d", &endereco_bloco02);
        fscanf (arquivo, "%d", &endereco_palavra02);
        fscanf (arquivo, "%d", &endereco_bloco03);
        fscanf (arquivo, "%d", &endereco_palavra03);
        preencher_instrucoes[i] = Criar_Instrucoes (opcode, endereco_bloco01,
                                                    endereco_palavra01, endereco_bloco02, 
                                                    endereco_palavra02, endereco_bloco03, 
                                                    endereco_palavra03);
    }
    fclose (arquivo);
    return preencher_instrucoes;
}

// gets e sets
void setInstrucao(Instrucao **instrucao, Instrucao *setInstrucao, int posicao){
    
    instrucao[posicao]->opcode = setInstrucao->opcode;
    instrucao[posicao]->endereco_01 = setInstrucao->endereco_01;
    instrucao[posicao]->endereco_02 = setInstrucao->endereco_02;
    instrucao[posicao]->endereco_03 = setInstrucao->endereco_03;
    
}

Instrucao *getInstrucao_posicao(Instrucao **instrucao, int posicao){
    return instrucao[posicao];
}

int getOpcode (Instrucao *instrucao){
    return instrucao->opcode;
}

void setOpcode (Instrucao *instrucao, int opcode){
    instrucao->opcode = opcode;
}

Endereco *getEndereco_01(Instrucao *instrucao){
    return instrucao->endereco_01;
}

Endereco *getEndereco_02(Instrucao *instrucao){
    return instrucao->endereco_02;
}

Endereco *getEndereco_03(Instrucao *instrucao){
    return instrucao->endereco_03;
}


void setEnd1 (Instrucao *aux, Endereco *end){
    aux->endereco_01 = end;
}

void setEnd2 (Instrucao *aux, Endereco *end){
    aux->endereco_02 = end;
}

void setEnd3 (Instrucao *aux, Endereco *end){
    aux->endereco_03 = end;
}
