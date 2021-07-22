#include"funcoes.h"
#include"define.h"
#include<math.h>

struct memoria{
    int RAM[tamanho];
    int Memoria_Instrucoes[1000][4];

};

int* RetornarRAM(Memoria* m){
  return m->RAM;
}
//aloca a variável e preenche o velor da struct com números aleatórios
Memoria* Alocar_Memoria(){
 
    Memoria *m = malloc(sizeof(Memoria));
    for(int i=0; i<tamanho; i++){
        m->RAM[i]=rand()%1000;
    }
    return m;
}

//aleatório
void Programa_Aleatorio(Memoria* m){

    for(int i=0; i<999; i++){
        m->Memoria_Instrucoes[i][0] = rand()%2;
        m->Memoria_Instrucoes[i][1] = rand()%100;
        m->Memoria_Instrucoes[i][2] = rand()%100;
        m->Memoria_Instrucoes[i][3]= rand()%100;
    }
    m->Memoria_Instrucoes[999][0] = -1;
    m->Memoria_Instrucoes[999][1] = -1;
    m->Memoria_Instrucoes[999][2] = -1;
    m->Memoria_Instrucoes[999][3]= -1;
}
 
//instruções da máquina
void maquina(Memoria* m){
 
    int contador = 0;
    int opcode = TMP_MAX;
    int end1, end2, end3, soma, subtracao;
 
    while(opcode != opcode_sair){
        opcode = m->Memoria_Instrucoes[contador][0];
        switch (opcode){

            case opcode_somar:
                end1 = m->Memoria_Instrucoes[contador][1];
                end2 = m->Memoria_Instrucoes[contador][2];
                end3 = m->Memoria_Instrucoes[contador][3];
            
                soma = m->RAM[end1] + m->RAM[end2];

                m->RAM[end3] = soma;
                break;
            
            case opcode_subtrair:
                end1 = m->Memoria_Instrucoes[contador][1];
                end2 = m->Memoria_Instrucoes[contador][2];
                end3 = m->Memoria_Instrucoes[contador][3];

                subtracao = m->RAM[end1] - m->RAM[end2];

                m->RAM[end3] = subtracao;
                break;
            
            case opcode_levar_ram:
                end1 = m->Memoria_Instrucoes[contador][1];
                end2 = m->Memoria_Instrucoes[contador][2];
            
                m->RAM[end2] = end1;
                break;
        }

        contador++;
    }
}

void Free(Memoria* m){
    free(m);
}

//matemática básica
void Adicao(Memoria* m, int primeiro_valor, int segundo_valor){
  
    m->Memoria_Instrucoes[0][0] = opcode_levar_ram;   
    m->Memoria_Instrucoes[0][1]= primeiro_valor;
    m->Memoria_Instrucoes[0][2] = opcode_somar;
    m->Memoria_Instrucoes[0][3] = opcode_sair;

    m->Memoria_Instrucoes[1][0] = opcode_levar_ram;   
    m->Memoria_Instrucoes[1][1] = segundo_valor;
    m->Memoria_Instrucoes[1][2]= opcode_subtrair;
    m->Memoria_Instrucoes[1][3]= opcode_sair;

    m->Memoria_Instrucoes[2][0] = opcode_somar;   
    m->Memoria_Instrucoes[2][1] = opcode_somar;
    m->Memoria_Instrucoes[2][2] = opcode_subtrair;
    m->Memoria_Instrucoes[2][3] = opcode_subtrair;

    m->Memoria_Instrucoes[3][0] = opcode_sair;   
    m->Memoria_Instrucoes[3][1] = opcode_sair;
    m->Memoria_Instrucoes[3][2] = opcode_sair;
    m->Memoria_Instrucoes[3][3] = opcode_sair;

    maquina(m);
}

