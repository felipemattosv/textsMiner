#include "tads/indices.h"
#include "tads/palavra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SAIR 0
#define BUSCAR 1
#define CLASSIFICAR 2
#define RELATORIO_WORD 3
#define RELATORIO_DOCS 4

void buscador_menu(Indices, int);
void menu_imprimir();

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

    buscador_menu(indices, k);

    indices_destroy(indices);

    return 0;
}

void buscador_menu(Indices i, int k) {

    int op=-1, encerrar=0;

    while (1) {

        menu_imprimir();
        scanf("%d%*c", &op);

        switch (op) {

            case SAIR:
                encerrar = 1;
                break;

            case BUSCAR:
                indices_buscarNoticias(i);
                break;

            case CLASSIFICAR:
                indices_classificarNoticias(i, k);
                break;

            case RELATORIO_WORD:
                //indices_relatorioPalavra(i);
                break;

            case RELATORIO_DOCS:
                indices_relatorioDocumentos(i);
                break;
        }
        if (encerrar) break;
    }
}

void menu_imprimir() {

    printf("Informe a operacao desejada:\n");
    printf("0 - Encerrar programa\n");
    printf("1 - Buscar noticias\n");
    printf("2 - Classificar noticias\n");
    printf("3 - Relatorio de Palavra\n");
    printf("4 - Relatorio de Documentos\n");
}