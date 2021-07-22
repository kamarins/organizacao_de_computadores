#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include "TP2.h"

#define tamanhoRAM 1000
#define tamanhoCache1 8
#define tamanhoCache2 16
#define tamanhoCache3 32
#define tamanhoPrograma 10001
#define tamanhoProgramaTi 101
#define tamanhoHD 30000
#define qntPalavrasBloco 4

struct blocomemoria{
    int palavras[4];
    int endBloco;
    bool atualizado;
    int numAcessos;
    int custo;
    int cacheHit;
};

 struct endereco{
    int endBloco;
    int endPalavra;
};

struct instrucao{
    Endereco add1;
    Endereco add2;
    Endereco add3;
    int opcode;
};

 struct hitsMiss{
    int missCache1,hitCache1;
    int missCache2,hitCache2;
    int missCache3,hitCache3;
    int missRAM,hitRAM;
    int hitHD;
    int custo;
};



int main(){  
    int PC = 0;
    srand(time(NULL));
    HitsMiss *HM = malloc(sizeof(HitsMiss));
    //dados = preencherDados(dados);
    Instrucao* memoriaInstrucoes = malloc(tamanhoPrograma * sizeof(Instrucao));
    BlocoMemoria* RAM = malloc(tamanhoRAM * sizeof(BlocoMemoria));
    BlocoMemoria* cache1 = malloc(tamanhoCache1 * sizeof(BlocoMemoria));
    BlocoMemoria* cache2 = malloc(tamanhoCache2 * sizeof(BlocoMemoria));
    BlocoMemoria* cache3 = malloc(tamanhoCache3 * sizeof(BlocoMemoria));
    char texto[30] = "programa.txt";
    arquivoBin();

    montarCaches(RAM, tamanhoRAM);
    montarCaches(cache1, tamanhoCache1);
    montarCaches(cache2, tamanhoCache2);
    montarCaches(cache3, tamanhoCache3);

    HM = preencherHitsMiss();
   
    programa(memoriaInstrucoes);
    maquina(texto,HM,memoriaInstrucoes, RAM, cache1, cache2, cache3, PC);

    free(memoriaInstrucoes);
    free(RAM);
    free(cache1);
    free(cache2);
    free(cache3);
    free(HM);

    return 0;
}

void montarRAM(BlocoMemoria* RAM){
    srand(time(NULL));
    for(int i=0; i<tamanhoRAM; i++){
        RAM[i].endBloco = i;
        for(int j=0; j<qntPalavrasBloco; j++){
            RAM[i].palavras[j] = rand()%tamanhoPrograma;
        }
    }
}

void montarCache(BlocoMemoria* cache, int tamanhoCache){
    for(int i=0; i<tamanhoCache; i++){
        cache[i].endBloco = -1;
        cache[i].numAcessos = 0;
        cache[i].atualizado = false;
    }
}

HitsMiss* preencherHitsMiss(){
    
    HitsMiss *HM = malloc(sizeof(HitsMiss));
    HM->missCache1 = 0;
    HM->hitCache1 = 0;
    HM->missCache2 = 0;
    HM->hitCache2 = 0;
    HM->missCache3 = 0;
    HM->hitCache3 = 0;
    HM->missRAM= 0;
    HM->hitRAM= 0;
    HM->custo = 0;
    HM->hitHD = 0;

    return HM;
}

void montarCaches(BlocoMemoria* cache, int tamanho){
    for(int i=0; i<tamanho; i++){
        cache[i].endBloco = -1;
        cache[i].numAcessos = 0; 
        cache[i].atualizado = false;
    }
}

