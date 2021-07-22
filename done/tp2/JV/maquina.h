#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#include "bloco_de_memoria.h"
#include "endereco.h"
#include "memoria_de_instrucoes.h"
#include "memoria_cache.h"


void maquina (Instrucao **instrucao, Cache *cache_01, Cache *cache_02, Cache *cache_03, Bloco **memoria_ram);
void executar (Cache *L1, Cache *L2, Cache *L3, Bloco **RAM, Instrucao *inst);


Bloco *MMU (Cache *L1, Cache *L2, Cache *L3, Bloco **RAM, int endBloco);
void salvar(Cache *L1, Cache *L2, Cache *L3, Bloco **RAM, int endBloco, int endP, int resultado);
void hitRAM (int cont);

