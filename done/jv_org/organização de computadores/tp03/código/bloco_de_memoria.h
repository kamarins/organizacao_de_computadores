#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//struct
typedef struct bloco Bloco;

//funcoes do bloco de memória
Bloco **Alocar_Memoria_Ram(int tamanho_ram);
Bloco *Criar_Bloco();

//void Preencher_Ram(Bloco **bloco, int tamanho_ram);
void Criar_Prencher_HD(int tamanho_hd);

Bloco *getBloco (Bloco **vetor, int indice);
void setBloco (Bloco **vetor, Bloco *novo, int indice);
void atualizarBlocoAtualizacao(Bloco* aux);
int getAtualizacaoBloco (Bloco *bloco);
time_t getTempo_acessado(Bloco *memoria_cache_ram);
void setTempo_acessado(Bloco *memoria_cache_ram, time_t tempo);
int getPalavra(Bloco *aux, int posicao);
void setPalavra (Bloco *aux, int palavra, int posicao);
int getEndereco_bloco_cache(Bloco *aux);
void setEndereco_bloco_cache(Bloco *auxiliar, int endereco_bloco_cache);
int getEndereco_bloco_hd(Bloco *auxiliar);
void setEndereco_bloco_hd(Bloco *auxiliar, int endereco_bloco_hd);
