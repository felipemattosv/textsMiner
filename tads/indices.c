#include "indices.h"
#include "palavra.h"
#include "documento.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

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
        i->documentos_usados++;

        //Registra passagem para novo texto
        i->numArqv++;

        fclose(texto);
    }
    fclose(sumario);

    return i;
}

Indices indices_lerTexto(Indices i, FILE * texto) {

    char word[100];

    while (!feof(texto)) {

        fscanf(texto, "%s", word);

        int index = indicePalavra(word, i);

        if(index == -1) {

            //Checa se precisa de Realloc
            if (i->palavras_usadas == i->palavras_alocadas) {
                
                i = indices_realocarWordIndex(i);
            }

            RegistraPalavra(i, word); //Adiciona palavra ao indice
            i->palavras_usadas++;
        }
        else {
            
            //Verifica se eh a 1a aparicao nesse texto
            if(palavra_retornaArqvPassado(i->idxPalavras[index]) != i->numArqv) {

                palavra_setArqvPassado(i->idxPalavras[index], i->numArqv);
                palavra_incrementaAparicoes(i->idxPalavras[index]);

                if (palavra_retornaAparicoes(i->idxPalavras[index]) == (palavra_retornaMetricasAlocadas(i->idxPalavras[index]) -1)) {

                    i->idxPalavras[index] = palavra_realocar(i->idxPalavras[index]);
                }

                palavra_atualizaPos(i->idxPalavras[index], i->numArqv); //Seta a posicao de p->metricas[p->aparicoes] como sendo o .txt atual
            }

            palavra_incrementaMetricas(i->idxPalavras[index]); //Aumenta frequencia da palavra no documento atual
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

//Testando:
void indices_imprimeDocIndex(Indices i) {

    printf("classe: %s\n\n", documento_retornaClasse(i->idxDocumentos[249]));

    for (int k=0; k<7; k++) {

        printf("POS DA PALAVRA NO IDX PALAVRAS: %d\n", documento_retornaPos(i->idxDocumentos[249], k));
        printf("FREQ DA PALAVRA NO IDX PALAVRAS: %d\n", documento_retornaFreq(i->idxDocumentos[249], k));

        printf("\n");
    }
}

void indices_calculaTF_IDFs(Indices i) {

    for (int k=0; k < i->palavras_usadas; k++) {

        double idf = CalculaIDF(i->numArqv, (palavra_retornaAparicoes(i->idxPalavras[k]) + 1));

        palavra_calculaTF_IDFs(i->idxPalavras[k], idf);
    }
}

double CalculaIDF(int n, int df) {

    return log((double)(1 + n)/(1 + df)) + 1;
}

void indices_destroy(Indices i) {

    for (int k=0; k<i->palavras_alocadas; k++) {

        palavra_destroy(i->idxPalavras[k]);
    }

    free(i->idxPalavras);

    for (int k=0; k<i->documentos_alocados; k++) {

       documento_destroy(i->idxDocumentos[k]);
    }

    free(i->idxDocumentos);

    free(i);
}

void indices_imprimeEstatisticas(Indices i) {

    printf("Num. de palavras diferentes: %d\n", (i->palavras_usadas - 1));
    printf("Num. de documentos: %d\n", i->documentos_usados);
}

void indices_gerarRelatorioBin(Indices i, char * caminhoBIN) {

    FILE * bin = fopen(caminhoBIN, "w+b");

    if (bin == NULL) {
     
        printf("ERRO! %s eh um caminho INVALIDO para o binario!\n", caminhoBIN);
        exit(1);
    }

    //Imprime indice de palavras:
    int qtdPalavras = (i->palavras_usadas - 1);
    fwrite(&qtdPalavras, sizeof(int), 1, bin);

    for (int k=0; k<i->palavras_usadas; k++) {

        palavra_imprimeBIN(i->idxPalavras[k], bin);
    }

    //Imprime indice de documentos:
    int qtdDocumentos = i->documentos_usados;
    fwrite(&qtdDocumentos, sizeof(int), 1, bin);

    for (int j=0; j<i->documentos_usados; j++) {

        documento_imprimeBIN(i->idxDocumentos[j], bin);
    }

    fclose(bin);
}

//Leitura no classificador.c (proximo programa)
Indices indices_lerBIN(Indices n, char * path) {

    n = (Indices)calloc(1, sizeof(struct indices));

    FILE * bin = fopen(path, "rb");

    //Lendo palavras:
    fread(&n->palavras_usadas, sizeof(int), 1, bin);

    n->idxPalavras = (Palavra *)calloc(n->palavras_usadas, sizeof(Palavra));
    n->palavras_alocadas = n->palavras_usadas;

    for (int k=0; k <= n->palavras_usadas; k++) {

        n->idxPalavras[k] = palavra_alocar();

        n->idxPalavras[k] = palavra_lerBIN(n->idxPalavras[k], bin);
    }

    //Lendo documentos:
    fread(&n->documentos_usados, sizeof(int), 1, bin);

    n->idxDocumentos = (Documento *)calloc(n->documentos_usados, sizeof(Documento));
    n->documentos_alocados = n->documentos_usados;

    for (int j=0; j < n->documentos_usados; j++) {

        n->idxDocumentos[j] = documento_alocar();

        n->idxDocumentos[j] = documento_lerBIN(n->idxDocumentos[j], bin);
    }

    fclose(bin);

    return n;
}

Indices indices_alfabeticaWordIndex(Indices i) {

    i->idxPalavras = palavras_ordemAlfabetica(i->idxPalavras, i->palavras_usadas - 1);

    return i;
}