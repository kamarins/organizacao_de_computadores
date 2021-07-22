#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//struct
typedef struct bloco Bloco;

//funcoes do bloco de memória
Bloco **Alocar_Memoria_Ram(int tamanho_ram);
Bloco *Criar_Bloco();

void Preencher_Ram(Bloco **bloco, int tamanho_ram);
Bloco *getBloco (Bloco **vetor, int indice);
void setBloco (Bloco **vetor, Bloco *novo, int indice);
void atualizarBlocoAtualizacao(Bloco* aux);
int getAtualizacaoBloco (Bloco *bloco);
time_t getTempo_acessado(Bloco *memoria_cache_ram);
void setTempo_acessado(Bloco *memoria_cache_ram, time_t tempo);
int getPalavra(Bloco *aux, int posicao);
void setPalavra (Bloco *aux, int palavra, int posicao);


int getEndereco_bloco_cache(Bloco *aux);

int getEndereco_bloco_ram(Bloco *auxiliar);

void setEndereco_bloco_ram(Bloco *auxiliar, int endereco_bloco_ram);

void setEndereco_bloco_cache(Bloco *auxiliar, int endereco_bloco_cache);
