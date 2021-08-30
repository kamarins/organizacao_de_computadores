#include "functions.h"

int main(){

    clock_t temp;

    //=> Inicializando memorias e instrucoes.   
    MemoryBlock **cache_01 = createMemory(SIZE_CACHE_01);
    MemoryBlock **cache_02 = createMemory(SIZE_CACHE_02);
    MemoryBlock **cache_03 = createMemory(SIZE_CACHE_03);
    MemoryBlock **RAM = createMemory(SIZE_RAM);
    createHD(SIZE_HD);

    Instructions **instructions = malloc(SIZE_INSTRUCTIONS * sizeof(Instructions*));
	Instructions **interruptions = malloc(SIZE_INTERRUPTION_INSTRUCTIONS * sizeof(Instructions*));

    Address *aux_01;
	Address *aux_02;
	Address *aux_03;

    FILE *instructions_file = fopen("melhorcaso.txt","r");

    int opcode, address_block_01, address_word_01, address_block_02, address_word_02, address_block_03, address_word_03;

	for(int i = 0; i < SIZE_INSTRUCTIONS; i++){
        fscanf (instructions_file, "%d", &opcode);

        fscanf (instructions_file, "%d", &address_word_01);
        fscanf (instructions_file, "%d", &address_block_01);
        
        fscanf (instructions_file, "%d", &address_word_02);
        fscanf (instructions_file, "%d", &address_block_02);
        
        fscanf (instructions_file, "%d", &address_word_03);
        fscanf (instructions_file, "%d", &address_block_03);

		aux_01 = createAddress(address_word_01, address_block_01);
		aux_02 = createAddress(address_word_02, address_block_02);
		aux_03 = createAddress(address_word_03, address_block_03);

		instructions[i] = createInstruction(opcode, aux_01, aux_02, aux_03);
    }

    fclose(instructions_file);

    temp = clock(); // Aloca tempo inicial
    int PC = 0;
    int hit_total = 0;
    int miss_total = 0;
    long int custo_total = 0;

    while (instructions[PC]->opcode != -1){
        
        int frist_cache_position = -1;
        int second_cache_position = -1;
        int third_cache_position = -1;

        if(instructions[PC]->opcode != -1){
            
            frist_cache_position = MMU(cache_01, cache_02, cache_03, RAM, instructions[PC]->address_01);
            second_cache_position = MMU(cache_01, cache_02, cache_03, RAM, instructions[PC]->address_02);
            third_cache_position = MMU(cache_01, cache_02, cache_03, RAM, instructions[PC]->address_03);

            switch (instructions[PC]->opcode){
            case ADDITION:            
                    addition(instructions[PC], cache_01[frist_cache_position], cache_01[second_cache_position], 
                    cache_01[third_cache_position]);

                    cache_01[third_cache_position]->updated = 1;

                break;
            case SUB:
                    subtraction(instructions[PC], cache_01[frist_cache_position], cache_01[second_cache_position], 
                    cache_01[third_cache_position]);   
                    
                    cache_01[third_cache_position]->updated = 1;
                
                break;
            case HALT:
                printf("\nNAO HA DEMANDA POR LEVAR DADOS EXTERNOS PARA AS MEMORIAS.\n");
                break;
            }
        }
        
        int interruptionRate = rand() % 11;

		if( interruptionRate >= 0 && interruptionRate <= 3){

            printf("interruptionRate: %d\n",interruptionRate);

            int PCi = 0;

            FILE* interruption_file = fopen("interruptions.txt","r"); 

            for(int i = 0; i < SIZE_INTERRUPTION_INSTRUCTIONS; i++){

                fscanf (instructions_file, "%d", &opcode);

                fscanf (instructions_file, "%d", &address_word_01);
                fscanf (instructions_file, "%d", &address_block_01);
                
                fscanf (instructions_file, "%d", &address_word_02);
                fscanf (instructions_file, "%d", &address_block_02);
                
                fscanf (instructions_file, "%d", &address_word_03);
                fscanf (instructions_file, "%d", &address_block_03);

                aux_01 = createAddress(address_word_01, address_block_01);
                aux_02 = createAddress(address_word_02, address_block_02);
                aux_03 = createAddress(address_word_03, address_block_03);

                interruptions[i] = createInstruction(opcode, aux_01, aux_02, aux_03);
            }

            fclose(interruption_file);
            
            while (interruptions[PCi]->opcode != -1){
            
            int frist_cache_position = -1;
            int second_cache_position = -1;
            int third_cache_position = -1;

            if(interruptions[PCi]->opcode != -1){

                frist_cache_position = MMU(cache_01, cache_02, cache_03, RAM, interruptions[PCi]->address_01);
                second_cache_position = MMU(cache_01, cache_02, cache_03, RAM, interruptions[PCi]->address_02);
                third_cache_position = MMU(cache_01, cache_02, cache_03, RAM, interruptions[PCi]->address_03);
                
                switch (interruptions[PCi]->opcode){
                case ADDITION:
                        addition(interruptions[PCi], cache_01[frist_cache_position], cache_01[second_cache_position], 
                        cache_01[third_cache_position]);

                        cache_01[third_cache_position]->updated = 1;
                    

                    break;
                case SUB:
                        subtraction(interruptions[PCi], cache_01[frist_cache_position], cache_01[second_cache_position], 
                        cache_01[third_cache_position]);   
                        
                        cache_01[third_cache_position]->updated = 1;
                    
                    break;
                case HALT:
                    printf("\nNAO HA DEMANDA POR LEVAR DADOS EXTERNOS PARA AS MEMORIAS.\n");
                    break;
                }
            }

            PCi++;
            
            }
	    }
	PC++;
    }
		
    hit_total = cache_01[0]->hit + cache_02[0]->hit + cache_03[0]->hit + RAM[0]->hit + RAM[1]->hit;
    miss_total = cache_01[0]->miss + cache_02[0]->miss + cache_03[0]->miss + RAM[0]->miss;

    custo_total = cache_01[0]->cost + cache_02[0]->cost + cache_03[0]->cost + RAM[0]->cost + RAM[1]->cost;

    printf("\n| TAMANHO CACHE 1 -> %d|\n", SIZE_CACHE_01);
    printf("| TAMANHO CACHE 2 -> %d|\n", SIZE_CACHE_02);
    printf("| TAMANHO CACHE 3 -> %d|\n", SIZE_CACHE_03);
    printf("| TAMANHO RAM     -> %d|\n\n", SIZE_RAM);
    printf("| TAMANHO HD      -> %d|\n\n", SIZE_HD);
   
    printf("| HIT CACHE 1 -> %d | MISS CACHE 1 -> %d |\n", cache_01[0]->hit, cache_01[0]->miss);
    printf("| HIT CACHE 2 -> %d | MISS CACHE 2 -> %d |\n", cache_02[0]->hit, cache_02[0]->miss);
    printf("| HIT CACHE 3 -> %d | MISS CACHE 3 -> %d |\n", cache_03[0]->hit, cache_03[0]->miss);
    printf("| HIT RAM     -> %d | MISS RAM     -> %d  |\n", RAM[0]->hit, RAM[0]->miss);
    printf("| HIT HD     -> %d | MISS HD       -> 0  |\n", RAM[1]->hit);

    printf("\n| HIT TOTAL   -> %d | MISS TOTAL   -> %d |\n", hit_total, miss_total);
    
    printf("\n| CUSTO CACHE 1 -> %ld |", cache_01[0]->cost);
    printf("\n| CUSTO CACHE 2 -> %ld |", cache_02[0]->cost);
    printf("\n| CUSTO CACHE 3 -> %ld |", cache_03[0]->cost);
    printf("\n| CUSTO RAM      -> %ld|", RAM[0]->cost);
    printf("\n| CUSTO HD       -> %ld|", RAM[1]->cost);

    printf("\n\n| CUSTO TOTAL    -> %ld|\n\n", custo_total);
    
    temp = clock() - temp; // armazena tempo final - inicial   
    double *tempProgram=malloc(sizeof(double));
    *tempProgram = ((double)temp)/((CLOCKS_PER_SEC/1000));
     
    printf("\nTempo de execucao: %.2lf ms.\n\n", *tempProgram);

    for (int i = 0; i < SIZE_CACHE_01; i++){
        free(cache_01[i]);
    }
    free(cache_01);
    
    for (int i = 0; i < SIZE_CACHE_02; i++){
        free(cache_02[i]);
    }
    free(cache_02);
    
    for (int i = 0; i < SIZE_CACHE_03; i++){
        free(cache_03[i]);
    }
    free(cache_03);

    for (int i = 0; i < SIZE_RAM; i++){
        free(RAM[i]);
    }
    free(RAM);
    
    for (int i = 0; i < SIZE_INSTRUCTIONS; i++){
        free(instructions[i]);
    }
    free(instructions);
    
    for (int i = 0; i < SIZE_INTERRUPTION_INSTRUCTIONS; i++){
        free(interruptions[i]);
    }
    free(interruptions);
    
    free(tempProgram);

    return 0;
}

