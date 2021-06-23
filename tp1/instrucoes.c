#include "instrucoes.h"
#include "define.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//aqui tem-se a composição da memória. 
struct memoria{
    int memoriaDados[tamanho];
    int memoriaInstrucoes[100][4]; //programa que seja interpretado

};

//aloca a memoria e preenche com números aleatórios
Memoria* montarRam(){
    Memoria *memoria = (Memoria*) malloc(sizeof(Memoria));

    for(int i=0; i<tamanho; i++){
        memoria->memoriaDados[i]=rand()%1000;
    }
    
    return memoria;
};

//desaloca a memoria
void liberarMemoria(Memoria* memoria){
    free(memoria);
}

int* retornarRam(Memoria* memoria){
  return memoria->memoriaDados;
}

//intrucoes da maquina
void maquina(Memoria *memoria){

    int end1, end2, end3, soma, sub,
        opcode = TMP_MAX, //maior inteiro possivel;
        PC=0;
        
    while (opcode != opcodeSair){
        
        opcode = memoria->memoriaInstrucoes[PC][0];

        switch (opcode){
            //soma
            case opcodeSomar:
                end1 = memoria->memoriaInstrucoes[PC][1];
                end2 = memoria->memoriaInstrucoes[PC][2];
                end3 = memoria->memoriaInstrucoes[PC][3];

                soma = memoria->memoriaDados[end1] + memoria->memoriaDados[end2];

                memoria->memoriaDados[end3] = soma;

                break;

            //subtracao
            case opcodeSubtrair:
                end1 = memoria->memoriaInstrucoes[PC][1];
                end2 = memoria->memoriaInstrucoes[PC][2];
                end3 = memoria->memoriaInstrucoes[PC][3];

                sub = memoria->memoriaDados[end1] - memoria->memoriaDados[end2];

                memoria->memoriaDados[end3] = sub;

                break;

            //levar para memoria
            case opcodeLevarMem:
                end1 = memoria->memoriaInstrucoes[PC][1];
                end2 = memoria->memoriaInstrucoes[PC][2];
            
                memoria->memoriaDados[end2] = end1;

                break;

            //trazer da memoria
            case opcodeTrazerMem:

                memoria->memoriaInstrucoes[PC][1]= memoria->memoriaDados[memoria->memoriaInstrucoes[PC][2]];

                break;
        }

        PC++;

    }
}

//programa aleatorio
void programaAleatorio(Memoria* memoria){

    //0 -> opcode -> somar 
    //1 -> opcode -> subtrair
    //-1 -> halt

    for(int i=0; i<99; i++){
        memoria->memoriaInstrucoes[i][0] = rand()%2; //recebe o opcode
        memoria->memoriaInstrucoes[i][1] = rand()%1000;
        memoria->memoriaInstrucoes[i][2] = rand()%1000;
        memoria->memoriaInstrucoes[i][3]= rand()%1000;
    }

    //halt
    memoria->memoriaInstrucoes[99][0] = -1;
    memoria->memoriaInstrucoes[99][1] = -1;
    memoria->memoriaInstrucoes[99][2] = -1;
    memoria->memoriaInstrucoes[99][3] = -1;

    //maquina();
}

//operações matematicas
void adicao(Memoria* memoria, int primeiroValor, int segundoValor){

    //leva os valores para a memoria de instrucoes
    memoria->memoriaInstrucoes[0][0] = 2;                                          //Notes
    memoria->memoriaInstrucoes[0][1] = primeiroValor;                              //0 => opcode => somar
    memoria->memoriaInstrucoes[0][2] = 0;                                          //1 => opcode => subtrair
    memoria->memoriaInstrucoes[0][3] = opcodeSair;                                 //2 => opcode => levar para memoriaDados
                                                                                   //3 => trazer da memoriaDados
    memoria->memoriaInstrucoes[1][0] = 2;                                          //-1 => halt
    memoria->memoriaInstrucoes[1][1] = segundoValor;
    memoria->memoriaInstrucoes[1][2] = 1;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;                         

    //efetua a soma
    memoria->memoriaInstrucoes[2][0] = 0;
    memoria->memoriaInstrucoes[2][1] = 0;
    memoria->memoriaInstrucoes[2][2] = 1;
    memoria->memoriaInstrucoes[2][3] = 2;

    memoria->memoriaInstrucoes[3][0] = opcodeSair;   
    memoria->memoriaInstrucoes[3][1] = opcodeSair;
    memoria->memoriaInstrucoes[3][2] = opcodeSair;
    memoria->memoriaInstrucoes[3][3] = opcodeSair;

    maquina(memoria);
  
}

