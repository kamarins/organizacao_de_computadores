#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

void montarRAM(int* RAM){
    srand(time(NULL));
    for(int i=0; i<100; i++){           //Lembrando que 100 é o número de Memoria RAM's que teremos, se fosse necessário aumentar/diminuir basta alterar o 100
        RAM[i]= rand()%1000;
    }
}

void alocarmatrizdeinstrucoes(int*** matrizdeinstrucoes){
    *matrizdeinstrucoes= malloc(10*sizeof(int*));          //alocando dinamicamente 10 linhas para a matriz
    for(int i=0; i<10;i++){
        (*matrizdeinstrucoes)[i]=malloc(4*sizeof(int));          //um for para alocar as 4 colunas da matriz. Linha por Linha
    }
    
}

void montarInstrucoes(int** matrizdeinstrucoes){
    //00 => salvar na memória
	//01 => opcode => somar
	//02 => opcode => subtrair
    //03 => 
	//-1 => halt

    srand(time(NULL));

    int* instrucao;      //Aqui iremos criar uma instrução, essa instruções seram aleatórias, podendo realizar somas ou subtrações sequenciais
    for(int i=0; i<10; i++){
        instrucao = malloc(4*sizeof(int*));
        instrucao[0]= rand()%4;
        instrucao[1]= rand()%100;
        instrucao[2]= rand()%100;
        instrucao[3]= rand()%100;

        matrizdeinstrucoes[i]= instrucao;           //Aqui passamos para a nossa matriz as instruções que seram executadas na máquina
    }


    instrucao[0]= -1;
    instrucao[1]= -1;
    instrucao[2]= -1;
    instrucao[3]= -1;
    matrizdeinstrucoes[9]=instrucao;                 //Aqui iremos parar o nosso programa, pois a instrução -1 representa o Halt

    free(instrucao);
}

void maquinaInterpretada(int* instrucao, int* RAM){
    int opcode = instrucao[0];
    switch (opcode){
        case 0:{                                                    //Opcode 0 = Salvar na RAM
            RAM[instrucao[2]] = instrucao[1];                       //Salva na RAM[instrucao[2]] o que está no conteudo da instrucao[1]
            break;
        }

        case 1:{                                                    //Opcode 1 = Somar
            int soma=0;                                             //salva na RAM[instrucao[3]] a soma de RAM[instrucao[1]] + RAM[instrucao[2]]
            int end1= instrucao[1];
            int end2= instrucao[2];

            int conteuRAM1 = RAM[end1];
            int conteuRAM2 = RAM[end2];

            soma = conteuRAM1 + conteuRAM2;
            int end3 = instrucao[3];
            RAM[end3] = soma;
            break;
        }

        case 2:{                                                    //Opcode 2 = Subtrair
            int sub=0;                                              //salva na RAM[instrucao[3]] a subtraçao de RAM[instrucao[1]] + RAM[instrucao[2]]
            int end1= instrucao[1];
            int end2= instrucao[2];

            int conteuRAM1 = RAM[end1];
            int conteuRAM2 = RAM[end2];

            sub = conteuRAM1 - conteuRAM2;
            int end3 = instrucao[3];
            RAM[end3] = sub;
			break;
        }

        case 3:{                                                    //Opcode 3 = Trazer da RAM
            instrucao[1] = RAM[instrucao[2]];                         //Tras o conteudo da RAM[instrucao[2]] e salva na instrucao[1]
            break;
        }
    }
}

void desalocarRAM(int* RAM){
    free(RAM);
}

void maquina(int** matrizdeinstrucoes, int* RAM){
    int PC=0;
    int opcode = INT_MAX;                           //Opcode setado para realizarmos o while
    while(opcode != -1){
        int* instrucao = matrizdeinstrucoes[PC];
        opcode = instrucao[0];                      //opcode necessario para podermos realizar a verificação no while
        maquinaInterpretada(instrucao, RAM);

        PC++;
    }
}

void multiplicacao(int multiplicando, int multiplicador, int** matrizdeinstrucoes, int* RAM){
    *matrizdeinstrucoes = malloc((multiplicador+3) *sizeof(int*));

	for(int i=0; i< multiplicador+3; i++)
	{
		(*matrizdeinstrucoes)[i] = malloc(4*sizeof(int));
	}
	//ela tem +3 linhas, pois na primeira iremos passar o nosso multiplicando para a RAM
	//na segunda linha iremos, zerar nossa RAM[1] que será nosso resultado, e na ultíma linha nosso halt
	int* instrucao = malloc(4*sizeof(int*));
	instrucao[0]= 0;	//opcode igual a 0 => salvar na RAM
	instrucao[1]= multiplicando;	//valor a ser levado para RAM
	instrucao[2]= 0;	//o add onde vai ser armazenado o valor levado
	instrucao[3]= -1;	// o add que nao serve para nada
	matrizdeinstrucoes[0] = instrucao;

    instrucao = malloc(4*sizeof(int*));
	instrucao[0]= 0;	//opcode igual a 0 => salvar a RAM
	instrucao[1]= 0;	//valor a ser levado para a RAM
	instrucao[2]= 1;	//posição da RAM onde vai ser armazenado o valor
	instrucao[3]= -1;	//add que não serve para nada
	matrizdeinstrucoes[1] = instrucao;


	for(int i=0; i<multiplicador; i++){
        instrucao = malloc(4*sizeof(int*));
		instrucao[0]= 1;	//opcode igual a 1 => somar
		instrucao[1]= 0;	//end1 igual a 0 => RAM[0]
		instrucao[2]= 1;	//end2 igual a 1 => RAM[1]
		instrucao[3]= 1;	//end3 igual a 1=> RAM[1]
		matrizdeinstrucoes[i+2] = instrucao;
	}

    instrucao = malloc(4*sizeof(int*));
	instrucao[0]= -1;
	instrucao[1]= -1;
	instrucao[2]= -1;
	instrucao[3]= -1;
	matrizdeinstrucoes[multiplicador+2]= instrucao;

    maquina(matrizdeinstrucoes,RAM);
	free(instrucao);

}

