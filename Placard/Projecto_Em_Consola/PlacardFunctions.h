#include "PlacardStructs.h"

//PRONTAS
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
	char modalidade_introduzida[20] = "", opcao = 0;
	modalidade modaux;
	FILE *fd;

	fd = fopen("modalidades.txt", "r");

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





//A PERCISAR DE REWORK
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