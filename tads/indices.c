#include "indices.h"
#include "palavra.h"
#include "documento.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct indices {

    Palavra * idxPalavras;
    int palavras_alocadas; //qtd de espacos alocados
    int palavras_usadas;   //qtd de espacos alocados usados

    Documento * idxDocumentos;
    int documentos_alocados;
    int documentos_usados;

    //Salva a posicao do arquivo atual no sumario
    int numArqv;
};

Indices indices_create() {

    Indices i = (Indices)calloc(1, sizeof(struct indices));

    //Palavras:
    i->idxPalavras = (Palavra *)calloc(100, sizeof(Palavra));

    for (int j=0; j<100; j++) {

        i->idxPalavras[j] = palavra_alocar();
    }

    i->palavras_alocadas = 100;
    i->palavras_usadas = 0;

    //Documentos:
    i->idxDocumentos = (Documento *)calloc(100, sizeof(Documento));

    for (int k=0; k<100; k++) {

        i->idxDocumentos[k] = documento_alocar();
    }
    
    i->documentos_alocados = 100;
    i->documentos_usados = 0;

    //atribui '0' para numAqrv (inicio no primeiro arquivo listado em train.txt)
    i->numArqv = 0;

    return i;
}

Indices indices_realocarWordIndex(Indices i) {

    i->palavras_alocadas *= 2;

    i->idxPalavras = (Palavra *)realloc(i->idxPalavras, i->palavras_alocadas * sizeof(Palavra));

    for (int j = (i->palavras_alocadas/2); j<i->palavras_alocadas; j++) {

        i->idxPalavras[j] = palavra_alocar();
    }

    return i;
}

Indices indices_realocarDocIndex(Indices i) {

    i->documentos_alocados *= 2;

    i->idxDocumentos = (Documento *)realloc(i->idxDocumentos, i->documentos_alocados * sizeof(Documento));

    for (int j = (i->documentos_alocados/2); j<i->documentos_alocados; j++) {

        i->idxDocumentos[j] = documento_alocar();
    }

    return i;
}

Indices indices_lerSumario(Indices i, char * caminhoSumario) {

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
        
        i = indices_lerTexto(i, texto);

        i = indices_docSetClasseENome(i, classeTexto, caminhoRelativoTexto);

        //Registra passagem para novo texto
        i->numArqv++;

        fclose(texto);
    }
    fclose(sumario);

    return i;
}

Indices indices_lerTexto(Indices i, FILE * texto) {

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

            //Checa se precisa de Realloc
            if (i->palavras_usadas == i->palavras_alocadas) {
                
                i = indices_realocarWordIndex(i);
            }

            //Adiciona palavra ao indice
            RegistraPalavra(i, word);
            i->palavras_usadas++;
        }
        else {
            
            //Verifica se eh a 1a aparicao nesse texto
            if(palavra_retornaArqvPassado(i->idxPalavras[index]) != i->numArqv) {

                palavra_setArqvPassado(i->idxPalavras[index], i->numArqv);
                palavra_incrementaAparicoes(i->idxPalavras[index]);

                //Seta a posicao de p->metricas[p->aparicoes] como sendo o .txt atual
                palavra_atualizaPos(i->idxPalavras[index], i->numArqv);
            }

            //Aumenta frequencia da palavra no documento atual
            palavra_incrementaMetricas(i->idxPalavras[index]);
        }
    }

    return i;
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

    palavra_setArqvPassado(i->idxPalavras[i->palavras_usadas], i->numArqv);

    palavra_setConteudo(i->idxPalavras[i->palavras_usadas], w);

    /*
    setInfo() params:
    1: palavra no indice;
    2: posicao;
    3: freq;
    */
    palavra_setInfo(i->idxPalavras[i->palavras_usadas], i->numArqv, 1);
}

Indices indices_docSetClasseENome(Indices i, char * classTxt, char * pathTxt) {

    if (i->documentos_usados == i->documentos_alocados) {

            i = indices_realocarDocIndex(i);
    }
    
    documento_setClasse(i->idxDocumentos[i->numArqv], classTxt);
        
    char * nome_texto = strtok(pathTxt, "/");
    nome_texto = strtok(NULL, ".");
    sprintf(nome_texto, "%s.txt", nome_texto);
    documento_setNome(i->idxDocumentos[i->numArqv], nome_texto);

    return i;
}

Indices indices_gerarDocIndex(Indices i) {

    for (int j=0; j < i->numArqv; j++) {

        for (int k=0; k < i->palavras_usadas; k++) {

            int index = palavra_indice_emMetricas(i->idxPalavras[k], j);

            if(index != -1) {

                i->idxDocumentos[j] = RegistraPalavraNoDocumento(i->idxDocumentos[j], k, palavra_retornaFreq(i->idxPalavras[k], index));
            }
        }
    }

   return i;
}