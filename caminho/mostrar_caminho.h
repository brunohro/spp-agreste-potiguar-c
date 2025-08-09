#ifndef MOSTRAR_CAMINHO_H
#define MOSTRAR_CAMINHO_H

#include "../rotas.h"

void mostrar_caminho(int origem, int destino,float (*mtz_distancias_minimas)[MAX_TOTAL_CIDADES],  int (*mtz_predecessores_cidades)[MAX_TOTAL_CIDADES],char (*vetor_cidades)[MAX_CARACTERES_NOMES_CIDADES]);
#endif