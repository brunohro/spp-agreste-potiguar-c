#include <stdio.h>
#include "matriz_float.h"

void imprimir_matriz_float(float M[MAX][MAX])
{
    printf("\t");
    for (int i = 0; i < n; i++)
    {
        printf("  |\t");
    }
    printf("\n\n");

    for (int i = 0; i < n; i++)
    {
        printf("--\t");
        for (int j = 0; j < n; j++)
        {
            if (M[i][j] == INF)
            {
                printf("  INF\t");
            }
            else
            {
                printf("%.2f\t", M[i][j]);
            }
        }
        printf("\n");
    }
}