void programa(Instrucao* memoriaInstrucoes){
    
    FILE* arquivo = fopen("programa.txt", "r");

    for(int i = 0; i < tamanhoPrograma-1; i++){
        Instrucao umaInstrucao;
        fscanf(arquivo, "%d", &umaInstrucao.opcode);
        fscanf(arquivo, "%d", &umaInstrucao.add1.endBloco);
        fscanf(arquivo, "%d", &umaInstrucao.add1.endPalavra);
        fscanf(arquivo, "%d", &umaInstrucao.add2.endBloco);
        fscanf(arquivo, "%d", &umaInstrucao.add2.endPalavra);
        fscanf(arquivo, "%d", &umaInstrucao.add3.endBloco);
        fscanf(arquivo, "%d", &umaInstrucao.add3.endPalavra);

        memoriaInstrucoes[i] = umaInstrucao;
    }

    Instrucao umaInstrucao;

    fscanf(arquivo, "%d", &umaInstrucao.opcode);

    memoriaInstrucoes[tamanhoPrograma-1] = umaInstrucao;
    fclose(arquivo);
}

void programaInterrupcao(Instrucao* memoriaInstrucoes){
    
    FILE* arquivo = fopen("interrupcao.txt", "r");
    for(int i = 0; i < tamanhoProgramaTi-1; i++){
        Instrucao umaInstrucao;
        fscanf(arquivo, "%d", &umaInstrucao.opcode);
        fscanf(arquivo, "%d", &umaInstrucao.add1.endBloco);
        fscanf(arquivo, "%d", &umaInstrucao.add1.endPalavra);
        fscanf(arquivo, "%d", &umaInstrucao.add2.endBloco);
        fscanf(arquivo, "%d", &umaInstrucao.add2.endPalavra);
        fscanf(arquivo, "%d", &umaInstrucao.add3.endBloco);
        fscanf(arquivo, "%d", &umaInstrucao.add3.endPalavra);

        memoriaInstrucoes[i] = umaInstrucao;
    }

    Instrucao umaInstrucao;

    fscanf(arquivo, "%d", &umaInstrucao.opcode);

    memoriaInstrucoes[tamanhoProgramaTi-1] = umaInstrucao;
    fclose(arquivo);
}

void arquivoBin(){

     BlocoMemoria HD;
     
     FILE* arquivo = fopen("Binario.bin", "wb");

     for(int i = 0; i < tamanhoHD; i++){
         HD.endBloco = i;
         for(int j = 0; j < qntPalavrasBloco; j++){
            HD.palavras[j] = rand()%1000;//4 de 0 a 10
         }
         HD.numAcessos = 0;
         HD.atualizado = false;
         fwrite(&HD, sizeof(BlocoMemoria),1, arquivo);
     }
     fclose(arquivo);
}

BlocoMemoria HD(BlocoMemoria* RAM, int endBloco, int posicaoRAM){
    int write0, write1, write2, write3;
    int read0, read1, read2, read3;

    FILE* arquivo= fopen("Binario.bin", "rb");
    long espaco_end = endBloco * sizeof(BlocoMemoria);
    fseek(arquivo, espaco_end, SEEK_SET);
    fread(&write0, sizeof(int), 1, arquivo);
    fread(&write1, sizeof(int), 1, arquivo);
    fread(&write2, sizeof(int), 1, arquivo);
    fread(&write3, sizeof(int), 1, arquivo);
    rewind(arquivo);//reniciar cursor
    fclose(arquivo);
    
    if(RAM[posicaoRAM].atualizado == true){
        RAM[posicaoRAM].atualizado = false;
       
        read0 = RAM[posicaoRAM].palavras[0];
        read1 = RAM[posicaoRAM].palavras[1];
        read2 = RAM[posicaoRAM].palavras[2];
        read3 = RAM[posicaoRAM].palavras[3];
       
        espaco_end = RAM[posicaoRAM].endBloco * sizeof(BlocoMemoria);
       
        arquivo= fopen("Binario.bin", "wb");
        fseek(arquivo, espaco_end, SEEK_SET);
        fwrite(&read0, sizeof(int), 1, arquivo);
        fwrite(&read1, sizeof(int), 1, arquivo);
        fwrite(&read2, sizeof(int), 1, arquivo);
        fwrite(&read3, sizeof(int), 1, arquivo);
        
        
        RAM[posicaoRAM].endBloco = endBloco;
        RAM[posicaoRAM].palavras[0] = write0;
        RAM[posicaoRAM].palavras[1] = write1;
        RAM[posicaoRAM].palavras[2] = write2;
        RAM[posicaoRAM].palavras[3] = write3;
        
        rewind(arquivo);
        fclose(arquivo);

    }
    else {
        RAM[posicaoRAM].endBloco = endBloco;
        RAM[posicaoRAM].palavras[0] = write0;
        RAM[posicaoRAM].palavras[1] = write1;
        RAM[posicaoRAM].palavras[2] = write2;
        RAM[posicaoRAM].palavras[3] = write3;
    }
    return RAM[posicaoRAM];
}

