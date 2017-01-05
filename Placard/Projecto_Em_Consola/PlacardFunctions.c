#include "PlacardStructs.h"

void LimpaEcra(void)	//Apresenta uma mensagem antes de continuar e limpa o ecra
{
	printf("\nCARREGUE QUALQUER TECLA PARA CONTINUAR...");
	getch();
	system("cls");
}
char AtribuiResultadoComProb(modalidade *mod, int indexJogo) //recebe o index do jogo para atribuir resultado. -> explicado no relatório
{
	FILE *fResultados;

	char nomeFicheiro[200];
	int pontosCasa, pontosFora;

	strcpy(nomeFicheiro, mod[0].nome);
	strcat(nomeFicheiro, "-resultados.txt");

	if (FicheiroExiste(nomeFicheiro, &fResultados))
	{
		pontosCasa = SimulaComBaseNasProbabilidadesCasa(&mod[0], indexJogo); //Calcula os pontos/golos marcados com base nas probabilidades para a equipa da Casa
		pontosFora = SimulaComBaseNasProbabilidadesFora(&mod[0], indexJogo); //Mesmo para a equipa visitante

		fprintf(fResultados, "%s %d - %d %s", (*mod[0].listaJogos[indexJogo].casa).nome, pontosCasa, pontosFora, (*mod[0].listaJogos[indexJogo].visitante).nome);
		printf("\n%s %d - %d %s", (*mod[0].listaJogos[indexJogo].casa).nome, pontosCasa, pontosFora, (*mod[0].listaJogos[indexJogo].visitante).nome);

	}
	fclose(nomeFicheiro);

	if (pontosCasa > pontosFora) return 'V';
	if (pontosCasa == pontosFora) return 'E';
	if (pontosCasa < pontosFora) return 'D';

}
void AtribuiResultado(modalidade *mod) //-> corre os jogos criados e atribui-lhes um resultado completamente random -> usado para criar base de dados
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
					apontos = ResultadoRandom(mod); //-> calcula golos/pontos marcados random para a equipa da casa
					bpontos = ResultadoRandom(mod); //-> mesmo para a equipa visitante
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
	int cont = 0, temporadacont = 0;
	//Gera todos os jogos
	fJogos = fopen(nomeFicheiro, "w");
	for (int i = 0; i <= mod[0].listaClubesCount; i++)
	{
		for (int j = 0; j < mod[0].listaClubesCount; j++)
		{
			//Gera o primeiro jogo do ficheiro
			if (i == 0 && j == 1)
			{
				mod[0].listaJogos[0].casa = &mod[0].listaClubes[i];
				mod[0].listaJogos[0].visitante = &mod[0].listaClubes[j];
				fprintf(fJogos, "%s - %s %f %f %f", mod[0].listaClubes[i], mod[0].listaClubes[j], mod[0].listaJogos[0].oddCasa, mod[0].listaJogos[0].oddEmpate, mod[0].listaJogos[0].oddVisitante);
				cont++;
			}
			//Gera o resto dos jogos
			else if (i != j)
			{
				mod[0].listaJogos[cont].casa = &mod[0].listaClubes[i];
				mod[0].listaJogos[cont].visitante = &mod[0].listaClubes[j];
				fprintf(fJogos, "\n%s - %s %f %f %f", mod[0].listaClubes[i], mod[0].listaClubes[j], mod[0].listaJogos[cont].oddCasa, mod[0].listaJogos[cont].oddEmpate, mod[0].listaJogos[cont].oddVisitante);
				cont++;
			}
		}
		if (cont == (mod[0].listaClubesCount - 1) * mod[0].listaClubesCount) break;
	}
	fclose(fJogos);
}
int EscolheJogo(modalidade *mod)	//Da ao utilizador a escolha de um jogo entre varios
{
	int opcao, seed, guarda = 0;

	do
	{
		opcao = -1;
		printf("-----------------------------------\nSELECCIONE O JOGO NO QUAL PRETENDE APOSTAR:\n\n");
		printf("\t     CASA\t   VISITANTE\tODD CASA\tODD EMPATE\tODD VISITANTE\n");
		//Imprime alguns jogos escolhidos aleatoriamente

		int numerosUsados[5] = { 0 }, flag;
		for (int i = 0; i < 5; i++)
		{
			guarda = rand() % mod[0].listaJogosCount; //entre 0 e valor do listaJogosCount -1
			numerosUsados[i] = guarda;
			do
			{
				//Confima que o valor random ainda nao foi usado, para nao sairem 2x o mesmo jogo
				flag = 0;
				for (int j = 0; j < 5; j++)
				{
					if (numerosUsados[i] == numerosUsados[j] && i != j)
					{
						guarda = rand() % mod[0].listaJogosCount;
						numerosUsados[i] = guarda;
						flag = 1;
						break;
					}
				}
			} while (flag);
			printf("%d- %15s - %15s |\t%2f \t%2f \t%2f\n", i + 1, (*mod[0].listaJogos[guarda].casa).nome, (*mod[0].listaJogos[guarda].visitante).nome, mod[0].listaJogos[guarda].oddCasa, mod[0].listaJogos[guarda].oddEmpate, mod[0].listaJogos[guarda].oddVisitante);
		}

		//Le o input do utilizador e retorna o jogo escolhido
		printf("\n0-CANCELAR\n\nOPCAO: ");
		scanf("%d", &opcao);
		while (getchar() != '\n');

		if (opcao > 0 && opcao <= 5)
		{
			return numerosUsados[opcao - 1];
		}
		else if (opcao != 0)
		{
			printf("INTRODUZA UM VALOR VALIDO.\n");
		}

	} while (opcao != 0);
	return -1;
}
int EscolheModalidade(modalidade *mod, int *quantidade)	//Da ao utilizador a escolha de uma modalidade e devolve-a
{
	char modalidade_introduzida[20] = { 0 }, charAux[20] = { 0 };
	int opcao = 0;

	do
	{
		opcao = -1;
		system("cls");
		//Imprime todas as modalidades
		printf("MODALIDADE DA APOSTA:\n");
		for (int i = 0; i < *quantidade; i++)
		{
			printf("\t%d- %s \n", i + 1, mod[i].nome);
		}

		printf("\t0- SAIR\n");
		printf("\nOPCAO: ");
		scanf("%d", &opcao);
		while (getchar() != '\n');
		printf("\n");

		//Verifica se o input esta dentro dos limites e guarda a modalidade escolhida
		if (opcao > 0 && opcao <= *quantidade)
		{
			return opcao - 1;
		}
		else if (opcao != 0)
		{
			printf("INTRODUZA UM VALOR VALIDO.\n");
			LimpaEcra();
		}
	} while (opcao != 0);

	return -1;
}
long factorial(int n) //-> calcula o factorial de um numero -> usado no calculo da distribuicao de poisson
{
	if (n == 0)
		return 1;
	else
		return(n * factorial(n - 1));
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
void FicheiroLeData(modalidade *mod, int *quantidadeMods, int *saldo)	//Le os ficheiros para memoria
{
	int i, j, k, l;
	float floatAux1, floatAux2, floatAux3;
	char charAux[100], charAux2[100];
	char nomeFicheiro[200];
	FILE *fModalidades, *fClubes, *fJogos, *fSaldo, *fPoisson;

	if (FicheiroExiste("saldo.txt", &fSaldo))
	{
		fscanf(fSaldo, "%d", saldo);
		fclose(fSaldo);
	}

	if (FicheiroExiste("modalidades.txt", &fModalidades))
	{
		//Guarda a quantidade de modalidades
		*quantidadeMods = FicheiroLinhas("modalidades.txt");
		for (i = 0; i < *quantidadeMods; i++)
		{
			//Para cada linha do ficheiro guarda uma modalidade em memoria
			fscanf(fModalidades, "%s %d %f %f", &mod[i].nome, &mod[i].maxpts, &mod[i].mediapts_casa, &mod[i].mediapts_fora);

			strcpy(nomeFicheiro, mod[i].nome);
			strcat(nomeFicheiro, "-clubes.txt");
			if (FicheiroExiste(nomeFicheiro, &fClubes))
			{
				//Procura se a modalidade tem clubes e adiciona em memoria à lista de clubes
				mod[i].listaClubesCount = FicheiroLinhas(nomeFicheiro);
				for (j = 0; j < mod[i].listaClubesCount; j++)
				{
					fscanf(fClubes, "%s %f %f %f %f", mod[i].listaClubes[j].nome, &mod[i].listaClubes[j].ataque_casa, &mod[i].listaClubes[j].ataque_fora, &mod[i].listaClubes[j].defesa_casa, &mod[i].listaClubes[j].defesa_fora);
				}

				strcpy(nomeFicheiro, mod[i].nome);
				strcat(nomeFicheiro, "-jogos.txt");
				if (FicheiroExiste(nomeFicheiro, &fJogos))
				{
					//Prcura se ha jogos associados a modalidade e adiciona em memoria
					mod[i].listaJogosCount = FicheiroLinhas(nomeFicheiro);
					for (k = 0; k < mod[i].listaJogosCount; k++)
					{
						fscanf(fJogos, "%s - %s %f %f %f", charAux, charAux2, &floatAux1, &floatAux2, &floatAux3);
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
						mod[i].listaJogos[k].oddCasa = floatAux1;
						mod[i].listaJogos[k].oddEmpate = floatAux2;
						mod[i].listaJogos[k].oddVisitante = floatAux3;
					}
					strcpy(nomeFicheiro, mod[i].nome);
					strcat(nomeFicheiro, "-poisson.txt");

					if (FicheiroExiste(nomeFicheiro, &fPoisson))
					{
						for (int x = 0; x < mod[i].listaJogosCount; x++)
						{
							for (int z = 0; z <= mod[i].maxpts; z++)
							{
								fscanf(fPoisson, "%f ", &mod[i].listaJogos[x].PoissonCasa[z]);
							}
							for (int z = 0; z <= mod[i].maxpts; z++)
							{
								fscanf(fPoisson, "%f ", &mod[i].listaJogos[x].PoissonFora[z]);
							}
							fscanf(fPoisson, "\*n");
						}
						fclose(fPoisson);
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
int ResultadoRandom(modalidade *mod) //recebe uma modalidade e devolve um valor random entre 0 e o valor maximo de pontos dessa modalidade
{
	int pontos;
	pontos = rand() % mod[0].maxpts + 1;
	return pontos;
}
int SeedAleatoria(void) //seed aleatoria. tinhamos usado para testes iniciais. Inutil neste momento
{
	int seed = 0;
	seed = rand() % 9999999999999999999;
	return seed;
}
int SimulaComBaseNasProbabilidadesCasa(modalidade *mod, int indexJogo) //-> recebe um index de um jogo, calcula como descrito no relatorio o nr de golos marcados pela equipa da casa
{
	float aux;
	float somaaux = 0;

	aux = rand() % 101; //random entre 0 e 100
	aux /= 100; //dividimos por 100 para termos um valor com casa decimais

	int i = 0;
	while (i <= mod[0].maxpts)
	{
		somaaux += mod[0].listaJogos[indexJogo].PoissonCasa[i]; //incrementa os valores das probabilidades de marcar i golos
		if (aux < somaaux)
			return i; //se o valor random gerado for < que a soma de probabilidades actual, retorna i, que sera o nr de golos marcados pela equipa
		else
			i++;
	}
}
int SimulaComBaseNasProbabilidadesFora(modalidade *mod, int indexJogo) //-> igual ao SimulaComBaseNasProbabilidadesCasa mas para a equipa de fora -> mesmo metodo
{
	float aux;
	float somaaux = 0;

	aux = rand() % 101;
	aux /= 100;

	int i = 0;
	while (i <= mod[0].maxpts)
	{
		somaaux += mod[0].listaJogos[indexJogo].PoissonFora[i]; //muda apenas esta linha
		if (aux < somaaux)
			return i;
		else
			i++;
	}
}
void CalculaMediaGolos(modalidade *mod, int modIndex, int *quantidade) //-> recebe todas as modalidades, um index duma modalidade e a quantidade de todas as modalidades existentes
{
	FILE *fModalidades;
	int golosCasa = 0, golosFora = 0, intAux1, intAux2;
	for (int i = 0; i < mod[modIndex].listaJogosCount; i++)
	{
		golosCasa += mod[modIndex].listaJogos[i].resultado[0]; //soma todos os golos marcados em casa
		golosFora += mod[modIndex].listaJogos[i].resultado[1]; //soma todos os golos marcados fora
	}
	mod[modIndex].mediapts_casa = ((float)golosCasa / (float)mod[modIndex].listaJogosCount); //calcula a media de golos marcados em casa por todas as equipas
	mod[modIndex].mediapts_fora = ((float)golosFora / (float)mod[modIndex].listaJogosCount); //calcula a media de golos marcados fora por todas as equipas

	fModalidades = fopen("modalidades.txt", "w");
	fprintf(fModalidades, "%s %d %f %f", mod[0].nome, mod[0].maxpts, mod[0].mediapts_casa, mod[0].mediapts_fora);
	for (int i = 1; i < *quantidade; i++)
	{
		fprintf(fModalidades, "\n%s %d %f %f", mod[i].nome, mod[i].maxpts, mod[i].mediapts_casa, mod[i].mediapts_fora);
	}
	fclose(fModalidades);
}
void CalculaAtteDef(modalidade *mod) //-> calcula a capacidade de ataque e defesa de cada equipa
{
	FILE *fClubes;
	int golosfora, goloscasa, golossofridoscasa, golossofridosfora, jogoscasa, jogosfora;
	char nomeFicheiro[200];
	float media;

	for (int indexClube = 0; indexClube <= mod[0].listaClubesCount; indexClube++)
	{
		golossofridoscasa = 0;
		goloscasa = 0;
		jogoscasa = 0;
		golossofridosfora = 0; //reseta os valores por cada clube percorrido
		golosfora = 0;
		jogosfora = 0;
		for (int i = 0; i < mod[0].listaJogosCount; i++)
		{
			if (strcmp((*mod[0].listaJogos[i].casa).nome, mod[0].listaClubes[indexClube].nome) == 0) //compara o nome da equipa da casa no index i da lista de jogos da modalidade recebida com o nome da equipa recebida
			{
				golossofridoscasa += mod[0].listaJogos[i].resultado[1];
				goloscasa += mod[0].listaJogos[i].resultado[0];
				jogoscasa++;
			}
			else if (strcmp((*mod[0].listaJogos[i].visitante).nome, mod[0].listaClubes[indexClube].nome) == 0) //compara o nome da equipa visitante no index i da lista de jogos da modalidade recebida com o nome da equipa recebida 
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

	strcpy(nomeFicheiro, mod[0].nome);
	strcat(nomeFicheiro, "-clubes.txt");
	fClubes = fopen(nomeFicheiro, "w");

	fprintf(fClubes, "%s %f %f %f %f", mod[0].listaClubes[0].nome, mod[0].listaClubes[0].ataque_casa, mod[0].listaClubes[0].ataque_fora, mod[0].listaClubes[0].defesa_casa, mod[0].listaClubes[0].defesa_fora);
	for (int i = 1; i < mod[0].listaClubesCount; i++)
	{
		//guarda para ficheiro os dados calculados
		fprintf(fClubes, "\n%s %f %f %f %f", mod[0].listaClubes[i].nome, mod[0].listaClubes[0].ataque_casa, mod[0].listaClubes[0].ataque_fora, mod[0].listaClubes[0].defesa_casa, mod[0].listaClubes[0].defesa_fora);
	}
	fclose(fClubes);

}
void Poisson(modalidade *mod) //-> recebe uma modalidade e calcula o PoissonCasa e Fora de cada jogo -> Explicado a pormenor no relatorio
{
	FILE *fPoisson;
	float lambda_c, lambda_f, normalizador_c[maximoJogos] = { 0 }, normalizador_f[maximoJogos] = { 0 }, aux;
	char nomeFicheiro[200];

	for (int i = 0; i < mod[0].listaJogosCount; i++) //-> calcula os lambdas necessarios para o calcula da distribuicao de poisson -> 2 lambdas por jogo -> relatorio
	{
		lambda_c = (*mod[0].listaJogos[i].casa).ataque_casa * (*mod[0].listaJogos[i].visitante).defesa_fora * mod[0].mediapts_casa;
		lambda_f = (*mod[0].listaJogos[i].visitante).ataque_fora * (*mod[0].listaJogos[i].casa).defesa_casa * mod[0].mediapts_fora;

		for (int j = 0; j <= mod[0].maxpts; j++) //-> aplica a formula para todos os j (golos possiveis) e calcula a probabilidade de cada um deles ocorrer -> relatorio
		{
			mod[0].listaJogos[i].PoissonCasa[j] = (exp(-lambda_c) * pow(lambda_c, j)) / factorial(j);
			normalizador_c[i] += mod[0].listaJogos[i].PoissonCasa[j];
			mod[0].listaJogos[i].PoissonFora[j] = (exp(-lambda_f) * pow(lambda_f, j)) / factorial(j);
			normalizador_f[i] += mod[0].listaJogos[i].PoissonFora[j];
		}
	}

	for (int i = 0; i < mod[0].listaJogosCount; i++)
	{
		for (int j = 0; j <= mod[0].maxpts; j++) //percorre as listas criadas para as normalizar como descrito no relatorio
		{
			aux = mod[0].listaJogos[i].PoissonCasa[j] / normalizador_c[i];
			mod[0].listaJogos[i].PoissonCasa[j] = aux;
			aux = mod[0].listaJogos[i].PoissonFora[j] / normalizador_f[i];
			mod[0].listaJogos[i].PoissonFora[j] = aux;
		}
	}

	strcpy(nomeFicheiro, mod[0].nome);
	strcat(nomeFicheiro, "-poisson.txt");
	fPoisson = fopen(nomeFicheiro, "w");
	for (int i = 0; i < mod[0].listaJogosCount; i++)
	{
		for (int j = 0; j <= mod[0].maxpts; j++)
		{
			fprintf(fPoisson, "%f ", mod[0].listaJogos[i].PoissonCasa[j]);
		}
		for (int j = 0; j <= mod[0].maxpts; j++)
		{
			fprintf(fPoisson, "%f ", mod[0].listaJogos[i].PoissonFora[j]);
		}
		fprintf(fPoisson, "\n");
	}
	fclose(fPoisson);
}
void CalculaOddsIniciais(modalidade *mod) //-> recebe uma modalidade e calcula as odds iniciais de cada jogo
{
	float empate = 0, vitoria = 0, derrota = 0, somaaux = 0, somaaux2 = 0;

	for (int indexJogo = 0; indexJogo <= mod[0].listaJogosCount; indexJogo++)
	{
		empate = 0;
		vitoria = 0;
		derrota = 0; //reseta os valores para cada jogo
		somaaux = 0;
		somaaux2 = 0;
		for (int i = 0; i <= mod[0].maxpts; i++)//percorre todos os golos possiveis duas vezes para fazer cruzamentos do tipo 0-1 0-2... 6-6
		{
			for (int j = 0; j <= mod[0].maxpts; j++)
			{
				if (i == j)
				{
					empate += mod[0].listaJogos[indexJogo].PoissonCasa[i] * mod[0].listaJogos[indexJogo].PoissonFora[j];//calcula a probabilidade de empate -> PM0c + PM0f... -> relatorio a pormenor
				}
				else if (i > j)
				{
					somaaux += mod[0].listaJogos[indexJogo].PoissonFora[j];
					vitoria += mod[0].listaJogos[indexJogo].PoissonCasa[i] * somaaux; //calcula a probabilidade de vitoria da equipa da casa
				}
				else
				{
					somaaux2 += mod[0].listaJogos[indexJogo].PoissonCasa[i];
					derrota += mod[0].listaJogos[indexJogo].PoissonFora[j] * somaaux2; //calcula a probabilidade de vitoria da equipa visitante
				}
			}
		}
		mod[0].listaJogos[indexJogo].oddCasa = 1 + (1 / vitoria);
		mod[0].listaJogos[indexJogo].oddEmpate = 1 + (1 / empate);
		mod[0].listaJogos[indexJogo].oddVisitante = 1 + (1 / derrota);
	}
}
//Funcoes chamadas do menu
void Definicoes(modalidade *mod, int *quantidade)	//Da ao utilizador as definiçoes que pode alterar
{
	FILE *fModalidades, *fJogos, *fClubes, *fPoisson;
	char input, input2, input3, YN;
	char nomeFicheiro[200], nomeFicheiroJogos[200], nomeFicheiroClubes[200], nomeFicheiroJogos2[200], nomeFicheiroClubes2[200], nomeFicheiroPoisson[200], nomeFicheiroPoisson2[200], charAux[50];
	int inputInt, inputInt2;
	do
	{
		//Imprime as escolhas e le input
		input = -1;
		system("cls");
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
				input2 = -1;
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
						a.mediapts_casa = 0;
						a.mediapts_fora = 0;

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
						fprintf(fModalidades, "%s %d %f %f", mod[0].nome, mod[0].maxpts, mod[i].mediapts_casa, mod[i].mediapts_fora);
						for (int i = 1; i < *quantidade; i++)
						{
							fprintf(fModalidades, "\n%s %d %f %f", mod[i].nome, mod[i].maxpts, mod[i].mediapts_casa, mod[i].mediapts_fora);
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

						strcpy(nomeFicheiro, a.nome);
						strcat(nomeFicheiro, "-poisson.txt");
						fPoisson = fopen(nomeFicheiro, "w");
						fclose(fPoisson);

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
						strcpy(nomeFicheiroPoisson, mod[inputInt - 1].nome);
						strcat(nomeFicheiroPoisson2, "-poisson.txt");

						//Guarda novo nome dos ficheiros
						strcpy(nomeFicheiroClubes2, modAux2.nome);
						strcat(nomeFicheiroClubes2, "-clubes.txt");
						strcpy(nomeFicheiroJogos2, modAux2.nome);
						strcat(nomeFicheiroJogos2, "-jogos.txt");
						strcpy(nomeFicheiroPoisson, modAux2.nome);
						strcat(nomeFicheiroPoisson2, "-poisson.txt");

						//Muda de nome aos ficheiros
						rename(nomeFicheiroClubes, nomeFicheiroClubes2);
						rename(nomeFicheiroJogos, nomeFicheiroJogos2);
						rename(nomeFicheiroPoisson, nomeFicheiroPoisson2);

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
						fprintf(fModalidades, "%s %d %f %f", mod[0].nome, mod[0].maxpts, mod[0].mediapts_casa, mod[0].mediapts_fora);
						for (int i = 1; i < *quantidade; i++)
						{
							fprintf(fModalidades, "\n%s %d %f %f", mod[i].nome, mod[i].maxpts, mod[i].mediapts_casa, mod[i].mediapts_fora);
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

								//Apaga os poissons associados à modalidade
								strcpy(nomeFicheiro, mod[inputInt - 1].nome);
								strcat(nomeFicheiro, "-poisson.txt");
								remove(nomeFicheiro);

								//Organiza os dado internamente. Puxa tudo 1 para cima.
								for (int j = inputInt - 1; j < *quantidade; j++)
								{
									mod[j] = mod[j + 1];
								}
								*quantidade -= 1;

								//Apaga o ficheiro e reimprime tudo.
								fModalidades = fopen("modalidades.txt", "w");
								fprintf(fModalidades, "%s %d %f %f", mod[0].nome, mod[0].maxpts, mod[0].mediapts_casa, mod[0].mediapts_fora);
								for (int j = 1; j < *quantidade; j++)
								{
									fprintf(fModalidades, "\n%s %d %f %f", mod[j].nome, mod[j].maxpts, mod[j].mediapts_casa, mod[j].mediapts_fora);
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
				inputInt = -1;
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
						input3 = -1;
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
								clubeAux.ataque_casa = 0;
								clubeAux.ataque_fora = 0;
								clubeAux.defesa_casa = 0;
								clubeAux.defesa_fora = 0;

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
								AtribuiResultado(&mod[inputInt - 1]);
								CalculaMediaGolos(mod, inputInt - 1, quantidade);
								CalculaAtteDef(&mod[inputInt - 1]);
								Poisson(&mod[inputInt - 1]);
								CalculaOddsIniciais(&mod[inputInt - 1]);
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
								AtribuiResultado(&mod[inputInt - 1]);
								CalculaMediaGolos(mod, inputInt - 1, quantidade);
								CalculaAtteDef(&mod[inputInt - 1]);
								Poisson(&mod[inputInt - 1]);
								CalculaOddsIniciais(&mod[inputInt - 1]);
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
										AtribuiResultado(&mod[inputInt - 1]);
										CalculaMediaGolos(mod, inputInt - 1, quantidade);
										CalculaAtteDef(&mod[inputInt - 1]);
										Poisson(&mod[inputInt - 1]);
										CalculaOddsIniciais(&mod[inputInt - 1]);
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
							printf("INTRODUZA UM VALOR VALIDO.\n");
							break;
						}
						LimpaEcra();
					} while (input3 != '0');
				}
				else if (inputInt != 0)
				{
					printf("INTRODUZA UM VALOR VALIDO.\n");
					LimpaEcra();
				}
			} while (inputInt != 0);
			LimpaEcra();
			break;
		}
		case '3':	//Alterar Cotas
		{
			do
			{
				inputInt = -1;
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
					do
					{
						input2 = -1;
						printf("\t\t1- RECALCULAR COTAS\n\t\t0- SAIR\n\nOPCAO: ");
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
							CalculaMediaGolos(mod, inputInt - 1, quantidade);
							CalculaAtteDef(&mod[inputInt - 1]);
							Poisson(&mod[inputInt - 1]);
							CalculaOddsIniciais(&mod[inputInt - 1]);
							CriaJogos(&mod[inputInt - 1]);

							LimpaEcra();
							break;
						}
						case '0':
						{
							break;
						}
						default:
							printf("INTRODUZA UM VALOR VALIDO.\n");
							LimpaEcra();
							break;
						}
					} while (input2 != '0');
				}
				else if (inputInt != 0)
				{
					printf("INTRODUZA UM VALOR VALIDO.\n");
					LimpaEcra();
				}
			} while (inputInt != 0);
		}
		case '0':
			break;
		default:
			printf("INTRODUZA UM VALOR VALIDO.\n");
			LimpaEcra();
		}
	} while (input != '0');
}
void GereJogo(modalidade *mod, int *quantidade, int *saldo) //recebe uma modalidade, a quantidade que sera usada para o EscolheModalidade e o saldo para gerir a opcao Jogar do menu
{
	FILE *fSaldoEscrita;
	int indexModalidade, indexJogo, valorAposta = 0, intAux;
	char charAux;

	indexModalidade = EscolheModalidade(mod, quantidade); //-> escolhe a modalidade em que se vai jogar
	if (indexModalidade < 0)
	{
		return;
	}

	indexJogo = EscolheJogo(&mod[indexModalidade]); //-> escolhe 5 jogos random para o utilizador poder apostar

	if (indexJogo < 0)
	{
		return;
	}
	if (*saldo > 0)
	{
		do
		{
			intAux = -1;
			printf("\nEM QUE PRETENDE APOSTAR?");
			printf("\n1- VITORIA %s", mod[indexModalidade].listaJogos[indexJogo].casa);
			printf("\n2- EMPATE");
			printf("\n3- VITORIA %s", mod[indexModalidade].listaJogos[indexJogo].visitante);
			printf("\n\nOPCAO: ");
			scanf("%d", &intAux);
			while (getchar() != '\n');
		} while (intAux < 1 || intAux > 3);

		do
		{
			if (valorAposta > *saldo) //verifica se o valor apostado e superio ao saldo disponivel
			{
				printf("\nNAO TEM SALDO SUFICIENTE PARA APOSTAR."); //se for da erro
			}

			printf("\nQUANTIDADE A APOSTAR (1-100): ");
			scanf("%d", &valorAposta);
			while (getchar() != '\n');
		} while (valorAposta <= 0 || valorAposta > 100 || valorAposta > *saldo);

		charAux = AtribuiResultadoComProb(&mod[indexModalidade], indexJogo); //atribui resultado ao jogo

		if (charAux == 'V' && intAux == 1)
		{
			*saldo += valorAposta * mod[indexModalidade].listaJogos[indexJogo].oddCasa;
			printf("\nGANHOU! SALDO: %d", *saldo);
		}
		else if (charAux == 'E' && intAux == 2)
		{
			*saldo += valorAposta * mod[indexModalidade].listaJogos[indexJogo].oddEmpate;
			printf("\nGANHOU! SALDO: %d", *saldo);
		}
		else if (charAux == 'D' && intAux == 3)
		{
			*saldo += valorAposta * mod[indexModalidade].listaJogos[indexJogo].oddVisitante;
			printf("\nGANHOU! SALDO: %d", *saldo);
		}
		else
		{
			*saldo -= valorAposta; //se n acertou na aposta -> retira ao saldo o valor apostado
			printf("\nPERDEU! SALDO: %d", *saldo);
		}

		fSaldoEscrita = fopen("saldo.txt", "w");
		fprintf(fSaldoEscrita, "%d", *saldo);
		fclose(fSaldoEscrita);
	}
	else
	{
		printf("CARREGE O SEU SALDO PARA PODER JOGAR.");
	}
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
				userInput = -1;
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
					LimpaEcra();
					break;
				}
				case 0:
				{
					break;
				}
				default:
					printf("INTRODUZA UM VALOR VALIDO.\n");
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
	FILE *fResultados;
	char opcao = 0, nomeFicheiro[200];
	int inputInt;
	system("cls");
	do
	{
		opcao = -1;
		printf("\t1- LISTAR MODALIDADES.\n");
		printf("\t2- LISTAR CLUBES.\n");
		printf("\t3- LISTAR JOGOS.\n");
		printf("\t4- LISTAR RESULTADOS.\n");
		printf("\t0- SAIR.\n");
		printf("\nOPCAO: ");
		scanf("%c", &opcao);
		while (getchar() != '\n');

		switch (opcao)
		{
		case '1':	//Imprimir modalidades
		{
			for (int i = 0; i < *quantidade; i++)
			{
					printf("\n%s", mod[i].nome);
			}
			printf("\n");
			LimpaEcra();
			break;
		}
		case'2':	//Imprimir clubes
		{
			//Imprime todas a modalidades e escolhe uma
			do
			{
				inputInt = -1;
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
				if (inputInt > 0 && inputInt <= *quantidade)
				{
					for (int i = 0; i < mod[inputInt - 1].listaClubesCount; i++)
					{
						printf("\n%s", mod[inputInt - 1].listaClubes[i].nome);
					}
				}
				else if (inputInt != 0)
				{
					printf("INTRODUZA UM VALOR VALIDO.\n");
				}

				printf("\n");
				LimpaEcra();
			} while (inputInt != 0);
			break;
		}
		case '3':	//Imprimir jogos
		{
			//Imprime todas a modalidades e escolhe uma
			do
			{
				inputInt = -1;
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
				if (inputInt > 0 && inputInt <= *quantidade)
				{
					for (int i = 0; i < mod[inputInt - 1].listaJogosCount; i++)
					{
						printf("\n%s - %s", (*mod[inputInt - 1].listaJogos[i].casa).nome, (*mod[inputInt - 1].listaJogos[i].visitante).nome);
					}
				}
				else if (inputInt != 0)
				{
					printf("INTRODUZA UM VALOR VALIDO.\n");
				}				
				printf("\n");
				LimpaEcra();
			} while (inputInt != 0);			
			break;
		}
		case '4':	//Imprimir resultados
			do
			{
				inputInt = -1;
				system("cls");
				printf("ESCOLHA A MODALIDADE DOS RESULTADOS:\n");
				for (int i = 0; i < *quantidade; i++)
				{
					printf("\t\t%d- %s\n", i + 1, mod[i]);
				}
				printf("\t\t0- SAIR\nOPCAO: ");
				scanf("%d", &inputInt);
				while (getchar() != '\n');

				//Imprime todos os resultados
				if (inputInt > 0 && inputInt <= *quantidade)
				{
					char charAux1[100], charAux2[100];
					int intAux1, intAux2;

					strcpy(nomeFicheiro, mod[inputInt - 1].nome);
					strcat(nomeFicheiro, "-resultados.txt");
					if (FicheiroExiste(nomeFicheiro, &fResultados))
					{
						for (int i = 0; i < FicheiroLinhas(nomeFicheiro); i++)
						{
							fscanf(fResultados, "%s %d - %d %s", charAux1, &intAux1, &intAux2, charAux2);
							printf("\n%s %d - %d %s", charAux1, intAux1, intAux2, charAux2);
						}
						fclose(fResultados);
					}
					printf("\n");
					LimpaEcra();
				}
				else if (inputInt != 0)
				{
					printf("INTRODUZA UM VALOR VALIDO.\n");
					LimpaEcra();
				}
				printf("\n");
			} while (inputInt != 0);
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
