/*HEADER FILE COM AS FUNCOES NECESSARIAS PARA TODO O CODIGO DO PROJETO*/
void			AtribuiResultado			(modalidade m, int a, int b);
void			CriaJogo					(modalidade mod, int a, int b);
int				CalculaDifGolos				(modalidade m, int a, int ultimos);
float			CalculaMediaGolos			(void);
void			Definicoes					(modalidade *mod, jogo *jogos);
modalidade		EscolheModalidade			(modalidade *mod);
void			FicheiroExiste				(char nomeficheiro[], FILE **fd);
void			FicheiroImprimir			(char nomeficheiro[]);
void			FicheiroLeData				(modalidade *mod, jogo *jogos);
int				FicheiroLinhas				(char nomeficheiro[]);
void			GerirSaldo					(int *saldo);
void			ListarTudo					(void);
int				ResultadoRandom				(clube a, int max);
int				SeedAleatoria				(void);
void			Stop						(void);
int				ValorRandomComBaseNaProb	(clube a, int max);