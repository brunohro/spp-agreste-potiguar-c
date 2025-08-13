#include <stdio.h>
#include <string.h>
#include "salvar_arquivo.h"

int salvar_arquivo_saida(int total_cidades_cadastradas, char nome_arquivo[MAX_LISTAR_ARQUIVOS], float mtz_distancias_minimas[][MAX_TOTAL_CIDADES], int mtz_predecessores_cidades[][MAX_TOTAL_CIDADES])
{

    char local_nome_arquivo[MAX_LISTAR_ARQUIVOS] = CONFIG_RESULTADOS; // recebendo local
    strcat(local_nome_arquivo, nome_arquivo);                         // // junta nome da pasta + nome do arquivo

    FILE *arq = fopen(local_nome_arquivo, "w"); // escrita 

    if (!arq)
    {
        printf("Erro ao salvar o arquivo.\n");
        return 0;
    }

    fprintf(arq, "%d\n", total_cidades_cadastradas);
    for (int i = 0; i < total_cidades_cadastradas; i++)
    {
        for (int j = 0; j < total_cidades_cadastradas; j++)
        {
            fprintf(arq, "%.2f;", mtz_distancias_minimas[i][j]); // distância miníma
        }
        fprintf(arq, "\n");
    }

    for (int i = 0; i < total_cidades_cadastradas; i++)
    {
        for (int j = 0; j < total_cidades_cadastradas; j++)
            fprintf(arq, "%d;", mtz_predecessores_cidades[i][j]); // prodecessores
        fprintf(arq, "\n");
    }
    fclose(arq);

    return 1;
}