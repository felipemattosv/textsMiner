#pragma once

#include <stdio.h>
#include "palavra.h"
#include "documento.h"

typedef struct indices *Indices;

Indices indices_create();

Indices indices_realocarWordIndex(Indices);

Indices indices_lerSumario(Indices, char *);

Indices indices_lerTexto(Indices, FILE *);

int indicePalavra(char *, Indices);

void RegistraPalavra(Indices, char *);

Indices indices_docSetClasseENome(Indices, char *, char *);

Indices indices_gerarDocIndex(Indices);

void indices_calculaTF_IDFs(Indices);

double CalculaIDF(int, int);

//Apenas para teste:
void indices_imprimeDocIndex(Indices);

void indices_destroy(Indices);

void indices_imprimeEstatisticas(Indices);

void indices_gerarRelatorioBin(Indices, char *);

Indices indices_lerBIN(Indices, char *);

Indices indices_alfabeticaWordIndex(Indices);

void indices_relatorioDocumentos(Indices);

int docIndex_ordenaDecrescenteTamanho(const void *, const void *);

int docIndex_ordenaCrescenteTamanho(const void *, const void *);

void indices_buscarNoticias(Indices);

int ComparaSomaTF_IDF(const void *, const void *);

Palavra * RetornaPonteiroPalavra(Indices, char *);

Documento CriaDocumentoClassificador(Indices, Documento);

void indices_classificarNoticias(Indices, int);

void indices_relatorioPalavra(Indices);