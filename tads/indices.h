#pragma once

#include <stdio.h>

typedef struct indices *Indices;

Indices indices_create();

Indices indices_realocarWordIndex(Indices);

Indices indices_lerSumario(Indices, char *);

Indices indices_lerTexto(Indices, FILE *);

int indicePalavra(char *, Indices);

void RegistraPalavra(Indices, char *);

Indices indices_docSetClasseENome(Indices, char *, char *);

Indices indices_gerarDocIndex(Indices);

void indices_calculaTF_IDFs(Indices);

double CalculaIDF(int, int);

//Apenas para teste:
void indices_imprimeDocIndex(Indices);

void indices_destroy(Indices);

void indices_imprimeEstatisticas(Indices);

void indices_gerarRelatorioBin(Indices, char *);


//Acontecera no Classificador.c(prox programa)
Indices indices_lerBIN(Indices, char *);