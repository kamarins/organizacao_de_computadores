#include "define.h"
#include "instrucoes.h"
#include <stdio.h>

struct memoria{
    int memoriaDados[tamanho];
    int memoriaInstrucoes[100][4]; //programa que seja interpretado

};

void menu(Memoria *memoria){

    int entrada;

    do {
        printf(" \n Bem vindo! Escolha a operacao que deseja efetuar: \n");
        printf("\n  _________________________________");
        printf(" \n |         MENU DE OPCOES         |");
        printf(" \n |-1 -> Sair                      |");
        printf(" \n | 0 -> Matematica Basica         |");
        printf(" \n | 1 -> Matematica Avancada       |");
        printf(" \n | 2 -> Fisica                    |");
        printf(" \n | 3 -> Conversor de medidas      |");
         printf("\n |________________________________|");
        printf(" \n Digite a operacao que deseja: ");
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
        
    int resultado;
        

    do{ 
        printf("\n ______________________________________________________________________________________");
        printf("\n |                     Para Matematica Basica temos as seguintes operações:            |");
        printf("\n |-1: Voltar      0: Adição      1: Subtracao       2: Multiplicacao    3: Divisao     |");
        printf("\n |_____________________________________________________________________________________|");
        printf("\n Digite a opção desejada: ");
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
                printf(" Digite 1 caso queira fazer outro tipo de operação. Caso não queira, digite 0: ");
                scanf("%d", &aux);
                getchar();
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
            printf("\n Gentileza, digitar o primeiro valor: ");
            scanf("%d", &n1);
            printf("\n Gentileza, digitar o segundo valor: ");
            scanf("%d", &n2);

            adicao(memoria, n1, n2);
            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 2; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1];
            
            printf("\n\n\tSomando %d com %d obtém-se %d\t\n\n", n1, n2, resultado);
            matBasica(memoria);
            break;

        case 1 : //subtracao
            printf("\n\t**VOCE SELECIONOU A OPCAO SUBTRACAO**\n\t ");
            printf("\n Gentileza, digitar o primeiro valor: ");
            scanf("%d", &n1);
            printf("\n Gentileza, digitar o segundo valor: ");
            scanf("%d", &n2);

            subtracao(memoria, n1, n2);
            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 2; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1];

            printf("\n\n\tSubtraindo %d de %d obtém-se %d\t\n\n", n2, n1, resultado);
            matBasica(memoria);
            break;

        case 2: //multiplicacao
            printf("\n\t**VOCE SELECIONOU A OPCAO MULTIPLICACAO**\n\t ");
            printf("\n Gentileza, digitar o primeiro valor: ");
            scanf("%d", &n1);
            printf("\n Gentileza, digitar o segundo valor: ");
            scanf("%d", &n2);
            
            multiplicacao(memoria, n1, n2);

            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 1; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1];
            
            printf("\n\n\tMultiplicando %d com %d obtém-se %d\t\n\n", n1, n2, resultado);
            matBasica(memoria);  
            break;

        case 3: //divisao
            printf("\n\t**VOCE SELECIONOU A OPCAO DIVISAO**\n\t ");
            printf("\n Gentileza, digitar o primeiro valor: ");
            scanf("%d", &n1);
            printf("\n Gentileza, digitar o segundo valor: ");
            scanf("%d", &n2);

            divisao(memoria, n1, n2);
            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 3; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1];

            printf("\n\n\tDividindo %d por %d obtém-se %d\t\n\n", n1, n2, resultado);
            matBasica(memoria);          
            break;
    }
}

