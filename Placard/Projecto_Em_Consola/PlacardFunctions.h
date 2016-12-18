/*HEADER FILE COM AS FUNCOES NECESSARIAS PARA TODO O CODIGO DO PROJETO*/
void			AtribuiResultado			(clube a, clube b);
void			CriaJogo					(modalidade mod, clube casa, clube fora);
modalidade		EscolheModalidade			(modalidade *mod);
void			FicheiroExiste				(char nomeficheiro[], FILE **fd);
void			FicheiroImprimir			(char nomeficheiro[]);
void			FicheiroLeModalidades		(modalidade *mod);
int				FicheiroLinhas(char nomeficheiro[]);
void			ListarTudo					();
int				ResultadoRandom				(clube a, int max);
int				ValorRandomComBaseNaProb	(clube a, int max);