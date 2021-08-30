#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define SIZE_CACHE_01 8      
#define SIZE_CACHE_02 16    
#define SIZE_CACHE_03 32    
#define SIZE_RAM 64
#define SIZE_HD 5000
#define SIZE_INSTRUCTIONS 1000  
#define SIZE_INTERRUPTION_INSTRUCTIONS 900

#define ADDITION 0
#define SUB 1
#define HALT -1
int cont = 0;

//================================================================================================//

typedef struct{
    
    int address_block;
    int address_word;
}Address;

Address *createAddress(int end_block, int end_word);

int getAddressWord(Address *a);
int getAddressBlock(Address *a);

//================================================================================================//

typedef struct{
    int opcode;
    Address *address_01;
    Address *address_02;
    Address *address_03;
}Instructions;

Instructions* createInstruction(int opcode, Address* ad1, Address* ad2, Address* ad3);

Address* getAD1(Instructions* i);
Address* getAD2(Instructions* i);
Address* getAD3(Instructions* i);

//================================================================================================//

typedef struct{   
    int address_block;
    int accessed;
    int hit;
    int miss;
    int size;
    long int cost;
    int word[4];
    int updated;
    bool empty; 
}MemoryBlock;

MemoryBlock *createMemoryBlock(int size);

int getWord(MemoryBlock *m, int ad);
void setWord(MemoryBlock *m, int ind, int word);
void setUpdated(MemoryBlock *m, int updated);

//================================================================================================//

MemoryBlock **createMemory(int size);

//================================================================================================//

void createHD(int size);

//============================================={MMU}==============================================//

int MMU(MemoryBlock **cache_01, MemoryBlock **cache_02, MemoryBlock **cache_03, MemoryBlock **RAM, Address *address);

//=> Funcoes de busca!

int searcheCache(MemoryBlock **cache, int address, int size);

int searcheRAM(MemoryBlock **RAM, int address, int size);

int searcheHD(MemoryBlock **RAM, int address, int size);

int dataTransfer(MemoryBlock **carrierBlock, MemoryBlock **receivingBlock, int cache_position_aux);

int getEmptyPosition(MemoryBlock **memory_cache);

void blockTransfer(MemoryBlock *receivingBlock, MemoryBlock *carrierBlock);

void wordsTransfer(int *receivingBlock, int *carrierBlock);

void blockOutdated(MemoryBlock *MemoryBlock);

//================================================================================================//
//==> Operações da Maquina 

void addition(Instructions *instructions, MemoryBlock *cache_01_frist_position, MemoryBlock *cache_01_second_position, MemoryBlock *cache_01_third_position);

void subtraction(Instructions *instructions, MemoryBlock *cache_01_frist_position, MemoryBlock *cache_01_second_position, MemoryBlock *cache_01_third_position);