#include "palavra.h"
#include "info.h"
#include <stdlib.h>
#include <stdio.h>

struct palavra {

    char * conteudo;
    Info * metricas;
};

Palavra palavra_alocar() {

    Palavra p = calloc(1, sizeof(struct palavra));

    p->conteudo = calloc(100, sizeof(char));
    
    p->metricas = calloc(1, sizeof(Info *));

    for (int j=0; j<100; j++) {

        p->metricas[j] = info_alocar();
    }

    return p;
}

char * RetornaConteudo(Palavra p) {

    return p->conteudo;
}

void palavra_destroy(Palavra p) {

}