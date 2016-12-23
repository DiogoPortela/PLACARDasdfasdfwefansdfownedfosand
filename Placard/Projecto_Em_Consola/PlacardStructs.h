#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef	struct
{
	char nome[60];
	float probabilidade;
}clube;

typedef struct
{
	char nome[60];
	clube listaClubes[20];
	int maxpts, identificador;
}modalidade;

typedef struct
{
	modalidade mod;
	clube casa;
	clube visitante;
	int resultado[2];
}jogo;