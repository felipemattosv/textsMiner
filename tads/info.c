#include "info.h"
#include <stdlib.h>
#include <stdio.h>

struct info {

    int pos; //numero do documento
    int freq;
    double tf_idf;
};

Info info_alocar() {

    return (Info)calloc(1, sizeof(struct info));
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