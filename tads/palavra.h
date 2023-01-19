#pragma once

typedef struct palavra *Palavra;

Palavra palavra_alocar();

char * palavra_retornaConteudo(Palavra);

void palavra_destroy(Palavra);

void palavra_incrementaAparicoes(Palavra);

void palavra_setConteudo(Palavra, char *);

void palavra_setInfo(Palavra, int, int);