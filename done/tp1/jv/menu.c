#include"define.h"
#include "funcoes.h"
#include <stdio.h>

void Menu(Memoria* m){

    int valor_menu;   
    int valor04;
    int valor05;
    int operacao;   

     do{
        printf("\n Olá, seja bem vindo(a)! E aí, vamos calcular?\n");
        printf("\n     MENU DE OPÇÕES \n ---------------------- \t \n");
        printf("\n -1 -> Sair \t 0 -> Operações Básicas \t 1 -> Matemática Aplicada \t 2 -> Física \t 3 -> Conversor de Unidades de Medidas \n");
        printf("\n Digite a opção desejada: \t");
        scanf("%d", &valor_menu);
        getchar();
        if(valor_menu < -1 || valor_menu >3){
            printf(" \n Você digitou uma opção inválida, digite novamente! \n");
            Menu(m);
        }
    } while (valor_menu < -1 || valor_menu >3);

    switch (valor_menu) {

        case -1:
            if(valor_menu == -1){
                printf("\nVocê saiu!\n\n");
                printf("Programa encerrado!\n\n");
                break;
            }
        break;

        case 0:   
            Submenu_Mat_Basica(m);
        break;
        
        case 1:
            Submenu_Mat_Aplicada(m);
        break;
        
        case 2:
            Submenu_Fisica(m);
        break;
        
        case 3:
            Submenu_Conversor_Unidade(m);
        break;
    }
}
              
void Submenu_Mat_Basica(Memoria* m){
    
    int valor01;
    int valor02;
    int valor03;
    int* var_salvar;
    int valor_operacao;

    do{
        printf("\n -1: Voltar \t 0: Adição \t 1: Subtração \t 2: Multiplicação \t 3: Divisão \n");
        printf("\n Digite a opção desejada: \t");
        scanf("%d", &valor_operacao);
        getchar();
        if(valor_operacao < -1 || valor_operacao >3){
            printf(" \n Você digitou uma opção inválida, digite novamente! \n");
            Submenu_Mat_Basica(m);
        }
    }while (valor_operacao < -1 || valor_operacao >3);
 
        switch (valor_operacao) { 
            case -1:
                if(valor_operacao == -1){
                    printf("\n Você saiu!\n\n");
                    int op;
                    printf(" Digite 1 caso queira fazer outro tipo de operação. Caso não queira, digite 0: \t");
                    scanf("%d", &op);
                    if(op==1){
                        Menu(m);
                    }else{
                        printf("\n Programa encerrado!\n\n");
                        break;
                    }
                }
            break;

            case 0:
                printf(" Digite o primeiro valor: \t");
                scanf("%d", &valor01);
                printf(" Digite o segundo valor:  \t");
                scanf("%d", &valor02);
                Adicao(m, valor01, valor02);
                var_salvar = RetornarRAM(m);
                printf(" Aqui está o resultado da soma de %d + %d é: %d\t\n\n", valor01, valor02, var_salvar[1]);
                Submenu_Mat_Basica(m);
            break;

            case 1 :
                printf(" Digite o primeiro valor:  \t");
                scanf("%d", &valor01);
                printf(" Digite o segundo valor:  \t");
                scanf("%d", &valor02);   
                Subtracao(m, valor01, valor02);
                var_salvar = RetornarRAM(m);
                printf(" Aqui está o resultado da subtração de %d - %d é: %d\t\n\n", valor01, valor02, var_salvar[1]);   
                Submenu_Mat_Basica(m);
            break;

            case 2:
                printf(" Digite o primeiro valor:  \t");
                scanf("%d", &valor01);
                printf(" Digite o segundo valor:  \t");
                scanf("%d", &valor02);     
                Multiplicacao(m, valor01, valor02);  
                var_salvar = RetornarRAM(m);
                printf(" Aqui está o resultado da multiplicação de %d * %d é: %d\t\n\n", valor01, valor02, var_salvar[1]);
                Submenu_Mat_Basica(m);   
            break;

            case 3:
                printf(" Digite o primeiro valor:  \t");
                scanf("%d", &valor01);
                printf(" Digite o segundo valor:  \t");
                scanf("%d", &valor02);   
                Divisao(m, valor01, valor02);
                var_salvar = RetornarRAM(m);
                printf(" Aqui está o resultado da multiplicação de %d / %d é: %d\t\n\n", valor01, valor02, var_salvar[0]);
                Submenu_Mat_Basica(m);       
            break;
        }
}