void Subtracao(Memoria* m, int primeiro_valor, int segundo_valor){
   
    m->Memoria_Instrucoes[0][0] = opcode_levar_ram;   //Leva pra RAM  --- [linha][coluna]
    m->Memoria_Instrucoes[0][1]= primeiro_valor;
    m->Memoria_Instrucoes[0][2] = opcode_somar;
    m->Memoria_Instrucoes[0][3] = opcode_sair;

    m->Memoria_Instrucoes[1][0] = opcode_levar_ram;   //Leva pra RAM
    m->Memoria_Instrucoes[1][1] = segundo_valor;
    m->Memoria_Instrucoes[1][2]= opcode_subtrair;
    m->Memoria_Instrucoes[1][3]= opcode_sair;

    m->Memoria_Instrucoes[2][0] = opcode_subtrair;
    m->Memoria_Instrucoes[2][1] = opcode_somar;
    m->Memoria_Instrucoes[2][2] = opcode_subtrair;
    m->Memoria_Instrucoes[2][3] = opcode_subtrair;

    m->Memoria_Instrucoes[3][0] = opcode_sair;    //Halt
    m->Memoria_Instrucoes[3][1] = opcode_sair;
    m->Memoria_Instrucoes[3][2] = opcode_sair;
    m->Memoria_Instrucoes[3][3] = opcode_sair;

    maquina(m);
}

void Multiplicacao(Memoria* m, int primeiro_valor, int segundo_valor){
   
    int i =0;
    
    m->Memoria_Instrucoes[0][0] = opcode_levar_ram;   //Leva pra RAM  --- [linha][coluna]
    m->Memoria_Instrucoes[0][1] = primeiro_valor;
    m->Memoria_Instrucoes[0][2] = opcode_somar;
    m->Memoria_Instrucoes[0][3] = opcode_sair;

    m->Memoria_Instrucoes[1][0] = opcode_levar_ram;   //Leva pra RAM
    m->Memoria_Instrucoes[1][1] = opcode_somar;
    m->Memoria_Instrucoes[1][2] = opcode_subtrair;
    m->Memoria_Instrucoes[1][3] = opcode_sair;

    //Realiza multiplas somas salvando o resultado na RAM[1]
    for(i=0; i<segundo_valor; i++){

        m->Memoria_Instrucoes[i+2][0] = opcode_somar;
        m->Memoria_Instrucoes[i+2][1] = opcode_somar;
        m->Memoria_Instrucoes[i+2][2] = opcode_subtrair;
        m->Memoria_Instrucoes[i+2][3] = opcode_subtrair;
    }

    //instrucao para parar a maquina
    m->Memoria_Instrucoes[segundo_valor+2][0] = opcode_sair;
    m->Memoria_Instrucoes[segundo_valor+2][1] = opcode_sair;
    m->Memoria_Instrucoes[segundo_valor+2][2] = opcode_sair;
    m->Memoria_Instrucoes[segundo_valor+2][3] = opcode_sair;

    maquina(m);
}

void Divisao(Memoria* m, int primeiro_valor, int segundo_valor){

    int contador = 0;

    m->Memoria_Instrucoes[0][0] = opcode_levar_ram;   //Leva pra RAM  --- [linha][coluna]
    m->Memoria_Instrucoes[0][1]= primeiro_valor;
    m->Memoria_Instrucoes[0][2] = opcode_somar;
    m->Memoria_Instrucoes[0][3] = opcode_sair;

    m->Memoria_Instrucoes[1][0] = opcode_levar_ram;   //Leva pra RAM
    m->Memoria_Instrucoes[1][1] = segundo_valor;
    m->Memoria_Instrucoes[1][2]= opcode_subtrair;
    m->Memoria_Instrucoes[1][3]= opcode_sair;

    
    m->Memoria_Instrucoes[2][0] = opcode_sair;    //Halt
    m->Memoria_Instrucoes[2][1] = opcode_sair;
    m->Memoria_Instrucoes[2][2] = opcode_sair;
    m->Memoria_Instrucoes[2][3] = opcode_sair;

    maquina(m);

    //Looping para realizar a divisão
    while (m->RAM[0] >= m->RAM[1]){

        m->Memoria_Instrucoes[0][0] = opcode_subtrair;   //Leva pra RAM
        m->Memoria_Instrucoes[0][1] = opcode_somar;
        m->Memoria_Instrucoes[0][2] = opcode_subtrair;
        m->Memoria_Instrucoes[0][3] = opcode_somar;

        m->Memoria_Instrucoes[1][0] = opcode_sair;  //Halt
        m->Memoria_Instrucoes[1][1] = opcode_sair;
        m->Memoria_Instrucoes[1][2] = opcode_sair;
        m->Memoria_Instrucoes[1][3] = opcode_sair;

        maquina(m);

        //Cont para armazenar quantas vezes o looping foi executado
        //Cont = Resultado da divisão
        contador++;
    }

    m->RAM[0]=contador;
}

