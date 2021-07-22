#include "memoria.hpp"

void processador(Instrucao** inst, Memoria** c1, Memoria** c2, Memoria** c3, Memoria** ram, HitMiss* hitMiss, double tempoInicial);

int main(){
	int opcao;

	//geraInstrucao();
	Instrucao** inst = alocaInstrucao(TAM_INST_GERADOR);
	lerInstrucao(inst);
	HitMiss* hitMiss = inicializarHitMiss();

	clock_t tempo;
	tempo = clock();
	//tempo do processador consumido pelo programa/milissegundos
	double tempoInicial = (double)tempo / 1000.0;
	//cout << "TEMPO INICIAL: " << tempoInicial << endl;

	Memoria** ram = alocarMemoria(TAM_RAM);
	Memoria** cacheUm = alocarMemoria(TAM_C1);
	Memoria** cacheDois = alocarMemoria(TAM_C2);
	Memoria** cacheTres = alocarMemoria(TAM_C3);

	preencherRam(ram, inst);
    
    processador(inst, cacheUm, cacheDois, cacheTres, ram, hitMiss, tempoInicial);

    limpaMemoria(cacheUm, TAM_C1);
    limpaMemoria(cacheDois, TAM_C2);
    limpaMemoria(cacheTres, TAM_C3);
    //imprimirCache(cacheUm, TAM_C1);
    //imprimirCache(cacheDois, TAM_C2);
    //imprimirCache(cacheTres, TAM_C3);
    //imprimeRam(ram);
    
	cout << "\n \tCACHE HIT CACHE 1: " << getHitOne(hitMiss) << endl;
	cout << "\tCACHE MISS CACHE 1: " << getMissOne(hitMiss) << endl;
	cout << "\tCACHE HIT CACHE 2: " << getHitTwo(hitMiss) << endl;
	cout << "\tCACHE MISS CACHE 2: " << getMissTwo(hitMiss) << endl;
	cout << "\tCACHE HIT CACHE 3: " << getHitThree(hitMiss) << endl;
	cout << "\tCACHE MISS CACHE 3: " << getMissThree(hitMiss) << endl;
	cout << "\n \tCUSTO TOTAL: " << getCusto(hitMiss) << endl;
	cout << "\tTOTAL DE HIT: " << getHitOne(hitMiss) + getHitTwo(hitMiss) + getHitThree(hitMiss) << endl;
	cout << "\tTOTAL DE MISS: " << getMissOne(hitMiss) + getMissTwo(hitMiss) + getMissThree(hitMiss) << endl;

    //deletarInstrucao(inst);
    liberarMemoria(cacheUm, TAM_C1);
    liberarMemoria(cacheDois, TAM_C2);
    liberarMemoria(cacheTres, TAM_C3);
    liberarMemoria(ram, TAM_RAM);
	return 0;
}

void processador(Instrucao** inst, Memoria** c1, Memoria** c2, Memoria** c3, Memoria** ram, HitMiss* hitMiss, double tempoInicial){
	int soma = 0, conteudoUm, conteudoDois, indice = 0;
	Memoria* dadoMemoriaEnd1 = alocarVetor();
	Memoria* dadoMemoriaEnd2 = alocarVetor();
	
	while(getOpcode(inst[indice]) != -1){
		switch(getOpcode(inst[indice])){
            case 0:
            	dadoMemoriaEnd1 = MMU(c1, c2, c3, ram, getEnd1(inst[indice]), hitMiss, tempoInicial);
            	dadoMemoriaEnd2 = MMU(c1, c2, c3, ram, getEnd2(inst[indice]), hitMiss, tempoInicial);

            	conteudoUm = getPalavra(dadoMemoriaEnd1, getEndPalavra(getEnd1(inst[indice])));
            	conteudoDois = getPalavra(dadoMemoriaEnd2, getEndPalavra(getEnd2(inst[indice])));
                soma = conteudoUm + conteudoDois;

                insereCache(soma, c1, getEnd2(inst[indice]), tempoInicial);
                
                cout << "\n \tSOMA: " << conteudoUm << " + " << conteudoDois << " = " << soma << endl;
                break;
            case 1:
                dadoMemoriaEnd1 = MMU(c1, c2, c3, ram, getEnd1(inst[indice]), hitMiss, tempoInicial);
            	dadoMemoriaEnd2 = MMU(c1, c2, c3, ram, getEnd2(inst[indice]), hitMiss, tempoInicial);

            	conteudoUm = getPalavra(dadoMemoriaEnd1, getEndPalavra(getEnd1(inst[indice])));
            	conteudoDois = getPalavra(dadoMemoriaEnd2, getEndPalavra(getEnd2(inst[indice])));
                soma = conteudoUm - conteudoDois;
             
                insereCache(soma, c1, getEnd2(inst[indice]), tempoInicial);

                cout << "\n \tSUB: " << conteudoUm << " - " << conteudoDois << " = " << soma << endl;
                break;
            case -1:
             	break;
		}
        indice++;
    }
    liberarVetor(dadoMemoriaEnd1);
    liberarVetor(dadoMemoriaEnd2);
}

