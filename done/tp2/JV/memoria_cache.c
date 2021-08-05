#include "memoria_cache.h"
#include "bloco_de_memoria.h"
#include "define.h" 

struct cache{
   int tamanho_cache;
   int cache_hit;
   int cache_miss;
   long int custo;
   int qtd_acessos;
   Bloco **bloco;
   long int custo_ram; //Vai armazenar o custo da RAM.
};

Cache *Criar_Cache(int tamanho_cache){

   Cache *memoria_cache = malloc(sizeof (Cache));
   
   memoria_cache->tamanho_cache = tamanho_cache;
   memoria_cache->cache_hit = 0; //necessário inicializar com zero pra indicar que não realizamos nenhuma busca;
   memoria_cache->cache_miss = 0; //necessário inicializar com zero pra indicar que não realizamos nenhuma busca;
   memoria_cache->custo = 0;
   memoria_cache->qtd_acessos = 0; //necessário inicializar com zero pra indicar que não acessamos nenhuma vez; 

   memoria_cache->bloco = malloc (tamanho_cache * sizeof (Bloco*));
   
   for (int i = 0; i < tamanho_cache; i++){
      memoria_cache->bloco[i] = Criar_Bloco();
   }
   memoria_cache->custo_ram = 0;
   
	return memoria_cache;
}




void trocaCaches (Cache *primeiro, Cache *segundo, int endBloco){
   int indice = 0;
   int menoratt = getAtualizacaoBloco(getBloco(getCacheBloco(segundo), 0));

   time_t final = time(NULL);

   float maiorTemp = difftime (final, getTempo_acessado(getBloco(getCacheBloco(segundo), 0)));

   for (int i = 0; i < getCacheTamanho(segundo); i++){
      
      //Verifica se tem algum bloco vazio
      if (getEndereco_bloco_ram(getBloco(getCacheBloco(segundo), i)) == -1){
            
         indice = i;
         break;
      }
      //Verifica de acordo com a atutalizacao.
      else if (getAtualizacaoBloco(getBloco(getCacheBloco(segundo), i)) < menoratt && difftime (final, getTempo_acessado(getBloco(getCacheBloco(segundo), i))) > maiorTemp){
         
         menoratt = getAtualizacaoBloco(getBloco(getCacheBloco(segundo), i));
         maiorTemp = difftime (final, getTempo_acessado(getBloco(getCacheBloco(segundo), i)));
         indice = i;
      }
   }
   
   //Troca os blocos
   for (int i = 0; i < getCacheTamanho(primeiro); i++){
      
      if (getEndereco_bloco_ram(getBloco(getCacheBloco(primeiro), i)) == endBloco){
         
         Bloco *aux = getBloco(getCacheBloco(primeiro), i);
         setBloco (getCacheBloco(segundo), getBloco(getCacheBloco(primeiro), i), indice);
         setBloco (getCacheBloco(primeiro), aux, i);
         //zeraBlocoAtuazliacao(get1Bloco(getCacheBloco(segundo), indice));
         //zeraBlocoAtuazliacao(get1Bloco(getCacheBloco(primeiro), i));
         break;
         
      }
   }
}


void RAM_L3(Bloco **RAM, Cache *L3, int endBloco){
   int indice = 0;
   int menoratt = getAtualizacaoBloco(getBloco(getCacheBloco(L3), 0));

   time_t final = time(NULL);

   float maiorTemp = difftime (final, getTempo_acessado(getBloco(RAM, 0)));

   for (int i = 0; i < getCacheTamanho(L3); i++){
      //Verifica se tem algum bloco vazio
      if (getEndereco_bloco_ram(getBloco(getCacheBloco(L3), i)) == -1){
         indice = i;
         break;
      }
      //Verifica de acordo com att
      else if (getAtualizacaoBloco(getBloco(getCacheBloco(L3), i)) < menoratt && difftime (final, getTempo_acessado(getBloco(RAM, i))) > maiorTemp){
         menoratt = getAtualizacaoBloco(getBloco(getCacheBloco(L3), i));
         maiorTemp = difftime (final, getTempo_acessado(getBloco(RAM, i)));
         indice = i;
      }
   }
   
   //Troca os blocos
   for (int i = 0; i < 100; i++){
      if (getEndereco_bloco_ram(getBloco(RAM, i)) == endBloco){
         
         Bloco *aux = getBloco(RAM, i);
         setBloco(RAM, getBloco(getCacheBloco(L3), indice), i);
         setBloco (getCacheBloco(L3), aux, indice);
         
         break;
      }
   }
}


