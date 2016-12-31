/*HEADER FILE COM AS FUNCOES NECESSARIAS PARA TODO O CODIGO DO PROJETO*/
void			AtribuiResultado			(modalidade m, int a, int b);
void			CriaJogos					(modalidade *mod);
int				CalculaDifGolos				(modalidade m, int a, int ultimos);
float			CalculaMediaGolos			(void);
void			Definicoes					(modalidade *mod, int *quantidade);
jogo			EscolheJogo					(modalidade *mod);
modalidade		EscolheModalidade			(modalidade *mod, int *quantidade);
void			FicheiroExiste				(char nomeficheiro[], FILE **fd);
void			FicheiroImprimir			(char nomeficheiro[]);
void			FicheiroLeData				(modalidade *mod, int *quantidadeMods);
int				FicheiroLinhas				(char nomeficheiro[]);
void			GerirSaldo					(int *saldo);
void			ListarTudo					(void);
void			LimpaEcra(void);
int				ResultadoRandom				(clube a, int max);
int				SeedAleatoria				(void);
int				ValorRandomComBaseNaProb	(clube a, int max);