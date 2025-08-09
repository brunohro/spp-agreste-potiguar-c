#include <stdio.h>
#include <string.h>
#include "floyd_warshall.h"

void floyd_warshall(int total_cidades_cadastradas,  float (*mtz_adjacente_cidades)[MAX_TOTAL_CIDADES], float (*mtz_distancias_minimas)[MAX_TOTAL_CIDADES],  int (*mtz_predecessores_cidades)[MAX_TOTAL_CIDADES])
{
    for (int i = 0; i < total_cidades_cadastradas; i++)
    {
        for (int j = 0; j <total_cidades_cadastradas; j++)
        {
            mtz_distancias_minimas[i][j] = mtz_adjacente_cidades[i][j];
            if (mtz_distancias_minimas[i][j] == INF)
            {
                mtz_predecessores_cidades[i][j] = -1;
            }
            else
            {
                mtz_predecessores_cidades[i][j] = i;
            }
        }
    }

    for (int k = 0; k < total_cidades_cadastradas; k++)
    {
        for (int i = 0; i < total_cidades_cadastradas; i++)
        {
            for (int j = 0; j < total_cidades_cadastradas; j++)
            {
                if (mtz_distancias_minimas[i][k] + mtz_distancias_minimas[k][j] < mtz_distancias_minimas[i][j])
                {
                    mtz_distancias_minimas[i][j] = mtz_distancias_minimas[i][k] + mtz_distancias_minimas[k][j];
                    mtz_predecessores_cidades[i][j] = mtz_predecessores_cidades[k][j];
                }
            }
        }
    }
}
