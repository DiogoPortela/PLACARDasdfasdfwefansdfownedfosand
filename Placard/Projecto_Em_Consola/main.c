#include "PlacardStructs.h"
#include "PlacardFunctions.h"

int main(void) //Menu
{
	char tecla_menu = 0;
	modalidade modaux, modalidades[10];
	int pontos, pontos2;
	clube x, x2;

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
			*x.nome = "BENFICA";
			x.probabilidade = 0.6;
			*x2.nome = "SPORTING";
			x2.probabilidade = 0.4;
			break;
		case '2':
			modaux = EscolheModalidade(modalidades);
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