int procurarNaMemoria(BlocoMemoria* memoria, Endereco endereco, int tamanhoMemoria){
    for(int i=0; i<tamanhoMemoria; i++){
        if(memoria[i].endBloco == endereco.endBloco){
            memoria[i].numAcessos++;
            return i;
        }
    }
    return -1;
}

int LFU(int tamanho, BlocoMemoria* cache){
    int aux = INT_MAX;
    int posicaoCache;

    for(int i=0; i<tamanho; i++){
        if(cache[i].numAcessos <= aux){
            if(cache[i].endBloco == -1){
                return i;
            }else{
                aux = cache[i].numAcessos;
                posicaoCache = i;
            }
        }
    }

    return posicaoCache;
}

BlocoMemoria trocaDadosMemoria(int posicaoDestino, int posicaoRaiz, BlocoMemoria* memoriaDestino, BlocoMemoria* memoriaRaiz, int custo, Endereco endereco){
    
    BlocoMemoria aux = memoriaDestino[posicaoDestino];
    memoriaDestino[posicaoDestino] = memoriaRaiz[posicaoRaiz];
    memoriaRaiz[posicaoRaiz] = aux;

    memoriaDestino[posicaoDestino].custo = custo;

    memoriaRaiz[posicaoRaiz].numAcessos++;
    memoriaDestino[posicaoDestino].numAcessos++;

    return memoriaDestino[posicaoDestino];
}

