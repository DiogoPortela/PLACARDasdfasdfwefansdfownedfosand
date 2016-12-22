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
	char modalidade_introduzida[20] = { 0 }, charAux[20];
	int opcao = 0, intAux, numeroLinhas;
	modalidade modAux;
	FILE *fModalidades;

	if (FicheiroExiste("modalidades.txt", &fModalidades))
	{
		printf("-----------------------\n");
		printf("MODALIDADE DA APOSTA:\n");

		// LOOP QUE IMPRIME TODAS AS MODALIDADES APARTIR DO FICHEIRO
		numeroLinhas = FicheiroLinhas("modalidades.txt");
		for (intAux = 0; intAux < numeroLinhas; intAux++)
		{
			printf("\t%d- %s\n", intAux + 1, mod[intAux].nome);
		}

		printf("\t0- VOLTAR ATRAS\n");
		printf("OPCAO: ");
		scanf("%d", &opcao);
		while (getchar() != '\n');

		// USAR UM LOOP PARA IMPRIMIR TODOS AS MODALIDADES

		for (int i = 1; i <= numeroLinhas; i++)
		{
			fscanf(fModalidades, "%s", charAux);
			if (opcao == i)
			{
				strcpy(modAux.nome, charAux);
				break;
			}
		}
		fclose(fModalidades);
	}
	return modAux;
}
int FicheiroExiste(char nomeficheiro[], FILE **fd) //testa se determinado ficheiro existe
{
	*fd = fopen(nomeficheiro, "r+");

	if (*fd == NULL)
	{
		printf("\nFICHEIRO %s NAO ENCONTRADO!\n\n", nomeficheiro);
		return 0;
	}
	return 1;
}
void FicheiroImprimir(char nomeficheiro[])
{
	FILE *fAux;
	char charAux;
	int numeroLinhas = FicheiroLinhas(nomeficheiro);

	fAux = fopen(nomeficheiro, "r+");

	charAux = fgetc(fAux);
	while (charAux != EOF)
	{
		printf("%c", charAux);
		charAux = fgetc(fAux);
	}
	printf("\n");
	fclose(fAux);
}
void FicheiroLeModalidades(modalidade *mod)
{
	int numeroDeLinhas;
	FILE *fModalidades, *fClubes;

	if (FicheiroExiste("modalidades.txt", &fModalidades))
	{
		numeroDeLinhas = FicheiroLinhas("modalidades.txt");
		for (int i = 0; i < numeroDeLinhas; i++)
		{
			fscanf(fModalidades, "%*d- %s", &mod[i].nome);
			mod[i].identificador = i;
		}
		fclose(fModalidades);
	}
	if (FicheiroExiste("clubes.txt", &fClubes))
	{
		int idAux = 0, contadorModalidades[10] = { 0 };
		char charAux[100];
		numeroDeLinhas = FicheiroLinhas("clubes.txt");
		for (int j = 0; j <= numeroDeLinhas; j++)
		{
			fscanf(fClubes, "%d- %s", &idAux, charAux);
			strcpy(mod[idAux - 1].clube[contadorModalidades[idAux - 1]].nome, charAux);
			contadorModalidades[idAux - 1]++;
		}
		fclose(fClubes);
	}
}
int FicheiroLinhas(char nomeficheiro[])
{
	FILE *fAux;
	int linhas = 1, letra;

	fAux = fopen(nomeficheiro, "r+");
	letra = fgetc(fAux);

	if (letra != EOF)
	{
		do
		{
			if (letra == '\n')
			{
				linhas++;
			}
			letra = fgetc(fAux);
		} while (letra != EOF);
	}
	else
	{
		linhas = 0;
	}
	fclose(fAux);
	return linhas;
}
void ListarTudo()
{
	char opcao = 0;

	do
	{
		printf("-----------------------\n");
		printf("\t1- LISTAR MODALIDADES.\n");
		printf("\t2- LISTAR JOGOS.\n");
		printf("\t3- LISTAR RESULTADOS.\n");
		printf("\t0- SAIR.\n");
		printf("OPCAO: ");
		scanf("%c", &opcao);
		printf("\n");
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
void GerirSaldo(int *saldo)
{
	FILE *fSaldo;
	if (FicheiroExiste("saldo.txt", &fSaldo))
	{
		fprintf(fSaldo, "%d", -1);
		fscanf(fSaldo, "%d", saldo);
		if (saldo < 0)
		{
			printf("Introduza um valor inicial: ");
			scanf("%d", saldo);
		}
		printf("O seu salto actual: %d\n", saldo);
		fclose(fSaldo);
	}
}
void CriaJogo(modalidade mod, int a, int b)
{
	FILE *fJogosLeitura, *fJogosEscrita;
	clube clubAux1, clubAux2;
	int idAux = 0;

	//para o futebol e basquetebol assumi que funciona como na realidade, 2 equipas so podem jogar 2 vezes numa temporada, uma x na casa de cada 1
	if (FicheiroExiste("jogos.txt", &fJogosLeitura))
	{
		fJogosEscrita = fopen("jogos.txt", "a+");

		if (mod.nome != "TENIS")
		{

			if (fgetc(fJogosLeitura) == -1)
			{
				fprintf(fJogosEscrita, "%d- %s - %s\n", mod.identificador + 1, mod.clube[a].nome, mod.clube[b].nome);
			}
			else
			{
				while (fgetc(fJogosLeitura) != -1)
				{
					fscanf(fJogosLeitura, "%d- %s - %s", &idAux, clubAux1.nome, clubAux2.nome);
					if (idAux == mod.identificador + 1 && strcmp(clubAux1.nome, mod.clube[a].nome) == 0 && strcmp(clubAux2.nome, mod.clube[b].nome) == 0)
					{
						printf("AS DUAS EQUIPAS J� JOGARAM EM CASA DO %s\n", mod.clube[a].nome);
						break;
					}
					else
					{
						fprintf(fJogosEscrita, "%d- %s - %s\n", mod.identificador + 1, mod.clube[a].nome, mod.clube[b].nome);
						break;
					}
				}				
			}
		}
		//para o tenis assumi que podes jogar varias vezes com a mesma pessoa (cria sempre o jogo)
		else
		{
			fprintf(fJogosEscrita, "%d- %s - %s\n", mod.identificador, mod.clube[a].nome, mod.clube[b].nome);
		}
		fclose(fJogosEscrita);
		fclose(fJogosLeitura);
	}
}
int CalculaDifGolos(modalidade m, int a)
{
	FILE *fresultados;
	//fresultados = fopen("resultados.txt", "r");
	char *dividestr;
	char buffer[66], str1[2], str2[30], str3[2], str4[2], str5[30];
	int golosmarcados = 0, golossofridos = 0, tmp;

	if (ExisteFicheiro("resultados.txt"))
	{
		while (fgets(buffer, sizeof(buffer), &fresultados) != NULL)
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
				if (strcmp(str2, m.clube[a].nome) == 0)
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