Address* createAddress(int end_block, int end_word){
    Address *new = malloc(sizeof(Address));
    new->address_block = end_block;
    new->address_word = end_word;
    
    return new;
}

int getAddressWord(Address *a){
	return a->address_word;
}

int getAddressBlock(Address *a){
	return a->address_block;
}

Instructions* createInstruction(int opcode, Address* ad1, Address* ad2, Address* ad3){
	Instructions *new = malloc(sizeof(Instructions));
	new->opcode = opcode;
	new->address_01 = ad1;
	new->address_02 = ad2;
	new->address_03 = ad3;
	return new;
}

Address* getAD1(Instructions* i){
	return i->address_01;
}

Address* getAD2(Instructions* i){
	return i->address_02;
}

Address* getAD3(Instructions* i){
	return i->address_03;
}

MemoryBlock *createMemoryBlock(int size){
    MemoryBlock *new = malloc(sizeof(MemoryBlock));

    for(int i = 0; i < 4; i++){
	    new->word[i] = -1;
    }

    new->size = size;
    new->empty = true;
    new->updated = 0;
    new->hit = 0;
    new->miss = 0;
    new->accessed = 0;
    new->cost = 0;

    return new;
}

MemoryBlock **createMemory(int size){
   
    MemoryBlock **new = malloc(size * sizeof(MemoryBlock));

    for (int i = 0; i < size; i++){
        new[i] = createMemoryBlock(size);
        new[i]->address_block = -1;
    }

    return new;
}