void subtracao(Memoria* memoria, int primeiroValor, int segundoValor){

    //leva os valores para a memoria de instrucoes
    memoria->memoriaInstrucoes[0][0] = 2;                                          //Notes
    memoria->memoriaInstrucoes[0][1] = primeiroValor;                              //0 => opcode => somar
    memoria->memoriaInstrucoes[0][2] = 0;                                          //1 => opcode => subtrair
    memoria->memoriaInstrucoes[0][3] = opcodeSair;                                 //2 => opcode => levar para memoriaDados
                                                                                   //3 => trazer da memoriaDados
    memoria->memoriaInstrucoes[1][0] = 2;                                          //-1 => halt
    memoria->memoriaInstrucoes[1][1] = segundoValor;
    memoria->memoriaInstrucoes[1][2] = 1;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;                         

    //efetua a subtracao
    memoria->memoriaInstrucoes[2][0] = 1;
    memoria->memoriaInstrucoes[2][1] = 0;
    memoria->memoriaInstrucoes[2][2] = 1;
    memoria->memoriaInstrucoes[2][3] = 2;

    memoria->memoriaInstrucoes[3][0] = opcodeSair;   
    memoria->memoriaInstrucoes[3][1] = opcodeSair;
    memoria->memoriaInstrucoes[3][2] = opcodeSair;
    memoria->memoriaInstrucoes[3][3] = opcodeSair;

    maquina(memoria);
} 

void multiplicacao(Memoria* memoria, int primeiroValor, int segundoValor ){

    //leva os valores para a memoria de instrucoes
    memoria->memoriaInstrucoes[0][0] = opcodeLevarMem;                                          //Notes
    memoria->memoriaInstrucoes[0][1] = primeiroValor;                              //0 => opcode => somar
    memoria->memoriaInstrucoes[0][2] = 0;                                          //1 => opcode => subtrair
    memoria->memoriaInstrucoes[0][3] = opcodeSair;                                 //2 => opcode => levar para memoriaDados
                                                                                   //3 => trazer da memoriaDados
    memoria->memoriaInstrucoes[1][0] = opcodeLevarMem;                                          //-1 => halt
    memoria->memoriaInstrucoes[1][1] = 0;
    memoria->memoriaInstrucoes[1][2] = 1;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;   

    //Realiza multiplas somas salvando o resultado na em[1]
    for(int i=0; i<segundoValor; i++){

        memoria->memoriaInstrucoes[i+2][0] = opcodeSomar;  
        memoria->memoriaInstrucoes[i+2][1] = 0;
        memoria->memoriaInstrucoes[i+2][2] = 1; 
        memoria->memoriaInstrucoes[i+2][3] = 1;
        
    }

    memoria->memoriaInstrucoes[segundoValor+2][0] = opcodeSair;
    memoria->memoriaInstrucoes[segundoValor+2][1] = opcodeSair;
    memoria->memoriaInstrucoes[segundoValor+2][2] = opcodeSair;
    memoria->memoriaInstrucoes[segundoValor+2][3] = opcodeSair;

    maquina(memoria);
}