//matematica aplicada
void Volume_Paralelepipedo(Memoria* m, int primeiro_valor, int segundo_valor, int terceiro_valor){

    int var_aux;

    Multiplicacao(m, primeiro_valor, segundo_valor);
    var_aux = m->RAM[1];
    Multiplicacao(m, var_aux, terceiro_valor);
}

void Delta(Memoria* m, int primeiro_valor, int segundo_valor, int terceiro_valor){

    int var_aux;
    int quatro_negativo = -4;
    int var_aux2;
    int var_aux3;
    int calculo;

    Multiplicacao(m, segundo_valor, segundo_valor); // b^2
    var_aux = m->RAM[1];
    Multiplicacao(m, quatro_negativo, primeiro_valor);
    var_aux2 = m->RAM[1];
    Multiplicacao(m, var_aux2, terceiro_valor);
    var_aux3 = m->RAM[1];

    calculo = var_aux + var_aux3;
    printf(" Você inseriu %d para a, %d para b e %d para c, o resultado da operação é: %d\t\n\n", primeiro_valor, segundo_valor, terceiro_valor, calculo);
        
}

void IMC(Memoria* m, int primeiro_valor, int segundo_valor){

    int var_aux;

    Multiplicacao(m, segundo_valor, segundo_valor); 
    var_aux = m->RAM[1];
    Divisao(m, primeiro_valor, var_aux);
    var_aux = m->RAM[1];
}

void Potencia(Memoria* m, int primeiro_valor, int segundo_valor){

    int calculo = primeiro_valor;
    int i;

    if(segundo_valor == 0){
        calculo = 1;
    }else{
       for (i = 0; i < (segundo_valor-1); i++){
            Multiplicacao(m,calculo,primeiro_valor);
            calculo = m->RAM[1];
        }  
    }
}

void Area_Triangulo(Memoria* m, int primeiro_valor, int segundo_valor){

    int var_aux;
    int dois_positivo = 2;

    Multiplicacao(m, primeiro_valor, segundo_valor); 
    var_aux = m->RAM[1];
    Divisao(m, var_aux, dois_positivo);
}

void Area_Quadrado(Memoria* m, int primeiro_valor){
    
    Multiplicacao(m, primeiro_valor, primeiro_valor); 
}

void Area_Retangulo(Memoria* m, int primeiro_valor, int segundo_valor){

    int var_aux;
    int dois_positivo = 2;
    int var_aux2;

    Adicao(m, primeiro_valor, segundo_valor);
    var_aux = m-> RAM[1];
    Multiplicacao(m,  dois_positivo, var_aux);
    var_aux2 = m-> RAM[1];
}

void Porcentagem(Memoria* m, int primeiro_valor, int segundo_valor){
    
    int var_aux;
    int cem_positivo = 100;
    int var_aux2;
    int var_aux3;

    Multiplicacao(m,  primeiro_valor, segundo_valor);
    var_aux = m->RAM[1];

    Divisao(m, var_aux, cem_positivo);
    var_aux2 = m->RAM[0];   

    printf("\n Você inseriu %d e descontou %d por cento, sendo %d o valor referente a porcentagem",primeiro_valor, segundo_valor, var_aux2); 
    
    Subtracao(m, primeiro_valor, var_aux2);
    var_aux3 = m->RAM[1]; 

    printf("\n Você ficou com %d \n", var_aux3);
}

