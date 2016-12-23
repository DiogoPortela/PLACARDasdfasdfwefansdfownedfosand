/*HEADER FILE COM AS FUNCOES NECESSARIAS PARA TODO O CODIGO DO PROJETO*/
void			AtribuiResultado			(modalidade m, int a, int b);
void			CriaJogo					(modalidade mod, int a, int b);
int				CalculaDifGolos				(modalidade m, int a);
modalidade		EscolheModalidade			(modalidade *mod);
void			FicheiroExiste				(char nomeficheiro[], FILE **fd);
void			FicheiroImprimir			(char nomeficheiro[]);
void			FicheiroLeData				(modalidade *mod, jogo *jogos);
int				FicheiroLinhas				(char nomeficheiro[]);
void			GerirSaldo					(int *saldo);
void			ListarTudo					();
int				ResultadoRandom				(clube a, int max);
int				ValorRandomComBaseNaProb	(clube a, int max);