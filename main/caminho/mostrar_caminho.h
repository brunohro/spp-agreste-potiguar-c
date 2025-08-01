#ifndef MOSTRAR_CAMINHO_H
#define MOSTRAR_CAMINHO_H

#define MAX 100
#define INF 10000.0

int n;
char nomes[MAX][50];
float M_ADJACENCIA[MAX][MAX];
float M_DISTANCIA_M[MAX][MAX];
int M_PRODECESSORES[MAX][MAX];

void mostrar_caminho(int origem, int destino);
#endif