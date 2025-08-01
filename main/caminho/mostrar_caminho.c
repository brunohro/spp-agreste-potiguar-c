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

    printf("Caminho:    ");
    for (int i = tam - 1; i >= 0; i--)
    {
        printf("%s", nomes[caminho[i]]);
        if (i > 0)
        {
            printf(" -> ");
        }
        printf("\nCusto total: %.2f\n", M_DISTANCIA_M[origem][destino]);
    }
}