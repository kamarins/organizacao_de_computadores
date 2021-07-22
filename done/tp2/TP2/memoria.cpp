#include "memoria.hpp"

struct memoria{
	int endBloco;
	int palavras[TAM_BLOCO];
	int nAcessos;
	double tempo;
	bool atualizado;
};

struct hitMiss{
	int l1Miss, l1Hit;
	int l2Miss, l2Hit;
	int l3Miss, l3Hit;
	int custo;
};

int getEndBloco(Memoria* memoria){
	return memoria->endBloco;
}

int getPalavra(Memoria* memoria, int indiceP){
	return memoria->palavras[indiceP];
}

int getAcesso(Memoria* memoria){
	return memoria->nAcessos;
}

double getTempo(Memoria* memoria){
	return memoria->tempo;
}

void setEndBloco(Memoria* memoria, int endBloco){
	memoria->endBloco = endBloco;
}

void setPalavra(Memoria* memoria, int indiceP, int palavra){
	memoria->palavras[indiceP] = palavra;
}

void setAcesso(Memoria* memoria, int nAcessos){
	memoria->nAcessos += nAcessos;
}

void setTempo(Memoria* memoria, double tempo){
	memoria->tempo = tempo;
}

int getHitOne(HitMiss* hitMiss){
	return hitMiss->l1Hit;
}

int getMissOne(HitMiss* hitMiss){
	return hitMiss->l1Miss;
}

int getHitTwo(HitMiss* hitMiss){
	return hitMiss->l2Hit;
}

int getMissTwo(HitMiss* hitMiss){
	return hitMiss->l2Miss;
}

int getHitThree(HitMiss* hitMiss){
	return hitMiss->l3Hit;
}

int getMissThree(HitMiss* hitMiss){
	return hitMiss->l3Miss;
}

int getCusto(hitMiss* hitMiss){
	return hitMiss->custo;
}

void setHitOne(hitMiss* hitMiss){
	hitMiss->l1Hit++;
}

void setMissOne(HitMiss* hitMiss){
	hitMiss->l1Miss++;
}

void setHitTwo(hitMiss* hitMiss){
	hitMiss->l2Hit++;
}

void setMissTwo(HitMiss* hitMiss){
	hitMiss->l2Miss++;
}

void setHitThree(hitMiss* hitMiss){
	hitMiss->l3Hit++;
}

void setMissThree(HitMiss* hitMiss){
	hitMiss->l3Miss++;
}

void setCusto(HitMiss* hitMiss, int custo){
	hitMiss->custo += custo;
}

Memoria** alocarMemoria(int tamanho){
	Memoria** memoria = new Memoria*[tamanho];

	for(int i = 0; i < tamanho; i++){
		memoria[i] = new Memoria;
		memoria[i]->endBloco = -1;
		for(int j = 0; j < TAM_BLOCO; j++)
			memoria[i]->palavras[j] = 0;
		memoria[i]->nAcessos = 0;
		memoria[i]->tempo = 0;
		memoria[i]->atualizado = false;
	}

	return memoria;
}

Memoria* alocarVetor(){
	Memoria* memoria = new Memoria[1];

	memoria[0].endBloco = -1;
	for(int i = 0; i < TAM_BLOCO; i++)
		memoria[0].palavras[i] = 0;
	memoria[0].nAcessos = 0;
	memoria[0].tempo = 0;
	memoria[0].atualizado = false;

	return memoria;
}

void preencherRam(Memoria** ram, Instrucao** inst){
	time_t t;
	srand((unsigned) time(&t));
	for(int i = 0; i < TAM_RAM; i++){
		for(int j = 0; j < TAM_BLOCO; j++)
			ram[i]->palavras[j] = rand() % 10;
		//ram[i]->endBloco = getEndBloco(getEnd1(inst[i]));
	}
}

void imprimeRam(Memoria** ram){
	for(int i = 0; i < TAM_RAM; i++){
		cout << "INDICE " << i << endl;
		cout << ram[i]->endBloco << endl;
		for(int j = 0; j < TAM_BLOCO; j++){
			cout << ram[i]->palavras[j] << endl;
		}
	}
}

void imprimirCache(Memoria** memoria, int tamanho){
	for(int i = 0; i < tamanho; i++){
		cout << "\nINDICE" << i << endl;
		cout << memoria[i]->endBloco << endl;
		for(int k = 0; k < TAM_BLOCO; k++)
			cout << memoria[i]->palavras[k] << endl;
	}
}

HitMiss* inicializarHitMiss(){
	HitMiss* hitMiss = new HitMiss;

	hitMiss->l1Miss = 0;
	hitMiss->l1Hit = 0;
	hitMiss->l2Miss = 0;
	hitMiss->l2Hit = 0;
	hitMiss->l3Miss = 0;
	hitMiss->l3Hit = 0;
	hitMiss->custo = 0;

	return hitMiss;
}

int buscarCache(Endereco* e, Memoria** cache, int tam_cache){ 
	//verifica a existencia do endereco para cada bloco dentro de uma cache
	for(int i = 0; i < tam_cache; i++)
		if(cache[i]->endBloco == getEndBloco(e)){
			setAcesso(cache[i], 1);
			return i;
		}
	return -1;
}

void insereCache(int valor, Memoria** memoria, Endereco* e, double tempoInicial){
	clock_t tempo;
	tempo = clock();
	double tempoCache = (double)tempo/1000.0 - tempoInicial;

	for(int i = 0; i < TAM_C1; i++){
		if(memoria[i]->endBloco == getEndBloco(e)){
			memoria[i]->palavras[getEndPalavra(e)] = valor;
			memoria[i]->tempo = tempoCache;
			memoria[i]->nAcessos = 0;
			memoria[i]->atualizado = true;
			break;
		}
	}
}

