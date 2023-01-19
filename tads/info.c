#include "info.h"
#include <stdlib.h>
#include <stdio.h>

struct info {

    int pos; //IdxPalavras: numero do documento
    int freq;
    double tf_idf;
};

Info info_alocar() {

    return calloc(1, sizeof(struct info));
}

void info_setPos(Info inf, int numArqv) {

    inf->pos = numArqv;
}

void info_setFreq(Info inf, int newFreq) {

    inf->freq = newFreq;
}