void matAvanc(Memoria* memoria){
    
    int n1,
        n2, 
        n3;
    int opcao;
    int resultado;

    do{
        printf("\n ________________________________________________________________________________________________________");
        printf("\n |                        Para Matematica Avançada temos as seguintes operações:                         |");
        printf("\n |-1: Voltar                                                                                             |");     
        printf("\n |0:Potencia               1: Porcentagem              2: Delta                 3: Vol. Paralelelepipedo |");
        printf("\n |4: Vol. Cilindro         5: Vol. Esfera              6: Vol. Cubo             7: Vol. Piramide         |");
        printf("\n |8: Area Triangulo        9: Area Quadrado            10: Per. Quadrado        11: Per. Retangulo       |");
        printf("\n |12: PA                   13: Fatorial                14: Permutação Simples   15: Arranjo              |");
        printf("\n |16: Finonnaci            17: IMC                                                                       |");
        printf("\n |_______________________________________________________________________________________________________|\n");
        
        printf("\n Digite a opção desejada: ");
        scanf("%d", &opcao);
        getchar();

        if(opcao < -1 || opcao > 17){
            printf(" \n Você digitou uma opção inválida, digite novamente! \n");
            matAvanc(memoria);
        }
    }while (opcao< -1 || opcao > 17);
 
    switch (opcao) { 
        case -1:
            if(opcao == -1){
                printf("\n Você saiu!\n\n");
                int aux;
                printf(" Digite 1 caso queira fazer outro tipo de operação. Caso não queira, digite 0: ");
                scanf("%d", &aux);
                if(aux==1){
                    menu(memoria);
                }else{
                    printf("\n Programa encerrado!\n\n");
                    break;
                }
            }
            break;

        case 0:
            printf(" Digite um número: ");
            scanf("%d", &n1);
            printf(" Digite a potência: ");
            scanf("%d", &n2);    
            
            potencia(memoria, n1, n2); 
            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 1; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1];

            printf(" Você inseriu o número %d e o elevou a %d potência, sendo %d o resultado da operação.\t\n\n", n1, n2, resultado);     
            matAvanc(memoria);
            break;

        case 1:
            printf(" Digite o valor: ");
            scanf("%d", &n1);
            printf(" Digite o valor da porcentagem:  \t");
            scanf("%d", &n2);   
            porcentagem(memoria, n1, n2);  

            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 2; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1];

            printf(" Portanto, obteve como resposta: %d", resultado);
            matAvanc(memoria);      
            break;

        case 2:
            printf(" Digite o valor de a: ");
            scanf("%d", &n1);
            printf(" Digite o valor de b: ");
            scanf("%d", &n2); 
            printf(" Digite o valor de c: ");
            scanf("%d", &n3); 

            delta(memoria, n1, n2, n3); 
            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 2; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1];

            printf("\n\tDelta = %d\n\t", resultado);     
            matAvanc(memoria);
            break;

        case 3:
            printf("Digite o comprimento:  ");
            scanf("%d", &n1);
            printf("Digite a altura:  ");
            scanf("%d", &n2); 
            printf("Digite a largura: ");
            scanf("%d", &n3);  

            volumeParalelepipedo(memoria, n1, n2, n3); 
            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 1; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1];
    
            printf("Você inseriu comprimento = %d, a altura %d e largura = %d, o resultado da operação é: %d\t\n\n", n1, n2,n3, resultado);
            matAvanc(memoria); 
            break;
        
        case 4:
            printf(" \nDigite o valor da area da base: ");
            scanf("%d", &n1);
            printf("\n Digite o valor da altura ");
            scanf("%d", &n2);

            volumeCilindro(memoria,n1,n2);
            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 1; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1];

            printf("\n Voce digitou %d como area da base e %d como altura. Portanto, obteve como %d u.v.\n", n1,n2,resultado);
            matAvanc(memoria);      
            break;
        
        case 5:
            printf("\n Digite o valor do raio:  ");
            scanf("%d", &n1);
            volumeEsfera(memoria,n1);

            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 1; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1];

            printf("\n Voce digitou %d como raio da esfera e obteve %d u.v como volume.\n",n1, resultado);
            matAvanc(memoria);      
            break;

        case 6:
            printf("\n Digite o valor do lado:  ");
            scanf("%d", &n1);

            volumeCubo(memoria,n1);
            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 1; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1];

            printf("\n Voce digitou %d como lado do cubo e obteve %d u.v como volume.\n",n1, resultado);
            matAvanc(memoria);      
            break;

        case 7:
            printf("\n Digite o valor da area da base: ");
            scanf("%d", &n1);
            printf("\n Digite o valor da altura: ");
            scanf("%d", &n2);
            volumePiramide(memoria, n1,n2);
            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 3; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1];

            printf("\n Voce digitou %d como area da base e %d como altura, obtendo %d u.v como volume.\n",n1,n2,resultado);
            matAvanc(memoria);      
            break;

        case 8:
            printf("\n Digite a base: ");
            scanf("%d", &n1);
            printf("\n Digite a altura: ");
            scanf("%d", &n2);    

            areaTriangulo(memoria, n1, n2); 
            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 3; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1];  

            printf("\n Você inseriu a base = %d e altura = %d, o resultado da operação é: %d\t\n\n", n1, n2,  resultado);
            matAvanc(memoria); 
            break;

        case 9:
            printf("\n Digite o valor do lado do quadrado: ");
            scanf("%d", &n1);  

            areaQuadrado(memoria, n1); 
            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 1; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1];  

            printf("\n Você inseriu o lado = %d e o resultado da operação é: %d\t\n\n", n1, resultado);
            matAvanc(memoria);      
            break;

        case 10:
            printf("\n Digite o valor de um dos lados do quadrado:  ");
            scanf("%d", &n1);

            perimetroQuadrado(memoria, n1); 
            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 1; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1];

            printf(" \n Você inseriu o lado = %d e o resultado da operação é: %d\t\n\n", n1, resultado);
            matAvanc(memoria);      
            break;


        case 11:
            printf("\n Digite o valor da base:  \t");
            scanf("%d", &n1);
            printf("\n Digite o valor da altura:  \t");
            scanf("%d", &n2);

            perimetroRetangulo(memoria, n1, n2); 
            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 1; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1];

            printf(" Você inseriu o lado = %d e o lado = %d, logo o resultado da operação é: %d\t\n\n", n1, n2, resultado);
            matAvanc(memoria);      
            break;


        case 12:
            printf("\n Digite o valor do primeiro termo:  \t");
            scanf("%d", &n1);
            printf(" Digite o valor a razao:  \t");
            scanf("%d", &n2);
            printf(" Digite a quantidade de termos:  \t");
            scanf("%d", &n3);   

            PA(memoria, n1, n2, n3);  
            matAvanc(memoria);      
            break;
    
        case 13:
            printf(" Digite o valor:  \t");
            scanf("%d", &n1);
            fatorial(memoria, n1); 
            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 1; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1];
            
            printf(" O fatorial de %d é %d\n", n1, resultado);     
            matAvanc(memoria);      
            break; 

        case 14:
            printf(" Digite o valor:  \t");
            scanf("%d", &n1);
            permutacaoSimples(memoria, n1); 
            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 1; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1];

            printf(" A Permutação de %d é %d\n", n1, resultado);     
            matAvanc(memoria);      
            break;


        case 15:
            printf(" Digite o numero de elementos totais:  \t");
            scanf("%d", &n1);
            printf(" Digite o numero de elemento do grupo:  \t");
            scanf("%d", &n2);    

            arranjo(memoria, n1, n2); 
            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 3; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1];
            
            printf("\nO resultado do seu arranjo é: %d", resultado);
            matAvanc(memoria);   
            break;

        

        case 16:
            printf(" Digite o último elemento da sequência:  \t");
            scanf("%d", &n1);  
            fibonnaci(memoria, n1);   
            matAvanc(memoria);      
            break;  

        case 17:
            printf(" Digite o peso:  \t");
            scanf("%d", &n1);
            printf(" Digite a altura:  \t");
            scanf("%d", &n2);    

            IMC(memoria, n1, n2); 
            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 3; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1];   

            printf(" Você inseriu o peso = %d e altura = %d, o resultado da operação é: %d\t\n\n", n1, n2,  resultado);
            matAvanc(memoria);
            break;
    }
}

