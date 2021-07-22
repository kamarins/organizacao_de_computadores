#ifndef tp2_h
#define tp2_h

typedef struct blocomemoria BlocoMemoria;
typedef struct endereco Endereco;
typedef struct instrucao Instrucao;
typedef struct hitsMiss HitsMiss;


void montarRam(BlocoMemoria* RAM,int tamanhoRAM,int qntPalavrasBloco,int tamanhoPrograma);
void montarCache(BlocoMemoria* cache, int tamanhoCache);
void programaInterrupcao(Instrucao* memoriaInstrucoes);
void programa(Instrucao* memoriaInstrucoes);
void arquivoBin();
BlocoMemoria HD(BlocoMemoria* RAM, int endBloco, int posicaoRAM);
int  procurarNaMemoria(BlocoMemoria* memoria, Endereco endereco, int tamanhoMemoria);
void programaInterrupcao(Instrucao* memoriaInstrucoes);
int  LFU(int tamanho, BlocoMemoria* cache);
BlocoMemoria trocaDadosMemoria(int posicaoDestino, int posicaoRaiz, BlocoMemoria* memoriaDestino, BlocoMemoria* memoriaRaiz, int custo, Endereco endereco);
BlocoMemoria UCM(Endereco endereco, BlocoMemoria* RAM, BlocoMemoria* cache1, BlocoMemoria* cache2, BlocoMemoria* cache3);
void maquina(char* texto, HitsMiss *HM, Instrucao* memoriaInstrucoes, BlocoMemoria* RAM, BlocoMemoria* cache1, BlocoMemoria* cache2, BlocoMemoria* cache3, int PC);
HitsMiss* preencherHitsMiss();
#endif
