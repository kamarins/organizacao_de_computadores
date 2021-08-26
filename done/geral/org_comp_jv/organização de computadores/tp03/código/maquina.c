#include "maquina.h"
#include "bloco_de_memoria.h"
#include "memoria_cache.h"
#include "memoria_de_instrucoes.h"
#include "endereco.h"
#include "define.h"

void maquina (Instrucao **instrucao, Cache *cache_01, Cache *cache_02, Cache *cache_03, Cache *memoria_ram){
    int opcode = 0; 
    int pc = 0;
    Instrucao *Auxinstrucao;

    while (opcode != -1){  
        
            Auxinstrucao = getInstrucao_posicao(instrucao, pc);
            opcode = getOpcode(Auxinstrucao);    
            
            executar (cache_01, cache_02, cache_03, memoria_ram, Auxinstrucao);
            pc++;
    }

}

void executar (Cache *L1, Cache *L2, Cache *L3, Cache *RAM, Instrucao *inst){

    int opCode = getOpcode(inst);
    Endereco *end1 = getEndereco_01(inst);
    Endereco *end2 = getEndereco_02(inst);
    Endereco *end3 = getEndereco_03(inst);
    int soma, subtracao, palavra1, palavra2;

    switch (opCode){
            case 0:

                palavra1 = getPalavra(MMU(L1, L2, L3, RAM, getEndereco_bloco_instrucao(end1)), getEndereco_palavra(end1));
                palavra2 = getPalavra(MMU(L1, L2, L3, RAM, getEndereco_bloco_instrucao(end2)), getEndereco_palavra(end2));
                
                soma = palavra1 + palavra2;

                salvar (L1, L2, L3, RAM, getEndereco_bloco_instrucao(end3), getEndereco_palavra(end3), soma);
                break;

            case 1:
                palavra1 = getPalavra(MMU(L1, L2, L3, RAM, getEndereco_bloco_instrucao(end1)), getEndereco_palavra(end1));
                palavra2 = getPalavra(MMU(L1, L2, L3, RAM, getEndereco_bloco_instrucao(end2)), getEndereco_palavra(end2));
                
                subtracao = palavra1 - palavra2;

                salvar (L1, L2, L3, RAM, getEndereco_bloco_instrucao(end3), getEndereco_palavra(end3), subtracao);
                break;
    }
    
    
    int random = rand () % 11;
    if(random >= 0 && random <= 3){
        Interrupcoes(L1, L2, L3, RAM);
    }
}

