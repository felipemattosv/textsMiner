#pragma once

#include <stdio.h>

typedef struct indices *Indices;

Indices indices_create();

Indices indices_realocar(Indices);

Indices indices_lerSumario(Indices, char *);

Indices indices_lerTexto(Indices, FILE *);

int indicePalavra(char *, Indices);

void RegistraPalavra(Indices, char *);