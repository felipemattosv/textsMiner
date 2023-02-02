#pragma once

#include <stdio.h>

typedef struct info *Info;

Info info_alocar();

void info_setPos(Info, int);

void info_setFreq(Info, int);

int info_retornaFreq(Info);

int info_retornaPos(Info);

void info_setTF_IDF(Info, double);

double info_retornaTF_IDF(Info);

void info_destroy(Info);

void info_imprimeBIN(Info, FILE *);

void info_lerBIN(Info, FILE *);