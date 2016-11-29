#include <stdio.h>
#define a  10

typedef	struct
{
	char nome[60];

}clube;
typedef struct
{
	clube clubes[a];
}modalidade;

int main()
{
	int tecla_menu;

	do
	{
		printf("OPCAO:\n");
		printf("\t1- VER O SEU SALDO\n");
		printf("\t2- JOGAR\n");
		printf("\t3- LISTAR\n");
		printf("\t4- ALTERAR DEFINICOES\n");
		printf("\t5- GRAVAR\n");
		printf("\t0- SAIR\n");
		scanf("%d", tecla_menu);

		switch (tecla_menu)
		{
		case 1:
			escolhemodalidade();
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		default:
			break;
		}
	} while (tecla_menu != 0);
	return 0;
}