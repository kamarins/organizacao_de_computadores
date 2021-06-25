#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <iomanip>
using namespace std;

struct Memoria{
    int opcode; //armazena código de operação da maquina
    int end1; //armazena o endereço de memoria que contem o primeiro valor
    int end2; //armazena o endereço de memoria que contem o segundo valor
    int end3; //armazena o endereço de memoria que contem o resultado da operação
};

int *montarMemoriaDados();
Memoria *criarInstrucoes();
void preencherInstrucoes(Memoria*, int, int, int, int);
void maquina(int&, Memoria*, int*);
void criaAleatorio(Memoria*, long long int);
void criaSoma(Memoria*, long long int, long long int);
void criaSubtracao(Memoria*, long long int, long long int);
void criaMultiplicacao(Memoria*, long long int, long long int);
void criaPA(Memoria*, long long int, long long int, long long int);
void criaFibonacci(Memoria*, long long int, int&, int*);
void criaRetangulo(Memoria*, long long int, long long int);
void criaHourstoMinutes(Memoria*, long long int, long long int, int&, int*);
void criaPotenciacao(Memoria*, long long int, long long int);
void criaFuncaoPrimeiroGrau(Memoria*, long long int, long long int, long long int, int&, int*);
void criaDelta(Memoria*, long long int, long long int, long long int, int&, int*);
void criarVelocidade(Memoria*, long long int, long long int, long long int, int&, int*);
void criaKelvintoCelsius(Memoria*, long long int);
void criaFatorial(Memoria*, long long int, int&, int*);
void preencherInstrucoes(Memoria*, int, int, int, int, int);

