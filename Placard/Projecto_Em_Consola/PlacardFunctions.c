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
	char nomeFicheiroJogos[200], nomeFicheiroResultados[200];
	clube aux1, aux2;

	strcpy(nomeFicheiroJogos, m.nome);
	strcat(nomeFicheiroJogos, "-jogos.txt");
	strcpy(nomeFicheiroResultados, m.nome);
	strcat(nomeFicheiroResultados, "-resultados.txt");

	if (FicheiroExiste(nomeFicheiroJogos, &fJogos) && FicheiroExiste(nomeFicheiroResultados, &fResultados))
	{
		while (fscanf(fJogos, "%s - %s", aux1.nome, aux2.nome) != EOF)
		{
			if (!strcmp(aux1.nome, m.listaClubes[a].nome) && !strcmp(aux2.nome, m.listaClubes[b].nome))
			{
				apontos = ResultadoRandom(m.listaClubes[a], m.maxpts);
				bpontos = ResultadoRandom(m.listaClubes[b], m.maxpts);
				fprintf(fResultados, "%s %d - %d %s\n", m.listaClubes[a].nome, apontos, bpontos, m.listaClubes[b].nome);
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
void FicheiroLeData(modalidade *mod, int *quantidadeMods)
{
	int i, j, k, l;
	char charAux[100], charAux2[100];
	char nomeFicheiro[200];
	FILE *fModalidades, *fClubes, *fJogos;

	if (FicheiroExiste("modalidades.txt", &fModalidades))
	{
		*quantidadeMods = FicheiroLinhas("modalidades.txt");
		for (i = 0; i < *quantidadeMods; i++)
		{
			fscanf(fModalidades, "%s %d", &mod[i].nome, &mod[i].maxpts);
			strcpy(nomeFicheiro, mod[i].nome);
			strcat(nomeFicheiro, "-clubes.txt");
			if (FicheiroExiste(nomeFicheiro, &fClubes))
			{
				mod[i].listaClubesCount = FicheiroLinhas(nomeFicheiro);
				for (j = 0; j < mod[i].listaClubesCount; j++)
				{
					fscanf(fClubes, "%s", charAux);
					strcpy(mod[i].listaClubes[j].nome, charAux);
				}

				strcpy(nomeFicheiro, mod[i].nome);
				strcat(nomeFicheiro, "-jogos.txt");

				if (FicheiroExiste(nomeFicheiro, &fJogos))
				{
					mod[i].listaJogosCount = FicheiroLinhas(nomeFicheiro);
					for (k = 0; k < mod[i].listaJogosCount - 1; k++)
					{
						fscanf(fJogos, "%s - %s", charAux, charAux2);
						for (int l = 0; l < mod[i].listaClubesCount; l++)
						{
							if (!strcmp(charAux, mod[i].listaClubes[l].nome))
							{
								mod[i].listaJogos[k].casa = mod[i].listaClubes[l];
							}
							if (!strcmp(charAux2, mod[i].listaClubes[l].nome))
							{
								mod[i].listaJogos[k].visitante = mod[i].listaClubes[l];
							}
						}

					}
					fclose(fJogos);
				}
				fclose(fClubes);
			}
		}
		fclose(fModalidades);
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
/*int ValorRandomComBaseNaProb(clube a, int max)
{
	int pontos = 0;
	for (int i = 0; i < max; i++)
	{
		pontos += rand() < a.probabilidade * ((float)RAND_MAX + 1.0);
	}
	return pontos;
}*/
long factorial(int n)
{
	if (n == 0)
		return 1;
	else
		return(n * factorial(n - 1));
}
float regra3simples(float n, float a)
{
	float aux;
	aux = (a * 100) / n;
	return aux;
}
/*void InverteArray(jogo arr[])
{
	jogo temp;
	int inicio = 0, fim = sizeof(arr) / sizeof(int);
	while (fim > inicio)
	{
		temp = arr[inicio];
		arr[inicio] = arr[fim];
		arr[fim] = temp;
		inicio++;
		fim--;
	}
}*/

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
				printf("\t1- CRIAR MODALIDADE\n\t2- ALTERAR MODALIDADE\n\t3- ELIMINAR MODALIDADE\n\t0- CANCELAR\nOPCAO: ");
				scanf("%c", &input2);
				while (getchar() != '\n');
				switch (input2)
				{
				case '1':
					fModalidades = fopen("modalidades.txt", "a+");
					numeroLinhas = FicheiroLinhas("modalidades.txt");
					if (numeroLinhas < 10)
					{
						printf("\nINTRODUZA O NOME DA NOVA MODALIDADE: ");
						scanf("%s", a.nome);
						while (getchar() != '\n');
						printf("INTRODUZA O NUMERO MAXIMO DE PONTOS: ");
						scanf("%d", &a.maxpts);
						while (getchar() != '\n');
						mod[numeroLinhas + 1] = a;
						fprintf(fModalidades, "\n%s %d", a.nome, a.maxpts);
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
						fprintf(fModalidades, "%s %d", mod[0].nome, mod[0].maxpts);
						for (int i = 1; i < numeroLinhas; i++)
						{
							fprintf(fModalidades, "\n%s %d", mod[i].nome, mod[i].maxpts);
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
								fprintf(fModalidades, " %s %d", mod[0].nome, mod[0].maxpts);
								for (int j = 1; j < numeroLinhas - 1; j++)
								{
									fprintf(fModalidades, "\n%s %d", mod[j].nome, mod[j].maxpts);
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
	int opcao, aux1 = 1, seed, guarda = 0, teste;
	jogo um, dois, tres, quatro, cinco;
	do
	{
		seed = SeedAleatoria();
		srand(seed);
		teste = sizeof(mod[0].listaJogos[1]);
		guarda = rand() % sizeof(mod[0].listaJogos) / 136;

		printf("SELECCIONE O JOGO NO QUAL PRETENDE APOSTAR:\n\n");
		for (int i = 0; i < 5; i++, aux1++)
		{
			printf("%d- %s - %s", aux1, mod[0].listaJogos[guarda].casa.nome, mod[0].listaJogos[guarda].visitante.nome);
			if (i == 0) um = mod[0].listaJogos[guarda];
			else if (i == 1) dois = mod[0].listaJogos[guarda];
			else if (i == 2) tres = mod[0].listaJogos[guarda];
			else if (i == 3) quatro = mod[0].listaJogos[guarda];
			else cinco = mod[0].listaJogos[guarda];
		}
		scanf("OPCAO: ", &opcao);

		switch (opcao)
		{
		case 1:
			return um;
			break;
		case 2:
			return dois;
			break;
		case 3:
			return tres;
			break;
		case 4:
			return quatro;
			break;
		case 5:
			return cinco;
			break;
		default:

			break;
		}
	} while (opcao != 0);
}
void CriaJogos(modalidade *mod)
{
	FILE *fJogos;
	char nomeFicheiro[200];

	//FILE *fJogosLeitura, *fJogosEscrita;
	//clube clubAux1, clubAux2;
	//int numeroLinhas;

	strcpy(nomeFicheiro, mod[0].nome);
	strcat(nomeFicheiro, "-jogos.txt");

	/*if (FicheiroExiste(nomeFicheiro, &fJogosLeitura))
	{
		numeroLinhas = FicheiroLinhas(nomeFicheiro);
		fJogosEscrita = fopen(nomeFicheiro, "a+");
		for (int a = 0; a < nomeFicheiro; a++)
		{
			for (int b = 0; b < nomeFicheiro; b++)
			{
				if (a != b)
				{
					if (mod[0].nome != "TENIS")
					{

						if (feof(fJogosLeitura))
						{
							fprintf(fJogosEscrita, "%s - %s", mod[0].listaClubes[a].nome, mod[0].listaClubes[b].nome);
						}
						else
						{
							while (!feof(fJogosLeitura))
							{
								fscanf(fJogosLeitura, "%s- %s", clubAux1.nome, clubAux2.nome);
								if (strcmp(clubAux1.nome, mod[0].listaClubes[a].nome) == 0 && strcmp(clubAux2.nome, mod[0].listaClubes[b].nome) == 0)
								{
									break;
								}
								else
								{
									fprintf(fJogosEscrita, "\n%s - %s", mod[0].listaClubes[a].nome, mod[0].listaClubes[b].nome);
									break;
								}
							}
						}
					}
					else
					{
						fprintf(fJogosEscrita, "%s - %s\n", mod[0].listaClubes[a].nome, mod[0].listaClubes[b].nome);
					}
				}
			}
		}
		
		fclose(fJogosEscrita);
		fclose(fJogosLeitura);
	}*/

	fJogos = fopen(nomeFicheiro, "w");
	for (int i = 0; i < mod[0].listaClubesCount; i++)
	{
		for (int j = 0; j < mod[0].listaClubesCount; j++)
		{
			if (i == 0 && j == 1)
			{
				fprintf(fJogos, "%s - %s", mod[0].listaClubes[i], mod[0].listaClubes[j]);
				mod[0].listaJogos[0].casa = mod[0].listaClubes[i];
				mod[0].listaJogos[0].visitante = mod[0].listaClubes[j];
			}
			else if (i != j)
			{
				fprintf(fJogos, "\n%s - %s", mod[0].listaClubes[i], mod[0].listaClubes[j]);
				mod[0].listaJogos[(i + 1) * (j + 1)].casa = mod[0].listaClubes[i];
				mod[0].listaJogos[(i + 1) * (j + 1)].visitante = mod[0].listaClubes[j];
			}
		}
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

//tem de ler so a ultima epoca
void CalculaMediaGolosCasa(modalidade *mod)
{
	FILE *fResultados;
	int goloscasa = 0, intAux, numeroLinhas;

	if (FicheiroExiste("resultados.txt", &fResultados))
	{
		numeroLinhas = FicheiroLinhas("resultados.txt");
		rewind(fResultados);
		for (int i = 0; i < numeroLinhas; i++)
		{
			fscanf(fResultados, "%*d- %*s %d - %*d %*s", &intAux);
			goloscasa += intAux;
		}
		fclose(fResultados);
		mod[0].mediapts_casa = ((float)goloscasa / (float)numeroLinhas);
	}
}
void CalculaMediaGolosFora(modalidade *mod)
{
	FILE *fResultados;
	int golosfora = 0, intAux, numeroLinhas;

	if (FicheiroExiste("resultados.txt", &fResultados))
	{
		numeroLinhas = FicheiroLinhas("resultados.txt");
		rewind(fResultados);
		for (int i = 0; i < numeroLinhas; i++)
		{
			fscanf(fResultados, "%*d- %*s %*d - %d %*s", &intAux);
			golosfora += intAux;
		}
		fclose(fResultados);
		mod[0].mediapts_fora = ((float)golosfora / (float)numeroLinhas);
	}
}

void CalculaAtteDef(modalidade *mod, int a)
{
	FILE *fResultados;
	int golosfora = 0, goloscasa = 0, golossofridoscasa = 0, golossofridosfora = 0, jogoscasa = 0, jogosfora = 0, intAux1, intAux2, numeroLinhas;
	char nomeAux1[20], nomeAux2[20];
	float media;

	if (FicheiroExiste("resultados.txt", &fResultados))
	{
		numeroLinhas = FicheiroLinhas("resultados.txt");
		rewind(fResultados);
		for (int i = 0; i < numeroLinhas; i++)
		{
			fscanf(fResultados, "%*d- %s %d - %d %s", nomeAux1, &intAux1, &intAux2, nomeAux2); //se n der com fscanf dps reformulo pa fgets com a divisao em 4 strings
			if (strcmp(nomeAux1, mod[0].listaClubes[a].nome) == 0)
			{
				golossofridoscasa += intAux2;
				goloscasa += intAux1;
				jogoscasa++;
			}
			else if (strcmp(nomeAux2, mod[0].listaClubes[a].nome) == 0)
			{
				golossofridosfora += intAux1;
				golosfora += intAux2;
				jogosfora++;
			}
		}
		fclose(fResultados);
		media = ((float)goloscasa / (float)jogoscasa);
		mod[0].listaClubes[a].ataque_casa = media / mod[0].mediapts_casa;
		media = ((float)golosfora / (float)jogosfora);
		mod[0].listaClubes[a].ataque_fora = media / mod[0].mediapts_fora;
		media = ((float)golossofridoscasa / (float)jogoscasa);
		mod[0].listaClubes[a].defesa_casa = media / mod[0].mediapts_fora;
		media = ((float)golossofridosfora / (float)jogosfora);
		mod[0].listaClubes[a].defesa_fora = media / mod[0].mediapts_casa;
	}
}
void Poisson(modalidade *mod)
{
	FILE *fResultados;
	int numeroLinhas = 0;
	float lambda_c, lambda_f, normalizador_c = 0, normalizador_f = 0, aux;
	numeroLinhas = FicheiroLinhas("resultados.txt");

	for (int i = 0; i < numeroLinhas; i++)
	{
		lambda_c = mod[0].listaJogos[i].casa.ataque_casa * mod[0].listaJogos[i].visitante.defesa_fora * mod[0].mediapts_casa;
		lambda_f = mod[0].listaJogos[i].visitante.ataque_fora * mod[0].listaJogos[i].casa.defesa_casa * mod[0].mediapts_fora;

		for (int j = 0; j <= mod[0].maxpts; j++)
		{
			mod[0].listaJogos[i].PoissonCasa[j] = (exp(-lambda_c) * pow(lambda_c, j)) / factorial(mod[0].maxpts);
			normalizador_c += mod[0].listaJogos[i].PoissonCasa[j];
			mod[0].listaJogos[i].PoissonFora[j] = (exp(-lambda_f) * pow(lambda_f, j)) / factorial(mod[0].maxpts);
			normalizador_f += mod[0].listaJogos[i].PoissonFora[j];
		}
	}

	for (int i = 0; i < numeroLinhas; i++)
	{
		for (int j = 0; j <= mod[0].maxpts; j++)
		{
			aux = regra3simples(normalizador_c, mod[0].listaJogos[i].PoissonCasa[j]);
			mod[0].listaJogos[i].PoissonCasa[j] = aux;
			aux = regra3simples(normalizador_f, mod[0].listaJogos[i].PoissonFora[j]);
			mod[0].listaJogos[i].PoissonFora[j] = aux;
		}
	}

}
void CalculaOddsIniciais(modalidade *mod, int a) // ja acabo
{
	float empate, vitoria = 0;

	for (int i = 0; i <= mod[0].maxpts; i++)
	{
		vitoria += mod[0].listaJogos[a].PoissonCasa[i] * mod[0].listaJogos[a].PoissonFora[i + 1];
	}

}