int getWord(MemoryBlock *m, int ad){
	return m->word[ad];
}

void setWord(MemoryBlock *m, int ind, int word){
	m->word[ind] = word;	
}

void setUpdated(MemoryBlock *m, int updated){
	m->updated = updated;
}

void createHD(int size){
    
    int word;
    srand(time(NULL));

    FILE *HD = fopen("HD.bin", "wb");

    for (int i = 0; i < size; i++){
        word = rand() % 3;
        fwrite(&word, sizeof(int), 1, HD);
    }

    fclose(HD);
}

int MMU(MemoryBlock **cache_01, MemoryBlock **cache_02, MemoryBlock **cache_03, MemoryBlock **RAM, Address *address){

    int cache_position = 0;

    if(searcheCache(cache_01, address->address_block, SIZE_CACHE_01) != -1){

        cache_position = searcheCache(cache_01, address->address_block, SIZE_CACHE_01);
        
        cache_01[0]->hit += 1;
        
        cache_01[0]->cost += 1;
        
        return cache_position;
    }
    else if(searcheCache(cache_02, address->address_block, SIZE_CACHE_02) != -1){

        cache_position = searcheCache(cache_02, address->address_block, SIZE_CACHE_02);
        cache_position = dataTransfer(cache_02, cache_01, cache_position);
        
        cache_02[0]->hit += 1;
        
        cache_01[0]->miss += 1;     
        
        cache_02[0]->cost += 11;
        
        return cache_position;
    }
   
    else if(searcheCache(cache_03, address->address_block, SIZE_CACHE_03) != -1){
        
        cache_position = searcheCache(cache_03, address->address_block, SIZE_CACHE_03);
        cache_position = dataTransfer(cache_03, cache_02, cache_position);
        cache_position = dataTransfer(cache_02, cache_01, cache_position);
        
        cache_03[0]->hit += 1;
        
        cache_01[0]->miss += 1;
        cache_02[0]->miss += 1;     

        cache_03[0]->cost += 111;

        return cache_position;
    }

    else if(searcheCache(RAM, address->address_block, SIZE_RAM) != -1){

        cache_position = dataTransfer(RAM, cache_03, cache_position);
        cache_position = dataTransfer(cache_03, cache_02, cache_position);
        cache_position = dataTransfer(cache_02, cache_01, cache_position);       
        
        cache_01[0]->miss += 1;   
        cache_02[0]->miss += 1;   
        cache_03[0]->miss += 1;

        RAM[0]->hit += 1;

        RAM[0]->cost += 5111;
        
        return cache_position;
    }
    else{

        cache_position = searcheHD(RAM, address->address_block, SIZE_RAM);
        cache_position = dataTransfer(RAM, cache_03, cache_position);
        cache_position = dataTransfer(cache_03, cache_02, cache_position);
        cache_position = dataTransfer(cache_02, cache_01, cache_position);  

        cache_01[0]->miss += 1;   
        cache_02[0]->miss += 1;   
        cache_03[0]->miss += 1;
        RAM[0]->miss += 1;

        RAM[1]->cost += 105111;
        RAM[1]->hit += 1;

        return cache_position; 
        
    }
}

