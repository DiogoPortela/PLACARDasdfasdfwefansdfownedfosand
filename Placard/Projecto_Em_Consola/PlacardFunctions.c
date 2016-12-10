#include "PlacardStructs.h"


//PRONTAS
int TestaFicheiro(char nomeficheiro[]) //testa se determinado ficheiro existe
{
	FILE *fd;
	fd = fopen(nomeficheiro, "r");
	if (fd == NULL)
	{
		printf("\nFICHEIRO %s NAO ENCONTRADO!\n\n", nomeficheiro);
		return 0;
	}
	return 1;
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
void AtribuiResultado(clube a, clube b)
{
	FILE *fd;
	fd = fopen("jogosfutebol.txt", "r");

	clube aux1, aux2;
	int agolos, bgolos;
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




//A PERCISAR DE REWORK
modalidade EscolheModalidade()
{
	char modalidade_introduzida[20] = "", opcao = 0, aux = 1;
	modalidade modaux;
	FILE *fd;

	fd = fopen("modalidades.txt", "r");
	if (TestaFicheiro("modalidades.txt"))
	{
		do
		{
			system("cls");
			printf("MODALIDADE DA APOSTA:\n");
			// LOOP QUE IMPRIME TODAS AS MODALIDADES APARTIR DO FICHEIRO
			//for(int i = 0; i < NUMERO DE LINHAS EXISTENTES NO FICHEIRO; i++)

			printf("\t1- FUTEBOL\n");
			printf("\t2- BASQUETEBOL\n");
			printf("\t3- TENIS\n");
			printf("\t0- VOLTAR ATRAS\n");
			printf("OPCAO: ");
			scanf("%d", &opcao);
			//opcao = getch(opcao);    ISTO AINDA NAO ESTA CORRECTO

			switch (opcao)
			{
			case 1:
				strcpy(modalidade_introduzida, "FUTEBOL");
				break;
			case 2:
				strcpy(modalidade_introduzida, "BASQUETEBOL");
				break;
			case 3:
				strcpy(modalidade_introduzida, "TENIS");
				break;
			case 0:
				break;
			default:
				printf("SELECIONE UMA DAS OPCOES!\n");
				break;
			}

		} while (opcao != 0 && (fscanf(fd, "%s\n", &modaux.nome) != EOF) && (strcmp(modalidade_introduzida, modaux.nome) != 0));
		fclose(fd);
	}
	return modaux;
}

void criajogo(modalidade mod, clube casa, clube fora) //tera de ser alterado para cada evento ter 1 ficheiro de jogos.
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