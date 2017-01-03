#include "PlacardStructs.h"
#include "PlacardFunctions.h"

int main(void) //Menu
{
	char tecla_menu = 0;
	modalidade modalidades[10];
	int saldo, modalidadesCount, valorAposta, pontos, pontos2, indexJogo, indexModalidades;

	FicheiroLeData(modalidades, &modalidadesCount);

	printf("-ooooooooooo+ +ooooooooooo--ooooooooooo+ +ooooooooooo-.ooooooooooo+ /ooooooooooo:.oooooooooooo`\n");
	printf("+hhhhhhhhhhhh`hhhhhhhhhhhh++hhhhhhhhhhhh`hhhhhhhhhhhho/hhhhhhhhhhhh.yhhhhhhhhhhho/hhhhhhhhhhhh.\n");
	printf("+h+------:shh`hhh:..ohhhhh++hhho----yhhh`hhs:.```./yho/hhh+----yhhh.yo.....-:+hho/h+......:ohh.\n");
	printf("+h-```.````yh`hhh```/hhhhh++hhh.````ohhh`hy```.:```:ho/hhh.````+hhh.y+```..```oho/h:```..```sh.\n");
	printf("+h-```ho```sh`hhh```/hhhhh++hhy`````:hhh`hs```+h.``-ho/hhy`````:hhh.y+```sy```/ho/h:```yo```oh.\n");
	printf("+h-```ho```sh`hhh```/hhhhh++hho``.``.hhh`hs```+h.``-ho/hhs``-``.hhh.y+```yy```/ho/h:```ho```oh.\n");
	printf("+h-```ho```sh`hhh```/hhhhh++hh/``/```hhh`hs```+ho/+sho/hh+``/```yhh.y+```yy```/ho/h:```ho```oh.\n");
	printf(":h:```:-```yy`shh```/hhhhh::hh-``o.``shy sy```+hhhhhh/-hh:``+.``ohy`s+```::```oh/-h:```hs```sy`\n");
	printf("-h-   ```./ho shh`  /hhhhh--hy`  s-  :hs os   +hhhhhh:-hh`  o-  /hs`o/      `:yh:.h:  `yo   oy`\n");
	printf("+h-  `sssyyyh`yyy   :yyyyy+/ys   o:  .hh`ys   +y+::+y+/ys   o:  .yh.y/   -  `yyyo:y-   yo   oh.\n");
	printf("+y-  `hyyyyyh`yyy   :yyyyy+/y+   ``   yh`ys   +h.  .h+/y+   `    yh.y/   o`  :yyo:y-   yo   oh.\n");
	printf("+y-  `hyyyyyh`yyy   :yyyyy+/y:  `--   oh`ys   +h.  .h+/y:  `--   oh.y/   s/   syo:y-   y+   oh.\n");
	printf("+y-  `hyyyyyh`yyy   `..+yy+/h`  :yy   /h`yy   .:   :y+/h.  -hy`  /h.y/   sy`  -yo:y-   .`   sh.\n");
	printf("+y/..-hyyyyyh`yyy-.....+yy+/y...+yh-../h`yyo-````.:sy+/h...+yh:../h.yo...yy/...yo:y+......-+yh.\n");
	printf("+yyyyyyyyyyyh`yyyyyyyyyyyy+/yyyyyyyyyyyh`yyyyysssyyyy+/yyyyyyyyyyyh.yyyyyyyyyyyyo:yyyyyyyyyyyh.\n");
	printf(":ssssssssssso`osssssssssss:-osssssssssso +sssssssssss:-osssssssssso`+sssssssssss:-osssssssssso`\n");

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
			indexModalidades = EscolheModalidade(modalidades, &modalidadesCount);
			indexJogo = EscolheJogo(&modalidades[indexModalidades - 1]);

			//AQUI FAZ AQUELA PARTE TODA DE GERAR NUMEROS MUITO LINDA <3
			

			//AQUI VERIFICA SE GANHOU PERDEU EMPATOU E ACTUALIZA O SALDO


			printf("SIMULACAO CONCLUIDA!\n");
			break;
		case '3':
			ListarTudo(modalidades, &modalidadesCount);
			break;
		case '4':
			Definicoes(modalidades, &modalidadesCount);
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