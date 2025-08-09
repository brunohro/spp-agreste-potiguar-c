#ifndef FLOYD_WARSHALL_H
#define FLOYD_WARSHALL_H
#include "../rotas.h"

void floyd_warshall(int total_cidades_cadastradas,  float (*mtz_adjacente_cidades)[MAX_TOTAL_CIDADES], float (*mtz_distancias_minimas)[MAX_TOTAL_CIDADES],  int (*mtz_predecessores_cidades)[MAX_TOTAL_CIDADES]);

#endif