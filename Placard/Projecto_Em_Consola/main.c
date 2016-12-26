#include "PlacardStructs.h"
#include "PlacardFunctions.h"

int main(void) //Menu
{
	char tecla_menu = 0;
	modalidade modalidades[10], modAux;
	jogo jogoAux;
	int saldo, pontos, pontos2, linhasFicheiro, contadorDaSeed;

	FicheiroLeData(modalidades);
	
	printf("PLACARD 1.0\n");
	LimpaEcra();

	do
	{
		printf("1- SALDO\n");
		printf("2- JOGAR\n");
		printf("3- LISTAR\n");
		printf("4- ALTERAR DEFINICOES\n");
		printf("0- SAIR\n\n");
		printf("OPCAO: ");
		scanf("%c", &tecla_menu);
		while (getchar() != '\n');

		switch (tecla_menu)
		{
		case '1':
			GerirSaldo(&saldo);
			break;
		case '2':
			modAux = EscolheModalidade(modalidades);
			//pontos = CalculaMediaGolos();
			//printf("%f\n", pontos);

			//AQUI DEVE FAZER DISPLAY DOS JOGOS POSSIVEIS DE APOSTAR (ESCOLHER PRAI UNS 5 ALEATORIOS E CERTIFICAR QUE NAO ESCOHLE O MESMO
			//JOGO DUAS VEZES DURANTE UMA TEMPORADA) E MOSTRAR A TAL COTA. NAO ESQUECER USAR O ARRAY DE JOGOS E AUMENTA-LO PARA MAIS MODALIDADES.
			jogoAux = EscolheJogo(&modAux);
			//AQUI FAZ AQUELA PARTE TODA DE GERAR NUMEROS MUITO LINDA <3

			//AQUI VERIFICA SE GANHOU PERDEU EMPATOU E ACTUALIZA O SALDO

			
			printf("SIMULACAO CONCLUIDA!\n");
			
			/*pontos = CalculaDifGolos(modalidades[0], 0);
			pontos2 = CalculaDifGolos(modalidades[0], 1);
			printf("%d %d\n", pontos, pontos2);*/
			break;
		case '3':
			ListarTudo();
			break;
		case '4':
			Definicoes(&modalidades);
			break;
		case '0':
			break;
		default:
			printf("INTRODUZA UM VALOR VALIDO.\n");
			break;
		}		
		LimpaEcra();
	} while (tecla_menu != '0');
	return 0;
}