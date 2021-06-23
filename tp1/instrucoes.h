
# ifndef instrucoes_h
# define instrucoes_h

typedef struct memoria Memoria;

Memoria* montarRam();

void liberarMemoria(Memoria* memoria);
int* retornarRam(Memoria* memoria);

void maquina(Memoria* memoria);

void menu(Memoria* memoria);

void programaAleatorio(Memoria* memoria);

void matBasica(Memoria* memoria);
void adicao(Memoria* memoria, int primeiroValor, int segundoValor );
void subtracao(Memoria* memoria, int primeiroValor, int segundoValor);
void multiplicacao(Memoria* memoria, int primeiroValor, int segundoValor );
void divisao(Memoria* memoria, int dividendo, int divisor);
void potencia(Memoria* memoria, int base, int potencia);
void porcentagem(Memoria* memoria, int primeiroValor, int segundoValor);

void delta(Memoria* memoria, int a, int b ,int c);
void volumeParalelepipedo(Memoria* memoria, int primeiroValor, int segundoValor, int terceiroValor);
void volumeCilindro(Memoria* memoria, int abase, int altura);
void volumeEsfera(Memoria* memoria, int raio);
void volumeCubo(Memoria* memoria, int a);
void volumePiramide(Memoria* memoria, int abase, int altura);

void areaTriangulo(Memoria* memoria, int base, int altura);
void areaQuadrado(Memoria* memoria, int n);
void perimetroQuadrado(Memoria* memoria, int lado);
void perimetroRetangulo(Memoria* memoria, int primeiroValor, int segundoValor);

void PA(Memoria* memoria,  int primeiroValor, int segundoValor, int terceiroValor);
void PG(Memoria* memoria, int primeiroValor, int segundoValor, int razao);
void fatorial(Memoria* memoria, int n);
void permutacaoSimples(Memoria* memoria, int n);
void combinacao(Memoria* memoria, int primeiroValor, int segundoValor);
void arranjo(Memoria* memoria, int primeiroValor, int segundoValor);
void fibonnaci(Memoria* memoria, int n);
void IMC(Memoria* memoria, int peso, int altura);

void distanciaPercorrida(Memoria* memoria, int primeiroValor, int segundoValor);
void velocidadeMedia(Memoria* memoria, int dist1, int dist2, int t1, int t2);
void acelaracao(Memoria* memoria, int v1, int v2, int t1, int t2);
void forca(Memoria* memoria, int primeiroValor, int segundoValor);
void calorimetria(Memoria* memoria,  int primeiroValor, int segundoValor, int terceiroValor);

void convSegMin(Memoria* memoria, int n);
void convMinSeg(Memoria* memoria, int n);
void convMinHr(Memoria* memoria, int n);
void convHrMin(Memoria* memoria, int n);
void convHrSeg(Memoria* memoria, int n);
void convCm_M(Memoria* memoria, int n);
void convM_Cm(Memoria* memoria, int n);
void KelvinCelsius(Memoria* memoria, int n);
void CelsiusKelvin(Memoria* memoria, int n);
void CelsiusFahrenheit(Memoria* memoria, int n);
void FahrenheitCelsius(Memoria* memoria, int n);


# endif