void divisao(int dividendo, int divisor, int** matrizdeinstrucoes, int* RAM){
		//0 => salvar na memória
		//3 => trazer da memória
		//1 => opcode => somar
		//2 => opcode => subtrair
		//-1 => halt
		
		// 12 / 3 = (12-3); (9-3); (6-3); (3-3); (0-3) => 4
		// 15 / 4 = (15-4); (11-4); (7-4); (3-4) => 3		
		
		alocarmatrizdeinstrucoes(&matrizdeinstrucoes);
		int* instrucao = malloc(4*sizeof(int));
		instrucao[0] = 0;
		instrucao[1] = dividendo;
		instrucao[2] = 0;
		instrucao[3] = -1;
		matrizdeinstrucoes[0] = instrucao;
		//RAM[0]= dividendo;

		instrucao = malloc(4*sizeof(int));
		instrucao[0] = 0;
		instrucao[1] = divisor;
		instrucao[2] = 1;
		instrucao[3] = -1;
		matrizdeinstrucoes[1]= instrucao;
		//RAM[1]= divisor;
		
		instrucao = malloc(4*sizeof(int));
		instrucao[0] = 0;
		instrucao[1] = 1;
		instrucao[2] = 2;
		instrucao[3] = -1;
		matrizdeinstrucoes[2]= instrucao;
		//RAM[2]=1
		
		//representa uma constante de incremento
		instrucao= malloc(4*sizeof(int));
		instrucao[0] = 0;
		instrucao[1] = 0;
		instrucao[2] = 3;
		instrucao[3] = -1;
		matrizdeinstrucoes[3]= instrucao;
		//RAM[3]=0
		// representa quantas vezes a subtração foi feita, que é o resultado da divisão
		
		instrucao= malloc(4*sizeof(int));
		instrucao[0] = -1;
		instrucao[1] = -1;
		instrucao[2] = -1;
		instrucao[3] = -1;
		matrizdeinstrucoes[4]= instrucao;
		
		maquina(matrizdeinstrucoes, RAM);
		
		//trazer da RAM[0]
		instrucao= malloc(4*sizeof(int));
		instrucao[0] = 3;
		instrucao[1] = -1;
		instrucao[2] = 0;
		instrucao[3] = -1;
		maquinaInterpretada(instrucao, RAM);
		int ram0 = instrucao[1];	//busca o conteudo que esta na RAM[0] e atribui a variavel ram0

		//trazer da RAM[1]
		instrucao= malloc(4*sizeof(int));
		instrucao[0] = 3;
		instrucao[1] = -1;
		instrucao[2] = 1;
		instrucao[3] = -1;
		maquinaInterpretada(instrucao, RAM);
		int ram1 = instrucao[1];	//buscar o conteudo que esta na RAM[1] e atribui a variavel ram1
		
		while(ram1>=ram0){			//enquanto o divisor for maior que o dividendo, eu faço a subtração de divisor = dividendo e guardo na ram1
			//subtrair
			instrucao = malloc(4*sizeof(int));
			instrucao[0] = 2;
			instrucao[1] = 1;
			instrucao[2] = 0;
			instrucao[3] = 1;		
			maquinaInterpretada(instrucao, RAM);

			//somar o contador
			instrucao = malloc(4*sizeof(int));
			instrucao[0] = 1;
			instrucao[1] = 2;
			instrucao[2] = 3;
			instrucao[3] = 3;		
			maquinaInterpretada(instrucao, RAM);	//incremento o contador

			//trazer para a RAM[0]
			instrucao = malloc(4*sizeof(int));
			instrucao[0] = 3;
			instrucao[1] = -1;
			instrucao[2] = 0;
			instrucao[3] = -1;		
			maquinaInterpretada(instrucao, RAM);
			ram0 = instrucao[1];	//atualizo o valor de ram0

			//trazer para a RAM[1]
			instrucao = malloc(4*sizeof(int));
			instrucao[0] = 3;
			instrucao[1] = -1;
			instrucao[2] = 1;
			instrucao[3] = -1;		
			maquinaInterpretada(instrucao, RAM);
			ram1 = instrucao[1];	//atualizo o valor de ram1
		}
		
		instrucao = malloc(4*sizeof(int));
		instrucao[0]=-1;
		instrucao[1]=-1;
		instrucao[2]=-1;
		instrucao[3]=-1;
		matrizdeinstrucoes[0]=instrucao;
		maquina(matrizdeinstrucoes, RAM);
		free(instrucao);
		desalocarmatrizdeinstrucoes(matrizdeinstrucoes);
}

void exponenciacao(int base, int expoente, int** matrizdeinstrucoes, int* RAM){

	alocarmatrizdeinstrucoes(&matrizdeinstrucoes);

	RAM[5]=base;

	while((expoente-1) != 0){
		multiplicacao(RAM[5], base, matrizdeinstrucoes, RAM);
		int* instrucao = malloc(4*sizeof(int));
		instrucao[0]= 0;
		instrucao[1]= RAM[1];
		instrucao[2]= 5;
		instrucao[3]= -1;
		matrizdeinstrucoes[0]= instrucao;
		maquinaInterpretada(matrizdeinstrucoes[0], RAM);

		expoente--;
	}
	int* instrucao = malloc(4*sizeof(int));
	instrucao[0]=-1;
	instrucao[1]=-1;
	instrucao[2]=-1;
	instrucao[3]=-1;
	matrizdeinstrucoes[1]=instrucao;
	maquinaInterpretada(matrizdeinstrucoes[1], RAM);
	free(instrucao);
	desalocarmatrizdeinstrucoes(matrizdeinstrucoes);
}