void PA(Memoria* m,  int primeiro_valor, int segundo_valor, int terceiro_valor){

    int var_aux;

    printf("%d  ", primeiro_valor);

    var_aux = primeiro_valor;

    for(int i=0; i<terceiro_valor-1; i++){
        Adicao(m, segundo_valor, var_aux);
        var_aux = m -> RAM[1];
        printf("%d  ", var_aux);
    }
    printf("\n");
}

void Perimetro_Quadrado(Memoria* m, int primeiro_valor){

    int var_aux;
    int var_aux2;
    int var_aux3;

    Multiplicacao(m, primeiro_valor, primeiro_valor);
    var_aux = m->RAM[1];

    Multiplicacao(m, var_aux, primeiro_valor);
    var_aux2 = m->RAM[1];

    Multiplicacao(m, var_aux2, primeiro_valor);
    var_aux3 = m->RAM[1];
    printf(" Você digitou %d, e o perímetro do quadrado é: %d", primeiro_valor, var_aux3);   
}

void Perimetro_Retangulo(Memoria* m, int primeiro_valor, int segundo_valor){

    int var_aux;
    int dois_positivo = 2; 
    int var_aux2;

    Adicao(m, primeiro_valor, segundo_valor);
    var_aux = m->RAM[1];

    Multiplicacao(m, dois_positivo, var_aux);
    var_aux2 = m->RAM[1];

    printf(" Você digitou %d como base e %d como altura, sendo %d o valor do perimetro", primeiro_valor, segundo_valor, var_aux2);
}

void Soma_Quadrados(Memoria* m, int primeiro_valor, int segundo_valor){
    
    int var_aux;
    int var_aux2;
    int var_aux3;

    Multiplicacao(m,  primeiro_valor, primeiro_valor);
    var_aux = m-> RAM[1];

    Multiplicacao(m,  segundo_valor, segundo_valor);
    var_aux2 = m-> RAM[1];
    int mostrar_usuario = var_aux2;

    Adicao(m, var_aux, var_aux2);
    var_aux3 = m -> RAM[1];

    printf("\n O primeiro valor digitado foi %d, e o seu quadrado é %d. O segundo valor digitado foi %d, e o seu quadrado é %d. O resultado da operação é %d.", primeiro_valor, m -> RAM[0], segundo_valor, mostrar_usuario, var_aux3);
}

void Fatorial(Memoria* m, int primeiro_valor){

    int aux = primeiro_valor;
    int aux2 = 1;

    for(int i = 0; i < primeiro_valor; i++){
        Multiplicacao(m, aux2, aux);
        aux2 = m -> RAM[1];
        aux--;
    } 
}

void Permutacao_Simples(Memoria* m, int primeiro_valor){

    Fatorial(m, primeiro_valor);

}

void Combinacao(Memoria* m, int primeiro_valor, int segundo_valor){

    int var_aux;
    int var_aux2;
    int var_aux3;
    int var_aux4;
    int var_aux5;
    int var_aux6;    

    Permutacao_Simples(m, primeiro_valor); // n!
    var_aux = m -> RAM[1];
    // int conta2 = var_aux;
    //printf("%d\n", var_aux);
    Permutacao_Simples(m, segundo_valor); // p!
    var_aux2 = m -> RAM[1];  
    // int conta = var_aux2;
    Subtracao(m, primeiro_valor, segundo_valor); // n - p
    var_aux3 = m -> RAM[1];
    //printf("%d", var_aux3);
    Permutacao_Simples(m, var_aux3); // (n - p) !
    var_aux4 = m -> RAM[1];
    //printf("\n%d\n", var_aux4);
    Multiplicacao(m, var_aux2, var_aux4); // p! * (n - p) !
    var_aux5 = m -> RAM[1];
    //printf("\n%d\n", var_aux5);
   
    Divisao(m, var_aux, var_aux5 ); // n! /  p! * (n - p) ! 
    var_aux6 = m -> RAM[0];

    printf(" Você digitou %d como número de elementos e %d como número natural e a sua combinação é %d\n",primeiro_valor, segundo_valor, var_aux6);

}

