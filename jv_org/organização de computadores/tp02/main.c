#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include"funcoes.h"

int main() {
	Memoria *m;
	m =  Alocar_Memoria();
	Menu (m);
	Free (m);
	return 0;
}