void termoPA(int A1, int n, int r, int** matrizdeinstrucoes, int* RAM){

	//An = A1+(n-1)*r

	alocarmatrizdeinstrucoes(&matrizdeinstrucoes);


	int* instrucao = malloc(4*sizeof(int));
	instrucao[0] = 0;
	instrucao[1] = A1;
	instrucao[2] = 2;
	instrucao[3] = -1;
	matrizdeinstrucoes[0] = instrucao;
	//RAM[2]=A1;
	maquinaInterpretada(matrizdeinstrucoes[0], RAM);
	instrucao = malloc(4*sizeof(int));
	instrucao[0] = 0;
	instrucao[1] = n;
	instrucao[2] = 3;
	instrucao[3] = -1;
	matrizdeinstrucoes[1] = instrucao;
	//RAM[3]=n;
	maquinaInterpretada(matrizdeinstrucoes[1], RAM);
	instrucao = malloc(4*sizeof(int));
	instrucao[0] = 0;
	instrucao[1] = r;
	instrucao[2] = 4;
	instrucao[3] = -1;
	matrizdeinstrucoes[2] = instrucao;
	//RAM[4]=r;
	maquinaInterpretada(matrizdeinstrucoes[2], RAM);
	instrucao = malloc(4*sizeof(int));
	instrucao[0] = 0;
	instrucao[1] = 1;
	instrucao[2] = 5;
	instrucao[3] = -1;
	matrizdeinstrucoes[3] = instrucao;
	//RAM[5]=1;
	maquinaInterpretada(matrizdeinstrucoes[3], RAM);
	instrucao = malloc(4*sizeof(int));
	instrucao[0] = -1;
	instrucao[1] = -1;
	instrucao[2] =-1;
	instrucao[3] = -1;
	matrizdeinstrucoes[4] = instrucao;
	maquinaInterpretada(matrizdeinstrucoes[4], RAM);

	instrucao=malloc(4*sizeof(int));
	instrucao[0]= 2;
	instrucao[1]= 3;
	instrucao[2]= 5;
	instrucao[3]= 6;
	matrizdeinstrucoes[0] = instrucao;

	maquinaInterpretada(matrizdeinstrucoes[0],RAM);
	multiplicacao(RAM[6], r, matrizdeinstrucoes, RAM);

	//printf("%d\n", RAM[1]);

	instrucao = malloc(4*sizeof(int));
	instrucao[0]= 1;
	instrucao[1]= 1;
	instrucao[2]= 2;
	instrucao[3]= 7;
	matrizdeinstrucoes[0]=instrucao;
	maquinaInterpretada(matrizdeinstrucoes[0],RAM);

	instrucao = malloc(4*sizeof(int));
	instrucao[0]= 0;
	instrucao[1]= RAM[7];
	instrucao[2]= 8;
	instrucao[3]= -1;
	matrizdeinstrucoes[0]=instrucao;
	//RAM[7]=A1+(n-1)*r
	maquinaInterpretada(matrizdeinstrucoes[0],RAM);
	instrucao = malloc(4*sizeof(int));
	instrucao[0]=-1;
	instrucao[1]=-1;
	instrucao[2]=-1;
	instrucao[3]=-1;
	matrizdeinstrucoes[0]=instrucao;
	maquina(matrizdeinstrucoes,RAM);
	free(instrucao);
	desalocarmatrizdeinstrucoes(matrizdeinstrucoes);
}

void nPA(int A1, int An, int r, int** matrizdeinstrucoes, int* RAM){
	//n = (((An-A1)+r)/r)*r

	alocarmatrizdeinstrucoes(&matrizdeinstrucoes);

	int* instrucao = malloc(4*sizeof(int));
	instrucao[0] = 0;
	instrucao[1] = A1;
	instrucao[2] = 4;
	instrucao[3] = -1;
	matrizdeinstrucoes[0] = instrucao;
	//RAM[4]=A1;
	maquinaInterpretada(matrizdeinstrucoes[0], RAM);

	instrucao = malloc(4*sizeof(int));
	instrucao[0] = 0;
	instrucao[1] = An;
	instrucao[2] = 5;
	instrucao[3] = -1;
	matrizdeinstrucoes[1] = instrucao;
	//RAM[5]=An;
	maquinaInterpretada(matrizdeinstrucoes[1], RAM);

	instrucao = malloc(4*sizeof(int));
	instrucao[0] = 0;
	instrucao[1] = r;
	instrucao[2] = 6;
	instrucao[3] = -1;
	matrizdeinstrucoes[2] = instrucao;
	//RAM[6]=r;

	maquinaInterpretada(matrizdeinstrucoes[2], RAM);

	instrucao = malloc(4*sizeof(int));
	instrucao[0] = 2;
	instrucao[1] = 5;
	instrucao[2] = 4;
	instrucao[3] = 7;
	matrizdeinstrucoes[0] = instrucao;
	//RAM[7]=(An-A1);
	maquinaInterpretada(matrizdeinstrucoes[0], RAM);

	instrucao = malloc(4*sizeof(int));
	instrucao[0] = 1;
	instrucao[1] = 7;
	instrucao[2] = 6;
	instrucao[3] = 8;
	matrizdeinstrucoes[0] = instrucao;
	//RAM[8]= (An-A1)+r;
	maquinaInterpretada(matrizdeinstrucoes[0], RAM);

	divisao(RAM[6], RAM[8], matrizdeinstrucoes, RAM);
	instrucao = malloc(4*sizeof(int));
	instrucao[0] = 0;
	instrucao[1] = RAM[3];
	instrucao[2] = 9;
	instrucao[3] = -1;
	matrizdeinstrucoes[2] = instrucao;
	//RAM[9]= ((An-A1)+r)/r = n;
	maquinaInterpretada(matrizdeinstrucoes[2], RAM);

	instrucao = malloc(4*sizeof(int));
	instrucao[0]=-1;
	instrucao[1]=-1;
	instrucao[2]=-1;
	instrucao[3]=-1;
	matrizdeinstrucoes[0]=instrucao;
	maquina(matrizdeinstrucoes, RAM);
	free(instrucao);
	desalocarmatrizdeinstrucoes(matrizdeinstrucoes);
}

