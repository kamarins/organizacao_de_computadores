#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "bloco_de_memoria.h"
#include "memoria_cache.h"
#include "endereco.h"
#include "memoria_de_instrucoes.h"
#include "maquina.h"
#include "define.h"

int main (){
    clock_t temp;

    Cache *cache_01, *cache_02, *cache_03, *memoria_ram;
    //Bloco **memoria_ram = Alocar_Memoria_Ram(tamanho_ram);
    Instrucao **instrucoes = Preencher_Instrucoes(quantidade_instrucoes);
    
    temp=clock(); // Aloca tempo inicial

    //Função para criar e preencher o HD(arquivo binário)
    Criar_Prencher_HD(tamanho_hd);
    //A Memoria Ram
    //Preencher_Ram(memoria_ram, tamanho_ram);

    cache_01 = Criar_Cache(tamanho_cache_01);
    cache_02 = Criar_Cache(tamanho_cache_02);
    cache_03 = Criar_Cache(tamanho_cache_03);
    memoria_ram = Criar_Cache(tamanho_ram);

    maquina(instrucoes, cache_01, cache_02, cache_03, memoria_ram);

    double *tempo=malloc(sizeof(double));
    *tempo = ((double)temp)/((CLOCKS_PER_SEC/1000));
    
    //Calcular e printar as estatisticas
    estatisticas(cache_01, cache_02, cache_03, memoria_ram);

    temp = clock() - temp; // armazena tempo final - inicial
    //printf("\nTempo de execucao: %lf ms.\n", *tempo);


    free(cache_01);
    free(cache_02);
    free(cache_03);
    free(memoria_ram);
    free(instrucoes);
    free(tempo);

    return 0;
}
