#define _CRT_SECURE_NO_WARNINGS
#define n 60

typedef	struct
{
	char nome[n];
}clube;

typedef struct
{
	char nome[n];
	clube clubes[n];
}evento;

typedef struct
{
	char nome[n];
	clube evento[n];
}modalidade;