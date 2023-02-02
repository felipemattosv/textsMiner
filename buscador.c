#include "tads/indices.h"
#include "tads/palavra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]) {

    char caminhoBIN[100];
    int k=0;

    if (argc == 1) {

        printf("ERRO: Caminho para o binario nao foi informado!\n");
        printf("ERRO: 'K' nao foi informado!\n");
        exit(1);
    }
    if (argc == 2) {

        printf("ERRO: 'K' nao foi informado!\n");
        exit(1);
    }
    if (argc >= 3) {

        sprintf(caminhoBIN, "%s", argv[1]);
        k = atoi(argv[2]);
    }

    Indices indices = indices_lerBIN(indices, caminhoBIN);

    indices_destroy(indices);

    return 0;
}