void razaoPA(int A1, int An, int n, int** matrizdeinstrucoes, int* RAM){
	//r=((An-A1)+n)/n
	alocarmatrizdeinstrucoes(&matrizdeinstrucoes);

	int* instrucao = malloc(4*sizeof(int));
	instrucao[0] = 0;
	instrucao[1] = A1;
	instrucao[2] = 4;
	instrucao[3] = -1;
	matrizdeinstrucoes[0] = instrucao;
	//RAM[4]=A1;
	maquinaInterpretada(matrizdeinstrucoes[0], RAM);

	instrucao = malloc(4*sizeof(int));
	instrucao[0] = 0;
	instrucao[1] = An;
	instrucao[2] = 5;
	instrucao[3] = -1;
	matrizdeinstrucoes[1] = instrucao;
	//RAM[5]=An;
	maquinaInterpretada(matrizdeinstrucoes[1], RAM);

	instrucao = malloc(4*sizeof(int));
	instrucao[0] = 0;
	instrucao[1] = n;
	instrucao[2] = 6;
	instrucao[3] = -1;
	matrizdeinstrucoes[2] = instrucao;
	//RAM[6]=n;

	maquinaInterpretada(matrizdeinstrucoes[2], RAM);

	instrucao = malloc(4*sizeof(int));
	instrucao[0] = 2;
	instrucao[1] = 5;
	instrucao[2] = 4;
	instrucao[3] = 7;
	matrizdeinstrucoes[0] = instrucao;
	//RAM[7]= An-A1
	maquinaInterpretada(matrizdeinstrucoes[0], RAM);

	instrucao = malloc(4*sizeof(int));
	instrucao[0] = 1;
	instrucao[1] = 7;
	instrucao[2] = 6;
	instrucao[3] = 8;
	matrizdeinstrucoes[0] = instrucao;
	//RAM[8]=(An-A1)+n
	maquinaInterpretada(matrizdeinstrucoes[0], RAM);

	divisao(RAM[6], RAM[8], matrizdeinstrucoes, RAM);
	//RAM[3]= ((An-A1)+n)/n = r
	instrucao = malloc(4*sizeof(int));
	instrucao[0] = 0;
	instrucao[1] = RAM[3];
	instrucao[2] = 1;
	instrucao[3] = -1;
	matrizdeinstrucoes[2] = instrucao;
	maquinaInterpretada(matrizdeinstrucoes[2], RAM);

	instrucao = malloc(4*sizeof(int));
	instrucao[0]=-1;
	instrucao[1]=-1;
	instrucao[2]=-1;
	instrucao[3]=-1;
	matrizdeinstrucoes[0]=instrucao;
	maquina(matrizdeinstrucoes, RAM);

	free(instrucao);
	desalocarmatrizdeinstrucoes(matrizdeinstrucoes);
}

void somatorioPA(int A1, int An, int n, int** matrizdeinstrucoes, int* RAM){

	//S = ((A1+An)*n)/2

	alocarmatrizdeinstrucoes(&matrizdeinstrucoes);

	int* instrucao = malloc(4*sizeof(int));
	instrucao[0] = 0;
	instrucao[1] = A1;
	instrucao[2] = 4;
	instrucao[3] = -1;
	matrizdeinstrucoes[0] = instrucao;
	//RAM[4]=A1;
	maquinaInterpretada(matrizdeinstrucoes[0], RAM);

	instrucao = malloc(4*sizeof(int));
	instrucao[0] = 0;
	instrucao[1] = An;
	instrucao[2] = 5;
	instrucao[3] = -1;
	matrizdeinstrucoes[1] = instrucao;
	//RAM[5]=An;
	maquinaInterpretada(matrizdeinstrucoes[1], RAM);

	instrucao = malloc(4*sizeof(int));
	instrucao[0] = 0;
	instrucao[1] = n;
	instrucao[2] = 6;
	instrucao[3] = -1;
	matrizdeinstrucoes[2] = instrucao;
	//RAM[6]=n;
	maquinaInterpretada(matrizdeinstrucoes[2], RAM);

	instrucao = malloc(4*sizeof(int));
	instrucao[0] = 1;
	instrucao[1] = 4;
	instrucao[2] = 5;
	instrucao[3] = 7;
	matrizdeinstrucoes[0] = instrucao;
	//RAM[7]=(A1+An)
	maquinaInterpretada(matrizdeinstrucoes[0], RAM);

	multiplicacao(RAM[7], RAM[6], matrizdeinstrucoes, RAM);
	//RAM[1]=(A1+An)*n	
	divisao(2, RAM[1], matrizdeinstrucoes, RAM);
	//RAM[3]=((A1+An)*n)/2 = S
	instrucao = malloc(4*sizeof(int));
	instrucao[0]=-1;
	instrucao[1]=-1;
	instrucao[2]=-1;
	instrucao[3]=-1;
	matrizdeinstrucoes[0]=instrucao;
	maquinaInterpretada(matrizdeinstrucoes[0], RAM);

	free(instrucao);
	desalocarmatrizdeinstrucoes(matrizdeinstrucoes);
}

