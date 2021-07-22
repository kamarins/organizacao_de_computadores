#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include "blocodememoria.h"
#include "endereco.h"
#include "instrucao.h"
#include "MMU.h"


void maquina(Instrucao** memoriaInstrucoes , BlocoMemoria** RAM, BlocoMemoria** cache1, BlocoMemoria** cache2, BlocoMemoria** cache3, int tamanhoCache1, int tamanhoCache2, int tamanhoCache3){
    int PC=0;
    int opcode = INT_MAX;
    int custo = 0;
    //caches 1  2 e 3 Hit e Miss
    int missC1 = 0;
    int hitC1 = 0;
    int missC2 = 0;
    int hitC2 = 0;
    int missC3 = 0;
    int hitC3 = 0;
    int hitRAM = 0;
    printf("\nopcode: %d", opcode);
    while(opcode != -1){
        Instrucao* umaInstrucao = cria_uma_ins();
        umaInstrucao = memoriaInstrucoes[PC];
        int opcode = getOpcode(umaInstrucao);
        //TP2
        if(opcode != -1){
            BlocoMemoria* dadoMemoriaAdd1 = cria_um_bloco();
            BlocoMemoria* dadoMemoriaAdd2 = cria_um_bloco();
            BlocoMemoria* dadoMemoriaAdd3 = cria_um_bloco();

            Endereco* add1 = getadd1(umaInstrucao);
            Endereco* add2 = getadd1(umaInstrucao);
            Endereco* add3 = getadd1(umaInstrucao);
            dadoMemoriaAdd1 = MMU(add1, RAM, cache1, cache2, cache3, tamanhoCache1, tamanhoCache2, tamanhoCache3);
            dadoMemoriaAdd2 = MMU(add2, RAM, cache1, cache2, cache3, tamanhoCache1, tamanhoCache2, tamanhoCache3);
            dadoMemoriaAdd3 = MMU(add3, RAM, cache1, cache2, cache3, tamanhoCache1, tamanhoCache2, tamanhoCache3);

            custo += getCusto(dadoMemoriaAdd1);
            custo += getCusto(dadoMemoriaAdd2);
            custo += getCusto(dadoMemoriaAdd3);

            if(getCacheHit(dadoMemoriaAdd1)==1){
                hitC1++;
            }else if(getCacheHit(dadoMemoriaAdd1)==2){
                missC1++;
                hitC2++;
            }else if(getCacheHit(dadoMemoriaAdd1)==3){
                missC1++;
                missC2++;
                hitC3++;
            }else if(getCacheHit(dadoMemoriaAdd1)==4){
                missC1++;
                missC2++;
                missC3++;
            }
            if(getCacheHit(dadoMemoriaAdd2)==1){
                hitC1++;
            }else if(getCacheHit(dadoMemoriaAdd2)==2){
                missC1++;
                hitC2++;
            }else if(getCacheHit(dadoMemoriaAdd2)==3){
                missC1++;
                missC2++;
                hitC3++;
            }else if(getCacheHit(dadoMemoriaAdd2)==4){
                missC1++;
                missC2++;
                missC3++;
            }
            if(getCacheHit(dadoMemoriaAdd3)==1){
                hitC1++;
            }else if(getCacheHit(dadoMemoriaAdd3)==2){
                missC1++;
                hitC2++;
            }else if(getCacheHit(dadoMemoriaAdd3)==3){
                missC1++;
                missC2++;
                hitC3++;
            }else if(getCacheHit(dadoMemoriaAdd3)==4){
                missC1++;
                missC2++;
                missC3++;
            }
            printf("\n4");

            printf("\nCusto ate o momento do programa em execucao: %d", custo);
            printf("\nHits e Misses ate o momento: C1 hit: %d | C1 miss: %d | C2 hit: %d | C2 miss: %d | C3 hit: %d | C3 miss: %d", hitC1, missC1, hitC2, missC2, hitC3, missC3);
        
            switch (opcode)
            {
                case 0:{
                    //levar para cache1 dados externos
                    printf("Nao ha demanda para levar dados para as memorias. ");
                    break;
                }
                case 1:{
                    //somar
                    int conteudo1 = getPalavras(dadoMemoriaAdd1 , 1);
                    int conteudo2 = getPalavras(dadoMemoriaAdd2, 2);
                    int soma = conteudo1 + conteudo2;

                    setPalavras(dadoMemoriaAdd3, soma, 3);
                    setAtualizado(dadoMemoriaAdd3);

                    printf("somando %d", soma);
                    break;
                }
                case 2:{
                    //subtrarir
                    int conteudo1 = getPalavras(dadoMemoriaAdd1, 1);
                    int conteudo2 = getPalavras(dadoMemoriaAdd2, 2);
                    int sub = conteudo1 - conteudo2;

                    setPalavras(dadoMemoriaAdd3, sub, 3);
                    setAtualizado(dadoMemoriaAdd3);

                    printf("subtraindo %d", sub);
                    break;
                }
            }
            PC++;
        }
    }
    printf("\nCusto total do programa: %d", custo);
    printf("\nHits e Misses do programa - C1 hit: %d | C1 miss: %d | C2 hit: %d | C2 miss: %d", hitC1, missC1, hitC2, missC2);
}

void montarCacheComDados(int tamanho, int tipoCache, BlocoMemoria** cache1, BlocoMemoria** cache2, int qtdPalavrasBloco){
    srand(time(NULL));
    for(int i=0; i<tamanho; i++){
        BlocoMemoria* aux = cria_um_bloco();
        setEndBloco(aux, INT_MIN);
        int palavras[qtdPalavrasBloco];
        for(int j=0; j<qtdPalavrasBloco; j++){
            palavras[j] = rand()%1000000;
        }
        setPalavrasVetor(aux, palavras);
        if(tipoCache==1)
            cache1[i]=aux;
        else
            cache2[i]=aux;
    }
}

