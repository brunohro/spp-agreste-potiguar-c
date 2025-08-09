#include <stdio.h>
#include "matriz_int.h"

void imprimir_matriz_int(int total_cidades_cadastradas, int (*mtz_predecessores_cidades)[MAX_TOTAL_CIDADES])
{
    printf("\t");
    for (int j = 0; j < total_cidades_cadastradas; j++)
    {
        printf(" |\t");
    }
    printf("\n\n");
    for (int i = 0; i < total_cidades_cadastradas; i++)
    {
        printf("--\t");
        for (int j = 0; j < total_cidades_cadastradas; j++)
        {
            if (mtz_predecessores_cidades[i][j] == -1)
            {
                printf("INF\t", mtz_predecessores_cidades[i][j]);
            }
            else
            {
                printf(" %i\t", mtz_predecessores_cidades[i][j]);
            }
        }
        printf("\n");
    }
}