void trocarCache(int endBloco, Memoria** cOrigem, int tam_cOrigem, Memoria** cDestino, int tam_cDestino, double tempoInicial){
	int indice = 0; 
	int menorAcesso = cDestino[0]->nAcessos;
	double maiorTempo = cDestino[0]->tempo - tempoInicial;
	
	for(int i = 0; i < tam_cDestino; i++){
		if(cDestino[i]->endBloco == -1){
			indice = i;
			break;
		} else if(maiorTempo > cDestino[i]->tempo - tempoInicial){
			maiorTempo = cDestino[i]->tempo - tempoInicial;
			indice = i;
		} else if(cDestino[i]->endBloco < menorAcesso){
			menorAcesso = cDestino[i]->nAcessos;
			indice = i;
		} 
	}

	for(int i = 0; i < tam_cOrigem; i++){
		if(cOrigem[i]->endBloco == endBloco){
			clock_t tempo;
			tempo = clock();
			double tempoCache = (double)tempo/1000.0 - tempoInicial;
			Memoria* aux;
			aux = cDestino[indice];
			cDestino[indice] = cOrigem[i];
			cOrigem[i] = aux;
			cDestino[indice]->tempo = tempoCache;
			cDestino[indice]->nAcessos = 0;
			cDestino[indice]->atualizado = false;
			break;
		}
	}
}

void trocarRam(int endBloco, Memoria** ram, int tam_ram, Memoria** cDestino, int tam_cDestino, double tempoInicial){
	int indice = 0;
	int menorAcesso = cDestino[0]->nAcessos;
	double maiorTempo = cDestino[0]->tempo - tempoInicial;

	
	for(int i = 0; i < tam_cDestino; i++){
		if(cDestino[i]->endBloco == -1){
			indice = i;
			break;
		} else if(maiorTempo > cDestino[i]->tempo - tempoInicial){
			maiorTempo = cDestino[i]->tempo - tempoInicial;
			indice = i;
		} else if(cDestino[i]->endBloco < menorAcesso){
			menorAcesso = cDestino[i]->nAcessos;
			indice = i;
		} 
	}

	if(cDestino[indice]->atualizado){
		clock_t tempo; 
		tempo = clock();
		double tempoCache = (double)tempo/1000.0 - tempoInicial;
		Memoria* aux;
		aux = cDestino[indice];
		cDestino[indice] = ram[endBloco];
		ram[endBloco] = aux;
		setTempo(cDestino[indice], tempoCache);
		setEndBloco(cDestino[indice], endBloco);
		for(int k = 0; k < TAM_BLOCO; k++){
			setPalavra(cDestino[indice], k, getPalavra(ram[endBloco], k));
		}
		setAcesso(cDestino[indice], 0);
		//cout << "ENTROUUUUUUUUUUUUUU" << endl;
	} else {
		clock_t tempo; 
		tempo = clock();
		double tempoCache = (double)tempo/1000.0 - tempoInicial;
		setTempo(cDestino[indice], tempoCache);
		setEndBloco(cDestino[indice], endBloco);
		for(int k = 0; k < TAM_BLOCO; k++){
			setPalavra(cDestino[indice], k, getPalavra(ram[endBloco], k));
		}
		setAcesso(cDestino[indice], 0);
	}
}

Memoria* MMU(Memoria** c1, Memoria** c2, Memoria** c3, Memoria** ram, Endereco* e, HitMiss* hitMiss, double tempoInicial){
	if(buscarCache(e, c1, TAM_C1) != -1){
		setHitOne(hitMiss);
		setCusto(hitMiss, 10);
	} else if(buscarCache(e, c2, TAM_C2) != -1){
		setMissOne(hitMiss);
		setHitTwo(hitMiss);
		setCusto(hitMiss, 100);
		trocarCache(getEndBloco(e), c2, TAM_C2, c1, TAM_C1, tempoInicial);
	} else if(buscarCache(e, c3, TAM_C3) != -1){
		setMissOne(hitMiss);
		setMissTwo(hitMiss);
		setHitThree(hitMiss);
		setCusto(hitMiss, 1000);
		trocarCache(getEndBloco(e), c3, TAM_C3, c2, TAM_C2, tempoInicial);
		trocarCache(getEndBloco(e), c2, TAM_C2, c1, TAM_C1, tempoInicial);
	} else {
		setMissOne(hitMiss);
		setMissTwo(hitMiss);
		setMissThree(hitMiss);
		setCusto(hitMiss, 100000);
		trocarRam(getEndBloco(e), ram, TAM_RAM, c3, TAM_C3, tempoInicial);
		trocarCache(getEndBloco(e), c3, TAM_C3, c2, TAM_C2, tempoInicial);
		trocarCache(getEndBloco(e), c2, TAM_C2, c1, TAM_C1, tempoInicial);
	}
	return c1[buscarCache(e, c1, TAM_C1)];
}

void limpaMemoria(Memoria** memoria, int tamanho){
	for(int i = 0; i < tamanho; i++){
		memoria[i]->endBloco = -1;
		for(int j = 0; j < TAM_BLOCO; j++)
			memoria[i]->palavras[j] = 0;
		memoria[i]->nAcessos = 0;
		memoria[i]->tempo = 0;
	}
}

void liberarMemoria(Memoria** memoria, int tamanho){
	for(int i = 0; i < tamanho; i++){
		delete memoria[i];
	}
	delete[] memoria;
}

void liberarVetor(Memoria* memoria){
	delete[] memoria;
}