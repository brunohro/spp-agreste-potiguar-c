#include <stdio.h>
#include <string.h>
#include "salvar_arquivo.h"

void salvar_arquivo_saida(const char *nome_arquivo)
{
    FILE *arq = fopen(nome_arquivo, "w");
    if (!arq)
    {
        printf("Erro ao salvar o arquivo.\n");
        return;
    }

    fprintf(arq, "%d\n", n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fprintf(arq, "%.2f;", M_DISTANCIA_M[i][j]); // distância miníma
        }
        fprintf(arq, "\n");
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            fprintf(arq, "%d;", M_PRODECESSORES[i][j]); // prodecessores
        fprintf(arq, "\n");
    }
    fclose(arq);
}