void Submenu_Mat_Aplicada(Memoria*m){
    
    int valor01;
    int valor02;
    int valor03;
    int* var_salvar;
    int valor_operacao;

    do{
        printf("\n -1: Voltar       0: Delta       1: IMC       2: Potencia       3:Porcentagem       4: PA \n");
        printf("\n 5: Área do Triângulo            6: Área do Quadrado            7: Área do Retângulo \n");
        printf("\n 8: Perímetro do Quadrado        9: Perímetro do Retângulo      10: Soma dos Quadrados \n");
        printf("\n 11: Permutação Simples          12: Combinação                 13: Arranjo\n");
        printf("\n 14: Fatorial                    15: Sequência de Fibonacci         \n");
        printf("\n Digite a opção desejada: \t");
        scanf("%d", &valor_operacao);
        getchar();
        if(valor_operacao < -1 || valor_operacao >15){
            printf(" \n Você digitou uma opção inválida, digite novamente! \n");
            Submenu_Mat_Aplicada(m);
        }
    }while (valor_operacao < -1 || valor_operacao >15);
 
        switch (valor_operacao) { 
            case -1:
                if(valor_operacao == -1){
                    printf("\n Você saiu!\n\n");
                    int op;
                    printf(" Digite 1 caso queira fazer outro tipo de operação. Caso não queira, digite 0: \t");
                    scanf("%d", &op);
                    if(op==1){
                        Menu(m);
                    }else{
                        printf("\n Programa encerrado!\n\n");
                        break;
                    }
                }
            break;

            case 0:
                printf(" Digite o valor de a:  \t");
                scanf("%d", &valor01);
                printf(" Digite o valor de b:  \t");
                scanf("%d", &valor02); 
                printf(" Digite o valor de c:  \t");
                scanf("%d", &valor03);   
                Delta(m, valor01, valor02, valor03); 
                var_salvar = RetornarRAM(m);           
                Submenu_Mat_Aplicada(m);
            break;

            case 1 :
                printf(" Digite o peso:  \t");
                scanf("%d", &valor01);
                printf(" Digite a altura:  \t");
                scanf("%d", &valor02);    
                IMC(m, valor01, valor02); 
                var_salvar = RetornarRAM(m);    
                printf(" Você inseriu o peso = %d e altura = %d, o resultado da operação é: %d\t\n\n", valor01, valor02,  var_salvar[0]);
                Submenu_Mat_Aplicada(m);
            break;

            case 2:
                printf(" Digite um número:  \t");
                scanf("%d", &valor01);
                printf(" Digite a potência:  \t");
                scanf("%d", &valor02);    
                Potencia(m, valor01, valor02); 
                var_salvar = RetornarRAM(m);
                printf(" Você inseriu o número %d e o elevou a %d potência, sendo %d o resultado da operação.\t\n\n", valor01, valor02,  var_salvar[1]);     
                Submenu_Mat_Aplicada(m);
            break;

            case 3:
                printf(" Digite o valor:  \t");
                scanf("%d", &valor01);
                printf(" Digite o valor a porcentagem:  \t");
                scanf("%d", &valor02);   
                Porcentagem(m, valor01, valor02); 
                var_salvar = RetornarRAM(m);    
                Submenu_Mat_Aplicada(m);      
            break;

            case 4:
                printf(" Digite o valor do primeiro termo:  \t");
                scanf("%d", &valor01);
                printf(" Digite o valor a razao:  \t");
                scanf("%d", &valor02);
                printf(" Digite a quantidade de termos:  \t");
                scanf("%d", &valor03);   
                PA(m, valor01, valor02, valor03); 
                Submenu_Mat_Aplicada(m);      
            break;
            
            case 5:
                printf(" Digite a base:  \t");
                scanf("%d", &valor01);
                printf(" Digite a altura:  \t");
                scanf("%d", &valor02);    
                Area_Triangulo(m, valor01, valor02); 
                var_salvar = RetornarRAM(m);    
                printf(" Você inseriu a base = %d e altura = %d, o resultado da operação é: %d\t\n\n", valor01, valor02,  var_salvar[0]);
                Submenu_Mat_Aplicada(m); 
            break;

            case 6:
                printf(" Digite o valor de um lado do quadrado:  \t");
                scanf("%d", &valor01);  
                Area_Quadrado(m, valor01); 
                var_salvar = RetornarRAM(m);    
                printf(" Você inseriu o lado = %d e o resultado da operação é: %d\t\n\n", valor01, var_salvar[1]);
                Submenu_Mat_Aplicada(m);      
            break;
            
            case 7:
                printf(" Digite a base:  \t");
                scanf("%d", &valor01);
                printf(" Digite a altura:  \t");
                scanf("%d", &valor02);    
                Area_Retangulo(m, valor01, valor02); 
                var_salvar = RetornarRAM(m);     
                printf(" Você inseriu a base = %d e altura = %d, o resultado da operação é: %d\t\n\n", valor01, valor02,  var_salvar[1]);
                Submenu_Mat_Aplicada(m);      
            break;

            case 8:
                printf(" Digite o valor de um dos lados do quadrado:  \t");
                scanf("%d", &valor01);
                Perimetro_Quadrado(m, valor01); 
                var_salvar = RetornarRAM(m);  
                Submenu_Mat_Aplicada(m);      
            break;

            case 9:
                printf(" Digite o valor da base:  \t");
                scanf("%d", &valor01);
                printf(" Digite o valor da altura:  \t");
                scanf("%d", &valor02);
                Perimetro_Retangulo(m, valor01, valor02); 
                var_salvar = RetornarRAM(m);    
                Submenu_Mat_Aplicada(m);      
            break;

            case 10:
                printf(" Digite o primeiro valor:  \t");
                scanf("%d", &valor01);
                printf(" Digite o segundo valor:  \t");
                scanf("%d", &valor02);
                Soma_Quadrados(m, valor01, valor02); 
                var_salvar = RetornarRAM(m);    
                Submenu_Mat_Aplicada(m);      
            break;

            case 11:
                printf(" Digite o valor:  \t");
                scanf("%d", &valor01);
                Permutacao_Simples(m, valor01); 
                var_salvar = RetornarRAM(m); 
                printf(" A Permutação de %d é %d\n", valor01, var_salvar[1]);     
                Submenu_Mat_Aplicada(m);      
            break;

            case 12:
                printf(" Digite o número de elementos:  \t");
                scanf("%d", &valor01);
                printf(" Digite o elemento natural qualquer:  \t");
                scanf("%d", &valor02);    
                Combinacao(m, valor01, valor02); 
                var_salvar = RetornarRAM(m);    
                //printf("\n cu %d", var_salvar[1]);
              //  printf(" Você inseriu o peso = %d e altura = %d, o resultado da operação é: %d\t\n\n", valor01, valor02,  var_salvar[0]);
                Submenu_Mat_Aplicada(m);
            break;

            case 13:
                printf(" Digite o numero de elementos totais:  \t");
                scanf("%d", &valor01);
                printf(" Digite o numero de elemento do grupo:  \t");
                scanf("%d", &valor02);    
                Arranjo(m, valor01, valor02); 
                var_salvar = RetornarRAM(m);    
                Submenu_Mat_Aplicada(m);
            break;

            case 14:
                printf(" Digite o valor:  \t");
                scanf("%d", &valor01);
                Fatorial(m, valor01); 
                var_salvar = RetornarRAM(m); 
                printf(" O fatorial de %d é %d\n", valor01, var_salvar[1]);     
                Submenu_Mat_Aplicada(m);      
            break;    

            case 15:
                printf(" Digite o último elemento da sequência:  \t");
                scanf("%d", &valor01);  
                Fibonacci(m, valor01); 
                var_salvar = RetornarRAM(m);    
                Submenu_Mat_Aplicada(m);      
            break;  
        }
}

