#include "documento.h"
#include "info.h"
#include <stdlib.h>
#include <string.h>

struct documento {

    char nome[100];
    char classe[100];
    Info * metricas;
    int qtdPalavras;
};

Documento documento_alocar() {

    Documento d = (Documento)calloc(1, sizeof(struct documento));

    d->metricas = (Info *)calloc(100, sizeof(Info));

    for (int j=0; j<100; j++) {

        d->metricas[j] = info_alocar();
    }

    d->qtdPalavras = -1;

    return d;
}

void documento_setClasse(Documento d, char * c) {

    strcpy(d->classe, c);
}

char * documento_retornaClasse(Documento d) {

    return d->classe;
}

void documento_setNome(Documento d, char * n) {

    strcpy(d->nome, n);
}

char * documento_retornaNome(Documento d) {

    return d->nome;
}

void documento_incrementaQtdPalavras(Documento d) {

    d->qtdPalavras++;
}

void documento_setInfo(Documento d, int pos, int freq) {

    info_setPos(d->metricas[d->qtdPalavras], pos);

    info_setFreq(d->metricas[d->qtdPalavras], freq);
}

int documento_retornaQtdPalavras(Documento d) {

    return d->qtdPalavras;
}

int documento_retornaPos(Documento d, int h) {

    return info_retornaPos(d->metricas[h]);
}

int documento_retornaFreq(Documento d, int f) {

    return info_retornaFreq(d->metricas[f]);
}