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

    //Salva a posicao do arquivo atual no sumario
    int numArqv;
};

Indices indices_create() {

    Indices i = (Indices)calloc(1, sizeof(struct indices));

    //cria idxPalavras
    //atribui 'palavras_alocadas'
    //atribui '0' para 'palavras_usadas'
    i->idxPalavras = (Palavra *)calloc(100, sizeof(Palavra));

    for (int j=0; j<100; j++) {

        i->idxPalavras[j] = palavra_alocar();
    }

    i->palavras_alocadas = 100;
    i->palavras_usadas = 0;

    //Futuro:
    //cria idxDocumentos
    //atribui 'documentos_alocados'
    //atribui '0' para 'documentos_usados'

    //atribui '0' para numAqrv (inicio no primeiro arquivo listado em train.txt)
    i->numArqv = 0;

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

        //Registra passagem para novo texto
        i->numArqv++;

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
        - Caso a palavra NAO esteja registrada: -1;
        */
        index = indicePalavra(word, i);

        if(index == -1) {

            //Adiciona palavra ao indice (palavras_usadas++) !!! Checar se precisa de Realloc
            RegistraPalavra(i, word);
            i->palavras_usadas++;
        }
        else {

            //Aumenta frequencia da palavra no documento atual
            
        }
    }

}

int indicePalavra(char * w, Indices i) {

    for (int j=0; j<i->palavras_usadas; j++) {

        if (strcmp(w, palavra_retornaConteudo(i->idxPalavras[j])) == 0) {

            return j;
        }
    }

    return -1;
}

void RegistraPalavra(Indices i, char * w) {

    palavra_incrementaAparicoes(i->idxPalavras[i->palavras_usadas]);

    palavra_setConteudo(i->idxPalavras[i->palavras_usadas], w);

    /*
    setInfo() params:
    1: palavra no indice;
    2: posicao;
    3: freq;
    */
    palavra_setInfo(i->idxPalavras[i->palavras_usadas], i->numArqv, 1);
}