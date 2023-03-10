#include "indices.h"
#include "palavra.h"
#include "documento.h"
#include "info.h"
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
        
        i = indices_docSetClasseENome(i, classeTexto, caminhoRelativoTexto);

        i = indices_lerTexto(i, texto);

        //i = indices_docSetClasseENome(i, classeTexto, caminhoRelativoTexto);
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

        documento_incrementaTamanho(i->idxDocumentos[i->numArqv]);

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
    int qtdPalavras = (i->palavras_usadas);
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

    if (bin == NULL) {

        printf("Binario nao encontrado em: '%s'!\n", path);
        exit(1);
    }

    //Lendo palavras:
    fread(&n->palavras_usadas, sizeof(int), 1, bin);

    n->idxPalavras = (Palavra *)calloc(n->palavras_usadas, sizeof(Palavra));
    n->palavras_alocadas = n->palavras_usadas;

    for (int k=0; k < n->palavras_usadas; k++) {

        n->idxPalavras[k] = palavra_alocar();

        n->idxPalavras[k] = palavra_lerBIN(n->idxPalavras[k], bin);
    }

    //Lendo documentos:
    fread(&n->documentos_usados, sizeof(int), 1, bin);

    n->idxDocumentos = (Documento *)calloc(n->documentos_usados, sizeof(Documento));
    n->documentos_alocados = n->documentos_usados;

    for (int j=0; j<n->documentos_usados; j++) {

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

void indices_relatorioDocumentos(Indices i) {

    qsort(i->idxDocumentos, i->documentos_usados, sizeof(Documento), docIndex_ordenaDecrescenteTamanho); 

    printf("10 Documentos mais longos:\n");
    for (int j=0; j<10; j++) {

        printf("Nome: %s", documento_retornaNome(i->idxDocumentos[j]));
        printf(" | Classe: %s", documento_retornaClasse(i->idxDocumentos[j]));
        printf(" | Tamanho: %d\n", documento_retornaTamanho(i->idxDocumentos[j]));
    }

    printf("\n");

    qsort(i->idxDocumentos, i->documentos_usados, sizeof(Documento), docIndex_ordenaCrescenteTamanho);

    printf("10 Documentos mais curtos:\n");
    for (int j=0; j<10; j++) {

        printf("Nome: %s", documento_retornaNome(i->idxDocumentos[j]));
        printf(" | Classe: %s", documento_retornaClasse(i->idxDocumentos[j]));
        printf(" | Tamanho: %d\n", documento_retornaTamanho(i->idxDocumentos[j]));
    } 
}

int docIndex_ordenaDecrescenteTamanho(const void *d1, const void *d2) {

    Documento doc1 = *(Documento *)d1;
    Documento doc2 = *(Documento *)d2;

    return (documento_retornaTamanho(doc2) - documento_retornaTamanho(doc1));
}

int docIndex_ordenaCrescenteTamanho(const void *d1, const void *d2) {

    Documento doc1 = *(Documento *)d1;
    Documento doc2 = *(Documento *)d2;

    return (documento_retornaTamanho(doc1) - documento_retornaTamanho(doc2));
}

void indices_buscarNoticias(Indices i) {

    char c='0';
    char str[99];

    int * indicesPalavrasEncontradas = (int *)calloc(100, sizeof(int));
    int qtdIndices_u=0, qtdIndices_a=100;    
    Palavra * alvo=0;

    //Loop de leitura
    while (c != '\n') {

        scanf("%s", str);
        
        // Caso 'str' esteja no idxPalavras, ...
        alvo = RetornaPonteiroPalavra(i, str);

        if (alvo != NULL) {
        // ... salvo o indice de 'str' (no idxPalavras) no vetor 'indicesPalavrasEncontradas'
        
            if (qtdIndices_u == qtdIndices_a) {

                qtdIndices_a *= 2;
                indicesPalavrasEncontradas = (int *)realloc(indicesPalavrasEncontradas, qtdIndices_a * sizeof(int));
            }

            indicesPalavrasEncontradas[qtdIndices_u] = (alvo - i->idxPalavras);
            qtdIndices_u++;
        }

        scanf("%c", &c);
    }

    //Somar o tf-idf para cada documento
    for (int j=0; j < i->documentos_usados; j++) {

        double soma=0.0;

        for (int y=0; y < qtdIndices_u; y++) {
            
            for (int z=0; z < palavra_retornaAparicoes(i->idxPalavras[indicesPalavrasEncontradas[y]]); z++) {

                if (j == palavra_retornaPos(i->idxPalavras[indicesPalavrasEncontradas[y]], z)) {

                    soma += palavra_retornaTF_IDFs(i->idxPalavras[indicesPalavrasEncontradas[y]], z);
                }
            }
            
        }

        documento_setSomaTF_IDF(i->idxDocumentos[j], soma);
    }
    
    qsort(i->idxDocumentos, i->documentos_usados, sizeof(Documento), ComparaSomaTF_IDF);

    for (int n=0; n < 10; n++) {

        printf("Nome: %s", documento_retornaNome(i->idxDocumentos[n]));
        printf(" | Soma TF-IDFs: %lf\n", documento_retornaSomaTF_IDF(i->idxDocumentos[n]));
    }

    
    free(indicesPalavrasEncontradas);
}

int ComparaSomaTF_IDF(const void *d1, const void *d2) {

    Documento doc1 = *(Documento *)d1;
    Documento doc2 = *(Documento *)d2;

    return (int)(documento_retornaSomaTF_IDF(doc1) - documento_retornaSomaTF_IDF(doc2));
}

Palavra * RetornaPonteiroPalavra(Indices i, char * str) {

    Palavra * alvo=0;

    Palavra buscada = palavra_alocar();
    palavra_setConteudo(buscada, str);
    alvo = (Palavra *)bsearch(&buscada, i->idxPalavras, i->palavras_usadas, sizeof(Palavra), ConteudoCompara);
    palavra_destroy(buscada);

    return alvo;
}

void indices_classificarNoticias(Indices i, int k) {

    Documento docDigitado = documento_alocar();
    
    docDigitado = CriaDocumentoClassificador(i, docDigitado);

    

    

    documento_destroy(docDigitado);
}

Documento CriaDocumentoClassificador(Indices i, Documento d) {

    char c='0', str[99];
    Palavra * alvo;
    int ind=0;

    while (c != '\n') {

        scanf("%s", str);

        alvo = RetornaPonteiroPalavra(i, str);

        if (alvo != NULL) {

            ind = (alvo - i->idxPalavras);

            int index = RetornaIndiceMetricas(ind, d);

            if (index == -1) {
                
                //Registra palavra 
                documento_incrementaQtdPalavras(d);
                
                if (documento_retornaQtdPalavras(d) == documento_retornaMetricasAlocadas(d)) documento_realocar(d);
                
                documento_setInfo(d, ind, 1);
            }
            else {
                //Incrementa metricas da palavra
                documento_incrementaFreq(d, index);
            }
        }

        scanf("%c", &c);
    }
    documento_incrementaQtdPalavras(d);

    return d;
}

void indices_relatorioPalavra(Indices i) {

    char str[99];
    printf("Digite a palavra:\n");
    scanf("%s", str);

    int index=0, qtd=0;
    Palavra * alvo = RetornaPonteiroPalavra(i, str);

    if (alvo != NULL) {

        index = alvo - i->idxPalavras;

        printf("Aparece em %d noticias;\n", palavra_retornaAparicoes(i->idxPalavras[index]));

        i->idxPalavras[index] = palavra_ordenaMetricas(i->idxPalavras[index]);

        if (palavra_retornaAparicoes(i->idxPalavras[index]) > 10) qtd = 10;
        else qtd = palavra_retornaAparicoes(i->idxPalavras[index]);
    }

    else printf("Palavra '%s' nao encontrada!\n", str);
}