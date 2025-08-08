#include <stdio.h>
#include "mostrar_caminho.h"

void mostrar_caminho(int origem, int destino)
{
    if (M_DISTANCIA_M[origem][destino] >= INF)
    {
        printf("Nao ha caminho disponivel entre os municipios.\n");
        return;
    }

    int caminho[MAX], tam = 0;
    int atual = destino;
    while (atual != origem)
    {
        caminho[tam++] = atual;
        atual = M_PRODECESSORES[origem][atual];
    }
    caminho[tam++] = origem;

    printf("\n======= CAMINHO ENCONTRADO =======\n");
    printf("Caminho: \n");
    for (int i = tam - 1; i >= 0; i--)
    {
        printf("        %s", nomes[caminho[i]]);
        if (i > 0)
        {
            printf("\n          | \n");
            printf("\n          | \n");
            printf("\n          v \n");
        }
    }

    printf("\nDistancia total: %.2f km\n", M_DISTANCIA_M[origem][destino]);
    printf("==================================\n");
}