void Arranjo(Memoria* m, int primeiro_valor, int segundo_valor){

    int var_aux;
    int var_aux2;
    int var_aux3;
    int var_aux4;
    int var_aux5;
   
    Permutacao_Simples(m, primeiro_valor); // n!
    var_aux = m -> RAM[1];
    // int conta2 = var_aux;
    //printf("%d", var_aux);
   
    Subtracao(m, primeiro_valor, segundo_valor); // n - p
    var_aux3 = m -> RAM[1];
    //printf("%d", var_aux3);
    Permutacao_Simples(m, var_aux3); // (n - p) !
    var_aux4 = m -> RAM[1];
    //printf("\n%d\n", var_aux4);
   
    Divisao(m, var_aux, var_aux4 ); // n! /  (n - p) ! 
    var_aux5 = m -> RAM[0];

    printf(" Você digitou %d como número de elementos e %d como número natural e a sua combinação é %d\n",primeiro_valor, segundo_valor, var_aux5);
}

void PG(Memoria* m, int termo, int termo1, int razao){
    
    int var_aux;
    int var_aux2;

    Subtracao(m, termo, 1);
    var_aux = m -> RAM[1];

    Potencia(m, razao, var_aux);
    var_aux2 = m -> RAM[1];

    Multiplicacao(m, termo1, var_aux);
}

void Fibonacci(Memoria* m, int primeiro_valor){

    int f1 = 0;
    int f2 = 1;
    int soma;

    if (primeiro_valor < 0){
        printf(" Valor Inválido");
        
    }else if (primeiro_valor == 0){
        printf(" 0 \n");
    }else{
        printf(" 0 - 1");

        while(f2 < primeiro_valor){
            Adicao(m, f1, f2);
            soma = m -> RAM [1];
            printf(" - %d", soma);
            f1 = f2;
            f2 = soma;
        }
        printf("\n");
    }
}

//física
void Distancia_Percorrida(Memoria* m, int primeiro_valor, int segundo_valor){

    Multiplicacao(m,  primeiro_valor, segundo_valor);
}

void Velocidade_Media(Memoria* m, int primeiro_distancia, int segundo_distancia, int primeiro_tempo, int segundo_tempo){
    
    int var_aux;
    int var_aux2;

    Subtracao(m, primeiro_distancia, segundo_distancia);
    var_aux = m-> RAM[1];

    Subtracao(m, primeiro_tempo, segundo_tempo);
    var_aux2 = m-> RAM[1];

    Divisao(m, var_aux, var_aux2);
}

void Aceleracao(Memoria* m, int primeiro_velocidade, int segundo_velocidade,int primeiro_tempo, int segundo_tempo){
     
    int var_aux;
    int var_aux2;
    int var_aux3;

    Subtracao(m, primeiro_velocidade, segundo_velocidade);
    var_aux = m-> RAM[1];

    Subtracao(m, primeiro_tempo, segundo_tempo);
    var_aux2 = m-> RAM[1];

    Divisao(m, var_aux, var_aux2);
    var_aux3 = m->RAM[0];
}

void Volume_Cubo(Memoria* m, int primeiro_valor){
    
    int potencia_cubo = 3;
    Potencia(m, primeiro_valor, potencia_cubo);
}

void Volume_Piramide(Memoria* m, int primeiro_valor, int segundo_valor){
   
    int var_aux;
    int var_aux2;
    int tres_positivo = 3;
    
    Multiplicacao(m, primeiro_valor, segundo_valor);
    var_aux = m -> RAM[1];

    Divisao(m, var_aux, tres_positivo);
    var_aux2 = m -> RAM[0];

    printf(" Você digitou %d como área da base e %d como altura, sendo %d seu resultado \n", primeiro_valor, segundo_valor, var_aux2);
}

