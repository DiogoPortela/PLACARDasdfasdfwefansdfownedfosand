#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define Numero 60

typedef	struct
{
	char nome[Numero];
	float probabilidade;
}clube;

typedef struct
{
	char nome[Numero];
	clube clube[Numero];
	int maxpts, identificador;
}modalidade;

typedef struct
{
	char text[Numero];
}string;