#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define n 60

typedef	struct
{
	char nome[n];
	float probabilidade;
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