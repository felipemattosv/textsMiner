#include "documento.h"
#include "info.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct documento {

    char nome[100];
    char classe[100];
    Info * metricas;
    int qtdPalavras; //qtd de palavras diferentes
    int metricas_alocadas;

    int tam; //total de palavras

    double somaTF_IDF; //no programa 2: Buscador: Soma dos tf-idfs
};

Documento documento_alocar() {

    Documento d = (Documento)calloc(1, sizeof(struct documento));

    d->metricas = (Info *)calloc(100, sizeof(Info));

    for (int j=0; j<100; j++) {

        d->metricas[j] = info_alocar();
    }

    d->qtdPalavras = -1;

    d->metricas_alocadas = 100;

    d->tam = 0; 

    d->somaTF_IDF = 0.0;

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

void documento_imprimeBIN(Documento d, FILE * bin) {

    //Nome
    int tamNome = (strlen(d->nome) + 1);
    fwrite(&tamNome, sizeof(int), 1, bin);
    fwrite(d->nome, tamNome, 1, bin);

    //Classe
    int tamClasse = (strlen(d->classe) + 1);
    fwrite(&tamClasse, sizeof(int), 1, bin);
    fwrite(d->classe, tamClasse, 1, bin);

    //Metricas
    int qtdPalavras = (d->qtdPalavras + 1);
    fwrite(&qtdPalavras, sizeof(int), 1, bin);
    for (int j=0; j < qtdPalavras; j++) {

        info_imprimeBIN(d->metricas[j], bin);
    }

    int tam = d->tam;
    fwrite(&tam, sizeof(int), 1, bin);
}

Documento documento_lerBIN(Documento d, FILE * bin) {

    int tamNome=0;
    fread(&tamNome, sizeof(int), 1, bin);
    fread(d->nome, tamNome, 1, bin);
    
    int tamClasse=0;
    fread(&tamClasse, sizeof(int), 1, bin);
    fread(d->classe, tamClasse, 1, bin);
    
    int qtdPalavras=0;
    fread(&qtdPalavras, sizeof(int), 1, bin);
    d->qtdPalavras = qtdPalavras;
    d->metricas_alocadas = qtdPalavras;

    for (int x=0; x<100; x++) {

        info_destroy(d->metricas[x]);
    }
    free(d->metricas);

    d->metricas = (Info *)calloc(qtdPalavras, sizeof(Info));

    for (int q=0; q < qtdPalavras; q++) {

        d->metricas[q] = info_alocar();
    }

    for (int j=0; j < qtdPalavras; j++) {

        info_lerBIN(d->metricas[j], bin);
    }

    fread(&d->tam, sizeof(int), 1, bin);

    return d;
}

void documento_incrementaTamanho(Documento d) {

    d->tam++;
}

int documento_retornaTamanho(Documento d) {

    return d->tam;
}

void documento_setSomaTF_IDF(Documento d, double v) {

    d->somaTF_IDF = v;
}

double documento_retornaSomaTF_IDF(Documento d) {

    return d->somaTF_IDF;
}

void documento_incrementaFreq(Documento d, int index) {

    info_setFreq(d->metricas[index], (documento_retornaFreq(d, index) + 1));
}

int RetornaIndiceMetricas(int ind, Documento d) {

    for (int g=0; g <= documento_retornaQtdPalavras(d); g++) {

        if (documento_retornaPos(d, g) == ind) {
         
            return g;
        }
    }

    return -1;
}