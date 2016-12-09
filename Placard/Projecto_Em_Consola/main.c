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

void AtribuiResultado(clube a, clube b)
{
	FILE *fd;
	fd = fopen("jogosfutebol.txt", "r");

	clube aux1, aux2;
	int agolos, bgolos;
	while (fscanf("%s - %s\n", aux1.nome, aux2.nome) != EOF)
	{
		if (strcmp(aux1.nome, a.nome) && strcmp(aux2.nome, b.nome))
		{
			fclose(fd);
			fd = fopen("resultados.txt", "a");
			agolos = ResultadoRandom(a, 4);
			bgolos = ResultadoRandom(a, 4);
			fprintf("%s %d - %d %s", a.nome, agolos, bgolos, b.nome);

		}
	}


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


// DO WHILE (FAZER COMPARAÇOES DENTRO DO 'DO')
// opcao = getch(); adicionado;
// CUIDADO COM AS PLICAS