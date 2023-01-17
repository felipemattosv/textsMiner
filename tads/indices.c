#include "indices.h"
#include "palavra.h"
#include <stdio.h>
#include <string.h>

struct indices {

    Palavra * idxPalavras;
    int palavras_alocadas; //qtd de espacos alocados
    int palavras_usadas;   //qtd de espacos alocados usados

    //Documento * idxDocumentos;
    //int documentos_alocados;
    //int documentos_usados;
};

Indices indices_create() {

    //cria idxPalavras
    //atribui 'palavras_alocadas'
    //atribui '0' para 'palavras_usadas'

    //cria idxDocumentos
    //atribui 'documentos_alocados'
    //atribui '0' para 'documentos_usados'
}

void indices_ler(Indices i, char * caminhoSumario) {

    FILE * sumario = fopen(caminhoSumario, "r");

    //Pega a pasta_mae dentro de datasets
    char * pasta_mae = strtok(caminhoSumario, "/");
    pasta_mae = strtok(NULL, "/");

    while (!feof(sumario)) { //passa por todos os .txt listados

        char caminhoRelativoTexto[100];
        char classeTexto[100];
        char caminhoAbsolutoTexto[1000];

        fscanf(sumario, "%s %s\n", caminhoRelativoTexto, classeTexto);

        sprintf(caminhoAbsolutoTexto, "datasets/%s/%s", pasta_mae, caminhoRelativoTexto);

        //Le o texto do ciclo
        FILE * texto = fopen(caminhoAbsolutoTexto, "r");

        while (!feof(texto)) {

            //Teste leitura de palavras
            char palavra[1000];

            fscanf(texto, "%s", palavra);
            printf("%s ", palavra);
        }

        fclose(texto);
    }
    
    fclose(sumario);
}