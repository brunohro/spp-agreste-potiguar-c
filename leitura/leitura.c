#include <stdio.h>
#include <string.h>
#include "leitura.h"

void ler_arquivo_entrada(const char *nome_arquivo)
{
    FILE *arq = fopen(nome_arquivo, "r"); // retorna um ponteiro para abrir um arquivo
    if (!arq)
    {
        printf("--> Erro ao abrir o arquivo. \n");
        return;
    }

    fscanf(arq, "%d\n", &n); // lendo o numero de municipios da primeira linha do arquivo

    for (int i = 0; i < n; i++)
    {
        fgets(nomes[i], 50, arq); // nomes dos municipios ( lê até  50 municipios )
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fscanf(arq, "%f;", &A[i][j]); // lê a matriz adjacente do grafo 
        }
    }

    fclose(arq); 
}

