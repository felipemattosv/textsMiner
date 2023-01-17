#include <stdio.h>
#include "tads/palavra.h"
#include "tads/indices.h"

int main(int argc, char * argv[]) {
    
    char caminhoSumario[100];

    if (argc <= 1) {

        printf("ERRO: Caminho para o train.txt nao foi informado");
    }
    else {

        sprintf(caminhoSumario, "%s", argv[1]);
    }

    //Comentario apenas para teste de leitura (em indices_ler())

    //Indices indices = indices_create();
    Indices indices;

    //printf("%s\n", caminhoSumario);

    indices_ler(indices, caminhoSumario);


    return 0;
}