#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "MMU.h"
#include "blocodememoria.h"
#include "endereco.h"
#include "instrucao.h"

int buscarNaMemoria(BlocoMemoria** memoria, Endereco* endereco, int tamanho){
    for(int i=0; i<tamanho; i++){
        if(getEndBloco(memoria[i]) == getEndBlocoEnd(endereco)){
            setNumAcessosAdd1(memoria[i]);
            return i;   //se for encontrado
        }
    }
    return -1;          //se nao for encontrado
}

int LFU(int tamanho, BlocoMemoria** cache){
    int aux = INT_MAX;
    int posicaoCache;

    for(int i=0; i<tamanho; i++){
        if(getNumAcessos(cache[i]) <= aux){
            if(getEndBloco(cache[i]) == -1){
                return i;
            }
            else{
                aux = getNumAcessos(cache[i]);
                posicaoCache = i;
            }
        }
    }
    return posicaoCache;
}

BlocoMemoria* trocadeMemoria(int posicaoDeDestino, int posicaoDeSaida, BlocoMemoria** memoriaDeDestino, BlocoMemoria** memoriaDeSaida, int custo, Endereco* Endereco){
    if(isAtualizado(memoriaDeDestino[posicaoDeDestino]) == false){
        printf("\nentrou");
        if(getEndBloco(memoriaDeSaida[posicaoDeSaida]) == getEndBlocoEnd(Endereco)){
            printf("\nentrou dnv");
            int aux = getEndBloco(memoriaDeDestino[posicaoDeDestino]);
            memoriaDeDestino[posicaoDeDestino] = memoriaDeSaida[posicaoDeSaida];
            setEndBloco(memoriaDeSaida[posicaoDeSaida], aux);
        }
    }
    else{
        printf("\nsaiu");
        BlocoMemoria* aux = memoriaDeDestino[posicaoDeDestino];
        memoriaDeDestino[posicaoDeDestino] = memoriaDeSaida[posicaoDeSaida];
        memoriaDeSaida[posicaoDeSaida] = aux;
    }

    setCusto(memoriaDeDestino[posicaoDeDestino], custo);
    setNumAcessosAdd1(memoriaDeSaida[posicaoDeSaida]);
    setNumAcessosAdd1(memoriaDeDestino[posicaoDeDestino]);

    return memoriaDeDestino[posicaoDeDestino];
}


BlocoMemoria* MMU(Endereco* endereco, BlocoMemoria** RAM, BlocoMemoria** cache1, BlocoMemoria** cache2, BlocoMemoria** cache3, int tamanhoCache1, int tamanhoCache2,int tamanhoCache3){
    int custo = 0;
    int posicaoCache1, posicaoCache2, posicaoCache3;

    posicaoCache1 = buscarNaMemoria(cache1, endereco, tamanhoCache1);
    
    if(posicaoCache1 != -1){
        custo+=10;
        setCusto(cache1[posicaoCache1], custo);
        setCacheHit(cache1[posicaoCache1], 1);
        setNumAcessosAdd1(cache1[posicaoCache1]);
        
        return cache1[posicaoCache1];
    }
    else{
        posicaoCache2 = buscarNaMemoria(cache2, endereco, tamanhoCache2);

        if(posicaoCache2 != -1){
            custo+=110;
            posicaoCache1 = LFU(tamanhoCache1, cache1);
            
            cache1[posicaoCache1] = trocadeMemoria(posicaoCache1, posicaoCache2, cache1, cache2, custo, endereco);

            setCacheHit(cache1[posicaoCache1], 2);

            return cache1[posicaoCache1];
        }
        else{
            posicaoCache3 = buscarNaMemoria(cache3, endereco, tamanhoCache3);

            if(posicaoCache3 != -1){
                custo+=220;
                posicaoCache2 = LFU(tamanhoCache2, cache2);
                cache2[posicaoCache2] = trocadeMemoria(posicaoCache2, posicaoCache3, cache2, cache3, custo, endereco);

                posicaoCache1 = LFU(tamanhoCache1, cache1);
                cache1[posicaoCache1] = trocadeMemoria(posicaoCache1, posicaoCache2, cache1, cache2, custo, endereco);
 
                setCacheHit(cache1[posicaoCache1], 3);

                return cache1[posicaoCache1]; 
            }
            else{ //ram
                custo += 1110;
                posicaoCache3 = LFU(tamanhoCache3, cache3);
                if(isAtualizado(cache3[posicaoCache3]) == false){  
                    printf("\n1");
                    cache3[posicaoCache3] = RAM[getEndBlocoEnd(endereco)];
                    printf("\n2");
                    posicaoCache2 = LFU(tamanhoCache2, cache2);
                    printf("\n3");
                    cache2[posicaoCache2] = trocadeMemoria(posicaoCache2, posicaoCache3, cache2, cache3, custo, endereco);
                    printf("\n4");
                    posicaoCache1 = LFU(tamanhoCache1, cache1);
                    printf("\n5");
                    cache1[posicaoCache1] = trocadeMemoria(posicaoCache1, posicaoCache2, cache1, cache2, custo, endereco);
                    printf("\n6");
                    setCacheHit(cache1[posicaoCache1], 4);
                    printf("\n7");
                    return cache1[posicaoCache1];
                }
                else{
                    setDesatualizado(cache3[posicaoCache3]);
                    BlocoMemoria* aux = cache3[posicaoCache3];
                    cache3[posicaoCache3] = RAM[getEndBlocoEnd(endereco)];
                    RAM[getEndBlocoEnd(endereco)] = aux;

                    posicaoCache2 = LFU(tamanhoCache2, cache2);
                    cache2[posicaoCache2] = trocadeMemoria(posicaoCache2, posicaoCache3, cache2, cache3, custo, endereco);
                    
                    posicaoCache1 = LFU(tamanhoCache1, cache1);
                    cache1[posicaoCache1] = trocadeMemoria(posicaoCache1, posicaoCache2, cache1, cache2, custo, endereco);
                    setCacheHit(cache1[posicaoCache1], 4);

                    return cache1[posicaoCache1];
                }
            }
        }
    }
}