void divisao(Memoria* memoria, int dividendo, int divisor){
    
    int ram1;
    int ram2;
    int cont=0;
    //levando para a memoria
    memoria->memoriaInstrucoes[0][0] = opcodeLevarMem;
    memoria->memoriaInstrucoes[0][1] = divisor;
    memoria->memoriaInstrucoes[0][2] = 0;
    memoria->memoriaInstrucoes[0][3] = opcodeSair;

    memoria->memoriaInstrucoes[1][0] = opcodeLevarMem;   
    memoria->memoriaInstrucoes[1][1] = dividendo;
    memoria->memoriaInstrucoes[1][2] = 1;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;
    
    memoria->memoriaInstrucoes[2][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[2][1] = opcodeSair;
    memoria->memoriaInstrucoes[2][2] = opcodeSair;
    memoria->memoriaInstrucoes[2][3] = opcodeSair;
    
    maquina(memoria);
   
    //trazendo da memoria
    memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[0][1] = -1; 
    memoria->memoriaInstrucoes[0][2] = 0; 
    memoria->memoriaInstrucoes[0][3] = opcodeSair;

    memoria->memoriaInstrucoes[1][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[1][1] = -1; 
    memoria->memoriaInstrucoes[1][2] = 1; 
    memoria->memoriaInstrucoes[1][3] = opcodeSair;
   
    memoria->memoriaInstrucoes[2][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[2][1] = opcodeSair;
    memoria->memoriaInstrucoes[2][2] = opcodeSair;
    memoria->memoriaInstrucoes[2][3] = opcodeSair;
    maquina(memoria);

    ram1 = memoria->memoriaInstrucoes[0][1];
    ram2 = memoria->memoriaInstrucoes[1][1];


    //Realizando a divisao
    while (ram2 >= ram1){

        memoria->memoriaInstrucoes[0][0] = opcodeSubtrair;   
        memoria->memoriaInstrucoes[0][1] = 1;
        memoria->memoriaInstrucoes[0][2] = 0;
        memoria->memoriaInstrucoes[0][3] = 1;

        memoria->memoriaInstrucoes[2][0] = opcodeSair;    //Halt
        memoria->memoriaInstrucoes[2][1] = opcodeSair;
        memoria->memoriaInstrucoes[2][2] = opcodeSair;
        memoria->memoriaInstrucoes[2][3] = opcodeSair;

        maquina(memoria);
        
        //trazer da memoria de dados da posicao 0
        memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
        memoria->memoriaInstrucoes[0][1] = -1; 
        memoria->memoriaInstrucoes[0][2] = 0; 
        memoria->memoriaInstrucoes[0][3] = opcodeSair;

        memoria->memoriaInstrucoes[2][0] = opcodeSair;    //Halt
        memoria->memoriaInstrucoes[2][1] = opcodeSair;
        memoria->memoriaInstrucoes[2][2] = opcodeSair;
        memoria->memoriaInstrucoes[2][3] = opcodeSair;

        maquina(memoria);
        
        ram1 = memoria->memoriaInstrucoes[0][1];

        memoria->memoriaInstrucoes[1][0] = opcodeTrazerMem;   
        memoria->memoriaInstrucoes[1][1] = -1; 
        memoria->memoriaInstrucoes[1][2] = 1; 
        memoria->memoriaInstrucoes[1][3] = opcodeSair;

        memoria->memoriaInstrucoes[2][0] = opcodeSair;    //Halt
        memoria->memoriaInstrucoes[2][1] = opcodeSair;
        memoria->memoriaInstrucoes[2][2] = opcodeSair;
        memoria->memoriaInstrucoes[2][3] = opcodeSair;
        maquina(memoria);

        ram2 = memoria->memoriaInstrucoes[1][1];
        
        cont++;
        
    }

    memoria->memoriaInstrucoes[0][0] = opcodeLevarMem;   
    memoria->memoriaInstrucoes[0][1] = cont;
    memoria->memoriaInstrucoes[0][2] = 3;
    memoria->memoriaInstrucoes[0][3] = opcodeSair;

    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria);
}

void potencia(Memoria* memoria, int base, int potencia){

    int r = base;
    
    if(potencia == 0){
        r = 1;
    }
    else
    {
        for (int i = 0; i < (potencia-1); i++){
            multiplicacao(memoria,r,base);

            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 1; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);

            r = memoria->memoriaInstrucoes[0][1];
        }  
    }

    memoria->memoriaInstrucoes[1][0] = opcodeLevarMem;                                          t
    memoria->memoriaInstrucoes[1][1] = r;
    memoria->memoriaInstrucoes[1][2] = 1;
    memoria->memoriaInstrucoes[1][3] = opcodeSair; 

    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria); 
   
}

