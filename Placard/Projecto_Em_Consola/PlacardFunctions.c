#include "PlacardStructs.h"

//PRONTAS
void LimpaEcra(void)
{
	printf("\nCARREGUE QUALQUER TECLA PARA CONTINUAR...");
	getch();
	system("cls");
}

void AtribuiResultado(modalidade m, int a, int b)
{
	FILE *fResultados, *fJogos;
	int apontos, bpontos;
	clube aux1, aux2;

	if (FicheiroExiste("jogos.txt", &fJogos) && FicheiroExiste("resultados.txt", &fResultados))
	{
		while (fscanf(fJogos, "%*d- %s - %s\n", aux1.nome, aux2.nome) != EOF)
		{
			if (!strcmp(aux1.nome, m.listaClubes[a].nome) && !strcmp(aux2.nome, m.listaClubes[b].nome))
			{
				apontos = ResultadoRandom(m.listaClubes[a], m.maxpts);
				bpontos = ResultadoRandom(m.listaClubes[b], m.maxpts);
				fprintf(fResultados, "%d- %s %d - %d %s\n", m.identificador + 1, m.listaClubes[a].nome, apontos, bpontos, m.listaClubes[b].nome);
			}
		}
		fclose(fJogos);
		fclose(fResultados);
	}
}
modalidade EscolheModalidade(modalidade *mod)
{
	char modalidade_introduzida[20] = { 0 }, charAux[20] = { 0 }, flag = 0;
	int opcao = 0, intAux, numeroLinhas;
	modalidade modAux;
	FILE *fModalidades;

	if (FicheiroExiste("modalidades.txt", &fModalidades))
	{
		do
		{
			system("cls");
			printf("MODALIDADE DA APOSTA:\n");

			// LOOP QUE IMPRIME TODAS AS MODALIDADES APARTIR DO FICHEIRO
			numeroLinhas = FicheiroLinhas("modalidades.txt");
			for (intAux = 0; intAux < numeroLinhas; intAux++)
			{
				printf("\t%d- %s \n", intAux + 1, mod[intAux].nome);
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
					flag = 1;
					break;
				}
			}
		} while (opcao != 0 && flag == 0);
		fclose(fModalidades);
	}
	LimpaEcra();
	return modAux;
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
	FILE *fAux;
	char charAux;
	int numeroLinhas = FicheiroLinhas(nomeficheiro);

	fAux = fopen(nomeficheiro, "r+");

	charAux = fgetc(fAux);
	printf("\n");
	while (charAux != EOF)
	{
		printf("%c", charAux);
		charAux = fgetc(fAux);
	}
	printf("\n");
	fclose(fAux);
}
void FicheiroLeData(modalidade *mod)
{
	int numeroDeLinhas, i, idAux = 0;
	char charAux[100], charAux2[100];
	FILE *fModalidades, *fClubes, *fJogos;

	if (FicheiroExiste("modalidades.txt", &fModalidades))
	{
		numeroDeLinhas = FicheiroLinhas("modalidades.txt");
		for (int i = 0; i < numeroDeLinhas; i++)
		{
			fscanf(fModalidades, "%*d- %s %d", &mod[i].nome, &mod[i].maxpts);
			mod[i].identificador = i;
		}
		fclose(fModalidades);
	}
	if (FicheiroExiste("clubes.txt", &fClubes))
	{
		int contadorModalidades[10] = { 0 };

		numeroDeLinhas = FicheiroLinhas("clubes.txt");

		for (i = 1; i <= numeroDeLinhas - 1; i++)
		{
			fscanf(fClubes, "%d- %s", &idAux, charAux);
			strcpy(mod[idAux - 1].listaClubes[contadorModalidades[idAux - 1]].nome, charAux);
			contadorModalidades[idAux - 1]++;
		}
		fclose(fClubes);
	}
	if (FicheiroExiste("jogos.txt", &fJogos))
	{
		int aux = numeroDeLinhas;
		numeroDeLinhas = FicheiroLinhas("jogos.txt");
		for (i = 0; i < numeroDeLinhas - 1; i++)
		{
			fscanf(fJogos, "%d- %s - %s", &idAux, charAux, charAux2);
			idAux--;
			//jogos[i].mod = mod[idAux];
			for (int j = 0; j < aux; j++)
			{
				if (!strcmp(charAux, mod[idAux].listaClubes[j].nome))
				{
					mod[idAux].listaJogos[i].casa = mod[idAux].listaClubes[j];
					//jogos[i].casa = mod[idAux].listaClubes[j];
				}
				if (!strcmp(charAux2, mod[idAux].listaClubes[j].nome))
				{
					mod[idAux].listaJogos[i].visitante = mod[idAux].listaClubes[j];
					//jogos[i].visitante = mod[idAux].listaClubes[j];
				}
			}

		}
		fclose(fJogos);
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
void GerirSaldo(int *saldo)
{
	FILE *fSaldoLeitura, *fSaldoEscrita;
	if (FicheiroExiste("saldo.txt", &fSaldoLeitura))
	{
		if (getc(fSaldoLeitura) == -1)
		{
			fSaldoEscrita = fopen("saldo.txt", "w");
			printf("\nINTRODUZA UM VALOR INICIAL: ");
			scanf("%d", saldo);
			while (getchar() != '\n');
			fprintf(fSaldoEscrita, "%d", *saldo);
			fclose(fSaldoEscrita);
		}
		rewind(fSaldoLeitura);
		fscanf(fSaldoLeitura, "%d", saldo);
		printf("\nO SEU SALDO ACTUAL: %d\n", *saldo);
		fclose(fSaldoLeitura);
	}
}
void ListarTudo()
{
	char opcao = 0;
	system("cls");
	do
	{
		printf("\t1- LISTAR MODALIDADES.\n");
		printf("\t2- LISTAR CLUBES.\n");
		printf("\t3- LISTAR JOGOS.\n");
		printf("\t4- LISTAR RESULTADOS.\n");
		printf("\t0- SAIR.\n");
		printf("OPCAO: ");
		scanf("%c", &opcao);
		while (getchar() != '\n');

		switch (opcao)
		{
		case '1':
			FicheiroImprimir("modalidades.txt");
			LimpaEcra();
			break;
		case'2':
			FicheiroImprimir("clubes.txt");
			LimpaEcra();
			break;
		case '3':
			FicheiroImprimir("jogos.txt");
			LimpaEcra();
			break;
		case '4':
			FicheiroImprimir("resultados.txt");
			LimpaEcra();
			break;
		case '0':
			break;
		default:
			printf("INTRODUZ UM VALOR VALIDO.\n");
			LimpaEcra();
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
int SeedAleatoria(void)
{
	int seed = 0;
	srand(time(NULL));
	seed += rand() % 9999999999999999999;
}
int ValorRandomComBaseNaProb(clube a, int max)
{
	int pontos = 0;
	for (int i = 0; i < max; i++)
	{
		pontos += rand() < a.probabilidade * ((float)RAND_MAX + 1.0);
	}
	return pontos;
}

//A PRECISAR DE REWORK
void Definicoes(modalidade *mod)
{
	char input, input2;
	system("cls");
	do
	{
		printf("\t1- ALTERAR MODALIDADES\n\t2- ALTERAR CLUBES\n\t3- ALTERAR COTAS\n\t0- SAIR\n\nOPCAO: ");
		scanf("%c", &input);
		while (getchar() != '\n');
		switch (input)
		{
		case '1':
		{
			//Criar e editar modalidade

			int numeroLinhas, intAux;
			FILE *fModalidades;
			modalidade a;
			do
			{
				system("cls");
				printf("\t\t1- CRIAR MODALIDADE\n\t\t2- ALTERAR MODALIDADE\n\t\t3- ELIMINAR MODALIDADE\n\t\t0- CANCELAR\nOPCAO: ");
				scanf("%c", &input2);
				while (getchar() != '\n');
				switch (input2)
				{
				case '1':
					fModalidades = fopen("modalidades.txt", "a+");
					if (mod[9].identificador < 0)
					{
						printf("\nINTRODUZA O NOME DA NOVA MODALIDADE: ");
						scanf("%s", a.nome);
						while (getchar() != '\n');
						printf("INTRODUZA O NUMERO MAXIMO DE PONTOS: ");
						scanf("%d", &a.maxpts);
						while (getchar() != '\n');
						for (int i = 0; i < 10; i++)
						{
							if (mod[i].identificador < 0)
							{
								a.identificador = i;
								mod[i] = a;
								fprintf(fModalidades, "\n%d- %s %d", a.identificador + 1, a.nome, a.maxpts);
								break;
							}
						}
					}
					else
					{
						printf("\nNAO E POSSIVEL CRIAR MAIS MODALIDADES\n");
					}

					fclose(fModalidades);
					LimpaEcra();
					break;

				case '2':
					//Alterar modalidade
					fModalidades = fopen("modalidades.txt", "a+");
					numeroLinhas = FicheiroLinhas("modalidades.txt");

					printf("\n");
					for (int i = 0; i < numeroLinhas; i++)
					{
						printf("%d- %s %d\n", i + 1, mod[i].nome, mod[i].maxpts);
					}
					printf("0- CANCELAR\n\nOPCAO: ");
					scanf("%d", &intAux);
					while (getchar() != '\n');

					if (intAux != 0 && intAux <= numeroLinhas)
					{
						printf("INTRODUZA O NOVO NOME DA MODALIDADE: ");
						scanf("%s", mod[intAux - 1].nome);
						while (getchar() != '\n');
						printf("INTRODUZA O NOVO NUMERO MAXIMO DE PONTOS: ");
						scanf("%d", &mod[intAux - 1].maxpts);
						while (getchar() != '\n');

						fclose(fModalidades);
						fModalidades = fopen("modalidades.txt", "w");
						fprintf(fModalidades, "%d- %s %d", 0, mod[0].nome, mod[0].maxpts);
						for (int j = 1; j < numeroLinhas; j++)
						{
							fprintf(fModalidades, "\n%d- %s %d", j, mod[j].nome, mod[j].maxpts);
						}
					}

					fclose(fModalidades);
					LimpaEcra();
					break;

				case '3':
				{
					//Eliminar Modalidade
					//Imprimir todas a modalidades e ler input

					fModalidades = fopen("modalidades.txt", "a+");
					numeroLinhas = FicheiroLinhas("modalidades.txt");

					printf("\n");
					for (int i = 0; i < numeroLinhas; i++)
					{
						printf("%d- %s %d\n", i + 1, mod[i].nome, mod[i].maxpts);
					}
					printf("0- CANCELAR\n\nOPCAO: ");
					scanf("%d", &intAux);
					while (getchar() != '\n');

					//Confirmar se deseja apagar e puxar tudo 1 para cima.
					if (intAux <= numeroLinhas && intAux != 0)
					{
						do
						{
							printf("\nPRETENDE ELIMINAR A OPCAO %d? (Y/N)", intAux);
							scanf("%c", &input2);
							while (getchar() != '\n');

							if (toupper(input2) == 'Y')
							{
								fclose(fModalidades);
								fModalidades = fopen("modalidades.txt", "w");

								for (int j = 0; j < numeroLinhas; j++)
								{
									if (j >= intAux - 1)
									{
										a = mod[j + 1];
										mod[j] = a;
									}
								}
								fprintf(fModalidades, "%d- %s %d", 0, mod[0].nome, mod[0].maxpts);
								for (int j = 1; j < numeroLinhas - 1; j++)
								{
									fprintf(fModalidades, "\n%d- %s %d", j, mod[j].nome, mod[j].maxpts);
								}
								break;
							}
							else if (toupper(input2) == 'N')
							{
								break;
							}
						} while (1);
					}
					fclose(fModalidades);
					LimpaEcra();
					break;
				}
				case '0':
					LimpaEcra();
					break;
				default:
					printf("INTRODUZA UM VALOR VALIDO.\n");
					LimpaEcra();
					break;
				}
			} while (input2 != '0');
			break;
		}
		case '2':
			//Criar e editar clubes (actualizar a lista de clubes com o criajogo)

			/*int contadorDaSeed = 0;
			int linhasFicheiro = FicheiroLinhas("clubes.txt");
			for (int i = 0; i < linhasFicheiro; i++)
			{
				for (int j = 0; j < linhasFicheiro; j++)
				{
					if (i != j)
					{
						srand(SeedAleatoria() + contadorDaSeed);
						//CriaJogo(modalidades[0], i, j);
						//AtribuiResultado(modalidades[0], i, j);
						contadorDaSeed++;
					}
				}
			}*/
			LimpaEcra();
			break;
		case '3':
			//Alterar Cotas
			LimpaEcra();
			break;
		case '0':
			break;
		default:
			printf("INTRODUZA UM VALOR VALIDO.\n");
			LimpaEcra();
			break;
		}

	} while (input != '0');
}
jogo EscolheJogo(modalidade *mod)
{
	//Trocar ordem dos elementos do array de jogos

	//Imprimir os 5 primeiros

	//Escolher 1.
}
void CriaJogo(modalidade *mod, int a, int b)
{
	FILE *fJogosLeitura, *fJogosEscrita;
	clube clubAux1, clubAux2;
	int idAux = 0;
	//para o futebol e basquetebol assumi que funciona como na realidade, 2 equipas so podem jogar 2 vezes numa temporada, uma x na casa de cada 1
	if (FicheiroExiste("jogos.txt", &fJogosLeitura))
	{
		fJogosEscrita = fopen("jogos.txt", "a+");

		if (mod[0].nome != "TENIS")
		{

			if (feof(fJogosLeitura))
			{
				fprintf(fJogosEscrita, "%d- %s - %s\n", mod[0].identificador + 1, mod[0].listaClubes[a].nome, mod[0].listaClubes[b].nome);
			}
			else
			{
				while (!feof(fJogosLeitura))
				{
					fscanf(fJogosLeitura, "%d- %s- %s", &idAux, clubAux1.nome, clubAux2.nome);
					if (idAux == mod[0].identificador + 1 && strcmp(clubAux1.nome, mod[0].listaClubes[a].nome) == 0 && strcmp(clubAux2.nome, mod[0].listaClubes[b].nome) == 0)
					{
						//ESTA PARTE DO CODIGO PODE SER REMOVIDA SE FIZERMOS A FUNÇÃO SÓ CORRER UMA VEZ.
						printf("AS DUAS EQUIPAS JA JOGARAM EM CASA DO %s\n", mod[0].listaClubes[a].nome);
						break;
					}
					else
					{
						fprintf(fJogosEscrita, "%d- %s - %s\n", mod[0].identificador + 1, mod[0].listaClubes[a].nome, mod[0].listaClubes[b].nome);
						break;
					}
				}
			}
		}
		//para o tenis assumi que podes jogar varias vezes com a mesma pessoa (cria sempre o jogo)
		else
		{
			fprintf(fJogosEscrita, "%d- %s - %s\n", mod[0].identificador, mod[0].listaClubes[a].nome, mod[0].listaClubes[b].nome);
		}
		fclose(fJogosEscrita);
		fclose(fJogosLeitura);
	}
}
int CalculaDifGolos(modalidade m, int a, int ultimos) //falta definir que e so para os ultimos 6 jogos (como eq limitamos que sao as ultimas 6 leituras no texto?)
{
	FILE *fResultados;
	//char *dividestr;
	//char buffer[66], str1[2], str2[30], str3[2], str4[2], str5[30];
	int golosMarcados = 0, golosSofridos = 0, numeroLinhas, numeroClube = 0, intAux1, intAux2;
	char nomeClube1[60], nomeClube2[60];

	if (FicheiroExiste("resultados.txt", &fResultados))
	{
		numeroLinhas = FicheiroLinhas("resultados.txt");
		rewind(fResultados);
		for (int i = 0; i < numeroLinhas; i++)
		{
			fscanf(fResultados, "%*d- %s %d - %d %s", nomeClube1, &intAux1, &intAux2, nomeClube2);
			if (!strcmp(nomeClube1, m.listaClubes[a].nome))
			{
				numeroClube++;
			}
			else if (!strcmp(nomeClube2, m.listaClubes[a].nome))
			{
				numeroClube++;
			}
		}

		if (ultimos == 0)
		{
			ultimos = numeroClube;
		}

		rewind(fResultados);
		numeroLinhas = FicheiroLinhas("resultados.txt");
		for (int i = 0; i < numeroLinhas; i++)
		{
			fscanf(fResultados, "%*d- %s %d - %d %s", nomeClube1, &intAux1, &intAux2, nomeClube2);
			if (!strcmp(nomeClube1, m.listaClubes[a].nome))
			{
				numeroClube--;
				if (numeroClube > ultimos)
				{
					golosMarcados += intAux1;
					golosSofridos += intAux2;
				}
			}
			else if (!strcmp(nomeClube2, m.listaClubes[a].nome))
			{
				numeroClube--;
				if (numeroClube > ultimos)
				{
					golosMarcados += intAux2;
					golosSofridos += intAux1;
				}
			}
		}
		/*while (fgets(buffer, sizeof(buffer), fresultados) != NULL)
		{
			if (strstr(buffer, m.listaClubes[a].nome) != NULL)
			{
				dividestr = _strdup(buffer);
				dividestr = strtok(dividestr, "- \n");
				strcpy(str1, dividestr);
				dividestr = strtok(NULL, "- \n");
				strcpy(str2, dividestr);
				dividestr = strtok(NULL, "- \n");
				strcpy(str3, dividestr);
				dividestr = strtok(NULL, "- \n");
				strcpy(str4, dividestr);
				dividestr = strtok(NULL, "- \n");
				strcpy(str5, dividestr);
				if (strcmp(str2, m.listaClubes[a].nome) == 0)
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
		}*/
		fclose(fResultados);
	}
	return golosMarcados - golosSofridos;
}
float CalculaMediaGolos(void)
{
	FILE *fResultados;
	//char *dividestr;
	//char buffer[66], str1[2], str2[30], str3[2], str4[2], str5[30];
	int golostotais = 0, intAux1, intAux2, numeroLinhas;

	if (FicheiroExiste("resultados.txt", &fResultados))
	{
		numeroLinhas = FicheiroLinhas("resultados.txt");
		rewind(fResultados);
		for (int i = 0; i < numeroLinhas; i++)
		{
			fscanf(fResultados, "%*d- %*s %d - %d %*s", &intAux1, &intAux2);
			golostotais += intAux1 + intAux2;
		}
		/*while (fgets(buffer, sizeof(buffer), fresultados) != NULL)
		{
			{
				dividestr = _strdup(buffer);
				dividestr = strtok(dividestr, "- \n");
				strcpy(str1, dividestr);
				dividestr = strtok(NULL, "- \n");
				strcpy(str2, dividestr);
				dividestr = strtok(NULL, "- \n");
				strcpy(str3, dividestr);
				dividestr = strtok(NULL, "- \n");
				strcpy(str4, dividestr);
				dividestr = strtok(NULL, "- \n");
				strcpy(str5, dividestr);

				tmp = atoi(str3) + atoi(str4);
				golostotais += tmp;
			}
		}*/

		fclose(fResultados);
		return ((float)golostotais / (float)numeroLinhas);
	}
}
