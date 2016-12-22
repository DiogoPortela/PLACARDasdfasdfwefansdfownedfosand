#include "PlacardStructs.h"
#include "PlacardFunctions.h"

int main(void) //Menu
{
	char tecla_menu = 0;
	modalidade modaux, modalidades[10];
	int pontos, pontos2;

	FicheiroLeModalidades(modalidades);
	//Ler Clubes
	//Ler Resultados

	do
	{
		printf("-----------------------\n");
		printf("1- VER O SEU SALDO\n");
		printf("2- JOGAR\n");
		printf("3- LISTAR\n");
		printf("4- ALTERAR DEFINICOES\n");
		printf("5- GRAVAR\n");
		printf("0- SAIR\n\n");
		printf("OPCAO: ");
		scanf("%c", &tecla_menu);
		while (getchar() != '\n');

		switch (tecla_menu)
		{
		case '1':	
			break;
		case '2':
			modalidades[0].maxpts = 6;
			/*int contadordaseed = 0;
			for (int i = 0; i < FicheiroLinhas("clubes.txt"); i++)
			{
				for (int j = 0; j < FicheiroLinhas("clubes.txt"); j++)
				{
					if (i != j)
					{
						srand(SeedAleatoria() + contadordaseed);
						CriaJogo(modalidades[0], i, j);
						AtribuiResultado(modalidades[0], i, j);
						contadordaseed++;
					}
				}
				
			}
			*/
			pontos = CalculaDifGolos(modalidades[0], 0);
			pontos2 = CalculaDifGolos(modalidades[0], 1);
			printf("SIMULACAO CONCLUIDA!\n");
			printf("%d %d\n", pontos, pontos2);
			//modaux = EscolheModalidade(modalidades);
			break;
		case '3':
			ListarTudo();
			break;
		case '4':
			break;
		case '5':
			break;
		default:
			break;
		}
	} while (tecla_menu != '0');
	return 0;
}