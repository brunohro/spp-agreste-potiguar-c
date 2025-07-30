#ifndef FLOYD_WARSHALL_H
#define FLOYD_WARSHALL_H

#define MAX 100
#define INF 10000.0

// variáveis globais acessadas em outros arquivos
extern int n;
extern char nomes[MAX][50];
extern float A[MAX][MAX];
extern float D[MAX][MAX];
extern int P[MAX][MAX];

void floyd_warshall(); // chamando minha função

#endif