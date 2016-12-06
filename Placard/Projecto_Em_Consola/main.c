#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "PlacardStructs.h"
#include "PlacardFunctions.h"


float ValorRandomComBaseNaProb(double probabilidade)
{
	int maxrand = 10;
	return (rand() / (double)maxrand) < probabilidade;
}

void ResultadoRandom(clube a, clube b)
{
	
}




int main(void) //Menu
{
	int tecla_menu, nrmod;
	char mod[20];
	do
	{
		printf("OPCAO:\n");
		printf("\t1- VER O SEU SALDO\n");
		printf("\t2- JOGAR\n");
		printf("\t3- LISTAR\n");
		printf("\t4- ALTERAR DEFINICOES\n");
		printf("\t5- GRAVAR\n");
		printf("\t0- SAIR\n");
		scanf("%d", tecla_menu);

		switch (tecla_menu)
		{
		case 1:	//esta no sitio do saldo temporariamente para ser mais facil de testar
				//sera posto na parte do codigo em que o utilizador insere a modalidade da aposta
				//em principio sera na opcao 2 e 3, onde me parece que sera preciso pedir a mod ao utilizador
			escolhemodalidade();
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		default:
			break;
		}
	} while (tecla_menu != 0);
	return 0;
}