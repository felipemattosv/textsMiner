#pragma once

typedef struct documento *Documento;

Documento documento_alocar();

void documento_setClasse(Documento, char *);

char * documento_retornaClasse(Documento);

void documento_setNome(Documento, char *);

char * documento_retornaNome(Documento);

void documento_incrementaQtdPalavras(Documento);

void documento_setInfo(Documento, int, int);

int documento_retornaQtdPalavras(Documento);

int documento_retornaPos(Documento, int);

int documento_retornaFreq(Documento, int);

void documento_dobraMetricasAlocadas(Documento);

int documento_retornaMetricasAlocadas(Documento);

Documento documento_realocar(Documento);

Documento RegistraPalavraNoDocumento(Documento, int, int);