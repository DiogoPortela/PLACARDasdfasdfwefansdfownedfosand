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
	char tecla_menu = 0;
	modalidade modaux;
	do
	{
		printf("1- VER O SEU SALDO\n");
		printf("2- JOGAR\n");
		printf("3- LISTAR\n");
		printf("4- ALTERAR DEFINICOES\n");
		printf("5- GRAVAR\n");
		printf("0- SAIR\n\n");
		printf("OPCAO: ");
		scanf("%d", &tecla_menu);

		switch (tecla_menu)
		{
		case 1:	//esta no sitio do saldo temporariamente para ser mais facil de testar
				//sera posto na parte do codigo em que o utilizador insere a modalidade da aposta
				//em principio sera na opcao 2 e 3, onde me parece que sera preciso pedir a mod ao utilizador			
			break;
		case 2:
			modaux = escolhemodalidade();
			break;
		case 3:
			modaux = escolhemodalidade();
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