int getCacheTamanho (Cache *aux){
    return aux->tamanho_cache;
}

void setCacheTamanho (Cache *aux, int tamanho_cache){
    aux->tamanho_cache = tamanho_cache;
}

Bloco **getCacheBloco(Cache *aux){
    return aux->bloco;
}

Bloco *getBloco_cache(Cache *memorias_caches_ram, int posicao){
   return memorias_caches_ram->bloco[posicao];
}

void setBloco_cache(Cache *cache, int posicao, Bloco *aux){
   cache->bloco[posicao] = aux;
}

int getCacheHit(Cache *cacheHit){
   return cacheHit->cache_hit;
}

void setCacheHit(Cache *cacheHitAux, int cache_hit){
   cacheHitAux->cache_hit += cache_hit;
}

int getCacheMiss (Cache *cacheMiss){
   return cacheMiss->cache_miss;
}

void setCacheMiss (Cache *cacheMissAux, int cache_miss){
   cacheMissAux->cache_miss += cache_miss;
}

int getCacheCusto(Cache *cacheCusto){
   return cacheCusto->custo;
}

void setCacheCusto (Cache *cacheCustoAux, int custo){
   cacheCustoAux->custo += custo;
}

//Printar o custo da RAM
int getRamCusto(Cache *cacheCusto){
   return cacheCusto->custo_ram;
}

void setRamCusto(Cache *cacheCustoAux, int custo){
   cacheCustoAux->custo_ram += custo;
}

//Funcão para retornar o bloco da memoria ram
Bloco *getBloco_da_ram(Bloco **memoria_ram, int posicao){
   return memoria_ram[posicao];
}

void setBloco_da_ram(Bloco **memoria_ram, int posicao, Bloco *aux){
   memoria_ram[posicao] = aux;
}

/*
void setEndereco_bloco(Cache *cache, int posicao, Bloco *trocado){
   cache->bloco[posicao] = trocado;
}
*/

void atualizarRam(Cache *cache_01, Cache *cache_02, Cache *cache_03, Bloco **memoria_ram){
   int i = 0, EnderecoBlocoMemorias, att_cache, att_ram;

   //CACHE 3
   for(i=0; i < tamanho_cache_03; i++){
        
      //Pegar qual é o bloco da cache 3
      EnderecoBlocoMemorias = getEndereco_bloco_ram(getBloco_cache(cache_03, i)); 


      att_cache = getAtualizacaoBloco(getBloco_cache(cache_03, i));
      att_ram = getAtualizacaoBloco(getBloco_da_ram(memoria_ram, EnderecoBlocoMemorias));
      

      if(att_cache >= att_ram){
        
         Bloco *aux1 = getBloco_cache(cache_03, i);

         //Pega o bloco da cache 3 e coloca na ram
         setBloco_da_ram(memoria_ram, EnderecoBlocoMemorias, aux1);
      }
   }
   

   //CACHE 2
   for(i = 0; i < tamanho_cache_02;i++){

      Bloco *aux1 = getBloco_cache(cache_02, i);
      setBloco_cache(cache_03, i, aux1);
   }

   //Para levar para a RAM
   for (i = 0; i < tamanho_cache_02; i++){
         
      //Pegar qual é o bloco da cache 3
      EnderecoBlocoMemorias = getEndereco_bloco_ram(getBloco_cache(cache_03, i));
         
      att_cache = getAtualizacaoBloco(getBloco_cache(cache_03, i));
      att_ram = getAtualizacaoBloco(getBloco_da_ram(memoria_ram, EnderecoBlocoMemorias));

      if(att_cache >= att_ram){
        
         Bloco *aux1 = getBloco_cache(cache_03, i);

         //Pega o bloco da cache 3 e coloca na ram
         setBloco_da_ram(memoria_ram, EnderecoBlocoMemorias, aux1);
      }
   } 
   

   //CACHE 1
   for(i = 0; i < tamanho_cache_01;i++){

      Bloco *aux1 = getBloco_cache(cache_01, i);
      setBloco_cache(cache_02, i, aux1);
   }

   for(i = 0; i < tamanho_cache_01;i++){

      Bloco *aux1 = getBloco_cache(cache_02, i);
      setBloco_cache(cache_03, i, aux1);
   }



   //Para levar para a RAM
   for (i = 0; i < tamanho_cache_01; i++){
         
      //Pegar qual é o bloco da cache 3
      EnderecoBlocoMemorias = getEndereco_bloco_ram(getBloco_cache(cache_03, i));
         
      att_cache = getAtualizacaoBloco(getBloco_cache(cache_03, i));
      att_ram = getAtualizacaoBloco(getBloco_da_ram(memoria_ram, EnderecoBlocoMemorias));

      if(att_cache >= att_ram){
        
         Bloco *aux1 = getBloco_cache(cache_03, i);

         //Pega o bloco da cache 3 e coloca na ram
         setBloco_da_ram(memoria_ram, EnderecoBlocoMemorias, aux1);
      }
   } 

}




