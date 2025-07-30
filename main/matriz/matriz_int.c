#include <stdio.h>
#include "matriz_int.h"

void imprimir_matriz_int(int M[MAX][MAX])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%i\t", M[i][j]);
        }
        printf("\n");
    }
}