BlocoMemoria UCM(Endereco endereco, BlocoMemoria* RAM, BlocoMemoria* cache1, BlocoMemoria* cache2, BlocoMemoria* cache3){

    int posicaoCache1, posicaoCache2, posicaoCache3, posicaoRAM, custo = 0;

    posicaoCache1 = procurarNaMemoria(cache1, endereco, tamanhoCache1);

    if(posicaoCache1!=-1){
        custo+=10;
        cache1[posicaoCache1].custo = custo;
        cache1[posicaoCache1].cacheHit = 1;
        cache1[posicaoCache1].numAcessos++;
        
        return cache1[posicaoCache1];
    }
    else{
        posicaoCache2 = procurarNaMemoria(cache2, endereco, tamanhoCache2);

        if(posicaoCache2!=-1){
            custo+=110;
            posicaoCache1 = LFU(tamanhoCache1, cache1);
            
            cache1[posicaoCache1] = trocaDadosMemoria(posicaoCache1, posicaoCache2, cache1, cache2, custo, endereco);
    
            cache1[posicaoCache1].cacheHit = 2;

            return cache1[posicaoCache1];
        }
        else{
            posicaoCache3 = procurarNaMemoria(cache3, endereco, tamanhoCache3);

            if(posicaoCache3!=-1){
                custo+=220;
                posicaoCache2 = LFU(tamanhoCache2, cache2);
                cache2[posicaoCache2] = trocaDadosMemoria(posicaoCache2, posicaoCache3, cache2, cache3, custo, endereco);

                posicaoCache1 = LFU(tamanhoCache1, cache1);
                cache1[posicaoCache1] = trocaDadosMemoria(posicaoCache1, posicaoCache2, cache1, cache2, custo, endereco);
 
                cache1[posicaoCache1].cacheHit = 3;

                return cache1[posicaoCache1]; 
            }
            else{
                 custo+=1110;
                 posicaoRAM = procurarNaMemoria(RAM, endereco, tamanhoRAM);

                if(posicaoRAM!= -1){
                    
                    posicaoCache3 = LFU(tamanhoCache3, cache3);
                    cache3[posicaoCache3] = trocaDadosMemoria(posicaoCache3, posicaoRAM, cache3, RAM, custo, endereco);
        
                    posicaoCache2 = LFU(tamanhoCache2, cache2);
                    cache2[posicaoCache2] = trocaDadosMemoria(posicaoCache2, posicaoCache3, cache2, cache3, custo, endereco);

                    posicaoCache1 = LFU(tamanhoCache1, cache1);
                    cache1[posicaoCache1] = trocaDadosMemoria(posicaoCache1, posicaoCache2, cache1, cache2, custo, endereco);
                    cache1[posicaoCache1].cacheHit = 4;

                    return cache1[posicaoCache1];
                }
                else{

                    posicaoRAM = LFU(tamanhoRAM,RAM);
                    
                    custo+=2150;
                    RAM[posicaoRAM] = HD(RAM,endereco.endBloco, posicaoRAM);

                    posicaoCache3 = LFU(tamanhoCache3, cache3);
                    cache3[posicaoCache3] = trocaDadosMemoria(posicaoCache3, posicaoRAM, cache3, RAM, custo, endereco);
        
                    posicaoCache2 = LFU(tamanhoCache2, cache2);
                    cache2[posicaoCache2] = trocaDadosMemoria(posicaoCache2, posicaoCache3, cache2, cache3, custo, endereco);

                    posicaoCache1 = LFU(tamanhoCache1, cache1);
                    cache1[posicaoCache1] = trocaDadosMemoria(posicaoCache1, posicaoCache2, cache1, cache2, custo, endereco);
                    cache1[posicaoCache1].cacheHit = 5;
                    return cache1[posicaoCache1];
                }
            }
        }
    }
}

