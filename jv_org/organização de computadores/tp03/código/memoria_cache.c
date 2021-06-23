#include "memoria_cache.h"
#include "bloco_de_memoria.h"
#include "define.h"

struct cache{
   int tamanho_cache_ram; //Tamanho cache e ram
   int cache_hit;
   int cache_miss;
   long int custo;
   int qtd_acessos;
   int hit_hd;
   long double custo_hd;
   Bloco **bloco;
};

Cache *Criar_Cache(int tamanho_cache){

   Cache *memoria_cache = malloc(sizeof (Cache));
   
   memoria_cache->tamanho_cache_ram = tamanho_cache;
   memoria_cache->cache_hit = 0; //necessário inicializar com zero pra indicar que não realizamos nenhuma busca;
   memoria_cache->cache_miss = 0; //necessário inicializar com zero pra indicar que não realizamos nenhuma busca;
   memoria_cache->custo = 0;
   memoria_cache->custo_hd = 0;
   memoria_cache->hit_hd=0;
   memoria_cache->qtd_acessos = 0; //necessário inicializar com zero pra indicar que não acessamos nenhuma vez; 

   memoria_cache->bloco = malloc (tamanho_cache * sizeof (Bloco*));
   
   for (int i = 0; i < tamanho_cache; i++){
      memoria_cache->bloco[i] = Criar_Bloco();
      }
   //memoria_cache->custo_ram = 0;
   
	return memoria_cache;
}

void trocaCaches (Cache *primeiro, Cache *segundo, int endBloco){
  
   int indice = 0;
   int menoratt = getAtualizacaoBloco(getBloco(getCacheBloco(segundo), 0)); // cache destino

   time_t final = time(NULL);

   float maiorTemp = difftime (final, getTempo_acessado(getBloco(getCacheBloco(segundo), 0))); // cache destino

   for (int i = 0; i < getCacheTamanho(segundo); i++){
      
      //Verifica se tem algum bloco vazio
      if (getEndereco_bloco_cache(getBloco(getCacheBloco(segundo), i)) == -1){
            
         indice = i; // diz onde ta o vazio
         break;
      }
      //Verifica de acordo com a atutalizacao.
      else if (getAtualizacaoBloco(getBloco(getCacheBloco(segundo), i)) < menoratt &&
                      difftime (final, getTempo_acessado(getBloco(getCacheBloco(segundo), i))) > maiorTemp){
         
         menoratt = getAtualizacaoBloco(getBloco(getCacheBloco(segundo), i));
         maiorTemp = difftime (final, getTempo_acessado(getBloco(getCacheBloco(segundo), i)));
         indice = i;
      }
   }
   
   //Troca os blocos
   for (int i = 0; i < getCacheTamanho(primeiro); i++){
      
      if (getEndereco_bloco_cache(getBloco(getCacheBloco(primeiro), i)) == endBloco){
          //primeiro == origem
         Bloco *aux = getBloco(getCacheBloco(primeiro), i); 
         
         setBloco (getCacheBloco(segundo), getBloco(getCacheBloco(primeiro), i), indice);
         setBloco (getCacheBloco(primeiro), aux, i);
         break;
         
      }
   }
}

