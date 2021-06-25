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

int HD_ram(Bloco *BlocoAux, Cache *RAM);

void trocaCaches (Cache *primeiro, Cache *segundo, int endBloco);
Bloco *getBloco_cache(Cache *memorias_caches_ram, int posicao);

void setBloco_cache(Cache *cache_01, int posicao, Bloco *aux);

int getCacheHit(Cache *cacheHit);
void setCacheHit(Cache *cacheHitAux, int cache_hit);

int getCacheMiss (Cache *cacheMiss);
void setCacheMiss (Cache *cacheMissAux, int cache_miss);

int getCacheCusto(Cache *cacheCusto);
void setCacheCusto (Cache *cacheCustoAux, int custo);

void Salvar_HD(Bloco *aux);

int getHDCusto(Cache *cacheCusto);
void setHDCusto(Cache *cacheCustoAux, int custo);

int getHDHit(Cache *aux);
void setHDHit(Cache *aux, int hit_hd);
/*
Bloco *getBloco_da_ram(Bloco **memoria_ram, int posicao);
void setBloco_da_ram(Bloco **memoria_ram, int posicao, Bloco *aux);

void setEndereco_bloco(Cache *cache, int posicao, Bloco *trocado);
*/

void atualizarRam(Cache *cache_01, Cache *cache_02, Cache *cache_03, Cache *memoria_ram);
void estatisticas(Cache* cache_01, Cache* cache_02, Cache* cache_03, Cache *memoria_ram);