void termoPG(int A1, int n, int q, int**matrizdeinstrucoes, int* RAM){

	alocarmatrizdeinstrucoes(&matrizdeinstrucoes);
	//An=A1*q^(n-1)
	//RAM[1] => multiplicacao
	//RAM[3] => divisao
	//RAM[5] => exponenciacao
	int* instrucao = malloc(4*sizeof(int));
	instrucao[0] = 0;
	instrucao[1] = A1;
	instrucao[2] = 4;
	instrucao[3] = -1;
	matrizdeinstrucoes[0] = instrucao;
	//RAM[4]=A1;
	maquinaInterpretada(matrizdeinstrucoes[0], RAM);

	instrucao = malloc(4*sizeof(int));
	instrucao[0] = 0;
	instrucao[1] = n;
	instrucao[2] = 6;
	instrucao[3] = -1;
	matrizdeinstrucoes[1] = instrucao;
	//RAM[6]=n;
	maquinaInterpretada(matrizdeinstrucoes[1], RAM);

	instrucao = malloc(4*sizeof(int));
	instrucao[0] = 0;
	instrucao[1] = q;
	instrucao[2] = 7;
	instrucao[3] = -1;
	matrizdeinstrucoes[2] = instrucao;
	//RAM[7]=q;
	maquinaInterpretada(matrizdeinstrucoes[2], RAM);

	instrucao = malloc(4*sizeof(int));
	instrucao[0] = 0;
	instrucao[1] = 1;
	instrucao[2] = 8;
	instrucao[3] = -1;
	matrizdeinstrucoes[3] = instrucao;
	//RAM[8]=1;

	maquinaInterpretada(matrizdeinstrucoes[3], RAM);

	instrucao = malloc(4*sizeof(int));
	instrucao[0] = 2;
	instrucao[1] = 6;
	instrucao[2] = 8;
	instrucao[3] = 9;
	matrizdeinstrucoes[0] = instrucao;
	maquinaInterpretada(matrizdeinstrucoes[0], RAM);
	//RAM[9]=n-1

	exponenciacao(RAM[7], RAM[9], matrizdeinstrucoes, RAM);
	multiplicacao(RAM[4], RAM[5], matrizdeinstrucoes, RAM);

	instrucao = malloc(4*sizeof(int));
	instrucao[0]=-1;
	instrucao[1]=-1;
	instrucao[2]=-1;
	instrucao[3]=-1;
	matrizdeinstrucoes[0]= instrucao;
	maquinaInterpretada(matrizdeinstrucoes[0], RAM);

	free(instrucao);
	desalocarmatrizdeinstrucoes(matrizdeinstrucoes);
}

void fibonacci(int** matrizdeinstrucoes, int* RAM){

	//F(n)=F(n-1)+F(n-2)
	alocarmatrizdeinstrucoes(&matrizdeinstrucoes);

	int* instrucao = malloc(4*sizeof(int));
	instrucao[0] = 0;
	instrucao[1] = 0;
	instrucao[2] = 4;
	instrucao[3] = -1;
	matrizdeinstrucoes[0] = instrucao;
	//RAM[4]=0;

	instrucao = malloc(4*sizeof(int));
	instrucao[0] = 0;
	instrucao[1] = 1;
	instrucao[2] = 6;
	instrucao[3] = -1;
	matrizdeinstrucoes[1] = instrucao;
	//RAM[6]=1;

	instrucao = malloc(4*sizeof(int));
	instrucao[0] = 0;
	instrucao[1] = 0;
	instrucao[2] = 7;
	instrucao[3] = -1;
	matrizdeinstrucoes[2]=instrucao;
	//RAM[7]=0 => zerando o endereço onde ficará guardado o valor da soma dos numeros anteriores

	instrucao = malloc(4*sizeof(int));
	instrucao[0] = -1;
	instrucao[1] = -1;
	instrucao[2] = -1;
	instrucao[3] = -1;
	matrizdeinstrucoes[3]=instrucao;

	maquina(matrizdeinstrucoes,RAM);

	printf("0, 1, ");

	for(int i=0; i<40; i++){

		instrucao = malloc(4*sizeof(int));
		instrucao[0] = 1;
		instrucao[1] = 4;
		instrucao[2] = 6;
		instrucao[3] = 7;
		matrizdeinstrucoes[0]= instrucao;
		//RAM[7]=RAM[4] + RAM[6]

		maquinaInterpretada(matrizdeinstrucoes[0], RAM);

		instrucao = malloc(4*sizeof(int));
		instrucao[0] = 0;
		instrucao[1] = RAM[6];
		instrucao[2] = 4;
		instrucao[3] = -1;
		matrizdeinstrucoes[0]= instrucao;
		//RAM[4] = RAM[6] => recebe o valor da proxima posicao
		maquinaInterpretada(matrizdeinstrucoes[0], RAM);

		instrucao = malloc(4*sizeof(int));
		instrucao[0] = 0;
		instrucao[1] = RAM[7];
		instrucao[2] = 6;
		instrucao[3] = -1;
		matrizdeinstrucoes[1]= instrucao;
		//RAM[6] = RAM[7]	=> recebe o valor da soma das posicoes

		maquinaInterpretada(matrizdeinstrucoes[1], RAM);
		printf("%d, ", RAM[7]);
	}
	instrucao = malloc(4*sizeof(int));
	instrucao[0]=-1;
	instrucao[1]=-1;
	instrucao[2]=-1;
	instrucao[3]=-1;
	matrizdeinstrucoes[0]=instrucao;
	maquinaInterpretada(matrizdeinstrucoes[0], RAM);

	desalocarmatrizdeinstrucoes(matrizdeinstrucoes);
	free(instrucao);
}

