#include "info.h"
#include <stdlib.h>
#include <stdio.h>

struct info {

    int pos;
    int freq;
    double tf_idf;
};

Info info_alocar() {

    return calloc(1, sizeof(struct info));
}