//Levar do HD para Ram
int HD_ram(Bloco *BlocoAux, Cache *RAM){

   int indice = 0;
   int menoratt = getAtualizacaoBloco(getBloco(getCacheBloco(RAM), 0));

   time_t final = time(NULL);

   float maiorTemp = difftime (final, getTempo_acessado(BlocoAux));

   for (int i = 0; i < getCacheTamanho(RAM); i++){
      //Verifica se tem algum bloco vazio
      if (getEndereco_bloco_cache(getBloco(getCacheBloco(RAM), i)) == -1){
         indice = i;
         break;
      }
      //Verifica de acordo com att
      else if (getAtualizacaoBloco(getBloco(getCacheBloco(RAM), i)) < menoratt && difftime (final, getTempo_acessado(BlocoAux)) > maiorTemp){

         menoratt = getAtualizacaoBloco(getBloco(getCacheBloco(RAM), i));
         maiorTemp = difftime (final, getTempo_acessado(BlocoAux));
         indice = i;
      }
   }
   
   //hd p ram
   //Troca os blocos
      //conferir se o bloco q ta na ram é vazio

      if(getEndereco_bloco_cache(getBloco(getCacheBloco(RAM), indice)) == -1){
            setBloco (getCacheBloco(RAM), BlocoAux, indice);
      }

      else{ 
            Bloco *aux = getBloco_cache(RAM, indice);
           // if(getAtualizacaoBloco(getBloco_cache(RAM, indice)) != 0){
               Salvar_HD(aux);
           // }
            //funcao que vai pegar bloco da ram e atualizar no hd
            setBloco (getCacheBloco(RAM), BlocoAux, indice);

      }

   return indice;
}

void Salvar_HD(Bloco *aux){
   
   FILE* hd = fopen("HD.dat","wb");
	int palavra, endereco;

   endereco = getEndereco_bloco_hd(aux);
   fseek(hd, endereco, SEEK_SET);
	
   //Preenchendo o HD
   for(int i=0;i<tamanho_hd;i++){
      palavra = getPalavra(aux, i);
		fwrite(&palavra, sizeof(int), 1, hd);
	}
	fclose(hd);

}

int getCacheTamanho (Cache *aux){
    return aux->tamanho_cache_ram;
}

