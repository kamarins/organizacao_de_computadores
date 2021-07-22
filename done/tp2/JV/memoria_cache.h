#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "bloco_de_memoria.h"
//struct
typedef struct cache Cache;

//funcoes da cache

Cache *Criar_Cache(int tamanho_cache);

int getCacheTamanho (Cache *aux);
void setCacheTamanho (Cache *aux, int tamanho_cache);

Bloco **getCacheBloco(Cache *aux);

void atualizarRam(Cache *cache_01, Cache *cache_02, Cache *cache_03, Bloco **memoria_ram);

void RAM_L3(Bloco **RAM, Cache *L3, int endBloco);

void trocaCaches (Cache *primeiro, Cache *segundo, int endBloco);
Bloco *getBloco_cache(Cache *memorias_caches_ram, int posicao);

void setBloco_cache(Cache *cache_01, int posicao, Bloco *aux);

int getCacheHit(Cache *cacheHit);
void setCacheHit(Cache *cacheHitAux, int cache_hit);

int getCacheMiss (Cache *cacheMiss);
void setCacheMiss (Cache *cacheMissAux, int cache_miss);

int getCacheCusto(Cache *cacheCusto);
void setCacheCusto (Cache *cacheCustoAux, int custo);

int getRamCusto(Cache *cacheCusto);
void setRamCusto(Cache *cacheCustoAux, int custo);

Bloco *getBloco_da_ram(Bloco **memoria_ram, int posicao);
void setBloco_da_ram(Bloco **memoria_ram, int posicao, Bloco *aux);
/*
void setEndereco_bloco(Cache *cache, int posicao, Bloco *trocado);
*/

void atualizarRam(Cache *cache_01, Cache *cache_02, Cache *cache_03, Bloco **memoria_ram);
void estatisticas(Cache* cache_01, Cache* cache_02, Cache* cache_03);
