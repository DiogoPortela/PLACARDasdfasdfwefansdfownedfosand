#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
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
	clube casa;
	clube visitante;
	int resultado[2];
}jogo;

typedef struct
{
	char nome[60];
	clube listaClubes[20];
	jogo listaJogos[320];
	int maxpts, identificador;
}modalidade;
