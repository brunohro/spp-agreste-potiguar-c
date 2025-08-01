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
        fgets(nomes[i], 50, arq); 
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fscanf(arq, "%f;", &M_ADJACENCIA[i][j]);
        }
    }

    fclose(arq);
    printf("Algoritmo executado com sucesso!\n"); // caso o arquivo tenha sido lido corretamente, executará também o algoritmo de Floyd-Warshall
}