int main(){
    int opcao;
    int pc = 0; //registrador
    int *ram = montarMemoriaDados(); //preencher vetor
    Memoria *instrucoes = criarInstrucoes(); //alocar dinamicamente o vetor responsavel por armazenar os dados da struct

    do{
        //MENU//
        cout << "\n" << setw(35) << " MENU " << setw(33) << "\n" << endl;
        cout << "\tDIGITE A OPCAO DA OPERACAO QUE DESEJA\t\t\t\t\t\t \n" << endl;
        cout << "\t(DIGITE 0) SAIR DO PROGRAMA\t\t\t\t\t\t " << endl;
        cout << "\t(DIGITE 1) PROGRAMA ALEATORIO\t\t\t\t\t\t " << endl;
        cout << "\t(DIGITE 2) MULTIPLICACAO\t\t\t\t\t\t " << endl;
        cout << "\t(DIGITE 3) PROGRESSAO ARITMETICA\t\t\t\t\t\t " << endl;
        cout << "\t(DIGITE 4) FIBONACCI\t\t\t\t\t\t " << endl;
        cout << "\t(DIGITE 5) AREA DO RETANGULO\t\t\t\t\t\t " << endl;
        cout << "\t(DIGITE 6) CONVERSAO DE HORAS PARA MINUTOS\t\t\t\t\t\t " << endl;
        cout << "\t(DIGITE 7) POTENCIACAO\t\t\t\t\t\t " << endl;
        cout << "\t(DIGITE 8) FUNCAO DO PRIMEIRO GRAU\t\t\t\t\t\t " << endl;
        cout << "\t(DIGITE 9) DELTA\t\t\t\t\t\t" << endl;
        cout << "\t(DIGITE 10) VELOCIDADE EM FUNCAO DO TEMPO\t\t\t\t\t\t" << endl;
        cout << "\t(DIGITE 11) CONVERSAO DE KELVIN PARA CELSIUS\t\t\t\t\t\t" << endl;
        cout << "\t(DIGITE 12) FATORIAL\t\t\t\t\t\t \n" << endl;

        cout << "\tOPCAO: ";

        cin >> opcao;
        switch(opcao){
            case 1:
                long long int tam;
                cout << "\n \tDigite o n: ";
                cin >> tam;
                criaAleatorio(instrucoes, tam);
                maquina(pc, instrucoes, ram);
                break;
            case 2:
                long long int multiplicando, multiplicador;
                cout << "\n \tDigite os dois valores a serem multiplicados: ";
                cin >> multiplicando >> multiplicador;
                criaMultiplicacao(instrucoes, multiplicando, multiplicador);
                maquina(pc, instrucoes, ram);
                cout << "\n \tRESULTADO: " << ram[1] << endl;
                break;
            case 3:
                long long int primeiroTermo, razao, limite;
                cout << "\n \tDigite os valores do primeiro termo, razao e limite: ";
                cin >> primeiroTermo >> razao >> limite;
                criaPA(instrucoes, primeiroTermo, razao, limite);
                maquina(pc, instrucoes, ram);
                cout << "\n \tRESULTADO: " << ram[1] << endl;
                break;
            case 4:
                long long int fib;
                cout << "\n \tDigite o valor do limite: ";
                cin >> fib;
                criaFibonacci(instrucoes, fib, pc, ram);
                maquina(pc, instrucoes, ram);
                cout << "\n \tRESULTADO: " << ram[1] << endl;
                break;
            case 5:
                long long int baseRetan, alturaRetan;
                cout << "\n \tDigite os valores da base e da altura: ";
                cin >> baseRetan >> alturaRetan;
                criaRetangulo(instrucoes, baseRetan, alturaRetan);
                maquina(pc, instrucoes, ram);
                cout << "\n \tRESULTADO: " << ram[1] << endl;
                break;
            case 6:
                long long int horas, minutos;
                cout << "\n \tDigite o valor das horas e dos minutos: ";
                cin >> horas >> minutos;
                criaHourstoMinutes(instrucoes, horas, minutos, pc, ram);
                maquina(pc, instrucoes, ram);
                cout << "\n \tRESULTADO: " << ram[1] << endl;
                break;
            case 7:
                long long int base, expoente;
                cout << "\n \tDigite os valores da base e do expoente: ";
                cin >> base >> expoente;
                criaPotenciacao(instrucoes, base, expoente);
                maquina(pc, instrucoes, ram);
                cout << "\n \tRESULTADO: " << ram[1] << endl;
                break;
            case 8:
                long long int tv, x, cl;
                cout << "\n \tDigite os valores da taxa de variação, do x e do coeficiente linear: ";
                cin >> tv >> x >> cl;
                criaFuncaoPrimeiroGrau(instrucoes, tv, x, cl, pc, ram);
                maquina(pc, instrucoes, ram);
                cout << "\n \tRESULTADO: " << ram[1] << endl;
                break;
            case 9:
                long long int a, b, c;
                cout << "\n \tDigite os valores de a, b, c: ";
                cin >> a >> b >> c ;
                criaDelta(instrucoes, a, b, c, pc, ram);
                maquina(pc, instrucoes, ram);
                cout << "\n \tRESULTADO: " << ram[1] << endl;
                break;
            case 10:
                long long int velInicial, aceleracao, tempo;
                cout << "\n \tDigite os valores da velocidade inicial, da aceleracao e do tempo: ";
                cin >> velInicial >> aceleracao >> tempo;
                criarVelocidade(instrucoes, velInicial, aceleracao, tempo, pc, ram);
                maquina(pc, instrucoes, ram);
                cout << "\n \tRESULTADO: " << ram[1] << endl;
                break;
            case 11:
                long long int kelvin;
                cout << "\n \tDigite o valor a ser convertido para celsius: ";
                cin >> kelvin;
                criaKelvintoCelsius(instrucoes, kelvin);
                maquina(pc, instrucoes, ram);
                cout << "\n \tRESULTADO: " << ram[1] << endl;
                break;
            case 12:
            	long long int n;
            	cout << "\n \tDigite o valor do termo: ";
            	cin >> n;
            	criaFatorial(instrucoes, n, pc, ram);
            	cout << "\n \tRESULTADO: " << ram[1] << endl;
            	break;
            case 0:
                cout << "\n \tPrograma encerrado." << endl;
                break;
        }
    }while(opcao != 0);
   
    //deletar memoria alocada pelos vetores
    delete[] ram;
    delete[] instrucoes;

    return 0;
}

int *montarMemoriaDados(){
    int *ram = new int[4];

    srand(time(NULL));

    for(int i = 0; i < 4; i++)
        ram[i] = rand() % 1000; //gerar valores aleatorios de 0 a 999

    return ram;
}

Memoria *criarInstrucoes(){
    Memoria *instrucoes = new Memoria[1000];

    srand(time(NULL));

    //gerando valores aleatorios
    for(int i = 0; i < 999; i++){
        instrucoes[i].opcode = rand() % 2;
        instrucoes[i].end1 = rand() % 4;
        instrucoes[i].end2 = rand() % 4;
        instrucoes[i].end3 = rand() % 4;
    }

    //inserindo a ultima instrução do programa
    instrucoes[999].opcode = -1;
    instrucoes[999].end1 = -1;
    instrucoes[999].end2 = -1;
    instrucoes[999].end3 = -1;

    return instrucoes;
}

