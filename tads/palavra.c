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
    int arqvPassado; //Comentar!!
};

Palavra palavra_alocar() {

    Palavra p = (Palavra)calloc(1, sizeof(struct palavra));

    p->conteudo = (char *)calloc(100, sizeof(char));
    
    p->metricas = (Info *)calloc(100, sizeof(Info));

    for (int j=0; j<100; j++) {

        p->metricas[j] = info_alocar();
    }

    p->aparicoes=-1;

    p->arqvPassado=-1;

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