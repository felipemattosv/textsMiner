#include "indices.h"
#include "palavra.h"

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

    //Le os arquivos listados no sumario

    /*
    FILE * sumario = fopen(caminhoSumario, "r");


    while (!eof(sumario)) { //esse loop passa por todos os .txt

        //Linha: "caminhoTexto" "classe"
        //Ex.: train/c3719052006int.txt int

        char caminhoTexto[100];
        char classeTexto[100];

        fscanf(sumario, "%s %s\n", caminhoTexto, classeTexto);

        //Le o texto do ciclo
        FILE * texto;

        texto = fopen(caminhoTexto, "r");

        //Salva palavras nos indices
    }
    

    fclose(sumario);

    */

}