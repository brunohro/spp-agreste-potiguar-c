#ifndef MATRIZ_INT_H
#define MATRIZ_INT_H

#define MAX 100

int n;
char nomes[MAX][50];
float M_ADJACENCIA[MAX][MAX];
float M_DISTANCIA_M[MAX][MAX];
int M_PRODECESSORES[MAX][MAX];

void imprimir_matriz_int(int M[MAX][MAX]);

#endif
