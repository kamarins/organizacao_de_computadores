#ifndef MEMORIA_HPP
#define MEMORIA_HPP
#include "instrucao.hpp"
#define TAM_BLOCO 4
#define TAM_C1 8
#define TAM_C2 16
#define TAM_C3 32
#define TAM_RAM 500

typedef struct memoria Memoria;
typedef struct hitMiss HitMiss; 

int getEndBloco(Memoria* memoria);
int getPalavra(Memoria* memoria, int indiceP);
int getAcesso(Memoria* memoria);
bool getAtualizado(Memoria* memoria);
void setEndBloco(Memoria* memoria, int endBloco);
void setPalavra(Memoria* memoria, int indiceP, int palavra);
void setAcesso(Memoria* memoria, int nAcessos);
void setAtualizado(Memoria* memoria, bool atualizado);
int getHitOne(HitMiss* hitMiss);
int getMissOne(HitMiss* hitMiss);
int getHitTwo(HitMiss* hitMiss);
int getMissTwo(HitMiss* hitMiss);
int getHitThree(HitMiss* hitMiss);
int getMissThree(HitMiss* hitMiss);
int getCusto(hitMiss* hitMiss);
void setHitOne(hitMiss* hitMiss, int l1Hit);
void setMissOne(HitMiss* hitMiss, int l1Miss);
void setHitTwo(hitMiss* hitMiss, int l2Hit);
void setMissTwo(HitMiss* hitMiss, int l2Miss);
void setHitThree(hitMiss* hitMiss, int l3Hit);
void setMissThree(HitMiss* hitMiss, int l3Miss);
void setCusto(HitMiss* hitMiss, int custo);
Memoria** alocarMemoria(int tamanho);
Memoria* alocarVetor();
void preencherRam(Memoria** ram, Instrucao** inst);
void imprimeRam(Memoria** ram);
void imprimirCache(Memoria** memoria, int tamanho);
HitMiss* inicializarHitMiss();
int buscarCache(Endereco* e, Memoria** cache, int tam_cache);
void insereCache(int valor, Memoria** memoria, Endereco* e, double tempoInicial);
void trocarCache(int endBloco, Memoria** cOrigem, int tam_cOrigem, Memoria** cDestino, int tam_cDestino, double tempoInicial);
void trocarRam(int endBloco, Memoria** ram, int tam_ram, Memoria** cDestino, int tam_cDestino, double tempoInicial);
Memoria* MMU(Memoria** c1, Memoria** c2, Memoria** c3, Memoria** ram, Endereco* e, HitMiss* hitMiss, double tempoInicial);
void limpaMemoria(Memoria** memoria, int tamanho);
void liberarMemoria(Memoria** memoria, int tamanho);
void liberarVetor(Memoria* memoria);

#endif