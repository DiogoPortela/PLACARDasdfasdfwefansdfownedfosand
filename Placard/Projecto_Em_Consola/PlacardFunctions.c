#include "PlacardStructs.h"

//PRONTAS
void LimpaEcra(void)	//Apresenta uma mensagem antes de continuar e limpa o ecra
{
	printf("\nCARREGUE QUALQUER TECLA PARA CONTINUAR...");
	getch();
	system("cls");
}
void AtribuiResultado(modalidade *mod)
{
	FILE *fResultados, *fJogos;
	int apontos, bpontos, intAux = 0;
	char nomeFicheiroJogos[200], nomeFicheiroResultados[200];
	clube aux1, aux2;

	strcpy(nomeFicheiroJogos, mod[0].nome);
	strcat(nomeFicheiroJogos, "-jogos.txt");
	strcpy(nomeFicheiroResultados, mod[0].nome);
	strcat(nomeFicheiroResultados, "-resultados.txt");

	fResultados = fopen(nomeFicheiroResultados, "a+");

	if (FicheiroExiste(nomeFicheiroJogos, &fJogos) && FicheiroExiste(nomeFicheiroResultados, &fResultados))
	{
		for (int i = 0; i < mod[0].listaClubesCount; i++)
		{
			for (int j = 0; j < mod[0].listaClubesCount; j++)
			{
				if (i != j)
				{
					apontos = ResultadoRandom(mod[0].listaClubes[i], mod[0].maxpts);
					bpontos = ResultadoRandom(mod[0].listaClubes[j], mod[0].maxpts);
					if (intAux == 0)
					{
						fprintf(fResultados, "%s %d - %d %s", mod[0].listaClubes[i].nome, apontos, bpontos, mod[0].listaClubes[j].nome);
					}
					else
					{
						fprintf(fResultados, "\n%s %d - %d %s", mod[0].listaClubes[i].nome, apontos, bpontos, mod[0].listaClubes[j].nome);
					}
					//printf("%d %d\n", apontos, bpontos);
					mod[0].listaJogos[intAux].resultado[0] = apontos;
					mod[0].listaJogos[intAux].resultado[1] = bpontos;
					intAux++;
				}
			}
		}
		fclose(fJogos);
		fclose(fResultados);
	}
}
void CriaJogos(modalidade *mod)	//Gera todos jogos possiveis associados a uma modalidade
{
	FILE *fJogos;
	char nomeFicheiro[200];

	//Adiciona o sufixo ao nome do ficheiro
	strcpy(nomeFicheiro, mod[0].nome);
	strcat(nomeFicheiro, "-jogos.txt");

	//Gera todos os jogos
	fJogos = fopen(nomeFicheiro, "w");
	for (int i = 0; i < mod[0].listaClubesCount; i++)
	{
		for (int j = 0; j < mod[0].listaClubesCount; j++)
		{
			//Gera o primeiro jogo do ficheiro
			if (i == 0 && j == 1)
			{
				mod[0].listaJogos[0].casa = &mod[0].listaClubes[i];
				mod[0].listaJogos[0].visitante = &mod[0].listaClubes[j];
				fprintf(fJogos, "%s - %s %f %f %f", mod[0].listaClubes[i], mod[0].listaClubes[j], mod[0].listaJogos[0].oddCasa, mod[0].listaJogos[0].oddEmpate, mod[0].listaJogos[0].oddVisitante);

			}
			//Gera o resto dos jogos
			else if (i != j)
			{
				mod[0].listaJogos[(i * mod[0].listaClubesCount) + j].casa = &mod[0].listaClubes[i];
				mod[0].listaJogos[(i * mod[0].listaClubesCount) + j].visitante = &mod[0].listaClubes[j];
				fprintf(fJogos, "\n%s - %s %f %f %f", mod[0].listaClubes[i], mod[0].listaClubes[j], mod[0].listaJogos[(i * mod[0].listaClubesCount) + j].oddCasa, mod[0].listaJogos[(i * mod[0].listaClubesCount) + j].oddEmpate, mod[0].listaJogos[(i * mod[0].listaClubesCount) + j].oddVisitante);
			}
			if (i == 17) break;
		}
	}
	fclose(fJogos);
}
int EscolheModalidade(modalidade *mod, int *quantidade)	//Da ao utilizador a escolha de uma modalidade e devolve-a
{
	char modalidade_introduzida[20] = { 0 }, charAux[20] = { 0 };
	int opcao = 0;

	do
	{
		system("cls");
		//Imprime todas as modalidades
		printf("MODALIDADE DA APOSTA:\n");
		for (int i = 0; i < *quantidade; i++)
		{
			printf("\t%d- %s \n", i + 1, mod[i].nome);
		}

		printf("\t0- VOLTAR ATRAS\n");
		printf("OPCAO: ");
		scanf("%d", &opcao);
		while (getchar() != '\n');

		//Verifica se o input esta dentro dos limites e guarda a modalidade escolhida
		if (opcao > 0 && opcao <= *quantidade)
		{
			return opcao - 1;
		}
	} while (opcao != 0);

	LimpaEcra();
	return -1;
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

//ESTA FUNCAO JA NAO SERVE DE MUITO
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

void FicheiroLeData(modalidade *mod, int *quantidadeMods)	//Le os ficheiros para memoria
{
	int i, j, k, l;
	char charAux[100], charAux2[100];
	char nomeFicheiro[200];
	FILE *fModalidades, *fClubes, *fJogos;

	if (FicheiroExiste("modalidades.txt", &fModalidades))
	{
		//Guarda a quantidade de modalidades
		*quantidadeMods = FicheiroLinhas("modalidades.txt");
		for (i = 0; i < *quantidadeMods; i++)
		{
			//Para cada linha do ficheiro guarda uma modalidade em memoria
			fscanf(fModalidades, "%s %d", &mod[i].nome, &mod[i].maxpts);

			strcpy(nomeFicheiro, mod[i].nome);
			strcat(nomeFicheiro, "-clubes.txt");
			if (FicheiroExiste(nomeFicheiro, &fClubes))
			{
				//Procura se a modalidade tem clubes e adiciona em memoria à lista de clubes
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
					//Prcura se ha jogos associados a modalidade e adiciona em memoria
					mod[i].listaJogosCount = FicheiroLinhas(nomeFicheiro);
					for (k = 0; k < mod[i].listaJogosCount; k++)
					{
						fscanf(fJogos, "%s - %s %*f %*f %*f", charAux, charAux2);
						for (int l = 0; l < mod[i].listaClubesCount; l++)
						{
							if (!strcmp(charAux, mod[i].listaClubes[l].nome))
							{
								mod[i].listaJogos[k].casa = &mod[i].listaClubes[l];
							}
							if (!strcmp(charAux2, mod[i].listaClubes[l].nome))
							{
								mod[i].listaJogos[k].visitante = &mod[i].listaClubes[l];
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
int FicheiroLinhas(char nomeficheiro[])	//Devolve a quantidade de linha existentes num ficheiro.
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
void GerirSaldo(int *saldo)	//Da ao utilizador o seu saldo e permite carrega-lo
{
	FILE *fSaldoLeitura, *fSaldoEscrita;
	int userInput, intAux;

	system("cls");
	if (FicheiroExiste("saldo.txt", &fSaldoLeitura))
	{
		if (FicheiroLinhas("saldo.txt") == 0)
		{
			//Se nao houver ficheiro pede uma carregamento inicial
			do
			{
				printf("CARREGUE UM SALDO INCIAL: ");
				scanf("%d", saldo);
				while (getchar() != '\n');
			} while (*saldo <= 0);

			fSaldoEscrita = fopen("saldo.txt", "w");
			fprintf(fSaldoEscrita, "%d", *saldo);
			fclose(fSaldoEscrita);
		}
		else
		{
			//Apresenta a possibilidade de carregar saldo
			fscanf(fSaldoLeitura, "%d", saldo);
			do
			{
				printf("O SEU SALDO ACTUAL: %d\n1- CARREGAR\n0- SAIR\n\nOPCAO: ", *saldo);
				scanf("%d", &userInput);
				while (getchar() != '\n');
				switch (userInput)
				{
				case 1:
				{
					printf("VALOR A CARREGAR: ");
					scanf("%d", &intAux);
					while (getchar() != '\n');
					if (intAux > 0)
					{
						*saldo = *saldo + intAux;
						fSaldoEscrita = fopen("saldo.txt", "w");
						fprintf(fSaldoEscrita, "%d", *saldo);
						fclose(fSaldoEscrita);
					}
					else
					{
						printf("VALOR INTRODUZIDO INVALIDO.");
					}
					LimpaEcra();
					break;
				}
				case 0:
				{
					break;
				}
				default:
					printf("INTRODUZA UM VALOR VALIDO.");
					LimpaEcra();
					break;
				}
			} while (userInput != 0);
		}
		fclose(fSaldoLeitura);
	}
}
void ListarTudo(modalidade *mod, int *quantidade)	//Da ao utilizador a escolha do que pretende ver listado, modalidades, clubes, jogos e resultados
{
	char opcao = 0, nomeFicheiro[200];
	int inputInt;
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
		case '1':	//Imprimir modalidades
		{
			FicheiroImprimir("modalidades.txt");
			LimpaEcra();
			break;
		}
		case'2':	//Imprimir clubes
		{
			//Imprime todas a modalidades e escolhe uma
			system("cls");
			printf("ESCOLHA A MODALIDADE DO CLUBE:\n");
			for (int i = 0; i < *quantidade; i++)
			{
				printf("\t\t%d- %s\n", i + 1, mod[i]);
			}
			printf("\t\t0- SAIR\nOPCAO: ");
			scanf("%d", &inputInt);
			while (getchar() != '\n');

			//Imprime todos os clubes

			for (int i = 0; i < mod[inputInt - 1].listaClubesCount; i++)
			{
				printf("\n%s", mod[inputInt - 1].listaClubes[i].nome);
			}

			printf("\n");
			LimpaEcra();
			break;
		}
		case '3':	//Imprimir jogos
		{
			//Imprime todas a modalidades e escolhe uma
			system("cls");
			printf("ESCOLHA A MODALIDADE DO CLUBE:\n");
			for (int i = 0; i < *quantidade; i++)
			{
				printf("\t\t%d- %s\n", i + 1, mod[i]);
			}
			printf("\t\t0- SAIR\nOPCAO: ");
			scanf("%d", &inputInt);
			while (getchar() != '\n');

			//Imprime todos os jogos

			for (int i = 0; i < mod[inputInt - 1].listaJogosCount; i++)
			{
				printf("\n%s - %s", (*mod[inputInt - 1].listaJogos[i].casa).nome, (*mod[inputInt - 1].listaJogos[i].visitante).nome);
			}

			printf("\n");
			LimpaEcra();
			break;
		}
		case '4':	//Imprimir resultados
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
//tem de ler so a ultima epoca
void CalculaMediaGolosCasa(modalidade *mod)
{
	int golosCasa = 0, golosFora = 0, intAux1, intAux2;
	for (int i = 0; i < mod[0].listaJogosCount; i++)
	{
		golosCasa += mod[0].listaJogos[i].resultado[0];
		golosFora += mod[0].listaJogos[i].resultado[1];
	}
	mod[0].mediapts_casa = ((float)golosCasa / (float)mod[0].listaJogosCount);
	mod[0].mediapts_fora = ((float)golosFora / (float)mod[0].listaJogosCount);
	/*FILE *fResultados;
	int golosCasa = 0, golosFora = 0, intAux1, intAux2, numeroLinhas;

	char nomeFicheiro[200];

	strcpy(nomeFicheiro, mod[0].nome);
	strcat(nomeFicheiro, "-resultados.txt");

	if (FicheiroExiste(nomeFicheiro, &fResultados))
	{
		numeroLinhas = FicheiroLinhas(nomeFicheiro);
		rewind(fResultados);
		for (int i = 0; i < numeroLinhas; i++)
		{
			fscanf(fResultados, "%*s %d - %d %*s", &intAux1, &intAux2);
			golosCasa += intAux1;
			golosFora += intAux2;
		}
		fclose(fResultados);
		mod[0].mediapts_casa = ((float)golosCasa / (float)numeroLinhas);
		mod[0].mediapts_fora = ((float)golosFora / (float)numeroLinhas);
	}*/
}
void CalculaAtteDef(modalidade *mod)
{
	int golosfora, goloscasa, golossofridoscasa, golossofridosfora, jogoscasa, jogosfora;
	char nomeAux1[20], nomeAux2[20], nomeFicheiro[200];
	float media;

	for (int indexClube = 0; indexClube <= mod[0].listaClubesCount; indexClube++)
	{
		golossofridoscasa = 0;
		goloscasa = 0;
		jogoscasa = 0;
		golossofridosfora = 0;
		golosfora = 0;
		jogosfora = 0;
		for (int i = 0; i < mod[0].listaJogosCount; i++)
		{
			if (strcmp((*mod[0].listaJogos[i].casa).nome, mod[0].listaClubes[indexClube].nome) == 0)
			{
				golossofridoscasa += mod[0].listaJogos[i].resultado[1];
				goloscasa += mod[0].listaJogos[i].resultado[0];
				jogoscasa++;
			}
			else if (strcmp((*mod[0].listaJogos[i].visitante).nome, mod[0].listaClubes[indexClube].nome) == 0)
			{
				golossofridosfora += mod[0].listaJogos[i].resultado[0];;
				golosfora += mod[0].listaJogos[i].resultado[1];;
				jogosfora++;
			}
		}
		media = ((float)goloscasa / (float)jogoscasa);
		mod[0].listaClubes[indexClube].ataque_casa = media / mod[0].mediapts_casa;
		media = ((float)golosfora / (float)jogosfora);
		mod[0].listaClubes[indexClube].ataque_fora = media / mod[0].mediapts_fora;
		media = ((float)golossofridoscasa / (float)jogoscasa);
		mod[0].listaClubes[indexClube].defesa_casa = media / mod[0].mediapts_fora;
		media = ((float)golossofridosfora / (float)jogosfora);
		mod[0].listaClubes[indexClube].defesa_fora = media / mod[0].mediapts_casa;
	}
	/*FILE *fResultados;
	int golosfora = 0, goloscasa = 0, golossofridoscasa = 0, golossofridosfora = 0, jogoscasa = 0, jogosfora = 0, intAux1, intAux2, numeroLinhas;
	char nomeAux1[20], nomeAux2[20], nomeFicheiro[200];
	float media;

	strcpy(nomeFicheiro, mod[0].nome);
	strcat(nomeFicheiro, "-resultados.txt");
	if (FicheiroExiste(nomeFicheiro, &fResultados))
	{
		numeroLinhas = FicheiroLinhas(nomeFicheiro);
		for (int indexClube = 0; indexClube <= mod[0].listaClubesCount; indexClube++)
		{
			rewind(fResultados);
			for (int i = 0; i < numeroLinhas; i++)
			{
				fscanf(fResultados, "%s %d - %d %s", nomeAux1, &intAux1, &intAux2, nomeAux2); //se n der com fscanf dps reformulo pa fgets com a divisao em 4 strings
				if (strcmp(nomeAux1, mod[0].listaClubes[indexClube].nome) == 0)
				{
					golossofridoscasa += intAux2;
					goloscasa += intAux1;
					jogoscasa++;
				}
				else if (strcmp(nomeAux2, mod[0].listaClubes[indexClube].nome) == 0)
				{
					golossofridosfora += intAux1;
					golosfora += intAux2;
					jogosfora++;
				}
			}
			media = ((float)goloscasa / (float)jogoscasa);
			mod[0].listaClubes[indexClube].ataque_casa = media / mod[0].mediapts_casa;
			media = ((float)golosfora / (float)jogosfora);
			mod[0].listaClubes[indexClube].ataque_fora = media / mod[0].mediapts_fora;
			media = ((float)golossofridoscasa / (float)jogoscasa);
			mod[0].listaClubes[indexClube].defesa_casa = media / mod[0].mediapts_fora;
			media = ((float)golossofridosfora / (float)jogosfora);
			mod[0].listaClubes[indexClube].defesa_fora = media / mod[0].mediapts_casa;
			golossofridoscasa = 0;
			goloscasa = 0;
			jogoscasa = 0;
			golossofridosfora = 0;
			golosfora = 0;
			jogosfora = 0;
		}
		fclose(fResultados);
	}*/
}
void Poisson(modalidade *mod)
{
	float lambda_c, lambda_f, normalizador_c = 0, normalizador_f = 0, aux;

	for (int i = 0; i < mod[0].listaJogosCount; i++)
	{
		lambda_c = (*mod[0].listaJogos[i].casa).ataque_casa * (*mod[0].listaJogos[i].visitante).defesa_fora * mod[0].mediapts_casa;
		lambda_f = (*mod[0].listaJogos[i].visitante).ataque_fora * (*mod[0].listaJogos[i].casa).defesa_casa * mod[0].mediapts_fora;

		for (int j = 0; j <= mod[0].maxpts; j++)
		{
			mod[0].listaJogos[i].PoissonCasa[j] = (exp(-lambda_c) * pow(lambda_c, j)) / factorial(j);
			normalizador_c += mod[0].listaJogos[i].PoissonCasa[j];
			mod[0].listaJogos[i].PoissonFora[j] = (exp(-lambda_f) * pow(lambda_f, j)) / factorial(j);
			normalizador_f += mod[0].listaJogos[i].PoissonFora[j];
		}
	}

	for (int i = 0; i < mod[0].listaJogosCount; i++)
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
void CalculaOddsIniciais(modalidade *mod)
{
	float empate = 0, vitoria = 0, somaaux = 0;

	for (int indexJogo = 0; indexJogo <= mod[0].listaJogosCount; indexJogo++)
	{
		empate = 0;
		vitoria = 0;
		somaaux = 0;
		for (int i = 0; i <= mod[0].maxpts; i++)
		{
			for (int j = 0; j <= i; j++)
			{
				if (i == j)
				{
					empate += mod[0].listaJogos[indexJogo].PoissonCasa[i] * mod[0].listaJogos[indexJogo].PoissonFora[j];
				}
				else
				{
					somaaux += mod[0].listaJogos[indexJogo].PoissonFora[j];
					vitoria += mod[0].listaJogos[indexJogo].PoissonCasa[i] * somaaux;
				}
			}
		}
		mod[0].listaJogos[indexJogo].oddCasa = vitoria;
		mod[0].listaJogos[indexJogo].oddEmpate = empate;
		mod[0].listaJogos[indexJogo].oddVisitante = 1 - vitoria - empate;
	}
}

//se possivel juntar as 2 numa...
int SimulaComBaseNasOddsCasa(modalidade *mod, int indexJogo)
{
	int aux;
	float somaaux = 0;

	srand(SeedAleatoria());
	aux = rand() % 101;

	int i = 0;
	while (i <= mod[0].maxpts)
	{
		somaaux += mod[0].listaJogos[indexJogo].PoissonCasa[i];
		if (aux < somaaux * 100)
			return i;
		else
			i++;
	}
}
int SimulaComBaseNasOddsFora(modalidade *mod, int indexJogo)
{
	int aux;
	float somaaux = 0;

	srand(SeedAleatoria());
	aux = rand() % 101;

	int i = 0;
	while (i <= mod[0].maxpts)
	{
		somaaux += mod[0].listaJogos[indexJogo].PoissonFora[i];
		if (aux < somaaux * 100)
			return i;
		else
			i++;
	}
}

char AtribuiResultadoComOdds(modalidade *mod, int indexJogo)
{
	FILE *fResultados;

	char nomeFicheiro[200];
	int pontosCasa, pontosFora;

	strcpy(nomeFicheiro, mod[0].nome);
	strcat(nomeFicheiro, "-resultados.txt");

	if (FicheiroExiste(nomeFicheiro, &fResultados))
	{
		pontosCasa = SimulaComBaseNasOddsCasa(&mod[0], indexJogo);
		pontosFora = SimulaComBaseNasOddsFora(&mod[0], indexJogo);

		fprintf(nomeFicheiro, "%s %d - %d %s", (*mod[0].listaJogos[indexJogo].casa).nome, pontosCasa, pontosFora, (*mod[0].listaJogos[indexJogo].visitante).nome);
		printf(nomeFicheiro, "%s %d - %d %s", (*mod[0].listaJogos[indexJogo].casa).nome, pontosCasa, pontosFora, (*mod[0].listaJogos[indexJogo].visitante).nome);

	}
	fclose(nomeFicheiro);

	if (pontosCasa > pontosFora) return 'V';
	if (pontosCasa == pontosFora) return 'E';
	if (pontosCasa < pontosFora) return 'D';

}

//A PRECISAR DE REWORK

void Definicoes(modalidade *mod, int *quantidade)	//Da ao utilizador as definiçoes que pode alterar
{
	FILE *fModalidades, *fJogos, *fClubes;
	char input, input2, input3, YN;
	char nomeFicheiro[200], nomeFicheiroJogos[200], nomeFicheiroClubes[200], nomeFicheiroJogos2[200], nomeFicheiroClubes2[200], charAux[50];
	int inputInt, inputInt2;
	system("cls");
	do
	{
		//Imprime as escolhas e le input
		printf("\t1- ALTERAR MODALIDADES\n\t2- ALTERAR CLUBES\n\t3- ALTERAR COTAS\n\t0- SAIR\n\nOPCAO: ");
		scanf("%c", &input);
		while (getchar() != '\n');
		switch (input)
		{
		case '1':	//Criar, editar e remover modalidade
		{
			modalidade a, modAux2;
			do
			{
				//Imprime escolhas e le input
				system("cls");
				printf("\t\t1- CRIAR MODALIDADE\n\t\t2- ALTERAR MODALIDADE\n\t\t3- ELIMINAR MODALIDADE\n\t\t0- CANCELAR\n\nOPCAO: ");
				scanf("%c", &input2);
				while (getchar() != '\n');
				switch (input2)
				{
				case '1':		//Criar Modalidade	
				{
					fModalidades = fopen("modalidades.txt", "a+");
					if (*quantidade < 10)
					{
						printf("\nINTRODUZA O NOME DA NOVA MODALIDADE: ");
						scanf("%s", a.nome);
						while (getchar() != '\n');
						printf("INTRODUZA O NUMERO MAXIMO DE PONTOS: ");
						scanf("%d", &a.maxpts);
						while (getchar() != '\n');
						a.listaClubesCount = 0;
						a.listaJogosCount = 0;

						//Tornar em maisculas
						int i = 0;
						while (a.nome[i])
						{
							a.nome[i] = toupper(a.nome[i]);
							i++;
						}

						//Adiciona Internamente
						mod[*quantidade] = a;
						*quantidade += 1;

						//Alfabetizar as modalidades
						for (int i = 0; i < *quantidade - 1; i++)
						{
							for (int j = i + 1; j < *quantidade; j++)
							{
								if (strcmp(mod[i].nome, mod[j].nome) > 0)
								{
									modAux2 = mod[i];
									mod[i] = mod[j];
									mod[j] = modAux2;
								}
							}
						}

						//Cria novo ficheiro onde guarda todos as modalidades
						fModalidades = fopen("modalidades.txt", "w");
						fprintf(fModalidades, "%s %d", mod[0].nome, mod[0].maxpts);
						for (int i = 1; i < *quantidade; i++)
						{
							fprintf(fModalidades, "\n%s %d", mod[i].nome, mod[i].maxpts);
						}
						fclose(fModalidades);

						//Adiciona os ficheiros necessarios à modalidade
						strcpy(nomeFicheiro, a.nome);
						strcat(nomeFicheiro, "-clubes.txt");
						fClubes = fopen(nomeFicheiro, "w");
						fclose(fClubes);

						strcpy(nomeFicheiro, a.nome);
						strcat(nomeFicheiro, "-jogos.txt");
						fJogos = fopen(nomeFicheiro, "w");
						fclose(fJogos);

					}
					else
					{
						printf("\nNAO E POSSIVEL CRIAR MAIS MODALIDADES\n");
					}

					fclose(fModalidades);
					LimpaEcra();
					break;
				}
				case '2':		//Alterar modalidade					
				{
					//Imprime todas a modalidades e le input
					printf("\n");
					for (int i = 0; i < *quantidade; i++)
					{
						printf("%d- %s %d\n", i + 1, mod[i].nome, mod[i].maxpts);
					}
					printf("0- CANCELAR\n\nOPCAO: ");
					scanf("%d", &inputInt);
					while (getchar() != '\n');

					//Verifica se input é valido
					if (inputInt != 0 && inputInt <= *quantidade)
					{
						printf("INTRODUZA O NOVO NOME DA MODALIDADE: ");
						scanf("%s", modAux2.nome);
						while (getchar() != '\n');
						printf("INTRODUZA O NOVO NUMERO MAXIMO DE PONTOS: ");
						scanf("%d", &modAux2.maxpts);
						while (getchar() != '\n');

						//Tornar em maisculas
						int i = 0;
						while (modAux2.nome[i])
						{
							modAux2.nome[i] = toupper(modAux2.nome[i]);
							i++;
						}

						//Guardar antigo nome dos ficheiros 
						strcpy(nomeFicheiroClubes, mod[inputInt - 1].nome);
						strcat(nomeFicheiroClubes, "-clubes.txt");
						strcpy(nomeFicheiroJogos, mod[inputInt - 1].nome);
						strcat(nomeFicheiroJogos, "-jogos.txt");

						//Guarda novo nome dos ficheiros
						strcpy(nomeFicheiroClubes2, modAux2.nome);
						strcat(nomeFicheiroClubes2, "-clubes.txt");
						strcpy(nomeFicheiroJogos2, modAux2.nome);
						strcat(nomeFicheiroJogos2, "-jogos.txt");

						//Muda de nome aos ficheiros
						rename(nomeFicheiroClubes, nomeFicheiroClubes2);
						rename(nomeFicheiroJogos, nomeFicheiroJogos2);

						//Alterar Internamente
						mod[inputInt - 1] = modAux2;

						//Alfabetizar as modalidades
						for (int i = 0; i < *quantidade - 1; i++)
						{
							for (int j = i + 1; j < *quantidade; j++)
							{
								if (strcmp(mod[i].nome, mod[j].nome) > 0)
								{
									modAux2 = mod[i];
									mod[i] = mod[j];
									mod[j] = modAux2;
								}
							}
						}

						//Cria novo ficheiro onde guarda todos as modalidades
						fModalidades = fopen("modalidades.txt", "w");
						fprintf(fModalidades, "%s %d", mod[0].nome, mod[0].maxpts);
						for (int i = 1; i < *quantidade; i++)
						{
							fprintf(fModalidades, "\n%s %d", mod[i].nome, mod[i].maxpts);
						}
						fclose(fModalidades);
					}
					LimpaEcra();
					break;
				}
				case '3':		//Eliminar Modalidade
				{
					//Imprimir todas a modalidades e ler input

					printf("\n");
					for (int i = 0; i < *quantidade; i++)
					{
						printf("%d- %s %d\n", i + 1, mod[i].nome, mod[i].maxpts);
					}
					printf("0- CANCELAR\n\nOPCAO: ");
					scanf("%d", &inputInt);
					while (getchar() != '\n');

					//Confirmar se deseja apagar e puxar tudo 1 para cima.
					if (inputInt <= *quantidade && inputInt != 0)
					{
						do
						{
							printf("\nPRETENDE ELIMINAR A OPCAO %d? (Y/N)", inputInt);
							scanf("%c", &YN);
							while (getchar() != '\n');

							if (toupper(YN) == 'Y')
							{
								//Apaga os clubes associados à modalidade
								strcpy(nomeFicheiro, mod[inputInt - 1].nome);
								strcat(nomeFicheiro, "-clubes.txt");
								remove(nomeFicheiro);

								//Apaga os jogos associados à modalidade
								strcpy(nomeFicheiro, mod[inputInt - 1].nome);
								strcat(nomeFicheiro, "-jogos.txt");
								remove(nomeFicheiro);

								//Organiza os dado internamente. Puxa tudo 1 para cima.
								for (int j = inputInt - 1; j < *quantidade; j++)
								{
									mod[j] = mod[j + 1];
								}
								*quantidade -= 1;

								//Apaga o ficheiro e reimprime tudo.
								fModalidades = fopen("modalidades.txt", "w");
								fprintf(fModalidades, "%s %d", mod[0].nome, mod[0].maxpts);
								for (int j = 1; j < *quantidade; j++)
								{
									fprintf(fModalidades, "\n%s %d", mod[j].nome, mod[j].maxpts);
								}
								fclose(fModalidades);

								break;
							}
							else if (toupper(YN) == 'N')
							{
								break;
							}
						} while (1);
					}
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
		case '2':	//Criar, editar e remover clubes
		{
			clube clubeAux, clubeAux2;
			do
			{
				//Imprime todas a modalidades e le input
				system("cls");
				printf("ESCOLHA A MODALIDADE DO CLUBE:\n");
				for (int i = 0; i < *quantidade; i++)
				{
					printf("\t\t%d- %s\n", i + 1, mod[i]);
				}
				printf("\t\t0- SAIR\nOPCAO: ");
				scanf("%d", &inputInt);
				while (getchar() != '\n');

				//Caso o input esta dentro dos parametros avanca
				if (inputInt <= *quantidade && inputInt > 0)
				{
					do
					{
						system("cls");
						printf("\t\t\t1- CRIAR CLUBE\n\t\t\t2- ALTERAR CLUBE\n\t\t\t3- ELIMINAR CLUBE\n\t\t\t0- SAIR\nOPCAO: ");
						scanf("%c", &input3);
						while (getchar() != '\n');
						switch (input3)
						{
						case '1':	//Criar clube
						{
							if (mod[inputInt - 1].listaClubesCount < maximoClubes)
							{
								//Introduzir detalhes do novo clube
								printf("\nINTRODUZA O NOME DO NOVO CLUBE: ");
								scanf("%s", clubeAux.nome);
								while (getchar() != '\n');

								//Tornar em maisculas
								int i = 0;
								while (clubeAux.nome[i])
								{
									clubeAux.nome[i] = toupper(clubeAux.nome[i]);
									i++;
								}

								//Guardar internamente
								mod[inputInt - 1].listaClubes[mod[inputInt - 1].listaClubesCount] = clubeAux;
								mod[inputInt - 1].listaClubesCount++;

								//Alfabetizar os clubes
								for (int i = 0; i < mod[inputInt - 1].listaClubesCount - 1; i++)
								{
									for (int j = i + 1; j < mod[inputInt - 1].listaClubesCount; j++)
									{
										if (strcmp(mod[inputInt - 1].listaClubes[i].nome, mod[inputInt - 1].listaClubes[j].nome) > 0)
										{
											clubeAux2 = mod[inputInt - 1].listaClubes[i];
											mod[inputInt - 1].listaClubes[i] = mod[inputInt - 1].listaClubes[j];
											mod[inputInt - 1].listaClubes[j] = clubeAux2;
										}
									}
								}

								//Cria novo ficheiro onde guarda todos as modalidades
								strcpy(nomeFicheiro, mod[inputInt - 1].nome);
								strcat(nomeFicheiro, "-clubes.txt");
								fClubes = fopen(nomeFicheiro, "w");
								fprintf(fClubes, "%s", mod[inputInt - 1].listaClubes[0].nome);
								for (int i = 1; i < mod[inputInt - 1].listaClubesCount; i++)
								{
									fprintf(fClubes, "\n%s", mod[inputInt - 1].listaClubes[i].nome);
								}
								fclose(fClubes);

								//Actualizar Lista de Jogos
								CriaJogos(&mod[inputInt - 1]);
								break;
							}
							else
							{
								printf("NAO PODE ADIONAR MAIS CLUBES");
							}
						}
						case '2':	//Alterar clube
						{
							//Imprime todas os clubes e le input
							printf("\n");
							for (int i = 0; i < mod[inputInt - 1].listaClubesCount; i++)
							{
								printf("%d- %s\n", i + 1, mod[inputInt - 1].listaClubes[i]);
							}
							printf("0- CANCELAR\n\nOPCAO: ");
							scanf("%d", &inputInt2);
							while (getchar() != '\n');

							//Verifica se input é valido
							if (inputInt2 != 0 && inputInt2 <= mod[inputInt - 1].listaClubesCount)
							{
								printf("INTRODUZA O NOVO NOME DO CLUBE: ");
								scanf("%s", charAux);
								while (getchar() != '\n');

								//Tornar em maisculas e guarda
								int i = 0;
								while (charAux[i])
								{
									charAux[i] = toupper(charAux[i]);
									i++;
								}
								strcpy(mod[inputInt - 1].listaClubes[inputInt2 - 1].nome, charAux);

								//Alfabetizar os clubes
								for (int i = 0; i < mod[inputInt - 1].listaClubesCount - 1; i++)
								{
									for (int j = i + 1; j < mod[inputInt - 1].listaClubesCount; j++)
									{
										if (strcmp(mod[inputInt - 1].listaClubes[i].nome, mod[inputInt - 1].listaClubes[j].nome) > 0)
										{
											clubeAux2 = mod[inputInt - 1].listaClubes[i];
											mod[inputInt - 1].listaClubes[i] = mod[inputInt - 1].listaClubes[j];
											mod[inputInt - 1].listaClubes[j] = clubeAux2;
										}
									}
								}

								//Cria novo ficheiro onde guarda todos as modalidades
								strcpy(nomeFicheiro, mod[inputInt - 1].nome);
								strcat(nomeFicheiro, "-clubes.txt");
								fClubes = fopen(nomeFicheiro, "w");
								fprintf(fClubes, "%s", mod[inputInt - 1].listaClubes[0].nome);
								for (int i = 1; i < mod[inputInt - 1].listaClubesCount; i++)
								{
									fprintf(fClubes, "\n%s", mod[inputInt - 1].listaClubes[i].nome);
								}
								fclose(fClubes);

								//Actualiza jogos
								CriaJogos(&mod[inputInt - 1]);
							}
							break;
						}
						case '3':	//Eliminar clube
						{
							printf("\n");
							for (int i = 0; i < mod[inputInt - 1].listaClubesCount; i++)
							{
								printf("%d- %s\n", i + 1, mod[inputInt - 1].listaClubes[i]);
							}
							printf("0- CANCELAR\n\nOPCAO: ");
							scanf("%d", &inputInt2);
							while (getchar() != '\n');

							if (inputInt2 != 0 && inputInt2 <= mod[inputInt - 1].listaClubesCount)
							{
								do
								{
									printf("\nPRETENDE ELIMINAR A OPCAO %d? (Y/N)", inputInt2);
									scanf("%c", &YN);
									while (getchar() != '\n');

									if (toupper(YN) == 'Y')
									{
										//Organiza os dado internamente. Puxa tudo 1 para cima.
										for (int j = inputInt2 - 1; j < mod[inputInt - 1].listaClubesCount; j++)
										{
											clubeAux = mod[inputInt - 1].listaClubes[j + 1];
											mod[inputInt - 1].listaClubes[j] = clubeAux;
										}
										mod[inputInt - 1].listaClubesCount--;

										//Apaga o ficheiro e reimprime tudo.
										strcpy(nomeFicheiro, mod[inputInt - 1].nome);
										strcat(nomeFicheiro, "-clubes.txt");
										fClubes = fopen(nomeFicheiro, "w");
										fprintf(fClubes, "%s", mod[inputInt - 1].listaClubes[0]);
										for (int j = 1; j < mod[inputInt - 1].listaClubesCount; j++)
										{
											fprintf(fClubes, "\n%s", mod[inputInt - 1].listaClubes[j]);
										}
										fclose(fClubes);

										//Actualizar Lista de Jogos
										CriaJogos(&mod[inputInt - 1]);

										break;
									}
									else if (toupper(YN) == 'N')
									{
										break;
									}
								} while (1);
							}

							break;
						}
						case '0':
							break;
						default:
							printf("VALOR INTRODUZIDO INVALIDO\n");
							break;
						}
						LimpaEcra();
					} while (input3 != '0');
				}
				else if (inputInt > *quantidade)
				{
					printf("VALOR INTRODUZIDO INVALIDO\n");
				}
			} while (inputInt != 0);
			LimpaEcra();
			break;
		}
		case '3':	//Alterar Cotas
		{
			system("cls");
			printf("ESCOLHA A MODALIDADE:\n");
			for (int i = 0; i < *quantidade; i++)
			{
				printf("\t\t%d- %s\n", i + 1, mod[i]);
			}
			printf("\t\t0- SAIR\nOPCAO: ");
			scanf("%d", &inputInt);
			while (getchar() != '\n');

			if (inputInt > 0 && inputInt < quantidade)
			{
				printf("\t\t1- RECALCULAR COTAS\n\t\t2- ALTERAS COTA INDIVIDUAL\n\t\t0- SAIR\n\nOPCAO: ");
				scanf("%c", &input2);
				while (getchar() != '\n');

				switch (input2)
				{
				case '1':
				{
					//Apaga o ficheiro
					strcpy(nomeFicheiro, mod[inputInt - 1].nome);
					strcat(nomeFicheiro, "-resultados.txt");
					remove(nomeFicheiro);

					AtribuiResultado(&mod[inputInt - 1]);
					CalculaMediaGolosCasa(&mod[inputInt - 1]);
					CalculaAtteDef(&mod[inputInt - 1]);
					Poisson(&mod[inputInt - 1]);
					CalculaOddsIniciais(&mod[inputInt - 1]);
					CriaJogos(&mod[inputInt - 1]);
					break;
				}
				case '2':
				{
					break;
				}
				case '0':
				{
					break;
				}
				default:
					printf("INTRODUZA UM VALOR VALIDO");
					break;
				}
				LimpaEcra();
				break;
			}

		}
		}
	} while (input != '0');
}
int EscolheJogo(modalidade *mod)	//Da ao utilizador a escolha de um jogo entre varios
{
	int opcao, seed, guarda = 0;

	do
	{
		seed = SeedAleatoria();
		srand(seed);

		printf("SELECCIONE O JOGO NO QUAL PRETENDE APOSTAR:\n\n");
		printf("  CASA\tVISITANTE\tODD CASA\tODD EMPATE\ODD VISITANTE\n");
		//Imprime alguns jogos escolhidos aleatoriamente

		int numerosUsados[5] = { 0 }, flag;
		for (int i = 0; i < 5; i++)
		{
			guarda = rand() % ((mod[0].listaJogosCount - 1) - 0 + 1) + 0;
			numerosUsados[i] = guarda;
			do
			{
				//Confima que o valor random ainda nao foi usado, para nao sairem 2x o mesmo jogo
				flag = 0;
				for (int j = 0; j < 5; j++)
				{
					if (numerosUsados[i] == numerosUsados[j] && i != j)
					{
						guarda = rand() % ((mod[0].listaJogosCount - 1) - 0 + 1) + 0;
						numerosUsados[i] = guarda;
						flag = 1;
						break;
					}
				}
			} while (flag);
			printf("%d- %s - %s %3f %3f %3f\n", i + 1, (*mod[0].listaJogos[guarda].casa).nome, (*mod[0].listaJogos[guarda].visitante).nome, mod[0].listaJogos[guarda].oddCasa, mod[0].listaJogos[guarda].oddEmpate, mod[0].listaJogos[guarda].oddVisitante);
		}

		//Le o input do utilizador e retorna o jogo escolhido
		printf("0- CANCELAR\n\nOPCAO: ");
		scanf("%d", &opcao);
		while (getchar() != '\n');

		if (opcao > 0 && opcao <= 5)
		{
			return numerosUsados[opcao - 1];
		}

	} while (opcao != 0);
	return -1;
}
void GereJogo(modalidade *mod, int *quantidade, int *saldo)
{
	FILE *fSaldo;
	int indexModalidade, indexJogo, valorAposta, intAux;
	char charAux;

	indexModalidade = EscolheModalidade(mod, quantidade);
	indexJogo = EscolheJogo(&mod[indexModalidade]);

	do
	{
		printf("EM QUE PRETENDE APOSTAR?");
		printf("\t1- VITORIA %s", mod[indexModalidade].listaJogos[indexJogo].casa);
		printf("\t2- EMPATE");
		printf("\t3- VITORIA %s", mod[indexModalidade].listaJogos[indexJogo].visitante);
		printf("\n\nOPCAO: ");
		scanf("%d", &intAux);
		while (getchar() != '\n');
	} while (intAux >= 1 || intAux <= 3);

	do
	{
		printf("QUANTIDADE A APOSTAR (1-100): ");
		scanf("%d", &valorAposta);
		while (getchar() != '\n');
	} while (valorAposta <= 0 || valorAposta > 100);

	charAux = AtribuiResultadoComOdds(&mod[indexModalidade], indexJogo);

	if (charAux == 'V' && intAux == 1)
	{
		*saldo += *saldo * mod[indexModalidade].listaJogos[indexJogo].oddCasa;
	}
	if (charAux == 'E' && intAux == 2)
	{
		*saldo += *saldo * mod[indexModalidade].listaJogos[indexJogo].oddEmpate;
	}
	if (charAux == 'D' && intAux == 3)
	{
		*saldo += *saldo * mod[indexModalidade].listaJogos[indexJogo].oddVisitante;
	}

	fSaldo = fopen("saldo.txt", "w");
	fprintf(fSaldo, "%d", *saldo);
	fclose(fSaldo);
}