void setCacheTamanho (Cache *aux, int tamanho_cache){
    aux->tamanho_cache_ram = tamanho_cache;
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
int getHDCusto(Cache *cacheCusto){
   return cacheCusto->custo_hd;
}

void setHDCusto(Cache *cacheCustoAux, int custo){
   cacheCustoAux->custo_hd += custo;
}

int getHDHit(Cache *aux){
   return aux->hit_hd;
}

void setHDHit(Cache *aux, int hit_hd){
   aux->hit_hd += hit_hd;
}

/*
//Funcão para retornar o bloco da memoria ram
Bloco *getBloco_da_ram(Bloco **memoria_ram, int posicao){
   return memoria_ram[posicao];
}


void setBloco_da_ram(Bloco **memoria_ram, int posicao, Bloco *aux){
   memoria_ram[posicao] = aux;
}
void setEndereco_bloco(Cache *cache, int posicao, Bloco *trocado){
   cache->bloco[posicao] = trocado;
}
*/

void atualizarRam(Cache *cache_01, Cache *cache_02, Cache *cache_03, Cache *memoria_ram){
   int i = 0, EnderecoBlocoMemorias, att_cache, att_ram;

   //CACHE 3
   for(i=0; i < tamanho_cache_03; i++){
        
      //Pegar qual é o bloco da cache 3
      EnderecoBlocoMemorias = getEndereco_bloco_cache(getBloco_cache(cache_03, i)); 


      att_cache = getAtualizacaoBloco(getBloco_cache(cache_03, i));
      att_ram = getAtualizacaoBloco(getBloco_cache(memoria_ram, EnderecoBlocoMemorias));
      

      if(att_cache >= att_ram){
        
         Bloco *aux1 = getBloco_cache(cache_03, i);

         //Pega o bloco da cache 3 e coloca na ram
         setBloco_cache(memoria_ram, EnderecoBlocoMemorias, aux1);
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
      EnderecoBlocoMemorias = getEndereco_bloco_cache(getBloco_cache(cache_03, i));
         
      att_cache = getAtualizacaoBloco(getBloco_cache(cache_03, i));
      att_ram = getAtualizacaoBloco(getBloco_cache(memoria_ram, EnderecoBlocoMemorias));

      if(att_cache >= att_ram){
        
         Bloco *aux1 = getBloco_cache(cache_03, i);

         //Pega o bloco da cache 3 e coloca na ram
         setBloco_cache(memoria_ram, EnderecoBlocoMemorias, aux1);
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
      EnderecoBlocoMemorias = getEndereco_bloco_cache(getBloco_cache(cache_03, i));
         
      att_cache = getAtualizacaoBloco(getBloco_cache(cache_03, i));
      att_ram = getAtualizacaoBloco(getBloco_cache(memoria_ram, EnderecoBlocoMemorias));

      if(att_cache >= att_ram){
        
         Bloco *aux1 = getBloco_cache(cache_03, i);

         //Pega o bloco da cache 3 e coloca na ram
         setBloco_cache(memoria_ram, EnderecoBlocoMemorias, aux1);
      }
   } 

}


void estatisticas(Cache* cache_01, Cache* cache_02, Cache* cache_03, Cache *memoria_ram){
//Cache* RAM_memory;
   printf("\n");
   printf("------------------------------------------------------------------------------------------\n");
   printf("\t\t\t\tInformativo\n");
   printf("------------------------------------------------------------------------------------------\n");


   double hit_L1 = getCacheHit(cache_01);
   double hit_L2 = getCacheHit(cache_02);
   double hit_L3 = getCacheHit(cache_03);
   double hit_RAM = getCacheHit(memoria_ram);

   double miss_L1 = getCacheMiss(cache_01);
   double miss_L2 = getCacheMiss(cache_02);
   double miss_L3 = getCacheMiss(cache_03);
   double miss_RAM = getCacheMiss(memoria_ram);

   printf (" \n\tL1 Hits %2.f \t Miss %2.f\n", hit_L1, miss_L1);
   printf (" \tL2 Hits  %2.f \t Miss %2.f\n", hit_L2, miss_L2);
   printf (" \tL3 Hits  %2.f \t Miss %2.f\n", hit_L3, miss_L3);
   printf (" \tRAM Hits %2.f \t Miss %2.f\n", hit_RAM, miss_RAM);
   //printf(" \tTamanho da Ram: %d",tamanho_ram );

   double l1 = ((hit_L1 * 100) / (hit_L1 + miss_L1));
   double l2 = ((hit_L2 * 100) / (hit_L2 + miss_L2));
   double l3 = ((hit_L3 * 100) / (hit_L3 + miss_L3));
   double ram = ((hit_RAM * 100) / (hit_RAM + miss_RAM));
   double hd = (100 - (l1 + l2 + l3 + ram));
   double ltotal=(l1 + l2 + l3 + ram);
   

  printf("\n\n \tDados estatisticos:\n\n");

  printf(" \tCache L1: HIT: %.2lf %%  | Miss: %.2lf %% |\n", l1, 100-l1);
  printf(" \tCache L2: HIT: %.2lf %%  | Miss: %.2lf %% |\n", l2, 100-l2);
  printf(" \tCache L3: HIT: %.2lf %%  | Miss: %.2lf %% |\n", l3, 100-l3);
  printf(" \tRam:      HIT: %.2lf %%  | Miss: %.2lf %% |\n", ram, 100-ram);
  printf(" \tHD:      HIT: %.2lf %%  | Miss:   0.0   |\n", hd );
  printf(" \tTotal:    HIT: %.2lf %%  | Miss: %.2lf %% |\n", ltotal, (100 - ltotal));      


   long int custoL1 = getCacheCusto(cache_01);
   long int custoL2 = getCacheCusto(cache_02);
   long int custoL3 = getCacheCusto(cache_03);
   long int custoRam = getCacheCusto(memoria_ram);
   
   long double custohd = getHDCusto(memoria_ram);

   long double custo_total = custoL1 + custoL2 + custoL3 + custoRam + custohd;
  
  printf(" \n\tCusto Cache L1: %ld.\n", custoL1);
  printf(" \n\tCusto Cache L2: %ld.\n", custoL2);
  printf(" \n\tCusto Cache L3: %ld.\n", custoL3);
  printf(" \n\tCusto RAM: %ld.\n", custoRam);
  printf(" \n\tCusto HD: %.LF.\n", custohd);
  printf(" \n\tCusto total: %.LF.\n", custo_total);
  
  printf("\n\n");
}
