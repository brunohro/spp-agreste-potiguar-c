#include <stdio.h>
#include "mostrar_caminho.h"

void mostrar_caminho(int origem, int destino,  float (*mtz_distancias_minimas)[MAX_TOTAL_CIDADES],  int (*mtz_predecessores_cidades)[MAX_TOTAL_CIDADES],char (*vetor_cidades)[MAX_CARACTERES_NOMES_CIDADES])
{
       
    if (mtz_distancias_minimas[origem][destino] >= INF)
    {
        printf("Nao ha caminho disponivel entre os municipios.\n");
        return;
    }

    int caminho[MAX], tam = 0;
    int atual = destino;
    while (atual != origem)
    {
        caminho[tam++] = atual;
        atual = mtz_predecessores_cidades[origem][atual];
    }
    caminho[tam++] = origem;

    printf("\n======= CAMINHO ENCONTRADO =======\n");
    printf("Caminho: \n");
    for (int i = tam - 1; i >= 0; i--)
    {
        printf("        %s", vetor_cidades[caminho[i]]);
        if (i > 0)
        {
            printf("\n          | \n");
            printf("\n          | \n");
            printf("\n          v \n");
        }
    }

    printf("\nDistancia total: %.2f km\n", mtz_distancias_minimas[origem][destino]);
    printf("==================================\n");
}