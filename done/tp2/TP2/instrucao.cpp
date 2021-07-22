#include "instrucao.hpp"

struct instrucao{
	Endereco* add1;
	Endereco* add2;
	int opcode;
};

struct endereco{
	int endBloco;
	int endPalavra;
};

Endereco* getEnd1(Instrucao* inst){
	return inst->add1;
}

Endereco* getEnd2(Instrucao* inst){
	return inst->add2;
}

int getEndBloco(Endereco* e){
	return e->endBloco; 
}

int getEndPalavra(Endereco* e){
	return e->endPalavra;
}

int getOpcode(Instrucao* inst){
	return inst->opcode;
}

void setEnd1(Instrucao* inst, Endereco* add1){
	inst->add1 = add1;
}

void setEnd2(Instrucao* inst, Endereco* add2){
	inst->add2 = add2;
}

void setEndBloco(Endereco* e, int endBloco){
	e->endBloco = endBloco;
}

void setEndPalavra(Endereco* e, int endPalavra){
	e->endPalavra = endPalavra;
}

void setOpcode(Instrucao* inst, int opcode){
	inst->opcode = opcode;
}

//GERADOR DE INSTRUCOES PARA OS TPS DE BCC 266 - JOUBERT

//UFOP

//FELIPE CESAR L. MACHADO 16.2.5890

void geraInstrucao(){
	ofstream instrucoes;
	instrucoes.open("instrucoes.txt");

	vector< vector<int> > vetor; vetor.clear();
	vector<int> aux; aux.clear();

	srand((unsigned int)time(NULL));

	int quant_for = NUM_INS / TAM_FOR;
	int quant_repeticoes = (REPETICOES / 100.0 + 0.0001)*(quant_for);

	vector<int> sequence; sequence.clear();
	for (int i = 0; i < quant_for; i++)
	{
		sequence.push_back(i);
	}

	for (int i = 0; i < quant_for - quant_repeticoes; i++)
	{
		size_t tmp = rand() % quant_for;
		while (tmp >= sequence.size())
			tmp -= sequence.size();

		sequence.erase(sequence.begin() + tmp);
	}
	//Sequencia aleatoria completa

	for (int i = 0; i<TAM_FOR; i++)
	{
		aux.push_back(rand() % (op_max - op_min + 1) + op_min);
		for (int add = 0; add < QUANTIDADE_DE_ENDERECOS; add++)
		{
			aux.push_back(rand() % TAM_MEM);
			if (ENDERECO_DE_PALAVRAS != 0)
				aux.push_back(rand() % 4);
		}

		vetor.push_back(aux);
		aux.clear();
	}
	//FOR a ser repetido completo

	int tamanho = (ENDERECO_DE_PALAVRAS == 0 ? QUANTIDADE_DE_ENDERECOS + 1 : QUANTIDADE_DE_ENDERECOS * 2 + 1);
	bool end = false, same = false;
	for (int a = 0; a<quant_for; a++)
	{

		if (!end)
		{
			if (a == sequence[0])
			{
				if (a == quant_for - 1)
					vetor[TAM_FOR - 1][0] = hault;

				for (int i = 0; i < TAM_FOR; i++)
				{
					for (int j = 0; j < tamanho; j++)
					{
						instrucoes << vetor[i][j] << (j == tamanho - 1 ? "\n" : " ");
					}
				}

				if (sequence.size() > 0)
				{
					sequence.erase(sequence.begin());
					if (sequence.size() == 0)
						end = true;
				}
				same = true;
			}
		}

		if (!same)
		{

			for (int j = 0; j<TAM_FOR; j++)
			{
				if (j == TAM_FOR - 1 && a == quant_for - 1)
					instrucoes << hault;
				else
					instrucoes << rand() % (op_max - op_min + 1) + op_min;

				for (int add = 0; add < QUANTIDADE_DE_ENDERECOS; add++)
				{
					instrucoes << " " << rand() % TAM_MEM;
					if (ENDERECO_DE_PALAVRAS != 0)
						instrucoes << " " << rand() % 4;
				}

				instrucoes << "\n";

			}

		}

		same = false;

	}

	instrucoes.close();
}

Instrucao** alocaInstrucao(int tamanho){
	Instrucao** inst = new Instrucao*[tamanho];

	for(int i = 0; i < tamanho; i++){
		inst[i] = new Instrucao;
		inst[i]->add1 = new Endereco;
		inst[i]->add2 = new Endereco;
	}
	return inst;
}



void lerInstrucao(Instrucao** inst){
	ifstream arquivo;
	arquivo.open("instrucoes.txt");
	
	for(int i = 0; i < TAM_INST_GERADOR; i++){
		arquivo >> inst[i]->opcode;
		arquivo >> inst[i]->add1->endBloco;
		arquivo >> inst[i]->add1->endPalavra;
		arquivo >> inst[i]->add2->endBloco;
		arquivo >> inst[i]->add2->endPalavra;
	}
	arquivo.close();
}



void deletarInstrucao(Instrucao** inst){
	for(int i = 0; i < TAM_INST_GERADOR; i++){
		delete inst[i]->add1;
		delete inst[i]->add2;
		delete inst[i];
	}
	delete[] inst;
}

