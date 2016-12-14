#include "PlacardStructs.h"

//PRONTAS
void AtribuiResultado(clube a, clube b)
{
	FILE *fd;
	clube aux1, aux2;
	int agolos, bgolos;

	fd = fopen("jogosfutebol.txt", "r");

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
int FicheiroExiste(char nomeficheiro[], FILE **fd) //testa se determinado ficheiro existe
{
	*fd = fopen(nomeficheiro, "r");

	if (*fd == NULL)
	{
		printf("\nFICHEIRO %s NAO ENCONTRADO!\n\n", nomeficheiro);
		return 0;
	}
	return 1;
}
void FicheiroImprimir(char nomeficheiro[])
{
	FILE *fd;
	char textoImprimir[60];
	fd = fopen(nomeficheiro, "r");
	for (int i = 0; i < FicheiroLinhas(nomeficheiro); i++)
	{
		fscanf(fd, "%s", textoImprimir);
		printf("\n %s \n", textoImprimir);
	}
}
void FicheiroLeModalidades(modalidade *mod)
{
	int numeroDeModalidades;
	FILE *fd;

	if (FicheiroExiste("modalidades.txt", &fd))
	{
		numeroDeModalidades = FicheiroLinhas("modalidades.txt");
		for (int i = 0; i < numeroDeModalidades; i++)
		{
			fscanf(fd, "%s", &mod[i].nome);
		}
	}
}
int FicheiroLinhas(char nomeficheiro[])
{
	FILE *fd;
	int linhas = 1, letra;

	fd = fopen(nomeficheiro, "r");

	do
	{
		letra = fgetc(fd);
		if (letra == '\n')
		{
			linhas++;
		}
	} while (letra != EOF);
	fclose(fd);
	return linhas;
}
void ListarTudo()
{
	char opcao = 0, ficheiroAbrir[60], textoImprimir[60];
	
	do
	{
		printf("-----------------------\n");
		printf("\t1- LISTAR MODALIDADES.\n");
		printf("\t2- LISTAR JOGOS.\n");
		printf("\t3- LISTAR RESULTADOS.\n");
		printf("\t0- SAIR.\n");
		printf("OPCAO: ");
		scanf("%c", &opcao);
		while (getchar() != '\n');

		switch (opcao)
		{
		case '1':
			FicheiroImprimir("modalidades.txt");
			break;
		case '2':
			FicheiroImprimir("jogos.txt");
			break;
		case '3':
			FicheiroImprimir("resultados.txt");
			break;
		case '0':
			break;
		default:
			printf("\nALGO DEU ERRO. \n");
			break;
		}
	} while (opcao != '0');
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



//A PERCISAR DE REWORK

modalidade EscolheModalidade(modalidade *mod)
{
	char modalidade_introduzida[20] = "", opcao = 0;
	modalidade modaux;
	FILE *fd;

	if (FicheiroExiste("modalidades.txt", &fd))
	{
		do
		{
			printf("-----------------------\n");
			printf("MODALIDADE DA APOSTA:\n");

			// LOOP QUE IMPRIME TODAS AS MODALIDADES APARTIR DO FICHEIRO
			for (int i = 0; i < FicheiroLinhas("modalidades.txt"); i++)
			{
				printf("\t%d- %s\n", i + 1, mod[i].nome);
			}

			printf("\t0- VOLTAR ATRAS\n");
			printf("OPCAO: ");
			scanf("%c", &opcao);
			while (getchar() != '\n');


			// USAR UM LOOP PARA IMPRIMIR TODOS AS MODALIDADES
			switch (opcao)
			{
			case '1':
				strcpy(modalidade_introduzida, "FUTEBOL");
				break;
			case '2':
				strcpy(modalidade_introduzida, "BASQUETEBOL");
				break;
			case '3':
				strcpy(modalidade_introduzida, "TENIS");
				break;
			case '0':
				break;
			default:
				printf("\nERRO: SELECIONE UMA DAS OPCOES!\n");
				break;
			}
			for (int i = 0; i < FicheiroLinhas("modalidades.txt"); i++)
			{

			}
		} while (opcao != '0' && (fscanf(fd, "%s\n", &modaux.nome) != EOF) && (strcmp(modalidade_introduzida, modaux.nome) != 0));
		fclose(fd);
	}
	return modaux;
}
void CriaJogo(modalidade mod, clube casa, clube fora) //tera de ser alterado para cada evento ter 1 ficheiro de jogos.
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
			while (fscanf(fd, "%s - %s\n", aux1.nome, aux2.nome) != EOF)
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