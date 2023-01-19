#pragma once

#include <stdio.h>

typedef struct indices *Indices;

Indices indices_create();

void indices_lerSumario(Indices, char *);

void indices_lerTexto(Indices, FILE *);

int indicePalavra(char *, Indices);

void RegistraPalavra(Indices, char *);