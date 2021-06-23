#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "bloco_de_memoria.h"
//struct
typedef struct endereco Endereco;

//funcoes do endereço
Endereco *Criar_Endereco(int endereco_bloco, int endereco_palavra);

int getEndereco_palavra(Endereco *enderecos);

int getEndereco_bloco_instrucao (Endereco *auxiliar);

void deleteAdress(Endereco *end);