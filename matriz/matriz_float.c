#include <stdio.h>
#include "matriz_float.h"

void imprimir_matriz_float(int total_cidades_cadastradas, float mtz_adjacente_distancia[][MAX_TOTAL_CIDADES])
{
    printf("\t");
     for (int i = 0; i < total_cidades_cadastradas; i++)
    {
        printf(" %.3i\t",i); // valor de i nas colunas
       
    }
    printf("\n\t");
    for (int i = 0; i < total_cidades_cadastradas; i++)
    {
        printf("  |\t"); // organizando coluna
    }
    printf("\n\n");

    for (int i = 0; i < total_cidades_cadastradas; i++)
    {
        printf("%.3i --\t",i); // aplicando no inicio da linha
        for (int j = 0; j < total_cidades_cadastradas; j++)
        {
            if (mtz_adjacente_distancia[i][j] == INF)
            {
                printf("  INF\t");
            }
            else
            {
                printf("%.2f\t", mtz_adjacente_distancia[i][j]);
            }
        }
        printf("\n");
    }
}