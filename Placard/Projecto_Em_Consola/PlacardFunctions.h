/*HEADER FILE COM AS FUNCOES NECESSARIAS PARA TODO O CODIGO DO PROJETO*/
void			AtribuiResultado			(modalidade m, int a, int b);
void			CriaJogo					(modalidade mod, int a, int b);
modalidade		EscolheModalidade			(modalidade *mod);
void			FicheiroExiste				(char nomeficheiro[], FILE **fd);
void			FicheiroImprimir			(char nomeficheiro[]);
void			FicheiroLeModalidades		(modalidade *mod);
int				FicheiroLinhas(char nomeficheiro[]);
void			ListarTudo					();
int				ResultadoRandom				(clube a, int max);
int				ValorRandomComBaseNaProb	(clube a, int max);