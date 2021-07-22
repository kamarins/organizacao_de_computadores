#include "bloco_de_memoria.h"
#include "memoria_cache.h"

struct bloco{
   int *palavras;
   int endereco_bloco_ram;
   int endereco_bloco_cache;
   int atualizacoes;
   time_t tempo; 
};


Bloco **Alocar_Memoria_Ram(int tamanho_ram){
    
    Bloco **memoria_ram = malloc(tamanho_ram * sizeof (Bloco*));
    
    for (int i = 0; i < tamanho_ram; i++){
        memoria_ram[i] = Criar_Bloco();
    }
	return memoria_ram;
}

Bloco *Criar_Bloco(){

    Bloco *bloco = malloc (sizeof(Bloco));

    bloco->palavras = malloc (4 * sizeof(int));
    bloco->endereco_bloco_ram = -1;
    bloco->endereco_bloco_cache = -1;
    bloco->atualizacoes = 0;

	time_t t = time(NULL);
    bloco->tempo = time(&t);

    return bloco; 
}

void Preencher_Ram(Bloco **bloco, int tamanho_ram){
    
    for (int i = 0; i < tamanho_ram; i++){
        
        for (int j = 0; j < 4; j++){
            bloco[i]->palavras[j] = rand() % 100;
            
            //Printar as palavras
            //printf("%d\n", getPalavra(getBloco_da_ram(bloco,i), j));

           /* RAM[0]-> 200 300 400 800
            RAM[1]-> 200 300 400 800
            RAM[2]-> 200 300 400 800
            RAM[3]-> 200 300 400 8001
            ...
            RAM[999] -> Preenchendo o bloco*/
        }
        setEndereco_bloco_ram(getBloco_da_ram(bloco, i), i);

        //bloco[i]->endereco_bloco_ram = i;
    }
}

Bloco *getBloco (Bloco **vetor, int indice){
    return vetor[indice];
}

void setBloco (Bloco **vetor, Bloco *novo, int indice){
    vetor[indice] = novo;
}

void atualizarBlocoAtualizacao(Bloco* aux){
    aux->atualizacoes+= 1;
}

int getAtualizacaoBloco (Bloco *bloco){
    return bloco->atualizacoes;
}

time_t getTempo_acessado(Bloco *memoria_cache_ram){
    return memoria_cache_ram->tempo;
}

void setTempo_acessado(Bloco *memoria_cache_ram, time_t tempo){
    memoria_cache_ram->tempo = tempo;
}
//ate aqui

int getPalavra(Bloco *aux, int posicao){
    return aux->palavras[posicao];
}

void setPalavra (Bloco *aux, int palavra, int posicao){
    aux->palavras[posicao] = palavra;
}

int getEndereco_bloco_cache(Bloco *aux){
    return aux->endereco_bloco_cache;
}

int getEndereco_bloco_ram(Bloco *auxiliar){
    return auxiliar->endereco_bloco_ram;
}

void setEndereco_bloco_ram(Bloco *auxiliar, int endereco_bloco_ram){
    auxiliar->endereco_bloco_ram = endereco_bloco_ram;
}

void setEndereco_bloco_cache(Bloco *auxiliar, int endereco_bloco_cache){
    auxiliar->endereco_bloco_cache = endereco_bloco_cache;
}