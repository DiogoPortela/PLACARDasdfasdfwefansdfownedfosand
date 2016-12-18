#include "PlacardStructs.h"
#include "PlacardFunctions.h"

int main(void) //Menu
{
	char tecla_menu = 0;
	modalidade modaux, modalidades[10];
	int pontos, pontos2;
	clube x, x2, x3, x4, x5, x6;

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
			modaux = EscolheModalidade(modalidades);
			strcpy(x.nome, "BENFICA");
			strcpy(x2.nome, "SPORTING");
			strcpy(x3.nome, "FC.PORTO");
			strcpy(x4.nome, "SP.BRAGA");
			strcpy(x5.nome, "BOAVISTA");
			strcpy(x6.nome, "BELENENSES");
			modalidades[0].identificador = 1;
			modalidades[0].maxpts = 6;
			modalidades[0].clube[0] = x;
			modalidades[0].clube[1] = x2;
			modalidades[0].clube[2] = x3;
			modalidades[0].clube[3] = x4;
			modalidades[0].clube[4] = x5;
			modalidades[0].clube[5] = x6;
			AtribuiResultado(modalidades[0], 0, 1);
			AtribuiResultado(modalidades[0], 2, 3);
			AtribuiResultado(modalidades[0], 4, 5);
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