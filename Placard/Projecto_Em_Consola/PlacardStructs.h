/*HEADER FILE COM AS STRUCTS NECESSARIAS PARA TODO O CODIGO DO PROJETO*/

#define n 18

typedef	struct
{
	char nome[60];
}clube;

typedef struct
{
	char nome[60];
	clube clubes[n];
}modalidade;