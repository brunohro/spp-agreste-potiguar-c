#ifndef SALVAR_H
#define SALVAR_H

#define MAX 100

int n;
char nomes[MAX][50];
float M_ADJACENCIA[MAX][MAX];
float M_DISTANCIA_M[MAX][MAX];
int M_PRODECESSORES[MAX][MAX];

void salvar_arquivo_saida(const char *nome_arquivo);

#endif