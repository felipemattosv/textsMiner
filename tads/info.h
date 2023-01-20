#pragma once

typedef struct info *Info;

Info info_alocar();

void info_setPos(Info, int);

void info_setFreq(Info, int);

int info_retornaFreq(Info);

int info_retornaPos(Info);