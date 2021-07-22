#ifndef endereco_h
#define endereco_h

typedef struct endereco Endereco;

Endereco* cria_end();
int getEndBlocoEnd(Endereco* end);
void setEndBlocoEnd(Endereco* end, int endBlocoAux);
int getEndPalavra(Endereco* end);
void setEndPalavra(Endereco* end, int endPalavraAux);






#endif