void porcentagem(Memoria* memoria, int primeiroValor, int segundoValor){
    
    int aux1, aux2, aux3;
    int cem=100;

    multiplicacao(memoria, primeiroValor, segundoValor);
    memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[0][1] = -1; 
    memoria->memoriaInstrucoes[0][2] = 1; 
    memoria->memoriaInstrucoes[0][3] = opcodeSair;
   
    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria);
    aux1 = memoria->memoriaInstrucoes[0][1];

    divisao(memoria, aux1, cem);
    memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[0][1] = -1; 
    memoria->memoriaInstrucoes[0][2] = 3; 
    memoria->memoriaInstrucoes[0][3] = opcodeSair;
   
    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria);
    aux2 = memoria->memoriaInstrucoes[0][1];  

    printf("\n Você inseriu %d e descontou %d por cento, sendo %d o valor referente a porcentagem",primeiroValor, segundoValor, aux2); 
    
    Subtracao(memoria, primeiroValor, aux2);
    memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[0][1] = -1; 
    memoria->memoriaInstrucoes[0][2] = 2; 
    memoria->memoriaInstrucoes[0][3] = opcodeSair;
   
    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria);
    aux3 = memoria->memoriaInstrucoes[0][1];

    memoria->memoriaInstrucoes[1][0] = opcodeLevarMem;                                        
    memoria->memoriaInstrucoes[1][1] = aux3;
    memoria->memoriaInstrucoes[1][2] = 1;
    memoria->memoriaInstrucoes[1][3] = opcodeSair; 

    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria); 

}

//operacoes matematicas avançadas
void delta(Memoria* memoria, int a, int b ,int c){
    //b² - 4ac
    int constante = -4;
    int aux1, aux2, aux3;
    int resultado;

    potencia(memoria, b, 2);

    memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[0][1] = -1; 
    memoria->memoriaInstrucoes[0][2] = 1; 
    memoria->memoriaInstrucoes[0][3] = opcodeSair;
   
    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria);

    aux1=memoria->memoriaInstrucoes[0][1];

    multiplicacao(memoria, constante, a);

    memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[0][1] = -1; 
    memoria->memoriaInstrucoes[0][2] = 1; 
    memoria->memoriaInstrucoes[0][3] = opcodeSair;
   
    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria);

    aux2=memoria->memoriaInstrucoes[0][1];

    multiplicacao(memoria, constante, a);

    memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[0][1] = -1; 
    memoria->memoriaInstrucoes[0][2] = 1; 
    memoria->memoriaInstrucoes[0][3] = opcodeSair;
   
    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria);

    aux3=memoria->memoriaInstrucoes[0][1];

    resultado = aux1+aux3;

    memoria->memoriaInstrucoes[1][0] = opcodeLevarMem;                                        
    memoria->memoriaInstrucoes[1][1] = resultado;
    memoria->memoriaInstrucoes[1][2] = 1;
    memoria->memoriaInstrucoes[1][3] = opcodeSair; 

    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria); 


}

void volumeParalelepipedo(Memoria* memoria, int primeiroValor, int segundoValor, int terceiroValor){
    // n1 * n2*n3
    int aux;
    
    multiplicacao(memoria, primeiroValor, segundoValor);

    memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[0][1] = -1; 
    memoria->memoriaInstrucoes[0][2] = 1; 
    memoria->memoriaInstrucoes[0][3] = opcodeSair;

    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria);    

    aux = memoria->memoriaInstrucoes[0][1];
    multiplicacao(memoria, aux, terceiroValor);
}

void volumeCilindro(Memoria* memoria, int abase, int altura){
    
    multiplicacao(memoria, abase, altura);
}

void volumeEsfera(Memoria* memoria, int raio){
    
    double constante = (4.0/3.0) * 3.1415;
    int aux;

    potencia(memoria,raio,3);

    memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[0][1] = -1; 
    memoria->memoriaInstrucoes[0][2] = 1; 
    memoria->memoriaInstrucoes[0][3] = opcodeSair;

    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria);

    aux = memoria->memoriaInstrucoes[0][1];

    multiplicacao(memoria, aux, constante);
    
}