void fisica(Memoria* memoria){
     
    int n1,
        n2, 
        n3,
        n4;
        
    int opcao;
    int resultado;

    do{
         printf("\n ______________________________________________________________________________________________________________");
        printf("\n |                                   Para Fisica temos as seguintes operações:                                  |");
        printf("\n |-1: Voltar      0: Dist. Percorrida     1: Vel. Media       2: Aceleracao      3: Forca     4:Calorimetria    |");
        printf("\n |______________________________________________________________________________________________________________|");
        printf("\n  Digite a opção desejada: ");
        scanf("%d", &opcao); 
        getchar();

        if(opcao < -1 || opcao > 5){
            printf(" \n Você digitou uma opção inválida, digite novamente! \n");
            matAvanc(memoria);
        }
    }while (opcao< -1 || opcao > 5);


    switch (opcao) { 
        case -1:
            if(opcao == -1){
                printf("\nVocê saiu!\n\n");
                int op;
                printf("Digite 1 caso queira fazer outro tipo de operação. Caso não queira, digite 0: ");
                scanf("%d", &op);

                if(op==1){
                    menu(memoria);
                }else{
                    printf("\nPrograma encerrado!\n\n");
                    break;
                }
            }
        break;

        case 0:
         
            printf("\n Digite o valor da velocidade em metros:  ");
            scanf("%d", &n1); 
            printf("\n Digite o valor do tempo em segundos:  ");
            scanf("%d", &n2);  
    
            distanciaPercorrida(memoria,n1, n2); 
            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 1; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1];   

            printf(" Você inseriu %d como velocidade e %d como tempo, o resultado da operação é: %d\t\n\n",n1,n2,resultado);
            fisica(memoria);       
            break;

        case 1: 
          
            printf("\n Digite a distância final: ");
            scanf("%d", &n1);
            printf("\n Digite a distância inicial: ");
            scanf("%d", &n2);    
            printf("\n Digite o tempo final: ");
            scanf("%d", &n3);
            printf("n Digite o tempo inicial: ");
            scanf("%d", &n4);    

            velocidadeMedia(memoria, n1, n2,n3, n4); 

            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 3; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1]; 
                
            printf("\n Você inseriu %d como distância final, %d como distância inicial e inseriu %d como tempo final e %d como tempo inicial, sendo esse o resultado da operação: %d\t\n\n", n1, n2, n3,n4, resultado);
            fisica(memoria);         
            break;

        case 2:
            printf("\n Digite a velocidade final: ");
            scanf("%d", &n1);
            printf("\n Digite a velocidade inicial: ");
            scanf("%d", &n2);    
            printf("\n Digite o tempo final:  ");
            scanf("%d", &n3);
            printf("\n Digite o tempo inicial:  ");
            scanf("%d", &n4);    

            aceleracao(memoria, n1, n2, n3, n4); 
            
            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 3; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1]; 
            
              
            printf("\n Você inseriu %d como velocidade final, %d como velocidade inicial e inseriu %d como tempo final e %d como tempo inicial, sendo esse o resultado da operação: %d\n\n", n1, n2, n3, n4,  resultado);
            fisica(memoria);         
            break;

        case 3:
            printf("\n Digite o valor da massa:  ");
            scanf("%d", &n1);
            printf("\n Digite o valor da aceleração:  ");
            scanf("%d", &n2);

            forca(memoria, n1, n2); 
            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 1; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1]; 

            printf(" Você inseriu a massa = %d, a aceleração = %d e o resultado da operação é: %d\n\n", n1, n2, resultado);    
            fisica(memoria);   
            break;

        case 4:
            printf("\n Digite o valor da massa:  \t");
            scanf("%d", &n1);
            printf("\n Digite o calor específico:  \t");
            scanf("%d", &n2);
            printf("\n Digite a temperatura:  \t");
            scanf("%d", &n3);
            calorimetria(memoria, n1, n2, n3); 
            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 1; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1]; 

            printf(" Você inseriu a massa = %d, o calor específica = %d, a temperatura = %d e o resultado da operação é: %d\n\n", n1, n2, n3, resultado);    
            fisica(memoria);  
            break;
    }       



}

