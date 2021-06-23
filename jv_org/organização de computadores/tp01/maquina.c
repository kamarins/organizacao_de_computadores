#include "maquina.h"
#include "bloco_de_memoria.h"
#include "memoria_cache.h"
#include "memoria_de_instrucoes.h"
#include "endereco.h"
#include "define.h"

void maquina (Instrucao **instrucao, Cache *cache_01, Cache *cache_02, Cache *cache_03, Bloco **memoria_ram){
    int opcode = 0; 
    int pc = 0;
    Instrucao *Auxinstrucao;

    while (opcode != -1){  
        //if(pc >=0 && instrucao != 0){
            Auxinstrucao = getInstrucao_posicao(instrucao, pc);
            opcode = getOpcode(Auxinstrucao);    
            executar (cache_01, cache_02, cache_03, memoria_ram, Auxinstrucao);
            pc++;
        //}
    }
}

void executar (Cache *L1, Cache *L2, Cache *L3, Bloco **RAM, Instrucao *inst){

    int opCode = getOpcode(inst);
    Endereco *end1 = getEndereco_01(inst);
    Endereco *end2 = getEndereco_02(inst);
    Endereco *end3 = getEndereco_03(inst);
    int soma, subtracao, palavra1, palavra2;

    switch (opCode){
            case 0:{
                palavra1 = getPalavra(MMU(L1, L2, L3, RAM, getEndereco_bloco_instrucao(end1)), getEndereco_palavra(end1));
                palavra2 = getPalavra(MMU(L1, L2, L3, RAM, getEndereco_bloco_instrucao(end2)), getEndereco_palavra(end2));
                soma = palavra1 + palavra2;
                //printf ("soma %d\n", soma);
                salvar (L1, L2, L3, RAM, getEndereco_bloco_instrucao(end3), getEndereco_palavra(end3), soma);
                break;
            }
            case 1:{
                palavra1 = getPalavra(MMU(L1, L2, L3, RAM, getEndereco_bloco_instrucao(end1)), getEndereco_palavra(end1));
                palavra2 = getPalavra(MMU(L1, L2, L3, RAM, getEndereco_bloco_instrucao(end2)), getEndereco_palavra(end2));
                subtracao = palavra1 - palavra2;
                //printf ("sub %d\n", subtracao);
                salvar (L1, L2, L3, RAM, getEndereco_bloco_instrucao(end3), getEndereco_palavra(end3), subtracao);
                break;
            }
    }
}

