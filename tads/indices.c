#include "indices.h"
#include "palavra.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct indices {

    Palavra * idxPalavras;
    int palavras_alocadas; //qtd de espacos alocados
    int palavras_usadas;   //qtd de espacos alocados usados

    //Documento * idxDocumentos;
    //int documentos_alocados;
    //int documentos_usados;
};

Indices indices_create() {

    Indices i = calloc(1, sizeof(struct indices));

    //cria idxPalavras
    //atribui 'palavras_alocadas'
    //atribui '0' para 'palavras_usadas'
    i->idxPalavras = calloc(1, sizeof(Palavra *));

    for (int j=0; j<100; j++) {

        i->idxPalavras[j] = palavra_alocar();
    }

    i->palavras_alocadas = 100;
    i->palavras_usadas = 0;

    //Futuro:
    //cria idxDocumentos
    //atribui 'documentos_alocados'
    //atribui '0' para 'documentos_usados'

    return i;
}

void indices_lerSumario(Indices i, char * caminhoSumario) {

    FILE * sumario = fopen(caminhoSumario, "r");

    //Pega a pasta_mae dentro de datasets (tiny, large, ...)
    char * pasta_mae = strtok(caminhoSumario, "/");
    pasta_mae = strtok(NULL, "/");

    while (!feof(sumario)) { //passa por todos os .txt listados

        char caminhoRelativoTexto[100];
        char classeTexto[100];
        char caminhoAbsolutoTexto[1000];

        fscanf(sumario, "%s %s\n", caminhoRelativoTexto, classeTexto);

        sprintf(caminhoAbsolutoTexto, "datasets/%s/%s", pasta_mae, caminhoRelativoTexto);

        FILE * texto = fopen(caminhoAbsolutoTexto, "r");

        indices_lerTexto(i, texto); //passar classe do texto para indice de docs

        fclose(texto);
    }
    
    fclose(sumario);
}

void indices_lerTexto(Indices i, FILE * texto) {

    char word[100];
    int index;

    while (!feof(texto)) {

        fscanf(texto, "%s", word);

        /*
        indicePalavra() retorna:
        - Caso a palavra ja esteja registrada: seu idx;
        - Caso a palavra nao esteja registrada: -1; 
        */
        index = indicePalavra(word, i);

        if(index == -1) {

            //Adiciona palavra ao indice (palavras_usadas++)
            
        }
        else {

            //Aumenta frequencia da palavra
            
        }
    }

}

int indicePalavra(char * w, Indices i) {

    for (int j=0; j<i->palavras_usadas; j++) {

        if (strcmp(w, RetornaConteudo(i->idxPalavras[j])) == 0) {

            return j;
        }
    }

    return -1;
}