#ifndef SALVAR_H
#define SALVAR_H

#define MAX 100

extern int n; // número de municipios
extern char nomes[MAX][50];
extern float D[MAX][MAX]; // matriz de distância mínimas
extern int P[MAX][MAX];   // matriz de prodecessores

void salvar_arquivo_saida(const char *nome_arquivo);

#endif