void estatisticas(Cache* cache_01, Cache* cache_02, Cache* cache_03){
//Cache* RAM_memory;
   printf("\n");
   printf("------------------------------------------------------------------------------------------\n");
   printf("\t\t\t\tInformativo\n");
   printf("------------------------------------------------------------------------------------------\n");


   double hit_L1 = getCacheHit(cache_01);
   double hit_L2 = getCacheHit(cache_02);
   double hit_L3 = getCacheHit(cache_03);

   double miss_L1 = getCacheMiss(cache_01);
   double miss_L2 = getCacheMiss(cache_02);
   double miss_L3 = getCacheMiss(cache_03);

   printf (" \n\tL1 Hits %2.f \t Miss %2.f\n", hit_L1, miss_L1);
   printf (" \tL2 Hits %2.f \t Miss %2.f\n", hit_L2, miss_L2);
   printf (" \tL3 Hits %2.f \t Miss %2.f\n", hit_L3, miss_L3);
   printf(" \tTamanho da Ram: %d",tamanho_ram );

   double l1 = ((hit_L1 * 100) / (hit_L1 + miss_L1));
   double l2 = ((hit_L2 * 100) / (hit_L2 + miss_L2));
   double l3 = ((hit_L3 * 100) / (hit_L3 + miss_L3));
   double ram=(100 - (l1 + l2 + l3));
   double ltotal=(l1 + l2 + l3);

  printf("\n\n \tDados estatisticos:\n\n");

  printf(" \tCache L1: HIT: %.2lf %% | Miss: %.2lf %% |\n", l1, 100-l1);
  printf(" \tCache L2: HIT: %.2lf %% | Miss: %.2lf %% |\n", l2, 100-l2);
  printf(" \tCache L3: HIT: %.2lf %% | Miss: %.2lf %% |\n", l3, 100-l3);
  printf(" \tRam:      HIT: %.2lf %% | Miss: 0.0      |\n", ram);
  printf(" \tTotal:    HIT: %.2lf %% | Miss: %.2lf %% |\n", ltotal, (100 - ltotal));      
   
   long int custoL1 =getCacheCusto(cache_01);
   long int custoL2 =getCacheCusto(cache_02);
   long int custoL3 =getCacheCusto(cache_03);
   long int custoRam =getRamCusto(cache_01);

   long int custo_total = custoL1 + custoL2 + custoL3 + custoRam;
  
  printf(" \n\tCusto Cache L1: %ld.\n", custoL1);
  printf(" \n\tCusto Cache L2: %ld.\n", custoL2);
  printf(" \n\tCusto Cache L3: %ld.\n", custoL3);
  printf(" \n\tCusto RAM: %ld.\n", custoRam);
  printf(" \n\tCusto total: %ld.\n", custo_total);
  
  printf("\n\n");

}