void volumeCubo(Memoria* memoria, int a){
    
    int aux; 

    multiplicacao(memoria,a,a);

    memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[0][1] = -1; 
    memoria->memoriaInstrucoes[0][2] = 1; 
    memoria->memoriaInstrucoes[0][3] = opcodeSair;
   
    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria);

    aux=memoria->memoriaInstrucoes[0][1];

    multiplicacao(memoria, aux, a);

}

void volumePiramide(Memoria* memoria, int abase, int altura){
    
    int aux1;
    int aux2;
    int constante=3;

    multiplicacao(memoria,abase,altura);

    memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[0][1] = -1; 
    memoria->memoriaInstrucoes[0][2] = 1; 
    memoria->memoriaInstrucoes[0][3] = opcodeSair;
   
    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria);

    aux1 = memoria->memoriaInstrucoes[0][1];

    Divisao(memoria, aux1, constante);

    memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[0][1] = -1; 
    memoria->memoriaInstrucoes[0][2] = 3; 
    memoria->memoriaInstrucoes[0][3] = opcodeSair;
   
    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria);

    aux2 = memoria->memoriaInstrucoes[0][1];

    memoria->memoriaInstrucoes[1][0] = opcodeLevarMem;                                        
    memoria->memoriaInstrucoes[1][1] = aux2;
    memoria->memoriaInstrucoes[1][2] = 1;
    memoria->memoriaInstrucoes[1][3] = opcodeSair; 

    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria); 

}

void areaTriangulo(Memoria* memoria, int base, int altura){

    int aux;
    int constante = 2;

    multiplicacao(memoria, base, altura); 

    memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[0][1] = -1; 
    memoria->memoriaInstrucoes[0][2] = 1; 
    memoria->memoriaInstrucoes[0][3] = opcodeSair;
   
    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria);

    //memoria->memoriaInstrucoes[PC][1]= memoria->memoriaDados[memoria->memoriaInstrucoes[PC][2]];

    aux = memoria->memoriaInstrucoes[0][1];

    Divisao(memoria, aux, constante);
}

void areaQuadrado(Memoria* memoria, int n){
    
    multiplicacao(memoria, n, n); 
}

void perimetroQuadrado(Memoria* memoria, int lado){

    multiplicacao(memoria, lado ,4);   
}

void perimetroRetangulo(Memoria* memoria, int primeiroValor, int segundoValor){
    int aux;

    adicao(memoria, primeiroValor,segundoValor);

    memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[0][1] = -1; 
    memoria->memoriaInstrucoes[0][2] = 2; 
    memoria->memoriaInstrucoes[0][3] = opcodeSair;
   
    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria);
    aux = memoria->memoriaInstrucoes[0][1];    

    multiplicacao(memoria, 2, aux);
}

void PA(Memoria* memoria,  int primeiroValor, int segundoValor, int terceiroValor){

    int aux;

    printf("\n\t A PA eh: ");
    printf("%d  ", primeiroValor);

    aux = primeiroValor;

    for(int i=0; i<terceiroValor-1; i++){
        adicao(memoria, segundoValor, aux);
        
        memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
        memoria->memoriaInstrucoes[0][1] = -1; 
        memoria->memoriaInstrucoes[0][2] = 2; 
        memoria->memoriaInstrucoes[0][3] = opcodeSair;
    
        memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
        memoria->memoriaInstrucoes[1][1] = opcodeSair;
        memoria->memoriaInstrucoes[1][2] = opcodeSair;
        memoria->memoriaInstrucoes[1][3] = opcodeSair;

        maquina(memoria);
        aux = memoria->memoriaInstrucoes[0][1];

        printf("%d  ", aux);
    }
    printf("\n");
}

