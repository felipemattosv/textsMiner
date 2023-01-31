#include "documento.h"
#include "info.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct documento {

    char nome[100];
    char classe[100];
    Info * metricas;
    int qtdPalavras;
    int metricas_alocadas;
};

Documento documento_alocar() {

    Documento d = (Documento)calloc(1, sizeof(struct documento));

    d->metricas = (Info *)calloc(100, sizeof(Info));

    for (int j=0; j<100; j++) {

        d->metricas[j] = info_alocar();
    }

    d->qtdPalavras = -1;

    d->metricas_alocadas = 100;

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

void documento_dobraMetricasAlocadas(Documento d) {

    d->metricas_alocadas *= 2;
}

int documento_retornaMetricasAlocadas(Documento d) {

    return d->metricas_alocadas;
}

Documento documento_realocar(Documento d) {

    d->metricas = (Info *)realloc(d->metricas, d->metricas_alocadas * sizeof(Info));

    for (int k=(d->metricas_alocadas / 2); k<d->metricas_alocadas; k++) {

        d->metricas[k] = info_alocar();
    }

    return d;
}

Documento RegistraPalavraNoDocumento(Documento d, int pos, int freq) {

    d->qtdPalavras++;

    if (d->qtdPalavras == d->metricas_alocadas) {

        documento_dobraMetricasAlocadas(d);
        d = documento_realocar(d);
    }

    documento_setInfo(d, pos, freq);

    return d;
}

void documento_destroy(Documento d) {

    for (int k=0; k<d->metricas_alocadas; k++) {

        info_destroy(d->metricas[k]);
    }

    free(d->metricas);

    free(d);
}