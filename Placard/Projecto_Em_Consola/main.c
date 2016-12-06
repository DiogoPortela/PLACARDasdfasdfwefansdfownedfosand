#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "PlacardStructs.h"
#include "PlacardFunctions.h"


int ValorRandomComBaseNaProb(clube a, int max)
{
	srand(time(NULL));
	int pontos = 0;
	for (int i = 0; i < max; i++)
	{
		pontos += rand() < a.probabilidade * ((float)RAND_MAX + 1.0);
		printf("%d\n", pontos);
	}
	return pontos;
}

int ResultadoRandom(clube a, int max)
{
	srand(time(NULL));
	int pontos = 0;
	for (int i = 0; i < max; i++)
	{
		pontos += rand() % 2;
		printf("%d\n", pontos);
	}
	return pontos;
}



int main(void) //Menu
{
	char tecla_menu = 0;
	modalidade modaux;
	int pontos, pontos2;
	clube x;
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
		case 1:	
			*x.nome = "BENFICA";
			x.probabilidade = 0.7;
			pontos = ResultadoRandom(x, 10);
			pontos2 = ValorRandomComBaseNaProb(x, 10);
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