int searcheCache(MemoryBlock **cache, int address, int size){  
    for(int i = 0; i < size; i++){
        if((cache[i]->address_block) == (address)){
            cont += 1;
            cache[i]->accessed = cont;
            return i;
        }
    }
    return -1;
}

int searcheHD(MemoryBlock **RAM, int address, int size){
    
    MemoryBlock *aux_trade = createMemoryBlock(1);
   
    FILE *HD = fopen("HD.bin", "rb");
    
    fseek(HD, address * 16, SEEK_SET);

    for(int i = 0; i < 4; i++ ){
        fread(&aux_trade->word[i], sizeof(int), 1, HD);
    }
    
    int emptyPosition = getEmptyPosition(RAM);

    if(emptyPosition != -1){
        
        blockTransfer(RAM[emptyPosition], aux_trade);
        RAM[emptyPosition]->address_block = address; 
        free(aux_trade);
        
        return emptyPosition;
    }
    else{
        
        int menor = 10000; 
        int selectedPosition = 0;
        
        for (int i = 0; i < SIZE_RAM; i++){
            if(RAM[i]->accessed < menor){
                menor = RAM[i]->accessed;
                selectedPosition = i;       
            }
        }

        // Bloco Atualizado ?

        if(RAM[selectedPosition]->updated == 1){
            
            HD = fopen("HD.bin","wb");

            MemoryBlock *words_aux = createMemoryBlock(1); 

            blockTransfer(words_aux, RAM[selectedPosition]);
            blockTransfer(RAM[selectedPosition], aux_trade);
            blockTransfer(aux_trade, words_aux);
           
            blockOutdated(RAM[selectedPosition]);
            
            for(int i = 0; i < 4; i++){
                fseek(HD, -sizeof(int), SEEK_CUR);
            }

            for(int i = 0;i < 4; i++){
                fwrite(&aux_trade->word[i], sizeof(int), 1, HD);
            }
            
			fclose(HD);

            RAM[selectedPosition]->address_block = address;
            free(aux_trade);
            free(words_aux);

            return selectedPosition;
        }
        
        blockTransfer(RAM[selectedPosition], aux_trade);
        RAM[selectedPosition]->address_block = address; 
        
        free(aux_trade);
        
        return selectedPosition;   
    }
}

