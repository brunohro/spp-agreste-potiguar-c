#include <stdio.h>
#include "matriz_float.h"

void imprimir_matriz_float(float M[MAX][MAX])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%.2f\t", M[i][j]);
        }
        printf("\n");
    }
}