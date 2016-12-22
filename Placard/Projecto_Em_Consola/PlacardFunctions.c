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
			apontos = ResultadoRandom(m.clube[a], m.maxpts);
			bpontos = ResultadoRandom(m.clube[b], m.maxpts);
			fprintf(fwrite, "%d- %s %d - %d %s\n", m.identificador + 1, m.clube[a].nome, apontos, bpontos, m.clube[b].nome);
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
	*fd = fopen(nomeficheiro, "a+");

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
	int numeroDeLinhas;
	FILE *fmodalidades, *fclubes;

	if (FicheiroExiste("modalidades.txt", &fmodalidades))
	{
		numeroDeLinhas = FicheiroLinhas("modalidades.txt");
		for (int i = 0; i < numeroDeLinhas; i++)
		{
			fscanf(fmodalidades, "%s", &mod[i].nome);
			mod[i].identificador = i;
		}
	}
	if (FicheiroExiste("clubes.txt", &fclubes))
	{
		int idaux = 0, contadorModalidades[60] = { 0 };
		char aux[100];
		numeroDeLinhas = FicheiroLinhas("clubes.txt");
		for (int j = 0; j <= numeroDeLinhas; j++)
		{
			fscanf(fclubes, "%d- %s", &idaux, aux);
			strcpy(mod[idaux - 1].clube[contadorModalidades[idaux - 1]].nome, aux);
			contadorModalidades[idaux - 1]++;
		}
	}
	fclose(fmodalidades); fclose(fclubes);
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
	}
	return pontos;
}
int SeedAleatoria()
{
	int seed = 0;
	srand(time(NULL));
	seed += rand() % 99999999999;
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
int ExisteFicheiro(char nome[])
{
	FILE* fp = fopen(nome, "r");
	if (fp == NULL) return 0;
	fclose(fp);
	return 1;
}


//A PRECISAR DE REWORK
void CriaJogo(modalidade mod, int a, int b)
{
	FILE *fwrite;
	clube aux1, aux2;
	int idaux = 0;
	char *dividestr = "";
	char buffer[62], str1[2], str2[30], str3[30];
	//para o futebol e basquetebol assumi que funciona como na realidade, 2 equipas so podem jogar 2 vezes numa temporada, uma x na casa de cada 1
	if (ExisteFicheiro("clubes.txt") && ExisteFicheiro("jogos.txt"))
	{
		fwrite = fopen("jogos.txt", "a+");

		if (mod.nome != "TENIS")
		{
			//fgets(buffer, sizeof(buffer), fwrite);

			if (feof(fwrite))
			{
				fprintf(fwrite, "%d- %s - %s\n", mod.identificador + 1, mod.clube[a].nome, mod.clube[b].nome);
			}
			else
			{
				fclose(fwrite);
				fwrite = fopen("jogos.txt", "a+");
				while (fgets(buffer, sizeof(buffer), fwrite) != NULL)
				{
					dividestr = _strdup(buffer);
					dividestr = strtok(dividestr, "- \n");
					strcpy(str1, dividestr);
					dividestr = _strdup(buffer);
					dividestr = strtok(NULL, "- \n");
					strcpy(str2, dividestr);
					dividestr = strtok(NULL, "- \n");
					strcpy(str3, dividestr);

					if (atoi(str1) == mod.identificador + 1 && strcmp(str2, mod.clube[a].nome) == 0 && strcmp(str3, mod.clube[b].nome) == 0)
					{
						printf("AS DUAS EQUIPAS JÁ JOGARAM EM CASA DO %s\n", mod.clube[a].nome);
						break;
					}
					else
					{
						fprintf(fwrite, "%d- %s - %s\n", mod.identificador + 1, mod.clube[a].nome, mod.clube[b].nome);
					}
				}
			}
		}
		//para o tenis assumi que podes jogar varias vezes com a mesma pessoa (cria sempre o jogo)
		else
		{
			fprintf(fwrite, "%d- %s - %s\n", mod.identificador, mod.clube[a].nome, mod.clube[b].nome);
		}
		fclose(fwrite);
	}
}
int CalculaDifGolos(modalidade m, int a)
{
	FILE *fresultados;
	fresultados = fopen("resultados.txt", "r");
	char *dividestr = "";
	char buffer[66], str1[2], str2[30], str3[2], str4[2], str5[30];
	int golosmarcados = 0, golossofridos = 0, tmp;

	if (ExisteFicheiro("resultados.txt"))
	{
		while (fgets(buffer, sizeof(buffer), fresultados) != NULL)
		{
			if (strstr(buffer, m.clube[a].nome) != NULL)
			{
				dividestr = _strdup(buffer);
				dividestr = strtok(dividestr, "- \n");
				strcpy(str1, dividestr);
				//dividestr = _strdup(buffer);
				dividestr = strtok(NULL, "- \n");
				strcpy(str2, dividestr);
				dividestr = strtok(NULL, "- \n");
				strcpy(str3, dividestr);
				dividestr = strtok(NULL, "- \n");
				strcpy(str4, dividestr);
				dividestr = strtok(NULL, "- \n");
				strcpy(str5, dividestr);
				if (strcmp(str2,m.clube[a].nome) == 0)
				{
					tmp = atoi(str3);
					golosmarcados += tmp;
					tmp = atoi(str4);
					golossofridos += tmp;
				}
				else
				{
					tmp = atoi(str4);
					golosmarcados += tmp;
					tmp = atoi(str3);
					golossofridos += tmp;
				}
			}
		}
		fclose(fresultados);
	}
	return golosmarcados - golossofridos;
}