void convMedidas(Memoria* memoria){
     
    int n1;
    int opcao;
    int resultado;

    do{
        printf("\n _____________________________________________________________________________________________________________");
        printf("\n |                        Para Conversão de Medidas temos as seguintes operações:                             |");
        printf("\n |-1: Voltar                                                                                                  |");     
        printf("\n |0: Conv. Seg/Min           1: Conv. Min/Seg               2: Conv. Min/Hr          3: Conv Hr/min           |");
        printf("\n |4: Conv. Hr/Seg            5: Conv. Cm/M                  6: Conv Kelvin/Celsius                            |");
        printf("\n |7: Conv. Celsius/Kelvin    8: Conv. Celsius/Fahrenheit    9:Conv. Fahrenheit/Celsius                       |");
        printf("\n |____________________________________________________________________________________________________________|\n");
        
        printf("\n Digite a opção desejada: ");
        scanf("%d", &opcao);
        getchar();

        if(opcao < -1 || opcao > 9){
            printf(" \n Você digitou uma opção inválida, digite novamente! \n");
            convMedidas(memoria);
        }
    }while (opcao < -1 || opcao > 9);
 
    switch (opcao) { 
        case -1:
            if(opcao == -1){
                printf("\n Você saiu!\n\n");
                int aux;
                printf(" Digite 1 caso queira fazer outro tipo de operação. Caso não queira, digite 0: ");
                scanf("%d", &aux);
               

                if(aux==1){
                    menu(memoria);
                }else{
                    printf("\n Programa encerrado!\n\n");
                    break;
                }
            }
            break;

        case 0:
            printf("\n Digite a quantidade de segundos: ");
            scanf("%d", &n1); 
            convSegMin(memoria,n1);

            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 3; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1]; 

            printf("\n Você digitou %d minutos e seu resultado em segundos é: %d \n", n1, resultado);
            convMedidas(memoria);
           
            break;

        case 1:
            printf("\n Digite a quantidade de minutos: ");
            scanf("%d", &n1);  
            convMinSeg(memoria,n1);

            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 1; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1]; 

            printf("\n Você digitou %d minutos e seu resultado em segundos é: %d \n", n1, resultado);
            convMedidas(memoria);
            break;

        case 2:

            printf("\n Digite a quantidade de minutos:  ");
            scanf("%d", &n1);  
          
            convMinHr(memoria, n1);
            
            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 3; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1];

            printf("\n Você digitou %d minutos e seu resultado em horas é: %d \n", n1, resultado); 
            convMedidas(memoria);
            break;

        case 3:
           
            printf("\n Digite a quantidade de horas: ");
            scanf("%d", &n1); 
            
            convHrMin(memoria, n1);

            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 1; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1];
            
            printf("\n Você digitou %d horas e seu resultado em minutos é: %d \n", n1, resultado);
            convMedidas(memoria);; 
            break;

        case 4:
        
            printf("\n Digite a quantidade de horas:  ");
            scanf("%d", &n1); 
            
            convHrSeg(memoria, n1);

            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 1; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1];

            printf("\n Você digitou %d horas e seu resultado em segundos é: %d \n", n1, resultado);
            convMedidas(memoria); 
            break;

        case 5:
            printf("\n Digite a quantidade de centímetros:  ");
            scanf("%d", &n1); 
            convCm_M(memoria, n1);
            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 3; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1];

            
            printf("\n Você digitou %d centímetros e seu resultado em metros é: %d \n", n1, resultado);
            convMedidas(memoria);
            break;           

        case 6:
            printf("\n Digite o valor de graus em Kelvin:  ");
            scanf("%d", &n1); 
            
            KelvinCelsius(memoria, n1); 

            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 2; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1];
   
            printf("\n Você inseriu %d graus em Kelvin e isso equivale a %d graus em Celsius \n\n", n1, resultado);
            convMedidas(memoria);
            break;

        case 7:
            printf("\n Digite o valor de graus em Celsius:  ");
            scanf("%d", &n1);
              
            CelsiusKelvin(memoria, n1); 

            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 2; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1];
   
            printf("\n Você inseriu %d graus em Celsius e isso equivale a %d graus em Kelvin \n\n", n1, resultado);
            convMedidas(memoria); 
            break;

        case 8:
            printf("\n Digite o valor de graus em Celsius: ");
            scanf("%d", &n1); 
           
            CelsiusFahrenheit(memoria, n1); 

            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 2; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1];
   
            printf("\n Você inseriu %d graus em Celsius e isso equivale a %d graus em Fahreinht \n\n", n1, resultado);
            convMedidas(memoria);
            break;

        case 9:
            printf("\n Digite o valor de graus em Fahreinht: ");
            scanf("%d", &n1);  
            
            FahrenheitCelsius(memoria, n1); 

            memoria->memoriaInstrucoes[0][0] = opcodeTrazerMem;   
            memoria->memoriaInstrucoes[0][1] = -1; 
            memoria->memoriaInstrucoes[0][2] = 2; 
            memoria->memoriaInstrucoes[0][3] = opcodeSair;
        
            memoria->memoriaInstrucoes[1][0] = opcodeSair;    //Halt
            memoria->memoriaInstrucoes[1][1] = opcodeSair;
            memoria->memoriaInstrucoes[1][2] = opcodeSair;
            memoria->memoriaInstrucoes[1][3] = opcodeSair;

            maquina(memoria);
            resultado = memoria->memoriaInstrucoes[0][1];
   
            printf(" \nVocê inseriu %d graus em Celsius e isso equivale a %d graus em Fahreinht \n\n", n1, resultado);
            convMedidas(memoria);
            break;

    }

}