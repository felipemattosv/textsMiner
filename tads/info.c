#include "info.h"
#include <stdlib.h>
#include <stdio.h>

struct info {

    int pos; // P/ as Palavras: num do doc ; P/ os Docs: num da palavra
    int freq;
    double tf_idf; //Utilizado somente p/ as palavras (do idxPalavras)
};

Info info_alocar() {

    return (Info)malloc(1 * sizeof(struct info));
}

void info_setPos(Info inf, int numArqv) {

    inf->pos = numArqv;
}

void info_setFreq(Info inf, int newFreq) {

    inf->freq = newFreq;
}

int info_retornaFreq(Info inf) {

    return inf->freq;
}

int info_retornaPos(Info inf) {

    return inf->pos;
}

void info_setTF_IDF(Info inf, double TF_IDF) {

    inf->tf_idf = TF_IDF;
}

double info_retornaTF_IDF(Info inf) {

    return inf->tf_idf;
}

void info_destroy(Info inf) {

    free(inf);
}

void info_imprimeBIN(Info inf, FILE * bin) {

    fwrite(&inf->pos, sizeof(int), 1, bin);

    fwrite(&inf->freq, sizeof(int), 1, bin);
    
    fwrite(&inf->tf_idf, sizeof(double), 1, bin);
}

void info_lerBIN(Info inf, FILE * bin) {

    fread(&inf->pos, sizeof(int), 1, bin);

    fread(&inf->freq, sizeof(int), 1, bin);
    
    fread(&inf->tf_idf, sizeof(double), 1, bin);    
}