int dataTransfer(MemoryBlock **carrierBlock, MemoryBlock **receivingBlock, int cache_position_aux){

    int emptyPosition = getEmptyPosition(receivingBlock);
    int selectedPosition = 0;

    if (emptyPosition == -1){

        int menor = 10000; 
        for (int i = 0; i < receivingBlock[0]->size; i++){
            if(receivingBlock[i]->accessed < menor){
                menor = receivingBlock[i]->accessed;
                selectedPosition = i;       
            }
        }
        
        MemoryBlock *aux = createMemoryBlock(1);
        blockTransfer(aux, receivingBlock[selectedPosition]);
        blockTransfer(receivingBlock[selectedPosition], carrierBlock[cache_position_aux]);
        blockTransfer(carrierBlock[cache_position_aux], aux);
        
        free(aux);
        return selectedPosition;
    }    

    MemoryBlock *aux = createMemoryBlock(1);

    blockTransfer(aux, receivingBlock[emptyPosition]);
    blockTransfer(receivingBlock[emptyPosition], carrierBlock[cache_position_aux]);
    blockTransfer(carrierBlock[cache_position_aux], aux);
    
    free(aux);
    return emptyPosition;
}

void blockTransfer(MemoryBlock *receivingBlock, MemoryBlock *carrierBlock){  
    
    receivingBlock->empty = false;
    receivingBlock->address_block = carrierBlock->address_block;  
    receivingBlock->updated = carrierBlock->updated;
    receivingBlock->word[0] = carrierBlock->word[0];
    receivingBlock->word[1] = carrierBlock->word[1];
    receivingBlock->word[2] = carrierBlock->word[2];
    receivingBlock->word[3] = carrierBlock->word[3];
    
}

void wordsTransfer(int *receivingBlock, int *carrierBlock){  
    receivingBlock[0] = carrierBlock[0];   
    receivingBlock[1] = carrierBlock[1];   
    receivingBlock[2] = carrierBlock[2];   
    receivingBlock[3] = carrierBlock[3];   
}

int getEmptyPosition(MemoryBlock **memory_cache){
    int emptyPosition;

    for (int i = 0; i < memory_cache[0]->size; i++){
        if(memory_cache[i]->address_block == -1){
            emptyPosition = i;
            return emptyPosition;
        }   
    }
    return -1;
}

void blockOutdated(MemoryBlock *MemoryBlock){
    MemoryBlock->updated = 0;
    MemoryBlock->accessed = 0;
}

void addition(Instructions *instructions, MemoryBlock *cache_01_frist_position, MemoryBlock *cache_01_second_position, MemoryBlock *cache_01_third_position){
    int word_01 = getWord(cache_01_frist_position, getAddressWord(getAD1(instructions)));
    int word_02 = getWord(cache_01_second_position, getAddressWord(getAD2(instructions)));

    int sum = word_01 + word_02;
    printf("\nSOMA -> %d + %d = %d\n", word_01, word_02, sum);

    setWord(cache_01_third_position, getAddressWord(getAD3(instructions)), sum);
    setUpdated(cache_01_third_position, 1);
}

void subtraction(Instructions *instructions, MemoryBlock *cache_01_frist_position, MemoryBlock *cache_01_second_position, MemoryBlock *cache_01_third_position){
    int word_01 = getWord(cache_01_frist_position, getAddressWord(getAD1(instructions)));
    int word_02 = getWord(cache_01_second_position, getAddressWord(getAD2(instructions)));

    int sub = word_01 - word_02;
    printf("\nSUBTRACAO -> %d - %d = %d\n", word_01, word_02, sub);

    setWord(cache_01_third_position, getAddressWord(getAD3(instructions)), sub);
    setUpdated(cache_01_third_position, 1);
}