void PG(Memoria* memoria, int primeiroValor, int segundoValor, int razao){
    
    int aux1;
    int aux2;

    subtracao(memoria, primeiroValor, 1);
     
    memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[0][1] = -1; 
    memoria->memoriaInstrucoes[0][2] = 2; 
    memoria->memoriaInstrucoes[0][3] = opcodeSair;

    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria);
    aux1 = memoria->memoriaInstrucoes[0][1];
  
    potencia(memoria, razao, aux1);
     
    memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[0][1] = -1; 
    memoria->memoriaInstrucoes[0][2] = 1; 
    memoria->memoriaInstrucoes[0][3] = opcodeSair;

    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria);
    aux2 = memoria->memoriaInstrucoes[0][1];

    multiplicacao(memoria, segundoValor, aux1);
}

void fatorial(Memoria* memoria, int n){
    int aux1 = n;
    int aux2 = 1;

    for(int i = 0; i < n; i++){
        Multiplicacao(memoria, aux2, aux1);

        memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
        memoria->memoriaInstrucoes[0][1] = -1; 
        memoria->memoriaInstrucoes[0][2] = 1; 
        memoria->memoriaInstrucoes[0][3] = opcodeSair;
    
        memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
        memoria->memoriaInstrucoes[1][1] = opcodeSair;
        memoria->memoriaInstrucoes[1][2] = opcodeSair;
        memoria->memoriaInstrucoes[1][3] = opcodeSair;

        maquina(memoria);
        aux2 = memoria->memoriaInstrucoes[0][1];   
        aux1--;
    } 
}

void permutacaoSimples(Memoria* memoria, int n){

    fatorial(memoria, n);

}

void combinacao(Memoria* memoria, int primeiroValor, int segundoValor){

    int aux1,aux2,aux3,aux4,aux5,aux6;    

    permutacaoSimples(memoria, primeiroValor); // n!
    memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[0][1] = -1; 
    memoria->memoriaInstrucoes[0][2] = 1; 
    memoria->memoriaInstrucoes[0][3] = opcodeSair;
   
    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria);
    aux1 = memoria->memoriaInstrucoes[0][1];    

    permutacaoSimples(memoria, segundoValor); // p!
    memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[0][1] = -1; 
    memoria->memoriaInstrucoes[0][2] = 1; 
    memoria->memoriaInstrucoes[0][3] = opcodeSair;
   
    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria);
    aux2 = memoria->memoriaInstrucoes[0][1];    

    subtracao(memoria, primeiroValor, segundoValor); // n - p
    memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[0][1] = -1; 
    memoria->memoriaInstrucoes[0][2] = 1; 
    memoria->memoriaInstrucoes[0][3] = opcodeSair;
   
    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria);
    aux3 = memoria->memoriaInstrucoes[0][1];    

    permutacaoSimples(memoria, aux3); // (n - p) !
    memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[0][1] = -1; 
    memoria->memoriaInstrucoes[0][2] = 1; 
    memoria->memoriaInstrucoes[0][3] = opcodeSair;
   
    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria);
    aux4 = memoria->memoriaInstrucoes[0][1];    

    
    multiplicacao(memoria, aux2, aux4); // p! * (n - p) !
    memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[0][1] = -1; 
    memoria->memoriaInstrucoes[0][2] = 1; 
    memoria->memoriaInstrucoes[0][3] = opcodeSair;
   
    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria);
    aux5 = memoria->memoriaInstrucoes[0][1];    

   
    divisao(memoria, aux1, aux5 ); // n! /  p! * (n - p) ! 
    memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[0][1] = -1; 
    memoria->memoriaInstrucoes[0][2] = 3; 
    memoria->memoriaInstrucoes[0][3] = opcodeSair;
   
    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria);
    aux6 = memoria->memoriaInstrucoes[0][1];    

    memoria->memoriaInstrucoes[1][0] = opcodeLevarMem;                                        
    memoria->memoriaInstrucoes[1][1] = aux6;
    memoria->memoriaInstrucoes[1][2] = 1;
    memoria->memoriaInstrucoes[1][3] = opcodeSair; 

    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria); 

    //printf(" Você digitou %d como número de elementos e %d como número natural e a sua combinação é %d\n",primeiro_valor, segundo_valor, var_aux6);

}

