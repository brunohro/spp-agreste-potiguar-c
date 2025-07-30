#ifndef MOSTRAR_CAMINHO_H
#define MOSTRAR_CAMINHO_H

#define MAX 100
#define INF 10000.0

extern int n; // número de municipios
extern char nomes[MAX][50];
extern float A[MAX][MAX]; // matriz de adjacência
extern float D[MAX][MAX]; // matriz de distância mínimas
extern int P[MAX][MAX];   // matriz de prodecessores

void mostrar_caminho(int origem, int destino);
#endif