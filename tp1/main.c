#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "instrucoes.h"

int main(){
    Memoria *memoria = NULL;
    
    memoria = montarRam();
    menu (memoria);
    liberarMemoria(memoria);

    return 0;
}