void arranjo(Memoria* memoria, int primeiroValor, int segundoValor){
    
    int aux1,aux2,aux3,aux4,aux5,aux6;    

    permutacaoSimples(memoria, primeiroValor); // n!
    memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[0][1] = -1; 
    memoria->memoriaInstrucoes[0][2] = 1; 
    memoria->memoriaInstrucoes[0][3] = opcodeSair;
   
    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria);
    aux1 = memoria->memoriaInstrucoes[0][1];    
   
    subtracao(memoria, primeiroValor, segundoValor); // n - p
    memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[0][1] = -1; 
    memoria->memoriaInstrucoes[0][2] = 2; 
    memoria->memoriaInstrucoes[0][3] = opcodeSair;
   
    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria);
    aux2 = memoria->memoriaInstrucoes[0][1];    

    permutacaoSimples(memoria, aux2); // (n - p) !
    memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[0][1] = -1; 
    memoria->memoriaInstrucoes[0][2] = 1; 
    memoria->memoriaInstrucoes[0][3] = opcodeSair;
   
    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria);
    aux3 = memoria->memoriaInstrucoes[0][1];    

   
    divisao(memoria, aux1, aux5 ); // n! /  p! * (n - p) ! 
    memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[0][1] = -1; 
    memoria->memoriaInstrucoes[0][2] = 3; 
    memoria->memoriaInstrucoes[0][3] = opcodeSair;
   
    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria);
    aux4 = memoria->memoriaInstrucoes[0][1];    

    memoria->memoriaInstrucoes[1][0] = opcodeLevarMem;                                        
    memoria->memoriaInstrucoes[1][1] = aux4;
    memoria->memoriaInstrucoes[1][2] = 1;
    memoria->memoriaInstrucoes[1][3] = opcodeSair; 

    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria); 

//printf(" Você digitou %d como número de elementos e %d como número natural e a sua combinação é %d\n",primeiro_valor, segundo_valor, var_aux4);
}

void fibonnaci(Memoria* memoria, int n){
    int f1 = 0;
    int f2 = 1;
    int soma;

    if (n < 0){
        printf(" Valor Inválido");
        
    }else if (n == 0){
        memoria->memoriaInstrucoes[1][0] = opcodeLevarMem;                                        
        memoria->memoriaInstrucoes[1][1] = 0;
        memoria->memoriaInstrucoes[1][2] = 1;
        memoria->memoriaInstrucoes[1][3] = opcodeSair; 

        memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
        memoria->memoriaInstrucoes[1][1] = opcodeSair;
        memoria->memoriaInstrucoes[1][2] = opcodeSair;
        memoria->memoriaInstrucoes[1][3] = opcodeSair;

        maquina(memoria); 

    }else{
        printf(" 0 - 1");

        while(f2 < n){
            adicao(memoria, f1, f2);

            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 2; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            soma = memoria->memoriaInstrucoes[0][1];  
            printf(" - %d", soma);
            f1 = f2;
            f2 = soma;
        }
        printf("\n");
    }
}

void IMC(Memoria* memoria, int peso, int altura){

    int aux;

    potencia(memoria, altura,2);

    memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[0][1] = -1; 
    memoria->memoriaInstrucoes[0][2] = 1; 
    memoria->memoriaInstrucoes[0][3] = opcodeSair;
   
    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria);

    //memoria->memoriaInstrucoes[PC][1]= memoria->memoriaDados[memoria->memoriaInstrucoes[PC][2]];

    aux = memoria->memoriaInstrucoes[0][1];

    divisao(memoria, peso ,aux);
    
}


//operacoes relacionadas a fisica

void distanciaPercorrida(Memoria* memoria, int primeiroValor, int segundoValor){
    multiplicacao(memoria, primeiroValor,segundoValor);
}

