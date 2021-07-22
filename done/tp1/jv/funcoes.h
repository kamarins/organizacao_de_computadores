#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"math.h"

typedef struct memoria Memoria;

int* RetornarRAM(Memoria* ram);
void Menu(Memoria* m);
void Programa_Aleatorio(Memoria* m);
Memoria* Alocar_Memoria();
void maquina(Memoria* m);
void Free(Memoria* m);

//submenus
void Submenu_Mat_Basica(Memoria* m);
void Submenu_Mat_Aplicada(Memoria* m);
void Submenu_Fisica(Memoria* m);
void Submenu_Conversor_Unidade(Memoria* m);

//matemática básica - 4
void Adicao(Memoria* m, int primeiro_valor, int segundo_valor);
void Subtracao(Memoria* m, int primeiro_valor, int segundo_valor);
void Multiplicacao(Memoria* m, int primeiro_valor, int segundo_valor);
void Divisao(Memoria* m, int primeiro_valor, int segundo_valor);

//matemática aplicada - 16
void Delta(Memoria* m, int primeiro_valor, int segundo_valor, int terceiro_valor);
void IMC(Memoria* m, int primeiro_valor, int segundo_valor);
void Potencia(Memoria* m, int primeiro_valor, int segundo_valor);
void Area_Triangulo(Memoria* m, int primeiro_valor, int segundo_valor);
void Area_Quadrado(Memoria* m, int primeiro_valor);
void Area_Retangulo(Memoria* m, int primeiro_valor, int segundo_valor);
void Porcentagem(Memoria *m, int primeiro_valor, int segundo_valor);
void PA(Memoria* ram,  int primeiro_valor, int segundo_valor, int terceiro_valor);
void Perimetro_Quadrado(Memoria* m, int primeiro_valor);
void Perimetro_Retangulo(Memoria* m, int primeiro_valor, int segundo_valor);
void Soma_Quadrados(Memoria* m, int primeiro_valor, int segundo_valor);
void Permutacao_Simples(Memoria* m, int primeiro_valor);
void Combinacao(Memoria* m, int primeiro_valor, int segundo_valor);
void Arranjo(Memoria* m, int primeiro_valor, int segundo_valor);
void Fatorial(Memoria* m, int primeiro_valor);
void Fibonacci(Memoria* m, int primeiro_valor);

//fisica - 9
void Volume_Paralelepipedo(Memoria* m, int primeiro_valor, int segundo_valor, int terceiro_valor);
void Distancia_Percorrida(Memoria* m, int primeiro_valor, int segundo_valor);
void Velocidade_Media(Memoria* m, int primeiro_distancia, int segundo_distancia,int primeiro_tempo, int segundo_tempo);
void Aceleracao(Memoria* m, int primeiro_distancia, int segundo_distancia,int primeiro_tempo, int segundo_tempo);
void Volume_Cubo(Memoria* m, int primeiro_valor);
void Volume_Piramide(Memoria* m, int primeiro_valor, int segundo_valor);
void Forca(Memoria *m, int primeiro_valor, int segundo_valor);
void Calorimetria(Memoria* m,  int primeiro_valor, int segundo_valor, int terceiro_valor);
void Efeito_Joule(Memoria* m,  int primeiro_valor, int segundo_valor, int terceiro_valor);

//conversores de unidades//
//tempo - 5
void Converter_Seg_Min(Memoria* m, int primeiro_valor);
void Converter_Min_Seg(Memoria* m, int primeiro_valor);
void Converter_Min_Hora(Memoria* m, int primeiro_valor);
void Converter_Hora_Min(Memoria* m, int primeiro_valor);
void Converter_Hora_Seg(Memoria* m, int primeiro_valor);

//comprimento - 5
void Converter_Cm_M(Memoria* m, int primeiro_valor);
void Converter_M_Cm(Memoria* m, int primeiro_valor);
void Converter_M_Km(Memoria* m, int primeiro_valor);
void Converter_Km_M(Memoria* m, int primeiro_valor);
void Converter_Km_Cm(Memoria* m, int primeiro_valor);

//temperatura -2
void Kelvin_Celsius(Memoria* m, int primeiro_valor);
void Celsius_Kelvin(Memoria* m, int primeiro_valor);
