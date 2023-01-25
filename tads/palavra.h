#pragma once

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