void Submenu_Fisica(Memoria* m){

    int valor01;
    int valor02;
    int valor03;
    int valor04;
    int valor05;
    int* var_salvar;
    int valor_operacao;

    do{
        printf("\n -1: Voltar       0: Volume do Paralelepipedo       1: Distância Percorrida       2: Velocidade Média \n");
        printf("\n 3: Aceleração    4: Volume do Cubo                 5: Volume da Pirâmide         6: Força           \n");
        printf("\n 7: Calorimetria  8: Efeito Joule  \n");
       
        printf("\n Digite a opção desejada: \t");
        scanf("%d", &valor_operacao);
        getchar();
        if(valor_operacao < -1 || valor_operacao >8){
            printf(" \n Você digitou uma opção inválida, digite novamente! \n");
            Submenu_Fisica(m);
        }
    }while (valor_operacao < -1 || valor_operacao >8);
 
        switch (valor_operacao) { 
            case -1:
                if(valor_operacao == -1){
                    printf("\nVocê saiu!\n\n");
                    int op;
                    printf("Digite 1 caso queira fazer outro tipo de operação. Caso não queira, digite 0: \t");
                    scanf("%d", &op);
                    if(op==1){
                        Menu(m);
                    }else{
                        printf("\nPrograma encerrado!\n\n");
                        break;
                    }
                }
            break;

            case 0:
                printf("Digite o comprimento:  \t");
                scanf("%d", &valor01);
                printf("Digite a altura:  \t");
                scanf("%d", &valor02); 
                printf("Digite a largura:  \t");
                scanf("%d", &valor03);   
                Volume_Paralelepipedo(m, valor01, valor02, valor03); 
                var_salvar = RetornarRAM(m);     
                printf("Você inseriu comprimento = %d, a altura %d e largura = %d, o resultado da operação é: %d\t\n\n", valor01, valor02, valor03, var_salvar[1]);
                Submenu_Fisica(m); 
            break;

            case 1:
                printf(" Digite o valor da velocidade em metros:  \t");
                scanf("%d", &valor01); 
                printf(" Digite o valor do tempo em segundos:  \t");
                scanf("%d", &valor02);  
                Distancia_Percorrida(m, valor01, valor02); 
                var_salvar = RetornarRAM(m);     
                printf(" Você inseriu %d como velocidade e %d como tempo, o resultado da operação é: %d\t\n\n", valor01, valor02, var_salvar[1]);
                Submenu_Fisica(m);             
            break;

            case 2:
                printf(" Digite a distância final:  \t");
                scanf("%d", &valor01);
                printf(" Digite a distância inicial:  \t");
                scanf("%d", &valor02);    
                printf(" Digite o tempo final:  \t");
                scanf("%d", &valor04);
                printf(" Digite o tempo inicial:  \t");
                scanf("%d", &valor05);    
                Velocidade_Media(m, valor01, valor02, valor04, valor05); 
                var_salvar = RetornarRAM(m);      
                printf(" Você inseriu %d como distância final, %d como distância inicial e inseriu %d como tempo final e %d como tempo inicial, sendo esse o resultado da operação: %d\t\n\n", valor01, valor02, valor04, valor05,  var_salvar[0]);
                Submenu_Fisica(m);              
            break;

            case 3:
                printf(" Digite a velocidade final:  \t");
                scanf("%d", &valor01);
                printf(" Digite a velocidade inicial:  \t");
                scanf("%d", &valor02);    
                printf(" Digite o tempo final:  \t");
                scanf("%d", &valor04);
                printf(" Digite o tempo inicial:  \t");
                scanf("%d", &valor05);    
                Aceleracao(m, valor01, valor02, valor04, valor05); 
                var_salvar = RetornarRAM(m);      
                printf(" Você inseriu %d como velocidade final, %d como velocidade inicial e inseriu %d como tempo final e %d como tempo inicial, sendo esse o resultado da operação: %d\t\n\n", valor01, valor02, valor04, valor05,  var_salvar[0]);
                Submenu_Fisica(m);              
            break;

            case 4:
                printf(" Digite o valor da aresta:  \t");
                scanf("%d", &valor01);  
                Volume_Cubo(m, valor01); 
                var_salvar = RetornarRAM(m);     
                printf(" Você inseriu a aresta = %d e o resultado da operação é: %d\t\n\n", valor01, var_salvar[1]);
                Submenu_Fisica(m);             
            break;

            case 5:
                printf(" Digite o valor da base:  \t");
                scanf("%d", &valor01);
                printf(" Digite o valor da altura:  \t");
                scanf("%d", &valor02);
                Volume_Piramide(m, valor01, valor02); 
                var_salvar = RetornarRAM(m);    
                Submenu_Fisica(m);      
            break;
            
            case 6:
                printf(" Digite o valor da massa:  \t");
                scanf("%d", &valor01);
                printf(" Digite o valor da aceleração:  \t");
                scanf("%d", &valor02);
                Forca(m, valor01, valor02); 
                var_salvar = RetornarRAM(m);
                printf(" Você inseriu a massa = %d, a aceleração = %d e o resultado da operação é: %d\t\n\n", valor01, valor02, var_salvar[1]);    
                Submenu_Fisica(m);      
            break;

            case 7:
                printf(" Digite o valor da massa:  \t");
                scanf("%d", &valor01);
                printf(" Digite o calor específico:  \t");
                scanf("%d", &valor02);
                printf(" Digite a temperatura:  \t");
                scanf("%d", &valor03);
                Calorimetria(m, valor01, valor02, valor03); 
                var_salvar = RetornarRAM(m);
                printf(" Você inseriu a massa = %d, o calor específica = %d, a temperatura = %d e o resultado da operação é: %d\t\n\n", valor01, valor02, valor03, var_salvar[1]);    
                Submenu_Fisica(m);      
            break;
            
            case 8:
                printf(" Digite o valor da corrente elétrica:  \t");
                scanf("%d", &valor01);
                printf(" Digite resistência elétrica:  \t");
                scanf("%d", &valor02);
                printf(" Digite o intervalo de tempo:  \t");
                scanf("%d", &valor03);
                Efeito_Joule(m, valor01, valor02, valor03); 
                var_salvar = RetornarRAM(m);
                printf(" Você inseriu a corrente elétrica = %d, a resistência elétrica = %d, o intervalo de tempo = %d e a quantidade de calor dissipada é: %d\t\n\n", valor01, valor02, valor03, var_salvar[1]);    
                Submenu_Fisica(m);      
            break;
        }
}