void fatorial(int** matrizdeinstrucoes, int* RAM, int fat){

	alocarmatrizdeinstrucoes(&matrizdeinstrucoes);

	int* instrucao = malloc(4*sizeof(int));
	instrucao[0] = 0;
	instrucao[1] = fat;
	instrucao[2] = 4;
	instrucao[3] = -1;
	matrizdeinstrucoes[0] = instrucao;
	//RAM[4]=fat

	instrucao = malloc(4*sizeof(int));
	instrucao[0] = 0;
	instrucao[1] = 0;
	instrucao[2] = 5;
	instrucao[3] = -1;
	matrizdeinstrucoes[1] = instrucao;
	//RAM[5]=0

	instrucao = malloc(4*sizeof(int));
	instrucao[0] = -1;
	instrucao[1] = -1;
	instrucao[2] = -1;
	instrucao[3] = -1;
	matrizdeinstrucoes[2] = instrucao; 

	maquina(matrizdeinstrucoes,RAM);

	int aux=fat;

	for(int i=0; i<fat-1; i++){

		multiplicacao(RAM[4], (aux-1) , matrizdeinstrucoes, RAM);

		instrucao = malloc(4*sizeof(int));
		instrucao[0] = 0;
		instrucao[1] = RAM[1];
		instrucao[2] = 5;
		instrucao[3] = -1;
		matrizdeinstrucoes[0] = instrucao;
		maquinaInterpretada(matrizdeinstrucoes[0],RAM);

		instrucao = malloc(4*sizeof(int));
		instrucao[0] = 0;
		instrucao[1] = RAM[5];
		instrucao[2] = 4;
		instrucao[3] = -1;
		matrizdeinstrucoes[0] = instrucao;

		maquinaInterpretada(matrizdeinstrucoes[0],RAM);
		aux--;
	}
	instrucao = malloc(4*sizeof(int));
	instrucao[0]= -1;
	instrucao[1]= -1;
	instrucao[2]= -1;
	instrucao[3]= -1;
	matrizdeinstrucoes[0]=instrucao;
	maquina(matrizdeinstrucoes, RAM);

	desalocarmatrizdeinstrucoes(matrizdeinstrucoes);
	free(instrucao);

}

void delta(int a, int b, int c, int** matrizdeinstrucoes, int* RAM){
	// delta = b^2 - 4*a*c
	alocarmatrizdeinstrucoes(&matrizdeinstrucoes);
	
	int* instrucao = malloc(4*sizeof(int));
	instrucao[0] = 0;
	instrucao[1] = a;
	instrucao[2] = 6;
	instrucao[3] = -1;
	matrizdeinstrucoes[0] = instrucao;
	//RAM[6]= a
	instrucao = malloc(4*sizeof(int));
	instrucao[0] = 0;
	instrucao[1] = b;
	instrucao[2] = 7;
	instrucao[3] = -1;
	matrizdeinstrucoes[1] = instrucao;
	//RAM[7] = b
	instrucao = malloc(4*sizeof(int));
	instrucao[0] = 0;
	instrucao[1] = c;
	instrucao[2] = 8;
	instrucao[3] = -1;
	matrizdeinstrucoes[2] = instrucao;
	//RAM[8] = c

	instrucao = malloc(4*sizeof(int));
	instrucao[0] = -1;
	instrucao[1] = -1;
	instrucao[2] = -1;
	instrucao[3] = -1;
	matrizdeinstrucoes[3] = instrucao;

	maquina(matrizdeinstrucoes, RAM);

	exponenciacao(RAM[7], 2, matrizdeinstrucoes, RAM);
	//RAM[5]= b^2
	multiplicacao(RAM[6], RAM[8], matrizdeinstrucoes, RAM);
	multiplicacao(RAM[1], 4, matrizdeinstrucoes, RAM);
	//RAM[1]= 4*a*c
	
	instrucao = malloc(4*sizeof(int));
	instrucao[0] = 2;
	instrucao[1] = 5;
	instrucao[2] = 1;
	instrucao[3] = 9;
	matrizdeinstrucoes[0] = instrucao;


	instrucao = malloc(4*sizeof(int));
	instrucao[0] = -1;
	instrucao[1] = -1;
	instrucao[2] = -1;
	instrucao[3] = -1;
	matrizdeinstrucoes[1] = instrucao;
	
	maquina(matrizdeinstrucoes,RAM);
	desalocarmatrizdeinstrucoes(matrizdeinstrucoes);
	free(instrucao);
}

