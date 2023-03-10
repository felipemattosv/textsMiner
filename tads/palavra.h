#pragma once

#include <stdio.h>

typedef struct palavra *Palavra;

Palavra palavra_alocar();

Palavra palavra_realocar(Palavra);

int palavra_retornaMetricasAlocadas(Palavra);

char * palavra_retornaConteudo(Palavra);

void palavra_destroy(Palavra);

void palavra_incrementaAparicoes(Palavra);

void palavra_setConteudo(Palavra, char *);

void palavra_setInfo(Palavra, int, int);

void palavra_incrementaMetricas(Palavra);

int palavra_retornaFreq(Palavra, int);

void palavra_setArqvPassado(Palavra, int);

int palavra_retornaArqvPassado(Palavra);

int palavra_retornaAparicoes(Palavra);

int palavra_retornaPos(Palavra, int);

void palavra_atualizaPos(Palavra, int);

int palavra_indice_emMetricas(Palavra, int);

void palavra_calculaTF_IDFs(Palavra, double);

double palavra_retornaTF_IDFs(Palavra, int);

void palavra_imprimeBIN(Palavra, FILE *);

Palavra palavra_lerBIN(Palavra, FILE *);

Palavra * palavras_ordemAlfabetica(Palavra *, int);

int ConteudoCompara(const void *, const void *);

Palavra palavra_ordenaMetricas(Palavra);

int FreqCompara(const void *, const void *);