#include "define.h"
#include "instrucoes.h"
#include <stdio.h>

void menu(Memoria* memoria){

    int entrada;

    do {
        printf(" \n Bem vindo! Escolha a operacao que deseja efetuar: \n");
        printf(" \n MENU DE OPCOES \n ");
        printf(" \n -1 -> Sair \n");
        printf(" \n  0 -> Matematica Basica\n");
        printf(" \n  1 -> Matemarica Avancada \n");
        printf(" \n  2 -> Fisica \n");
        printf(" \n  3 -> Conversor de medidas \n");
        printf(" \n Digite a operacao que deseja:");
        scanf("%d", &entrada);
        getchar();

        if (entrada < -1 || entrada > 3){
            printf("\n Voce digitou uma opção inválida! Por favor, tente novamente!\n");
            menu(memoria);
        }
    }while (entrada < -1 || entrada > 3);




    switch(entrada){
        case 3:
            convMedidas(memoria);
            break;

        case 2:
            fisica(memoria);
            break;

        case 1:
            matAvanc(memoria);
            break;

        case 0:
            matBasica(memoria);
            break;
        
        case -1:
            printf("\nVoce saiu!\n");
            printf("\nPrograma encerrado\n");
            break;
    }

}

void matBasica(Memoria* memoria){
    int n1=0,
        n2=0,
        opcao=TMP_MAX;
        
    int* resultado= NULL;
        

    do{ 
        printf("\n \tTemos as seguintes operações: \n\t");
        printf("\n \t-1: Voltar \n\t 0: Adição \n\t 1: Subtracao \n\t 2: Multiplicacao \n\t 3: Divisao \n\n");
        printf("\n \t Digite a opção desejada: ");
        scanf("%d", &opcao);
        getchar();
        if(opcao< -1 || opcao >3){
            printf(" \n Você digitou uma opção inválida, digite novamente! \n");
            matBasica(memoria);
        }
    }while (opcao < -1 || opcao > 3);


    switch (opcao) { 
        case -1:
            if(opcao == -1){
                printf("\n Você saiu!\n\n");
                int aux;
                printf(" Digite 1 caso queira fazer outro tipo de operação. Caso não queira, digite 0: \t");
                scanf("%d", &aux);
                if(aux==1){
                    menu(memoria);
                }else{
                    printf("\n Programa encerrado!\n\n");
                    break;
                }
            }
        break;

        case 0: //adicao
            printf("\n\t**VOCE SELECIONOU A OPCAO ADICAO**\n\t ");
            printf("\n\tGentileza, digitar o primeiro valor: \t");
            scanf("%d", &n1);
            printf("\n\tGentileza, digitar o segundo valor: \t");
            scanf("%d", &n2);
            adicao(memoria, n1, n2);
            resultado = retornarRam(memoria);
            printf("\n\n\tSomando %d com %d obtém-se %d\t\n\n", n1, n2, resultado[2]);
            matBasica(memoria);
        break;

        case 1 : //subtracao
            printf("\n\t**VOCE SELECIONOU A OPCAO SUBTRACAO**\n\t ");
            printf("\n\t Gentileza, digitar o primeiro valor: \t");
            scanf("%d", &n1);
            printf("\n\t Gentileza, digitar o segundo valor: \t");
            scanf("%d", &n2);
            subtracao(memoria, n1, n2);
            resultado = retornarRam(memoria);
            printf("\n\n\tSubtraindo %d de %d obtém-se %d\t\n\n", n2, n1, resultado[2]);
            matBasica(memoria);
        break;

        case 2: //multiplicacao
            printf("\n\t**VOCE SELECIONOU A OPCAO MULTIPLICACAO**\n\t ");
            printf("\n\t Gentileza, digitar o primeiro valor: \t");
            scanf("%d", &n1);
            printf("\n\t Gentileza, digitar o segundo valor: \t");
            scanf("%d", &n2);
            multiplicacao(memoria, n1, n2);
            resultado = retornarRam(memoria);
            printf("\n\n\tMultiplicando %d com %d obtém-se %d\t\n\n", n1, n2, resultado[1]);
            matBasica(memoria);  
        break;

        case 3: //divisao
            printf("\n\t**VOCE SELECIONOU A OPCAO DIVISAO**\n\t ");
            printf("\n\t Gentileza, digitar o primeiro valor: \t");
            scanf("%d", &n1);
            printf("\n\t Gentileza, digitar o segundo valor: \t");
            scanf("%d", &n2);
            divisao(memoria, n1, n2);
            resultado = retornarRam(memoria);
            printf("\n\n\tDividindo %d por %d obtém-se %d\t\n\n", n1, n2, resultado[3]);
            matBasica(memoria);          
        break;
    }
}


