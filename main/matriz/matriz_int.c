#include <stdio.h>
#include "matriz_int.h"

void imprimir_matriz_int(int M[MAX][MAX])
{
    printf("\t");
    for (int j = 0; j < n; j++)
    {
        printf(" |\t");
    }
    printf("\n\n");
    for (int i = 0; i < n; i++)
    {
        printf("--\t");
        for (int j = 0; j < n; j++)
        {
            if (M[i][j] == -1)
            {
                printf("%i\t", M[i][j]);
            }
            else
            {
                printf(" %i\t", M[i][j]);
            }
        }
        printf("\n");
    }
}