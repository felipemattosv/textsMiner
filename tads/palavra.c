#include "palavra.h"
#include "info.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct palavra {

    char * conteudo;
    Info * metricas;
    int aparicoes; /*Salva a qtd de arquivos em que a palavra aparece!
                     (NAO a qtd que aparece em cada arquivo)*/
};

Palavra palavra_alocar() {

    Palavra p = (Palavra)calloc(1, sizeof(struct palavra));

    p->conteudo = (char *)calloc(100, sizeof(char));
    
    p->metricas = (Info *)calloc(100, sizeof(Info));

    for (int j=0; j<100; j++) {

        p->metricas[j] = info_alocar();
    }

    p->aparicoes=0;

    return p;
}

char * palavra_retornaConteudo(Palavra p) {

    return p->conteudo;
}

void palavra_incrementaAparicoes(Palavra p) {

    p->aparicoes++;
}

void palavra_setConteudo(Palavra p, char * w) {

    strcpy(p->conteudo, w);
}

void palavra_setInfo(Palavra p, int numArqv, int newFreq) {

    info_setPos(p->metricas[p->aparicoes], numArqv);

    info_setFreq(p->metricas[p->aparicoes], newFreq);
}