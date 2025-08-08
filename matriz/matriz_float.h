#ifndef MATRIZ_FLOAT_H
#define MATRIZ_FLOAT_H

#define MAX 100
#define INF 100.0
int n;
char nomes[MAX][50];
float M_ADJACENCIA[MAX][MAX];
float M_DISTANCIA_M[MAX][MAX];
int M_PRODECESSORES[MAX][MAX];

void imprimir_matriz_float(float M[MAX][MAX]);
#endif