void Forca(Memoria *m, int primeiro_valor, int segundo_valor){

    Multiplicacao(m, primeiro_valor, segundo_valor);
}

void Calorimetria(Memoria* m,  int primeiro_valor, int segundo_valor, int terceiro_valor){
      
    int var_aux;

    Multiplicacao(m, primeiro_valor, segundo_valor);
    var_aux = m -> RAM[1];

    Multiplicacao(m, var_aux, terceiro_valor);
}

void Efeito_Joule(Memoria* m,  int primeiro_valor, int segundo_valor, int terceiro_valor){

    int var_aux;
    int var_aux2;

    Potencia(m, primeiro_valor, 2);
    var_aux = m -> RAM[1];

    Multiplicacao(m, var_aux, segundo_valor);
    var_aux2 = m -> RAM[1];

    Multiplicacao(m, var_aux2, terceiro_valor);
}

//conversor de unidades//

//tempo
void Converter_Seg_Min(Memoria* m, int primeiro_valor){

   /* 60 segundos = 1 minuto;
    entao pega o valor digitado de divide por 60, o resultado vai ser isso
    */
   int sessenta_divisor = 60;

   Divisao(m, primeiro_valor, sessenta_divisor);

}

void Converter_Min_Seg(Memoria* m, int primeiro_valor){
        
   /* 60 segundos = 1 minuto;
    entao pega o valor digitado e multiplica por 60, o resultado vai ser isso
    */
   int multiplicador = 60;

   Multiplicacao(m, primeiro_valor, multiplicador);
}

void Converter_Min_Hora(Memoria* m, int primeiro_valor){
    
    int sessenta_divisor = 60;
    int var_aux;

    Divisao(m, primeiro_valor, sessenta_divisor);
    var_aux = m->RAM[0];
   
    printf(" Você digitou %d minutos e seu resultado em horas é: %d \n", primeiro_valor, var_aux);
}

void Converter_Hora_Min(Memoria* m, int primeiro_valor){
    
    int multiplicador = 60;

    Multiplicacao(m, primeiro_valor, multiplicador);
}

void Converter_Hora_Seg(Memoria* m, int primeiro_valor){

    int multiplicador = 3600;

    Multiplicacao(m, primeiro_valor, multiplicador);
}

//comprimento
void Converter_Cm_M(Memoria* m, int primeiro_valor){

   /* 100 centimetros = 1 metro;
    entao pega o valor digitado de divide por 100, o resultado vai ser isso
    */
   int divisor = 100;

   Divisao(m, primeiro_valor, divisor);
}

void Converter_M_Cm(Memoria* m, int primeiro_valor){
    
    int multiplicador = 100;

    Multiplicacao(m, primeiro_valor, multiplicador);
}

void Converter_M_Km(Memoria* m, int primeiro_valor){

    int divisor = 1000;
    int var_aux;

    Divisao(m, primeiro_valor, divisor);
    var_aux = m->RAM[0];
   
    printf(" Você digitou %d metros e seu resultado em quilômetros é: %d \n", primeiro_valor, var_aux);
}

void Converter_Km_M(Memoria* m, int primeiro_valor){

    int multiplicador = 1000;

    Multiplicacao(m, primeiro_valor, multiplicador);
}

void Converter_Km_Cm(Memoria* m, int primeiro_valor){

    int multiplicador = 1000;
    int multiplicador2 = 100;
    int var_aux;
    int var_aux2;

    Multiplicacao(m, primeiro_valor, multiplicador);
    var_aux = m->RAM[1];
    Multiplicacao(m, var_aux, multiplicador2);
    var_aux2 = m->RAM[1];
    printf(" Você digitou %d quilômetros e seu resultado em centímetros é: %d \n", primeiro_valor, var_aux2);
}

//temperatura
void Kelvin_Celsius(Memoria* m, int primeiro_valor){

    int valor = 273;

    Subtracao(m, primeiro_valor, valor);
}

void Celsius_Kelvin(Memoria* m, int primeiro_valor){

    int valor = 273;

    Adicao(m, primeiro_valor, valor);
}
