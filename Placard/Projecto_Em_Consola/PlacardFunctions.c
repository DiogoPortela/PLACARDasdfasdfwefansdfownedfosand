#include "PlacardStructs.h"

//PRONTAS
void AtribuiResultado(modalidade m, int a, int b)
{
	FILE *fread;
	fread = fopen("jogos.txt", "r");
	FILE *fwrite;
	fwrite = fopen("resultados.txt", "a");
	int apontos, bpontos;
	clube aux1, aux2;

	while (fscanf(fread, "%*d- %s - %s\n", aux1.nome, aux2.nome) != EOF)
	{
		if (!strcmp(aux1.nome, m.clube[a].nome) && !strcmp(aux2.nome, m.clube[b].nome))
		{
			srand(time(NULL));
			apontos = ResultadoRandom(m.clube[a], m.maxpts);
			bpontos = ResultadoRandom(m.clube[b], m.maxpts);
			fprintf(fwrite, "%d- %s %d - %d %s\n", m.identificador, m.clube[a].nome, apontos, bpontos, m.clube[b].nome);
		}
	}
	fclose(fread); fclose(fwrite);
}
modalidade EscolheModalidade(modalidade *mod)
{
	char modalidade_introduzida[20] = "";
	int opcao = 0;
	modalidade modaux;
	FILE *fd;

	if (FicheiroExiste("modalidades.txt", &fd))
	{

		printf("-----------------------\n");
		printf("MODALIDADE DA APOSTA:\n");

		// LOOP QUE IMPRIME TODAS AS MODALIDADES APARTIR DO FICHEIRO

		int a = FicheiroLinhas("modalidades.txt");
		for (int i = 0; i < FicheiroLinhas("modalidades.txt"); i++)
		{
			printf("\t%d- %s\n", i + 1, mod[i].nome);
		}

		printf("\t0- VOLTAR ATRAS\n");
		printf("OPCAO: ");
		scanf("%d", &opcao);
		while (getchar() != '\n');

		// USAR UM LOOP PARA IMPRIMIR TODOS AS MODALIDADES

		FILE *fd;
		fd = fopen("modalidades.txt", "r");
		for (int i = 1; i <= FicheiroLinhas("modalidades.txt"); i++)
		{
			char aux[60];
			fscanf(fd, "%s", aux);
			if (opcao == i)
			{
				strcpy(modaux.nome, aux);
			}
		}
		fclose(fd);
	}
	return modaux;
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
	int pontos = 0;
	for (int i = 0; i < max; i++)
	{
		pontos += rand() < a.probabilidade * ((float)RAND_MAX + 1.0);
		printf("%d\n", pontos);
	}
	return pontos;
}



//A PRECISAR DE REWORK
void CriaJogo(modalidade mod, int a, int b)
{
	FILE *fread;
	fread = fopen("clubes.txt", "r");
	FILE *fwrite;
	fwrite = fopen("jogos.txt", "a");
	clube aux1, aux2;
	int idaux = 0;
	//para o futebol e basquetebol assumi que funciona como na realidade, 2 equipas so podem jogar 2 vezes numa temporada, uma x na casa de cada 1
	if (FicheiroExiste("clubes.txt", &fread) && FicheiroExiste("jogos.txt", &fwrite))
	{
		if (mod.nome != "TENIS")
		{
			while (fscanf(fwrite, "%d- %s - %s\n", idaux, aux1.nome, aux2.nome) != EOF)
			{
				if (idaux == mod.identificador && strcmp(aux1.nome, mod.clube[a].nome) && strcmp(aux2.nome, mod.clube[b].nome))
				{
					printf("AS DUAS EQUIPAS JÁ JOGARAM EM CASA DO %s", mod.clube[a].nome);
				}
				else
				{
					fprintf(fwrite, "%d- %s - %s\n", mod.identificador, mod.clube[a].nome, mod.clube[b].nome);
				}
			}
		}
		//para o tenis assumi que podes jogar varias vezes com a mesma pessoa (cria sempre o jogo)
		else
		{
			fprintf(fwrite, "%d- %s - %s\n", mod.identificador, mod.clube[a].nome, mod.clube[b].nome);
		}
	}
	fclose(fread); fclose(fwrite);
}

