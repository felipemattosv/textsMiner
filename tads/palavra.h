#pragma once

typedef struct palavra *Palavra;

Palavra palavra_alocar();

char * RetornaConteudo(Palavra);

void palavra_destroy(Palavra);