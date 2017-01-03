#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define maximoClubes 20
#define maximoJogos 320

typedef	struct
{
	char nome[60];
	float ataque_casa;
	float defesa_casa;
	float ataque_fora;
	float defesa_fora;
}clube;

typedef struct
{
	clube *casa;
	clube *visitante;
	float PoissonCasa[120];
	float PoissonFora[120];
	float oddCasa, oddEmpate, oddVisitante;
	int resultado[2];
}jogo;

typedef struct
{
	char nome[60];
	clube listaClubes[maximoClubes];
	jogo listaJogos[maximoJogos];
	int listaClubesCount;
	int listaJogosCount;
	int maxpts;
	float mediapts_casa;
	float mediapts_fora;
}modalidade;