void Submenu_Conversor_Unidade(Memoria* m){
  
    int valor01;
    int valor02;
    int valor03;
    int* var_salvar;
    int valor_operacao;

    do{
        printf("\n-1: Voltar\n");
        printf("\n 0: Centimetro para Metro \t 1: Metro para Centímetro \t 2: Metro para Quilômetro \t 3: Quilômetro para Metro   4: Quilômetro para Centímetro \n");
        printf("\n 5: Segundo para Minuto \t 6: Minuto para Segundo \t 7: Minuto para Hora \t         8: Hora para Minuto \t     9: Hora para Segundo \n");
        printf("\n 10: Celsius para Kelvin \t 11: Kelvin para Celsius \t \n");
        printf("\n Digite a opção desejada: \t");
        scanf("%d", &valor_operacao);
        getchar();
        if(valor_operacao < -1 || valor_operacao >11){
            printf(" \n Você digitou uma opção inválida, digite novamente! \n");
            Submenu_Conversor_Unidade(m);
        }
    }while (valor_operacao < -1 || valor_operacao >11);
 
        switch (valor_operacao) { 
            case -1:
                if(valor_operacao == -1){
                    printf("\n Você saiu!\n\n");
                    int op;
                    printf(" Digite 1 caso queira fazer outro tipo de operação. Caso não queira, digite 0: \t");
                    scanf("%d", &op);
                    if(op==1){
                        Menu(m);
                    }else{
                        printf("\n Programa encerrado!\n\n");
                        break;
                    }
                }
            break;

            case 0:
                printf(" Digite a quantidade de centímetros:  \t");
                scanf("%d", &valor01);  
                Converter_Cm_M(m, valor01);
                var_salvar = RetornarRAM(m);
                printf(" Você digitou %d centímetros e seu resultado em metros é: %d \n", valor01, var_salvar[0]);
                Submenu_Conversor_Unidade(m);
            break;

            case 1 :
                printf(" Digite a quantidade de metros:  \t");
                scanf("%d", &valor01);  
                Converter_M_Cm(m, valor01);
                var_salvar = RetornarRAM(m);
                printf(" Você digitou %d metros e seu resultado em centímetros é: %d \n", valor01, var_salvar[1]);
                Submenu_Conversor_Unidade(m);
            break;

            case 2:
                printf(" Digite a quantidade de metros:  \t");
                scanf("%d", &valor01);  
                Converter_M_Km(m, valor01);
                var_salvar = RetornarRAM(m);
                Submenu_Conversor_Unidade(m); 
            break;

            case 3:
                printf(" Digite a quantidade de quilômetros:  \t");
                scanf("%d", &valor01);  
                Converter_Km_M(m, valor01);
                var_salvar = RetornarRAM(m);
                printf(" Você digitou %d metros e seu resultado em quilômetros é: %d \n", valor01, var_salvar[1]);
                Submenu_Conversor_Unidade(m); 
            break;

            case 4:
                printf(" Digite a quantidade de quilômetros:  \t");
                scanf("%d", &valor01);  
                Converter_Km_Cm(m, valor01);
                var_salvar = RetornarRAM(m);
                Submenu_Conversor_Unidade(m); 
            break;           

            case 5:
                printf(" Digite a quantidade de segundos:  \t");
                scanf("%d", &valor01);  
                Converter_Seg_Min(m, valor01);
                var_salvar = RetornarRAM(m);
                printf(" Você digitou %d segundos e seu resultado em minutos é: %d \n", valor01, var_salvar[0]);
                Submenu_Conversor_Unidade(m); 
            break;

            case 6:
                printf(" Digite a quantidade de minutos:  \t");
                scanf("%d", &valor01);  
                Converter_Min_Seg(m, valor01);
                var_salvar = RetornarRAM(m);
                printf(" Você digitou %d minutos e seu resultado em segundos é: %d \n", valor01, var_salvar[1]);
                Submenu_Conversor_Unidade(m); 
            break;

            case 7:
                printf(" Digite a quantidade de minutos:  \t");
                scanf("%d", &valor01);  
                Converter_Min_Hora(m, valor01);
                var_salvar = RetornarRAM(m);
                Submenu_Conversor_Unidade(m); 
            break;

            case 8:
                printf(" Digite a quantidade de horas:  \t");
                scanf("%d", &valor01);  
                Converter_Hora_Min(m, valor01);
                var_salvar = RetornarRAM(m);
                printf(" Você digitou %d horas e seu resultado em minutos é: %d \n", valor01, var_salvar[1]);
                Submenu_Conversor_Unidade(m); 
            break;
            
            case 9:
                printf(" Digite a quantidade de horas:  \t");
                scanf("%d", &valor01);  
                Converter_Hora_Seg(m, valor01);
                var_salvar = RetornarRAM(m);
                printf(" Você digitou %d horas e seu resultado em segundos é: %d \n", valor01, var_salvar[1]);
                Submenu_Conversor_Unidade(m); 
            break;

            case 10:
                printf(" Digite o valor de graus em Kelvin:  \t");
                scanf("%d", &valor01);  
                Celsius_Kelvin(m, valor01); 
                var_salvar = RetornarRAM(m);     
                printf(" Você inseriu %d graus em Celsius e isso equivale a %d graus em Kelvin \t\n\n", valor01, var_salvar[1]);
                Submenu_Conversor_Unidade(m); 
            break;

            case 11:
                printf(" Digite o valor de graus em Kelvin:  \t");
                scanf("%d", &valor01);  
                Kelvin_Celsius(m, valor01); 
                var_salvar = RetornarRAM(m);    
                printf(" Você inseriu %d graus em Kelvin e isso equivale a %d graus em Celsius \t\n\n", valor01, var_salvar[1]);
                Submenu_Conversor_Unidade(m); 
            break;
        }
}