void combinacao(int n, int p, int** matrizdeinstrucoes, int* RAM){
	//combinacao = n!/p!*(n-p)!

	alocarmatrizdeinstrucoes(&matrizdeinstrucoes);

	int* instrucao = malloc(4*sizeof(int));
	instrucao[0] = 0;
	instrucao[1] = n;
	instrucao[2] = 10;
	instrucao[3] = -1;
	matrizdeinstrucoes[0] = instrucao;

	instrucao = malloc(4*sizeof(int));
	instrucao[0] = 0;
	instrucao[1] = p;
	instrucao[2] = 11;
	instrucao[3] = -1;
	matrizdeinstrucoes[1] = instrucao;

	instrucao = malloc(4*sizeof(int));
	instrucao[0] = -1;
	instrucao[1] = -1;
	instrucao[2] = -1;
	instrucao[3] = -1;
	matrizdeinstrucoes[2] = instrucao;
	maquina(matrizdeinstrucoes, RAM);

	fatorial(matrizdeinstrucoes, RAM, RAM[10]);

	instrucao = malloc(4*sizeof(int));
	instrucao[0] = 0;
	instrucao[1] = RAM[4];
	instrucao[2] = 6;
	instrucao[3] = -1;
	matrizdeinstrucoes[0] = instrucao;

	maquinaInterpretada(matrizdeinstrucoes[0], RAM);
	//RAM[6]= n!

	fatorial(matrizdeinstrucoes, RAM, RAM[11]);

	instrucao = malloc(4*sizeof(int));
	instrucao[0] = 0;
	instrucao[1] = RAM[4];
	instrucao[2] = 7;
	instrucao[3] = -1;
	matrizdeinstrucoes[0] = instrucao;

	maquinaInterpretada(matrizdeinstrucoes[0], RAM);
	//RAM[7]= p!

	instrucao = malloc(4*sizeof(int));
	instrucao[0] = 2;
	instrucao[1] = 10;
	instrucao[2] = 11;
	instrucao[3] = 8;
	matrizdeinstrucoes[0] = instrucao;

	maquinaInterpretada(matrizdeinstrucoes[0], RAM);
	//RAM[8]= n-p
	fatorial(matrizdeinstrucoes, RAM, RAM[8]);

	instrucao = malloc(4*sizeof(int));
	instrucao[0] = 0;
	instrucao[1] = RAM[4];
	instrucao[2] = 9;
	instrucao[3] = -1;
	matrizdeinstrucoes[0] = instrucao;

	maquinaInterpretada(matrizdeinstrucoes[0], RAM);
	//RAM[9]= (n-p)!

	multiplicacao(RAM[9], RAM[7], matrizdeinstrucoes, RAM);
	//RAM[1]= (n-p)!*p!
	divisao(RAM[1], RAM[6], matrizdeinstrucoes, RAM);
	//RAM[3]= n!/(n-p)!*p!

	instrucao = malloc(4*sizeof(int));
	instrucao[0] = -1;
	instrucao[1] = -1;
	instrucao[2] = -1;
	instrucao[3] = -1;
	matrizdeinstrucoes[0] = instrucao;
	maquina(matrizdeinstrucoes, RAM);

	desalocarmatrizdeinstrucoes(matrizdeinstrucoes);
	free(instrucao);
}

void losangulo(int dmaior, int dmenor, int** matrizdeinstrucoes, int* RAM){
	//Al= (diagonalmaior*diagonalmenor)/2
	alocarmatrizdeinstrucoes(&matrizdeinstrucoes);
	multiplicacao(dmaior, dmenor, matrizdeinstrucoes, RAM);
	divisao(2, RAM[1],matrizdeinstrucoes,RAM);
}

void quadrado(int l, int** matrizdeinstrucoes, int* RAM){
	//Aq= lado*lado = l^2
	alocarmatrizdeinstrucoes(&matrizdeinstrucoes);
	exponenciacao(l, 2, matrizdeinstrucoes, RAM);
}

void trapezio(int bmaior, int bmenor, int h, int** matrizdeinstrucoes, int* RAM){
	//At=((base maior + base menor)*h)/2
	alocarmatrizdeinstrucoes(&matrizdeinstrucoes);

	int* instrucao = malloc(4*sizeof(int));
	instrucao[0] = 0;
	instrucao[1] = bmaior;
	instrucao[2] = 4;
	instrucao[3] = -1;
	matrizdeinstrucoes[0] = instrucao;
	//RAM[4]=base maior;

	instrucao = malloc(4*sizeof(int));
	instrucao[0] = 0;
	instrucao[1] = bmenor;
	instrucao[2] = 6;
	instrucao[3] = -1;
	matrizdeinstrucoes[1] = instrucao;
	//RAM[6]= base menor;

	instrucao = malloc(4*sizeof(int));
	instrucao[0] = 1;
	instrucao[1] = 4;
	instrucao[2] = 6;
	instrucao[3] = 7;
	matrizdeinstrucoes[2]=instrucao;
	//RAM[7]= base maior + base menor;

	instrucao = malloc(4*sizeof(int));
	instrucao[0] = -1;
	instrucao[1] = -1;
	instrucao[2] = -1;
	instrucao[3] = -1;
	matrizdeinstrucoes[3]=instrucao;

	maquina(matrizdeinstrucoes,RAM);

	multiplicacao(RAM[7], h,matrizdeinstrucoes,RAM);
	//RAM[1]= (base maior+base menor)*h
	divisao(2, RAM[1],matrizdeinstrucoes,RAM);
	//RAM[3]= ((base maior + base menor)*h)/2
}

void desalocarmatrizdeinstrucoes(int** matrizdeinstrucoes){
    for(int i=0; i<10;i++){
        free(matrizdeinstrucoes[i]);
    }
    free(matrizdeinstrucoes);
}

