#include "palavra.h"
#include "info.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct palavra {

    char * conteudo;
    Info * metricas;
    int metricas_alocadas;
    int aparicoes; /*Salva a qtd de arquivos em que a palavra aparece!
                     (NAO a qtd que aparece em cada arquivo)*/
    int arqvPassado; //Comentar!!
};

Palavra palavra_alocar() {

    Palavra p = (Palavra)calloc(1, sizeof(struct palavra));

    p->conteudo = (char *)calloc(100, sizeof(char));
    
    p->metricas = (Info *)calloc(100, sizeof(Info));

    for (int j=0; j<100; j++) {

        p->metricas[j] = info_alocar();
    }

    p->metricas_alocadas = 100;

    p->aparicoes=-1;

    p->arqvPassado=-1;

    return p;
}

Palavra palavra_realocar(Palavra p) {

    p->metricas_alocadas *= 2;

    p->metricas = (Info *)realloc(p->metricas, p->metricas_alocadas * sizeof(Info));

    for (int k=(p->metricas_alocadas / 2); k<p->metricas_alocadas; k++) {

        p->metricas[k] = info_alocar();
    }

    return p;
}

int palavra_retornaMetricasAlocadas(Palavra p) {

    return p->metricas_alocadas;
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

void palavra_incrementaMetricas(Palavra p) {

    int freqAntiga = info_retornaFreq(p->metricas[p->aparicoes]);

    info_setFreq(p->metricas[p->aparicoes], (freqAntiga + 1));
}

int palavra_retornaFreq(Palavra p, int numArqv) {

    return info_retornaFreq(p->metricas[numArqv]);
}

void palavra_setArqvPassado(Palavra p, int a) {

    p->arqvPassado = a;
}

int palavra_retornaArqvPassado(Palavra p) {

    return p->arqvPassado;
}

int palavra_retornaAparicoes(Palavra p) {

    return p->aparicoes;
}

int palavra_retornaPos(Palavra p, int h) {

    return info_retornaPos(p->metricas[h]);
}

void palavra_atualizaPos(Palavra p, int h) {

    info_setPos(p->metricas[p->aparicoes], h);
}

int palavra_indice_emMetricas(Palavra p, int arq) {

    for (int j=0; j <= p->aparicoes; j++) {

        if (info_retornaPos(p->metricas[j]) == arq) {
            
            return j;
        }
    }

    return -1;
}

void palavra_calculaTF_IDFs(Palavra p, double idf) {

    for (int q=0; q < p->aparicoes; q++) {

        int tf = info_retornaFreq(p->metricas[q]);

        double TF_IDF = tf * idf;

        info_setTF_IDF(p->metricas[q], TF_IDF);
    }
}

double palavra_retornaTF_IDFs(Palavra p, int contMetricas) {

    return info_retornaTF_IDF(p->metricas[contMetricas]);
}

void palavra_destroy(Palavra p) {

    for (int k=0; k<p->metricas_alocadas; k++) {

        info_destroy(p->metricas[k]);
    }

    free(p->metricas);

    free(p->conteudo);

    free(p);
}