Bloco *MMU (Cache *L1, Cache *L2, Cache *L3, Cache *RAM, int endBloco){
   int EnderecoBlocoRam, custo = 0;

    //Cache 1
    for (int i  = 0; i < getCacheTamanho(L1); i++){
        
        Bloco *aux = getBloco (getCacheBloco(L1), i);

        EnderecoBlocoRam = getEndereco_bloco_cache(getBloco_cache(L1, i));
        
        if (EnderecoBlocoRam == endBloco){
            setCacheHit(L1, 1);
            custo = 1;
            setCacheCusto (L1, custo);
            atualizarBlocoAtualizacao(getBloco (getCacheBloco(L1), i));
            return aux;
        }
    }
    setCacheMiss(L1, 1);

    //Cache 2
    for (int i = 0; i < getCacheTamanho(L2); i++){
        
        Bloco *aux = getBloco (getCacheBloco(L2), i);
        EnderecoBlocoRam = getEndereco_bloco_cache(getBloco_cache(L2, i));
        
        if (EnderecoBlocoRam == endBloco){
            setCacheHit(L2, 1);
            custo = 10 + 1;
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
        EnderecoBlocoRam = getEndereco_bloco_cache(getBloco_cache(L3, i));
        if (EnderecoBlocoRam == endBloco){
            setCacheHit(L3, 1);
            custo = 100 + 10 + 1;
            setCacheCusto (L3, custo);
            
            atualizarBlocoAtualizacao(getBloco (getCacheBloco(L3), i));
            trocaCaches(L3, L2, endBloco);
            trocaCaches(L2, L1, endBloco);
            
            return aux;
        }
    }
    setCacheMiss(L3, 1);

    //RAM
    for (int i = 0; i < getCacheTamanho(RAM); i++){
        
        Bloco *aux = getBloco (getCacheBloco(RAM), i);
        EnderecoBlocoRam = getEndereco_bloco_cache(getBloco_cache(RAM, i));
        
        if (EnderecoBlocoRam == endBloco){
            setCacheHit(RAM, 1);
            custo = 5000 + 100 + 10 + 1;
            setCacheCusto (RAM, custo);

            atualizarBlocoAtualizacao(getBloco (getCacheBloco(RAM), i));
            trocaCaches(RAM, L3, endBloco);
            trocaCaches(L3, L2, endBloco);
            trocaCaches(L2, L1, endBloco);
            
            return aux;
        }
    }
    setCacheMiss(RAM, 1);

     //HD
        int word = 0;

        Bloco *blocoAux = Criar_Bloco(); // é aq q vai ta as 4 palavras

        FILE *hd = fopen("HD.bin", "rb");
            
        if(hd == NULL) printf("ERRO AO ABRIR O ARQUIVO.\n");

        fseek(hd, endBloco*16, SEEK_SET); // entra no arquivo, pega a posicao desde o inicio

        for(int j = 0; j < 4;j++){
            fread(&word, sizeof(int), 1, hd);         // ler as palavras do arquivo
            setPalavra(blocoAux, word, 1);
        }
        fclose(hd);
        
        setEndereco_bloco_hd(blocoAux, endBloco*16); 
        
        custo = 100000 + 5000 + 100 + 10 + 1;
        setHDCusto(RAM, custo);

        int posicao = HD_ram(blocoAux, RAM);
        trocaCaches(RAM, L3, posicao);
        trocaCaches(L3, L2, endBloco);
        trocaCaches(L2, L1, endBloco);
        setHDHit(RAM, 1);
   
    return blocoAux;
}

void salvar(Cache *L1, Cache *L2, Cache *L3, Cache *RAM, int endBloco, int endP, int resultado){
    //int *cont; 
    int EnderecoBlocoRam, custo = 0;

    //Cache 1
    for (int i  = 0; i < getCacheTamanho(L1); i++){
        EnderecoBlocoRam = getEndereco_bloco_cache(getBloco_cache(L1, i));
        if (EnderecoBlocoRam == endBloco){
            
            setCacheHit(L1, 1);
            custo = 1;
            setCacheCusto (L1, custo);

            atualizarBlocoAtualizacao(getBloco (getCacheBloco(L1), i));
            setPalavra(getBloco(getCacheBloco(L1), i), resultado, endP);

            return;
        }
    }
    setCacheMiss(L1, 1);
    
    //Cache 2
    for (int i = 0; i < getCacheTamanho(L2); i++){

        EnderecoBlocoRam = getEndereco_bloco_cache(getBloco_cache(L2, i));

        if (EnderecoBlocoRam == endBloco){
            
            setCacheHit(L2, 1);
            custo = 10 + 1;
            setCacheCusto (L2, custo);

            atualizarBlocoAtualizacao(getBloco (getCacheBloco(L2), i));
            setPalavra(getBloco(getCacheBloco(L2), i), resultado, endP);

            trocaCaches (L2, L1, endBloco);

            return;
        }
    }
    setCacheMiss(L2, 1);

    //Cache 3
    for (int i = 0; i < getCacheTamanho(L3); i++){

        EnderecoBlocoRam = getEndereco_bloco_cache(getBloco_cache(L3, i));

        if (EnderecoBlocoRam == endBloco){

            setCacheHit(L3, 1);
            custo = 100 + 10 + 1;
            setCacheCusto (L3, custo);
            
            atualizarBlocoAtualizacao(getBloco (getCacheBloco(L3), i));
            setPalavra(getBloco(getCacheBloco(L3), i), resultado, endP);

            trocaCaches(L3, L2, endBloco);
            trocaCaches(L2, L1, endBloco);
            
            return;
        }
    }
    setCacheMiss(L3, 1);

    //RAM
    for (int i = 0; i < getCacheTamanho(RAM); i++){
        if (endBloco == getEndereco_bloco_cache(getBloco_cache(RAM, i))){
            setCacheHit(RAM, 1);
            custo = 5000 + 100 + 10 + 1;
            setCacheCusto (RAM, custo);
           
            atualizarBlocoAtualizacao(getBloco(getCacheBloco(RAM), i));
            setPalavra(getBloco(getCacheBloco(RAM), i), resultado, endP);

            trocaCaches (RAM, L3, endBloco);
            trocaCaches(L3, L2, endBloco);
            trocaCaches(L2, L1, endBloco);
           
            return;
        }
    }

    //HD
    int word;
    Bloco *blocoAux = Criar_Bloco(); // é aq q vai ta as 4 palavras

    FILE *hd = fopen("HD.bin", "rb");
        
    fseek(hd, endBloco*16, SEEK_SET); // entra no arquivo, pega a posicao desde o inicio

    for(int j = 0; j < 4;j++){
        fwrite(&word, sizeof(int), 1, hd);         // ler as paplavras do arquivo
        setPalavra(blocoAux, word, 1);
    }
    fclose(hd);
        
    setEndereco_bloco_hd(blocoAux, endBloco*16); 

    int posicao = HD_ram (blocoAux, RAM);
    
    if (endBloco == getEndereco_bloco_cache(getBloco_cache(RAM, posicao))){
           
        atualizarBlocoAtualizacao(getBloco(getCacheBloco(RAM), posicao));
        setPalavra(getBloco(getCacheBloco(RAM), posicao), resultado, endP);  
            
        trocaCaches (RAM, L3, endBloco);
        trocaCaches(L3, L2, endBloco);
        trocaCaches(L2, L1, endBloco);

        custo = 100000 + 5000 + 100 + 10 + 1;;
        setHDCusto(RAM, custo);
        setHDHit(RAM, 1);
        return;
    }
}

//Tratador de Interrupções
void Interrupcoes(Cache *L1, Cache *L2, Cache *L3, Cache *RAM){
    int pc = 0;
    int opcode;
    int endereco_bloco01;
    int endereco_palavra01;
    int endereco_bloco02; 
    int endereco_palavra02;
    int endereco_bloco03;
    int endereco_palavra03;

    FILE *interruption = fopen("interrupcao.txt", "r");
    
    Instrucao **instrucoesInterruption = malloc (interrupcoes * sizeof (Instrucao*));
    Instrucao *Auxinstrucao;

    for (int i = 0; i < interrupcoes; i++){
        fscanf (interruption, "%d", &opcode);
        fscanf (interruption, "%d", &endereco_bloco01);
        fscanf (interruption, "%d", &endereco_palavra01);
        fscanf (interruption, "%d", &endereco_bloco02);
        fscanf (interruption, "%d", &endereco_palavra02);
        fscanf (interruption, "%d", &endereco_bloco03);
        fscanf (interruption, "%d", &endereco_palavra03);
        instrucoesInterruption[i] = Criar_Instrucoes (opcode, endereco_bloco01,
                                                    endereco_palavra01, endereco_bloco02, 
                                                    endereco_palavra02, endereco_bloco03, 
                                                    endereco_palavra03);
    }
    fclose (interruption);

    opcode = 0;
    while (opcode != -1){
        Auxinstrucao = getInstrucao_posicao(instrucoesInterruption, pc);
        opcode = getOpcode(Auxinstrucao);   

        if(opcode != -1){
            Endereco *end1 = getEndereco_01(Auxinstrucao);
            Endereco *end2 = getEndereco_02(Auxinstrucao);
            Endereco *end3 = getEndereco_03(Auxinstrucao);

            int soma, subtracao, palavra1, palavra2;

            switch (opcode){
                case 0:
                    palavra1 = getPalavra(MMU(L1, L2, L3, RAM, getEndereco_bloco_instrucao(end1)), getEndereco_palavra(end1));
                    palavra2 = getPalavra(MMU(L1, L2, L3, RAM, getEndereco_bloco_instrucao(end2)), getEndereco_palavra(end2));
                    soma = palavra1 + palavra2;
                    //printf ("\nsoma = %d\n", soma);
                    salvar (L1, L2, L3, RAM, getEndereco_bloco_instrucao(end3), getEndereco_palavra(end3), soma);
                    break;

                case 1:
                    palavra1 = getPalavra(MMU(L1, L2, L3, RAM, getEndereco_bloco_instrucao(end1)), getEndereco_palavra(end1));
                    palavra2 = getPalavra(MMU(L1, L2, L3, RAM, getEndereco_bloco_instrucao(end2)), getEndereco_palavra(end2));
                    subtracao = palavra1 - palavra2;
                    //printf ("\nsub = %d\n", subtracao);
                    salvar (L1, L2, L3, RAM, getEndereco_bloco_instrucao(end3), getEndereco_palavra(end3), subtracao);
                    break;
            }   
        }
        pc++;
    }    

    free(instrucoesInterruption);
    free(Auxinstrucao);
    
}
