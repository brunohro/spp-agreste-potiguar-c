#include <stdio.h>
#include <string.h>
#include "floyd_warshall.h"

void floyd_warshall()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            D[i][j] = A[i][j];
            if (i == j)
            {
                P[i][j] = -1;
            }
            else if (A[i][j] < INF)
            {
                P[i][j] = i;
            }
            else
            {
                P[i][j] = -1;
            }
        }
    }

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (D[i][k] + D[k][j] < D[i][j])
                {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = P[k][j];
                }
            }
        }
    }
}