void montarCacheVazia(int tamanho, BlocoMemoria** qqCache){
    //posso criar tudo de uma vez
    for(int i=0; i<tamanho; i++){
        BlocoMemoria* aux = cria_um_bloco();
        qqCache[i] = aux;
    }
}

/*void montarRAM(BlocoMemoria** RAM){
    srand(time(NULL));
    for(int i=0; i<tamanhoRAM; i++){
        BlocoMemoria* aux = cria_um_bloco();
        setEndBloco(aux,i);
        int palavras[qtdPalavrasBloco];
        for(int j=0; j<qtdPalavrasBloco; j++){
            palavras[j] = rand()%1000000;
        }
        setPalavrasVetor(aux, palavras);
        RAM[i] = aux;
    }
}*/

void montarRAM(BlocoMemoria** RAM, int tamanhoRAM, int qtdPalavrasBloco, int tamanhoPrograma){
    srand(time(NULL));
    for(int i=0; i<tamanhoRAM; i++){
        int palavras[qtdPalavrasBloco];
        setEndBloco(RAM[i], i);
        for(int j=0; j<qtdPalavrasBloco; j++){
        }
        setPalavrasVetor(RAM[i],palavras);
    }
}

void montarInstrucoesProgramaAleatorio(Instrucao** memoriaInstrucoes, int tamanhoPrograma, int tamanhoRAM, int qtdPalavrasBloco){
    memoriaInstrucoes = cria_ins(tamanhoPrograma);
    srand(time(NULL));
    for(int i=0; i<tamanhoPrograma; i++){
        Instrucao* umaInstrucao = cria_uma_ins();
        setOpcode(umaInstrucao, rand()%3);

        Endereco* add1 = cria_end();
        setEndBlocoEnd(add1, rand()%tamanhoRAM);
        setEndPalavra(add1, rand()%qtdPalavrasBloco);
        setadd1(umaInstrucao, add1);

        Endereco* add2 = cria_end();
        setEndBlocoEnd(add2, rand()%tamanhoRAM);
        setEndPalavra(add2, rand()%qtdPalavrasBloco);
        setadd1(umaInstrucao, add2);

        Endereco* add3 = cria_end();
        setEndBlocoEnd(add3, rand()%tamanhoRAM);
        setEndPalavra(add3, rand()%qtdPalavrasBloco);
        setadd1(umaInstrucao, add3);

        memoriaInstrucoes[i] = umaInstrucao;

    }

    Instrucao* umaInstrucao = cria_uma_ins();
    setOpcode(umaInstrucao, -1);

    memoriaInstrucoes[tamanhoPrograma - 1] = umaInstrucao;
}


void montarProgramaGerador(Instrucao** memoriaInstrucoes,int tamanhoPrograma){
    printf("\n1");
    FILE* teste = fopen("teste.txt", "r");
    int aux;
    Endereco* end_aux = cria_end();
    printf("\n2");
    for(int i=0; i<tamanhoPrograma-1; i++){
        Instrucao* umaInstrucao = cria_uma_ins();
        fscanf(teste, "%d", &aux);
        setOpcode(umaInstrucao, aux);
        fscanf(teste, "%d", &end_aux);
        setadd1(umaInstrucao, end_aux);
        fscanf(teste, "%d", &aux);
        setEndPalavra(getadd1(umaInstrucao), aux);
        fscanf(teste, "%d", &end_aux);
        setadd2(umaInstrucao, end_aux);
        fscanf(teste, "%d", &aux);
        setEndPalavra(getAdd2(umaInstrucao), aux);
        fscanf(teste, "%d", &end_aux);
        setAdd3(umaInstrucao, end_aux);
        fscanf(teste, "%d", &aux);
        setEndPalavra(getAdd3(umaInstrucao), aux);

        memoriaInstrucoes[i] = umaInstrucao;
    }
    printf("\n3");
    Instrucao* umaInstrucao = cria_uma_ins();
    fscanf(teste, "%d", getOpcode(umaInstrucao));
    //setOpcode(umaInstrucao, aux);
    
    memoriaInstrucoes[tamanhoPrograma-1]=umaInstrucao;
    fclose(teste);
} 

void main(){

    int tamanhoRAM = 1000;
    int tamanhoCache1 = 16;
    int tamanhoCache2 = 32;
    int tamanhoCache3 = 64;
    int tamanhoPrograma = 10001;
    int qtdPalavrasBloco = 4;

    Instrucao** memoriaInstrucoes = cria_ins(tamanhoPrograma);
    BlocoMemoria** RAM = cria_bloco(tamanhoPrograma); 
    BlocoMemoria** cache1 = cria_bloco(tamanhoCache1);
    BlocoMemoria** cache2 = cria_bloco(tamanhoCache2);
    BlocoMemoria** cache3 = cria_bloco(tamanhoCache3);
    montarRAM(RAM, tamanhoRAM, qtdPalavrasBloco, tamanhoPrograma);
    montarCacheVazia(tamanhoCache1, cache1);
    montarCacheVazia(tamanhoCache2, cache2);
    montarCacheVazia(tamanhoCache3, cache3);
    printf("\nA");
    //montarInstrucoesProgramaAleatorio(memoriaInstrucoes, tamanhoPrograma, tamanhoRAM, qtdPalavrasBloco);
    montarProgramaGerador(memoriaInstrucoes, tamanhoPrograma);
    printf("\nB");
    maquina(memoriaInstrucoes, RAM, cache1, cache2, cache3, tamanhoCache1, tamanhoCache2, tamanhoCache3);
    printf("\nC");
    printf("\nterminou");
}