Bloco *MMU (Cache *L1, Cache *L2, Cache *L3, Bloco **RAM, int endBloco){
    int hitL1=0, hitL2=0, hitL3=0;int EnderecoBlocoRam, custo;

    //Cache 1
    for (int i  = 0; i < getCacheTamanho(L1); i++){
        
        Bloco *aux = getBloco (getCacheBloco(L1), i);
        EnderecoBlocoRam = getEndereco_bloco_ram(getBloco_cache(L1, i));
        
        if (EnderecoBlocoRam == endBloco){
            //printf ("encontrado na L1\n");
            setCacheHit(L1, 1);
            hitL1++;
            
            custo = 10;
            setCacheCusto (L1, custo);

            atualizarBlocoAtualizacao(getBloco (getCacheBloco(L1), i));
            return aux;
        }
    }
    setCacheMiss(L1, 1);

    //Cache 2
    for (int i = 0; i < getCacheTamanho(L2); i++){
        
        Bloco *aux = getBloco (getCacheBloco(L2), i);
        EnderecoBlocoRam = getEndereco_bloco_ram(getBloco_cache(L2, i));
        
        if (EnderecoBlocoRam == endBloco){
            setCacheHit(L2, 1);
            hitL2++;

            custo = 100 + 10;
            setCacheCusto (L2, custo);

            atualizarBlocoAtualizacao(getBloco (getCacheBloco(L2), i));
            trocaCaches (L2, L1, endBloco);

            return aux;
        }
    }
    setCacheMiss(L2, 1);

    //Cache 3
    for (int i = 0; i < getCacheTamanho(L3); i++){
        
        Bloco *aux = getBloco (getCacheBloco(L3), i);
        EnderecoBlocoRam = getEndereco_bloco_ram(getBloco_cache(L3, i));
        
        if (EnderecoBlocoRam == endBloco){
            setCacheHit(L3, 1);
            hitL3++;
            
            custo = 1000 + 100 + 10;
            setCacheCusto (L3, custo);

            atualizarBlocoAtualizacao(getBloco (getCacheBloco(L3), i));
            
            trocaCaches(L3, L2, endBloco);
            trocaCaches(L2, L1, endBloco);
            
            return aux;
        }
    }
    setCacheMiss(L3, 1);

    //RAM
    for (int i = 0; i < 100; i++){
        
        //Conferindo onde esta o endereço
        if (endBloco == getEndereco_bloco_ram(getBloco(RAM, i))){
            atualizarBlocoAtualizacao(getBloco(RAM, i));

            custo = 100000 + 1000 + 100 + 10;
            setRamCusto(L1, custo);

            RAM_L3 (RAM, L3, endBloco);
            trocaCaches(L3, L2, endBloco);
            trocaCaches(L2, L1, endBloco);

            return getBloco(RAM, i);
        }
    }

    return NULL;
}

void salvar(Cache *L1, Cache *L2, Cache *L3, Bloco **RAM, int endBloco, int endP, int resultado){
    int *cont; int EnderecoBlocoRam;

    //Cache 1
    for (int i  = 0; i < getCacheTamanho(L1); i++){
        EnderecoBlocoRam = getEndereco_bloco_ram(getBloco_cache(L1, i));
        if (EnderecoBlocoRam == endBloco){
            
            setCacheHit(L1, 1);

            atualizarBlocoAtualizacao(getBloco (getCacheBloco(L1), i));
            setPalavra(getBloco(getCacheBloco(L1), i), resultado, endP);

            return;
        }
    }
    setCacheMiss(L1, 1);
    
    //Cache 2
    for (int i = 0; i < getCacheTamanho(L2); i++){

        EnderecoBlocoRam = getEndereco_bloco_ram(getBloco_cache(L2, i));

        if (EnderecoBlocoRam == endBloco){
            
            setCacheHit(L2, 1);

            atualizarBlocoAtualizacao(getBloco (getCacheBloco(L2), i));
            setPalavra(getBloco(getCacheBloco(L2), i), resultado, endP);

            trocaCaches (L2, L1, endBloco);

            return;
        }
    }
    setCacheMiss(L2, 1);

    //Cache 3
    for (int i = 0; i < getCacheTamanho(L3); i++){

        EnderecoBlocoRam = getEndereco_bloco_ram(getBloco_cache(L3, i));

        if (EnderecoBlocoRam == endBloco){

            setCacheHit(L3, 1);
            
            atualizarBlocoAtualizacao(getBloco (getCacheBloco(L3), i));
            setPalavra(getBloco(getCacheBloco(L3), i), resultado, endP);

            trocaCaches(L3, L2, endBloco);
            trocaCaches(L2, L1, endBloco);
            
            return;
        }
    }
    setCacheMiss(L3, 1);

    //RAM
    for (int i = 0; i < 100; i++){
        if (endBloco == getEndereco_bloco_ram(getBloco(RAM, i))){
           
            atualizarBlocoAtualizacao(getBloco(RAM, i));
            setPalavra(getBloco(RAM, i), resultado, endP);

            RAM_L3 (RAM, L3, endBloco);
            trocaCaches(L3, L2, endBloco);
            trocaCaches(L2, L1, endBloco);
           
            return;
        }
    }
}

void hitRAM (int cont){
    cont += 1;
}