void matAvanc(Memoria* memoria){
    
    int n1,
        n2, 
        n3;
    int opcao;
    int* resultado;

    do{
        printf("\n -1: Voltar       0: Delta       1: IMC       2: Potencia       3:Porcentagem       4: PA \n");
        printf("\n 5: Área do Triângulo            6: Área do Quadrado            7: Área do Retângulo \n");
        printf("\n 8: Perímetro do Quadrado        9: Perímetro do Retângulo      10: Soma dos Quadrados \n");
        printf("\n 11: Permutação Simples          12: Combinação                 13: Arranjo\n");
        printf("\n 14: Fatorial                    15: Sequência de Fibonacci         \n");
        printf("\n Digite a opção desejada: \t");
        scanf("%d", &opcao);
        getchar();
        if(opcao < -1 || opcao >15){
            printf(" \n Você digitou uma opção inválida, digite novamente! \n");
            matAvanc(memoria);
        }
    }while (opcao< -1 || opcao > 15);
 
        switch (opcao) { 
            case -1:
                if(opcao == -1){
                    printf("\n Você saiu!\n\n");
                    int aux;
                    printf(" Digite 1 caso queira fazer outro tipo de operação. Caso não queira, digite 0: \t");
                    scanf("%d", &op);
                    if(aux==1){
                        menu(memoria);
                    }else{
                        printf("\n Programa encerrado!\n\n");
                        break;
                    }
                }
            break;

            case 0:
                printf(" Digite o valor de a:  \t");
                scanf("%d", &n1);
                printf(" Digite o valor de b:  \t");
                scanf("%d", &n2); 
                printf(" Digite o valor de c:  \t");
                scanf("%d", &n3);   
                Delta(memoria, n1, n2, n3); 
                resultado= RetornarRAM(memoria);   
                printf("\n\tDelta = %d\n\t", resultado[1]);     
                matAvanc(memoria);
            break;

            case 1 :
                printf(" Digite o peso:  \t");
                scanf("%d", &n1);
                printf(" Digite a altura:  \t");
                scanf("%d", &n2);    
                IMC(memoria, n1, n2); 
                resultado= RetornarRAM(memoria);    
                printf(" Você inseriu o peso = %d e altura = %d, o resultado da operação é: %d\t\n\n", n1, n2,  resultado[3]);
                matAvanc(memoria);
            break;

            case 2:
                printf(" Digite um número:  \t");
                scanf("%d", &n1);
                printf(" Digite a potência:  \t");
                scanf("%d", &n2);    
                Potencia(memoria, n1, n2); 
                resultado= RetornarRAM(memoria);
                printf(" Você inseriu o número %d e o elevou a %d potência, sendo %d o resultado da operação.\t\n\n", n1, n2, resultado[1]);     
                matAvanc(memoria);
            break;

            case 3:
                printf(" Digite o valor:  \t");
                scanf("%d", &n1);
                printf(" Digite o valor a porcentagem:  \t");
                scanf("%d", &n2);   
                Porcentagem(m, n1, n2); 
                resultado= RetornarRAM(memoria);   
                printf("Portanto, obteve como resposta: %d", resultado[1]);
                matAvanc(memoria);      
            break;

            case 4:
                printf(" Digite o valor do primeiro termo:  \t");
                scanf("%d", &n1);
                printf(" Digite o valor a razao:  \t");
                scanf("%d", &n2);
                printf(" Digite a quantidade de termos:  \t");
                scanf("%d", &n3);   
                PA(m, n1, n2, n3); 
                matAvanc(memoria);      
            break;
            
            case 5:
                printf(" Digite a base:  \t");
                scanf("%d", &n1);
                printf(" Digite a altura:  \t");
                scanf("%d", &n2);    
                Area_Triangulo(m, n1, n2); 
                resultado= RetornarRAM(m);    
                printf(" Você inseriu a base = %d e altura = %d, o resultado da operação é: %d\t\n\n", n1, n2,  var_salvar[0]);
                matAvanc(memoria); 
            break;

            case 6:
                printf(" Digite o valor de um lado do quadrado:  \t");
                scanf("%d", &n1);  
                Area_Quadrado(m, n1); 
                resultado= RetornarRAM(m);    
                printf(" Você inseriu o lado = %d e o resultado da operação é: %d\t\n\n", n1, var_salvar[1]);
                matAvanc(memoria);      
            break;
            
            case 7:
                printf(" Digite a base:  \t");
                scanf("%d", &n1);
                printf(" Digite a altura:  \t");
                scanf("%d", &n2);    
                Area_Retangulo(m, n1, n2); 
                resultado= RetornarRAM(m);     
                printf(" Você inseriu a base = %d e altura = %d, o resultado da operação é: %d\t\n\n", n1, n2,  var_salvar[1]);
                matAvanc(memoria);      
            break;

            case 8:
                printf(" Digite o valor de um dos lados do quadrado:  \t");
                scanf("%d", &n1);
                Perimetro_Quadrado(m, n1); 
                resultado= RetornarRAM(m);  
                matAvanc(memoria);      
            break;

            case 9:
                printf(" Digite o valor da base:  \t");
                scanf("%d", &n1);
                printf(" Digite o valor da altura:  \t");
                scanf("%d", &n2);
                Perimetro_Retangulo(m, n1, n2); 
                resultado= RetornarRAM(m);    
                matAvanc(memoria);      
            break;

            case 10:
                printf(" Digite o primeiro valor:  \t");
                scanf("%d", &n1);
                printf(" Digite o segundo valor:  \t");
                scanf("%d", &n2);
                Soma_Quadrados(m, n1, n2); 
                resultado= RetornarRAM(m);    
                matAvanc(memoria);      
            break;

            case 11:
                printf(" Digite o valor:  \t");
                scanf("%d", &n1);
                Permutacao_Simples(m, n1); 
                resultado= RetornarRAM(m); 
                printf(" A Permutação de %d é %d\n", n1, var_salvar[1]);     
                matAvanc(memoria);      
            break;

            case 12:
                printf(" Digite o número de elementos:  \t");
                scanf("%d", &n1);
                printf(" Digite o elemento natural qualquer:  \t");
                scanf("%d", &n2);    
                Combinacao(m, n1, n2); 
                resultado= RetornarRAM(m);    
                //printf("\n cu %d", var_salvar[1]);
              //  printf(" Você inseriu o peso = %d e altura = %d, o resultado da operação é: %d\t\n\n", n1, n2,  var_salvar[0]);
                matAvanc(memoria);
            break;

            case 13:
                printf(" Digite o numero de elementos totais:  \t");
                scanf("%d", &n1);
                printf(" Digite o numero de elemento do grupo:  \t");
                scanf("%d", &n2);    
                Arranjo(m, n1, n2); 
                resultado= RetornarRAM(m);    
                matAvanc(memoria);
            break;

            case 14:
                printf(" Digite o valor:  \t");
                scanf("%d", &n1);
                Fatorial(m, n1); 
                resultado= RetornarRAM(m); 
                printf(" O fatorial de %d é %d\n", n1, var_salvar[1]);     
                matAvanc(memoria);      
            break;    

            case 15:
                printf(" Digite o último elemento da sequência:  \t");
                scanf("%d", &n1);  
                Fibonacci(m, n1); 
                resultado= RetornarRAM(m);    
                matAvanc(memoria);      
            break;  
        }
}