void preencherInstrucoes(Memoria* instrucoes, int pos, int opcode, int end1, int end2, int end3){
	instrucoes[pos].opcode = opcode; 
    instrucoes[pos].end1 = end1; 
    instrucoes[pos].end2 = end2;
    instrucoes[pos].end3 = end3;
}

void maquina(int& pc, Memoria* inst, int* ram){
    int conteudoRam1 = 0, conteudoRam2 = 0, 
        soma = 0, sub = 0; 

    while(inst[pc].opcode != -1){
        switch (inst[pc].opcode){
            case 0:
                //armazena o endereço de memoria do primeiro valor
                conteudoRam1 = ram[inst[pc].end1];
                //armazena o endereço de memoria do segundo valor
                conteudoRam2 = ram[inst[pc].end2];
                //somando...
                soma = conteudoRam1 + conteudoRam2;
                //armazena a soma no endereço de memoria 
                ram[inst[pc].end3] = soma;

                cout << "\n \tSOMA: " << conteudoRam1 << " + " << conteudoRam2 << " = " << soma << endl;
                break;
            case 1:
                //armazena o conteudo do endereço de memoria
                conteudoRam1 = ram[inst[pc].end1];
                //armazena o conteudo do endereço de memoria do segundo 
                conteudoRam2 = ram[inst[pc].end2];
                //subtraindo...
                sub = conteudoRam1 - conteudoRam2;
                ////armazena a soma no endereço de memoria 
                ram[inst[pc].end3] = sub;

                cout << "\n \tSUB: " << conteudoRam1 << " - " << conteudoRam2 << " = " << sub << endl;
                break;
            case 2: 
                //responsável por levar o valor  para a ram
                ram[inst[pc].end2] = inst[pc].end1;
                cout << "\n \tAtribuindo o valor a memoria " << ram[inst[pc].end2] << endl;
                break;
            case 3:
                //atualizando o valor contido na ram
                ram[inst[pc].end2] = ram[inst[pc].end1];
                cout << "\n \tAtualizando o valor da memoria " << ram[inst[pc].end2] << endl;
        }
        pc++;
    }
    pc = 0;
}

void criaSoma(Memoria *instrucoes, long long int valorUm, long long int valorDois){
    //levar pra ram o valorUm na posição 0
    preencherInstrucoes(instrucoes, 0, 2, valorUm, 0, -1);

    //levar pra ram o valorDois na posição 1
    preencherInstrucoes(instrucoes, 1, 2, valorDois, 1, -1);

    //somar os valores contidos na posição 0 e 1 e armarzenar o resultado na posição 1 da ram
    preencherInstrucoes(instrucoes, 2, 0, 0, 1, 1);

    //halt
    preencherInstrucoes(instrucoes, 3, -1, -1, -1, -1);
}

void criaSubtracao(Memoria *instrucoes, long long int valorUm, long long int valorDois){
    //levar pra ram o valorUm na posição 0
    preencherInstrucoes(instrucoes, 0, 2, valorUm, 0, -1);

    //levar pra ram o valorDois na posição 1
    preencherInstrucoes(instrucoes, 1, 2, valorDois, 1, -1);

    //subtrair os valores contidos na posição 0 e 1 e armarzenar o resultado na posição 1 da ram
    preencherInstrucoes(instrucoes, 2, 1, 0, 1, 1);

    //halt
    preencherInstrucoes(instrucoes, 3, -1, -1, -1, -1);
}

void criaAleatorio(Memoria* instrucoes, long long int tam){
	long long int opcode, end1, end2, end3;

	srand(time(NULL));
	for(int i = 0; i < tam; i++)
	{
		opcode = rand() % 2;
		end1 = rand() % 100;
		end2 = rand() % 100;
		end3 = 1;
		preencherInstrucoes(instrucoes, i, opcode, end1, end2, end3);
	}
	preencherInstrucoes(instrucoes, tam, -1, -1, -1, -1);
}

void criaMultiplicacao(Memoria *instrucoes, long long int multiplicando, long long int multiplicador){
    //levar pra ram o multiplicando na posição 0
    preencherInstrucoes(instrucoes, 0, 2, multiplicando, 0, -1);

    //levar pra ram o 0 na posição 1
    preencherInstrucoes(instrucoes, 1, 2, 0, 1, -1);

    //somar os valores até multiplicador
    for(int i = 0; i < multiplicador; i++){
        preencherInstrucoes(instrucoes, i+2, 0, 0, 1, 1);
    }

    //halt
    preencherInstrucoes(instrucoes, multiplicador+2, -1, -1, -1, -1);
}