void velocidadeMedia(Memoria* memoria, int dist1, int dist2, int t1, int t2){
    int aux1, aux2;

    subtracao(memoria,dist1,dist2);
    memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[0][1] = -1; 
    memoria->memoriaInstrucoes[0][2] = 2; 
    memoria->memoriaInstrucoes[0][3] = opcodeSair;
   
    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria);
    aux1 = memoria->memoriaInstrucoes[0][1];  

    subtracao(memoria,t1,t2);
    memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[0][1] = -1; 
    memoria->memoriaInstrucoes[0][2] = 2; 
    memoria->memoriaInstrucoes[0][3] = opcodeSair;
   
    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria);
    aux2 = memoria->memoriaInstrucoes[0][1];  

    divisao(memoria,aux1,aux2);
   
}

void acelaracao(Memoria* memoria, int v1, int v2, int t1, int t2){
    int aux1, aux2;

    subtracao(memoria,v1,v2);
    memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[0][1] = -1; 
    memoria->memoriaInstrucoes[0][2] = 2; 
    memoria->memoriaInstrucoes[0][3] = opcodeSair;
   
    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria);
    aux1 = memoria->memoriaInstrucoes[0][1];  

    subtracao(memoria,t1,t2);
    memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[0][1] = -1; 
    memoria->memoriaInstrucoes[0][2] = 2; 
    memoria->memoriaInstrucoes[0][3] = opcodeSair;
   
    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria);
    aux2 = memoria->memoriaInstrucoes[0][1];  

    divisao(memoria,aux1,aux2);
}

void forca(Memoria* memoria, int primeiroValor, int segundoValor){

    multiplicacao(memoria, primeiroValor, segundoValor);
}

void calorimetria(Memoria* memoria,  int primeiroValor, int segundoValor, int terceiroValor){
      
    int aux;

    multiplicacao(memoria, primeiroValor, segundoValor);
    
    memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[0][1] = -1; 
    memoria->memoriaInstrucoes[0][2] = 1; 
    memoria->memoriaInstrucoes[0][3] = opcodeSair;
   
    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria);
    aux = memoria->memoriaInstrucoes[0][1]; 

    multiplicacao(memoria, aux, terceiroValor);
}

//conversao de medidas

void convSegMin(Memoria* memoria, int n){
    
    divisao(memoria, n,60);
}

void convMinSeg(Memoria* memoria, int n){
    
    multiplicacao(memoria, n,60);
}

void convMinHr(Memoria* memoria, int n){

    divisao(memoria, n,60);

}

void convHrMin(Memoria* memoria, int n){
    
    multiplicacao(memoria, n,60);
}

void convHrSeg(Memoria* memoria, int n){
    
    multiplicacao(memoria, n,3600);
}

void convCm_M(Memoria* memoria, int n){
    
    divisao(memoria, n,100);
}

void convM_Cm(Memoria* memoria, int n){
    
    multiplicacao(memoria, n,100);
}

void KelvinCelsius(Memoria* memoria, int n){
    
    subtracao(memoria, n,273);
}

void CelsiusKelvin(Memoria* memoria, int n){
    Adicao(memoria, n, 273);
}

void CelsiusFahrenheit(Memoria* memoria, int n){
    float constante = 2; //aproximado
    int aux;

    multiplicacao(memoria, n, 2);

    memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[0][1] = -1; 
    memoria->memoriaInstrucoes[0][2] = 1; 
    memoria->memoriaInstrucoes[0][3] = opcodeSair;
   
    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria);
    aux = memoria->memoriaInstrucoes[0][1]; 

    adicao(memoria, aux,32);
}

void FahrenheitCelsius(Memoria* memoria, int n){
    float constante = 2; //aproximado
    int aux;

    subtracao(memoria, n, 32);

    memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
    memoria->memoriaInstrucoes[0][1] = -1; 
    memoria->memoriaInstrucoes[0][2] = 2; 
    memoria->memoriaInstrucoes[0][3] = opcodeSair;
   
    memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
    memoria->memoriaInstrucoes[1][1] = opcodeSair;
    memoria->memoriaInstrucoes[1][2] = opcodeSair;
    memoria->memoriaInstrucoes[1][3] = opcodeSair;

    maquina(memoria);
    aux = memoria->memoriaInstrucoes[0][1]; 

   divisao(memoria, aux, 2);
}

