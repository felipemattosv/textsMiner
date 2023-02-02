#include <stdio.h>
#include "tads/palavra.h"
#include "tads/indices.h"
#include <stdlib.h>

int main(int argc, char * argv[]) {
    
    char caminhoSumario[100];
    char caminhoBIN[100];

    if (argc == 1) {

        printf("ERRO: Caminho para o train.txt nao foi informado!\n");
        printf("ERRO: Nome do arquivo de saida nao foi informado!\n");
        exit(1);
    }
    if (argc == 2) {

        printf("ERRO: Nome do arquivo de saida nao foi informado!\n");
        exit(1);
    }
    if (argc >= 3) {

        sprintf(caminhoSumario, "%s", argv[1]);
        sprintf(caminhoBIN, "%s", argv[2]);
    }

    Indices indices = indices_create();
    
    indices = indices_lerSumario(indices, caminhoSumario);

    indices = indices_gerarDocIndex(indices);

    indices_calculaTF_IDFs(indices);

    indices_gerarRelatorioBin(indices, caminhoBIN);

    indices_imprimeEstatisticas(indices);

    indices_destroy(indices);

    //No programa 2:
    //Indices next = indices_lerBIN(next, caminhoBIN);

    //indices_destroy(next);

    return 0;
}