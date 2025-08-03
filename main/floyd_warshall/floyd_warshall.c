#include <stdio.h>
#include <string.h>
#include "floyd_warshall.h"

void floyd_warshall()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            M_DISTANCIA_M[i][j] = M_ADJACENCIA[i][j];
            if(M_DISTANCIA_M[i][j] >= INF){
                M_PRODECESSORES[i][j] = -1;
            } else{
                M_PRODECESSORES[i][j] = i;
            }
            // if (i == j)
            // {
            //     M_PRODECESSORES[i][j] = 0;
            // }
            // else if (M_ADJACENCIA[i][j] < INF)
            // {
            //     M_PRODECESSORES[i][j] = i;
            // }
            // else
            // {
            //     M_PRODECESSORES[i][j] = -1;
            // }
        }
    }

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (M_DISTANCIA_M[i][k] + M_DISTANCIA_M[k][j] < M_DISTANCIA_M[i][j])
                {
                    M_DISTANCIA_M[i][j] = M_DISTANCIA_M[i][k] + M_DISTANCIA_M[k][j];
                    M_PRODECESSORES[i][j] = M_PRODECESSORES[k][j];
                }
            }
        }
    }
}