void menu(int** matrizdeinstrucoes, int* RAM){
	int aux, end=1;
	while(end != 2){
		printf("\nMENU \n");
		printf("1- Operacoes aleatorias\n");
		printf("2- Multiplicacao\n");
		printf("3- Divisao\n");
		printf("4- Exponenciacao\n");
		printf("5- Encontre o termo da PA\n");
		printf("6- Encontre o numero de termos da PA\n");
		printf("7- Encontre a razao da PA\n");
		printf("8- Somatorio dos termos da PA(finita)\n");
		printf("9- Encontre o termo da PG\n");
		printf("10- Sequencia de Fibonacci(os primeiros 40 termos)\n");
		printf("11- Fatorial\n");
		printf("12- Calculo do delta\n");
		printf("13- Combinacao simples\n");
		printf("14- Calcule a area do losangulo\n");
		printf("15- Calcule a area do quadrado\n");
		printf("16- Calculo da area do trapezio\n");
		printf("digite o numero da operacao: ");
		scanf("%d", &aux);
		switch(aux){
			case 1:{
				alocarmatrizdeinstrucoes(&matrizdeinstrucoes);
				montarInstrucoes(matrizdeinstrucoes);
				maquina(matrizdeinstrucoes,RAM);
				break;
			}
			case 2:{
				int multiplicando, multiplicador;
				printf("\nInforme o multiplicando e o multiplicador, respectivamente:");
				scanf("%d ",&multiplicando);
				scanf("%d", &multiplicador);
				multiplicacao(multiplicando, multiplicador, matrizdeinstrucoes,RAM);
				printf("Resultado da multiplicacao: %d \n", RAM[1]);
				break;
			}
			case 3:{
				int divisor, dividendo;
				printf("\nInforme o dividendo e o divisor, respectivamente:");
				scanf("%d ",&dividendo);
				scanf("%d", &divisor);
				divisao(divisor, dividendo, matrizdeinstrucoes,RAM);
				printf("Resultado da divisao: %d\n\n", RAM[3]);
				break;
			}
			case 4:{
				//2^4 = (((2x2)x2)x2)
				int base, expoente;
				printf("\nInforme a base e o expoente, respectivamente:");
				scanf("%d",&base);
				scanf("%d", &expoente);
				exponenciacao(base, expoente, matrizdeinstrucoes, RAM);

				printf("Resultado da exponenciacao = %d \n", RAM[5]);
				break;
			}
			case 5:{
				int A1, n, r;
				printf("\nInforme o primeiro termo da progressao, a posicao do termo que deseja achar e a razao, respectivamente:");
				scanf("%d", &A1);
				scanf("%d", &n);
				scanf("%d", &r);
				termoPA(A1, n, r, matrizdeinstrucoes, RAM);
				printf("\nO valor do termo %d eh = %d \n", n, RAM[8]);
				break;
			}
			case 6:{
				int A1, An, r;
				printf("\nInforme o primeiro termo da progressao, o ultimo termo e a razao, respectivamente:");
				scanf("%d", &A1);
				scanf("%d", &An);
				scanf("%d", &r);
				nPA(A1, An, r, matrizdeinstrucoes, RAM);
				printf("\nO numero de termos eh = %d \n", RAM[9]);
				break;
			}
			case 7:{
				int A1, An, n;
				printf("\nInforme o primeiro termo da progressao, o ultimo termo e o total de termos, respectivamente:");
				scanf("%d", &A1);
				scanf("%d", &An);
				scanf("%d", &n);
				razaoPA(A1, An, n, matrizdeinstrucoes, RAM);
				printf("\nO valor da razao eh = %d \n", RAM[1]);
				break;
			}
			case 8:{
				int A1, An, n;
				printf("\nInforme o primeiro termo da progressao, o ultimo termo e o total de termos, respectivamente:");
				scanf("%d", &A1);
				scanf("%d", &An);
				scanf("%d", &n);
				somatorioPA(A1, An, n, matrizdeinstrucoes, RAM);
				printf("\nO valor do somatorio eh = %d \n", RAM[3]);
				break;
			}

			case 9:{
				int A1, n, q;
				printf("\nInforme o primeiro termo da progressao, a posicao do termo que deseja achar e a razao, respectivamente:");
				scanf("%d", &A1);
				scanf("%d", &n);
				scanf("%d", &q);
				termoPG(A1, n, q, matrizdeinstrucoes, RAM);
				printf("\nO valor do termo %d eh = %d \n", n, RAM[1]);
				break;
			}

			case 10:{
				printf("Fibonacci: (");
				fibonacci(matrizdeinstrucoes, RAM);
				printf(")\n");
				break;
			}
			
			case 11:{
				int fat;
				printf("\nInforme o numero que deseja fazer o fatorial: ");
				scanf("%d", &fat);
				fatorial(matrizdeinstrucoes, RAM, fat);
				printf("\n%d! = ", fat);
				printf("%d \n", RAM[4]);
				break;
			}

			case 12:{
				int a, b, c;
				printf("\nInforme os valores de a, b e c, respectivamente: ");
				scanf("%d", &a);
				scanf("%d", &b);
				scanf("%d", &c);
				delta(a,b,c,matrizdeinstrucoes,RAM);
				printf("o valor de delta eh: %d\n", RAM[9]);
				break;
			}

			case 13:{
				int n,p;
				printf("\nInforme os valores de n e p, respectivamente (com n>=p): ");
				scanf("%d", &n);
				scanf("%d", &p);
				combinacao(n, p, matrizdeinstrucoes, RAM);
				printf("o numero de combinacoes eh: %d\n", RAM[3]);
				break;
			}
			

			case 14:{
				int dmaior, dmenor;
				printf("\nInforme os valores da diagonal maior e da diagonal menor: ");
				scanf("%d", &dmaior);
				scanf("%d", &dmenor);
				losangulo(dmaior,dmenor,matrizdeinstrucoes,RAM);
				printf("\n O valor da area do losangulo eh: %d\n", RAM[3]);
				break;
			}
			
			case 15:{
				int l;
				printf("\nInforme o tamanho do lado do quadrado: ");
				scanf("%d", &l);
				quadrado(l,matrizdeinstrucoes,RAM);
				printf("\n O valor da area do quadrado eh: %d\n", RAM[5]);
				break;
			}

			case 16:{
				int bmaior, bmenor, h;
				printf("\nInforme o valor da base maior, base menor e da altura, respectivamente: ");
				scanf("%d", &bmaior);
				scanf("%d", &bmenor);
				scanf("%d", &h);
				trapezio(bmaior,bmenor,h,matrizdeinstrucoes,RAM);
				printf("\n O valor da area do trapezio eh: %d\n", RAM[3]);
				break;
			}
		}
		printf("deseja realizar outra operacao? 1- para sim, 2- para nao:");
		scanf("%d", &end);
	}
}

void main(){

	int** matrizdeinstrucoes;
	int* RAM;
	RAM = malloc(100*sizeof(int));
	montarRAM(RAM);
	alocarmatrizdeinstrucoes(&matrizdeinstrucoes);
    menu(matrizdeinstrucoes, RAM);
    desalocarmatrizdeinstrucoes(matrizdeinstrucoes);
	desalocarRAM(RAM);
	desalocarmatrizdeinstrucoes(matrizdeinstrucoes);
}