void maquina(char* texto,HitsMiss *HM,Instrucao* memoriaInstrucoes, BlocoMemoria* RAM, BlocoMemoria* cache1, BlocoMemoria* cache2, BlocoMemoria* cache3, int PC){
    
    int opCode = INT_MAX;
    

    while(opCode!=-1){
        Instrucao umaInstrucao = memoriaInstrucoes[PC];
        opCode = umaInstrucao.opcode;

        if(opCode!=-1){
            BlocoMemoria dadoMemoriaAdd1 = UCM(umaInstrucao.add1, RAM, cache1, cache2, cache3);
            BlocoMemoria dadoMemoriaAdd2 = UCM(umaInstrucao.add2, RAM, cache1, cache2, cache3);
            BlocoMemoria dadoMemoriaAdd3 = UCM(umaInstrucao.add3, RAM, cache1, cache2, cache3);

            HM->custo += dadoMemoriaAdd1.custo;
            HM->custo += dadoMemoriaAdd2.custo;
            HM->custo += dadoMemoriaAdd3.custo;

            if(dadoMemoriaAdd1.cacheHit == 1){
                HM->hitCache1++;
            }
            else if(dadoMemoriaAdd1.cacheHit == 2){
                 HM->hitCache2++;
                 HM->missCache1++;
            }
            else if(dadoMemoriaAdd1.cacheHit == 3){
                 HM->hitCache3++;
                 HM->missCache1++;
                 HM->missCache2++;
            }
            else if(dadoMemoriaAdd1.cacheHit == 4){
                 HM->hitRAM++;
                 HM->missCache1++;
                 HM->missCache2++;
                 HM->missCache3++;
            }
            else if(dadoMemoriaAdd1.cacheHit == 5){
                HM->missCache1++; 
                HM->missCache2++;
                HM->missCache3++;
                HM->missRAM++;
                HM->hitHD++;
            }
            if(dadoMemoriaAdd2.cacheHit == 1){
                 HM->hitCache1++;
            }
            else if(dadoMemoriaAdd2.cacheHit == 2){
                 HM->hitCache2++;
                 HM->missCache1++;
            }
            else if(dadoMemoriaAdd2.cacheHit == 3){
                 HM->hitCache3++;
                HM->missCache1++;
                 HM->missCache2++;
            }
            else if(dadoMemoriaAdd2.cacheHit == 4){
                 HM->hitRAM++;
                 HM->missCache1++;
                 HM->missCache2++;
                 HM->missCache3++;
            }
            else if(dadoMemoriaAdd2.cacheHit == 5){
                HM->missCache1++; 
                HM->missCache2++;
                HM->missCache3++;
                HM->missRAM++;
                HM->hitHD++;
            }
            if(dadoMemoriaAdd3.cacheHit == 1){
                HM->hitCache1++;
            }
            else if(dadoMemoriaAdd3.cacheHit == 2){
                 HM->hitCache2++;
                 HM->missCache1++;
            }
            else if(dadoMemoriaAdd3.cacheHit == 3){
                 HM->hitCache3++;
                 HM->missCache1++;
                 HM->missCache2++;
            }
            else if(dadoMemoriaAdd3.cacheHit == 4){
                 HM->hitRAM++;
                 HM->missCache1++;
                 HM->missCache2++;
                 HM->missCache3++;
            }
            else if(dadoMemoriaAdd3.cacheHit == 5){
                HM->missCache1++; 
                HM->missCache2++;
                HM->missCache3++;
                HM->missRAM++;
                HM->hitHD++;
            }
          
           

            printf("\nCusto ate o momento do programa em execucao : %d\n\n", HM->custo);
            printf("Hits ate o momento:  | Cache1: %d  | Cache2: %d  | Cache3: %d  | RAM: %d| HD: %d|\n",HM->hitCache1,  HM->hitCache2,  HM->hitCache3,  HM->hitRAM,  HM->hitHD);
            printf("Misses ate o momento: | Cache1 miss: %d | Cache2 miss: %d | Cache3 miss: %d | RAM miss: %d|\n",  HM->missCache1,  HM->missCache2,  HM->missCache3,  HM->missRAM);
            switch(opCode){
                case 0:{
                    if(strcmp(texto,"programa.txt")==0){
                      
                      int chance = rand()%3;

                      if(chance == 0){
                        printf("\n\nTratador de interrupcao\n\n");
                        char texto2[30] = "interrupcao.txt";
                        programaInterrupcao(memoriaInstrucoes);
                        maquina(texto2,HM,memoriaInstrucoes, RAM, cache1, cache2, cache3, 0);
                        printf("\n\nFim do Tratador de interrupcao\n\n");
                        programa(memoriaInstrucoes);
                       }
                    }
                    break;
                }

                case 1:{
                    int conteudo1 = dadoMemoriaAdd1.palavras[umaInstrucao.add1.endPalavra];
                    int conteudo2 = dadoMemoriaAdd2.palavras[umaInstrucao.add2.endPalavra];
                    int  soma = conteudo1+conteudo2;

                    dadoMemoriaAdd3.palavras[umaInstrucao.add3.endPalavra] = soma;
                    dadoMemoriaAdd3.atualizado = true;

                    printf("\nSoma de: %d %d = %d\n", conteudo1, conteudo2, soma);
                    break;
                }

                case 2:{
                    int conteudo1 = dadoMemoriaAdd1.palavras[umaInstrucao.add1.endPalavra];
                    int conteudo2 = dadoMemoriaAdd2.palavras[umaInstrucao.add2.endPalavra];
                    int  sub = conteudo1-conteudo2;

                    dadoMemoriaAdd3.palavras[umaInstrucao.add3.endPalavra] = sub;
                    dadoMemoriaAdd3.atualizado = true;

                    printf("\nSubtracao de: %d %d = %d\n", conteudo1, conteudo2, sub);
                    
                    break;
                }
            }
        }
        PC++;
    }
}