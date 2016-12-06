#include <stdio.h>
#include <string.h>
#include "PlacardStructs.h"
#define _CRT_SECURE_NO_WARNINGS

/*TODO:
Acabar escolhemodalidade conforme os comments na funcao
*/


/*converte a string para o tipo modalidade | sera que isto e necessario?*/

void TestaFicheiro(char nomeficheiro[]) //testa se determinado ficheiro existe
{
	FILE *fd;
	fd = fopen(nomeficheiro, "r");
	if (fd == NULL)
	{
		printf("\nFICHEIRO %s NAO ENCONTRADO!", nomeficheiro);
	}
}
modalidade escolhemodalidade()
{
	FILE *fd;
	fd = fopen("modalidades.txt", "r");
	modalidade modaux;
	char modalidade_introduzida[20] = "";
	char opcao = 0;
	do
	{
		printf("MODALIDADE DA APOSTA:\n");
		printf("\t1- FUTEBOL\n");
		printf("\t2- BASQUETEBOL\n");
		printf("\t3- TENIS\n");
		printf("\t0- VOLTAR ATRAS\n");
		scanf("%c", opcao);
		switch (opcao)
		{
		case 1:
			*modalidade_introduzida = "FUTEBOL";
			break;
		case 2:
			*modalidade_introduzida = "BASQUETEBOL";
			break;
		case 3:
			*modalidade_introduzida = "TENIS";
			break;
		default:
			printf("SELECIONE UMA DAS OPCOES!");
			break;
		}
	} while ((fscanf("%s\n", modaux.nome) != EOF) && (!strcmp(modalidade_introduzida, modaux.nome) && opcao != 0));

	return modaux;
	fclose(fd);
}

void criajogo(modalidade mod, clube casa, clube fora)
{
	FILE *fd;
	clube aux1, aux2;
	//para o futebol e basquetebol assumi que funciona como na realidade, 2 equipas so podem jogar 2 vezes numa temporada, uma x na casa de cada 1
	if (mod.nome == "FUTEBOL")
	{
		fd = fopen("jogosfutebol.txt", "a");

		if (fd == NULL)
		{
			printf("\nFICHEIRO NAO ENCONTRADO!");
		}
		else
		{
			while (fscanf("%s - %s\n", aux1.nome, aux2.nome) != EOF)
			{
				if (strcmp(aux1.nome, casa.nome) && strcmp(aux2.nome, fora.nome))
				{
					printf("AS DUAS EQUIPAS JÁ JOGARAM EM CASA DO %S", casa.nome);
				}
				else
				{
					fprintf(fd, "%s - %s\n", casa.nome, fora.nome);
				}
			}
		}
	}

	if (mod.nome == "BASQUETEBOL")
	{
		fd = fopen("jogosbasquetebol.txt", "a");

		if (fd == NULL)
		{
			printf("\nFICHEIRO NAO ENCONTRADO!");
		}
		else
		{
			while (fscanf("%s - %s\n", aux1.nome, aux2.nome) != EOF)
			{
				if (strcmp(aux1.nome, casa.nome) && strcmp(aux2.nome, fora.nome))
				{
					printf("AS DUAS EQUIPAS JÁ JOGARAM EM CASA DO %S", casa.nome);
				}
				else
				{
					fprintf(fd, "%s - %s\n", casa.nome, fora.nome);
				}
			}
		}

	}
	//para o tenis assumi que podes jogar varias vezes com a mesma pessoa (cria sempre o jogo)
	if (mod.nome == "TENIS")
	{
		fd = fopen("jogostenis.txt", "a");

		if (fd == NULL)
		{
			printf("\nFICHEIRO NAO ENCONTRADO!");
		}
		else
		{
			while (fscanf("%s - %s\n", aux1.nome, aux2.nome) != EOF)
			{
				fprintf(fd, "%s - %s\n", casa.nome, fora.nome);
			}
		}
	}
}

int main(void)
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