void criaPA(Memoria* instrucoes, long long int primeiroTermo, long long int razao, long long int limite){
    preencherInstrucoes(instrucoes, 0, 2, razao, 0, -1);

    preencherInstrucoes(instrucoes, 1, 2, primeiroTermo, 1, -1);

    for(int i = 0; i < limite; i++){
        preencherInstrucoes(instrucoes, i+2, 0, 0, 1, 1);
    }

    preencherInstrucoes(instrucoes, limite+1, -1, -1, -1, -1);
}

void criaFibonacci(Memoria* instrucoes, long long int limite, int& pc, int* ram){
    long long int val1 = 0, val2 = 1, val3;

    criaSoma(instrucoes, val1, val2);
    maquina(pc, instrucoes, ram);

    //executa as somas sucessivas 
    for(int i = 0; i < limite - 2; i++){
        val3 = val1 + val2;
        criaSoma(instrucoes, val2, val3);
        val1 = val2;
        val2 = val3;
    }
}

void criaRetangulo(Memoria* instrucoes, long long int base, long long int altura){
    criaMultiplicacao(instrucoes, base, altura);
}

void criaHourstoMinutes(Memoria* instrucoes, long long int horas, long long int minutos, int& pc, int* ram){
	criaMultiplicacao(instrucoes, horas, 60);
	maquina(pc, instrucoes, ram);
	criaSoma(instrucoes, ram[1], minutos);
}

void criaPotenciacao(Memoria *instrucoes, long long int base, long long int expoente){
    int contInstrucoes = 0;

    if(expoente == 0){
    	preencherInstrucoes(instrucoes, contInstrucoes, 2, 1, 1, -1);
        contInstrucoes++;
    } else if(expoente == 1){
    	preencherInstrucoes(instrucoes, contInstrucoes, 2, base, 1, -1);
        contInstrucoes++;
    } else {
    	preencherInstrucoes(instrucoes, contInstrucoes, 2, base, 0, -1);
        contInstrucoes++;

        for(int i = 2; i <= expoente; i++){
        	preencherInstrucoes(instrucoes, contInstrucoes, 2, 0, 1, -1);
            contInstrucoes++;
            
            for(int j = 0; j < base; j++){
                preencherInstrucoes(instrucoes, contInstrucoes, 0, 0, 1, 1);
                contInstrucoes++;
            }
            preencherInstrucoes(instrucoes, contInstrucoes, 3, 1, 0, -1);
            contInstrucoes++;
        }
    }
    preencherInstrucoes(instrucoes, contInstrucoes, -1, -1, -1, -1);
}

void criaFuncaoPrimeiroGrau(Memoria *instrucoes, long long int a, long long int x, long long int b, int& pc, int* ram){
    criaMultiplicacao(instrucoes, a, x);
    maquina(pc, instrucoes, ram);
    criaSoma(instrucoes, ram[1], b);
}

void criaDelta(Memoria* instrucoes, long long int a, long long int b, long long int c, int& pc, int* ram){
    criaPotenciacao(instrucoes, b, 2);
    maquina(pc, instrucoes, ram);

    long long int aux = ram[instrucoes[1].end2];

    criaMultiplicacao(instrucoes, a, c);
    maquina(pc, instrucoes, ram);

    criaMultiplicacao(instrucoes, -4, ram[instrucoes[1].end2]);
    maquina(pc, instrucoes, ram);

    criaSoma(instrucoes, aux, ram[instrucoes[1].end2]);
}

void criarVelocidade(Memoria* instrucoes, long long int velInicial, long long int aceleracao, long long int tempo, int& pc, int* ram){
    criaMultiplicacao(instrucoes, aceleracao, tempo);
    maquina(pc, instrucoes, ram);
    criaSoma(instrucoes, ram[1], velInicial);
}

void criaKelvintoCelsius(Memoria* instrucoes, long long int k){
    criaSubtracao(instrucoes, k, 273);
}

void criaFatorial(Memoria* instrucoes, long long int n, int& pc, int* ram){
	criaMultiplicacao(instrucoes, n, 1);
	maquina(pc, instrucoes, ram);

	for(int i = 1; i < n-1; i++){
		criaMultiplicacao(instrucoes, ram[instrucoes[1].end2], i);
		preencherInstrucoes(instrucoes, 1, 3, 0, 1, -1);
		maquina(pc, instrucoes, ram);
	}
}