#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <dirent.h>

#include "salvar_cidades.h"

int salvarCidades(char *nome_arquivo, int total_cidades_cadastradas, char vetor_cidades[][MAX_CARACTERES_NOMES_CIDADES], float mtz_adjacente_cidades[][MAX_TOTAL_CIDADES])
{
    FILE *ptr_arquivo = NULL;
    int result = 0;
    char arquivo[100] = CONFIG; // pega o caminho

    strcat(arquivo, nome_arquivo); // junta nome + caminho
    strcat(arquivo, ".txt");       // definindo tipo txt

    ptr_arquivo = fopen(arquivo, "w"); // modo escrita

    if (ptr_arquivo != NULL)
    {
        system("cls");
        printf("\nsalvando...\n\n");
        fprintf(ptr_arquivo, "%i\n", total_cidades_cadastradas);

        for (int i = 0; i < total_cidades_cadastradas; i++)
        {
            fprintf(ptr_arquivo, "%s\n", vetor_cidades[i]);
        }

        for (int l = 0; l < total_cidades_cadastradas; l++)
        {
            for (int c = 0; c < total_cidades_cadastradas; c++)
            {
                (c != total_cidades_cadastradas - 1) ? fprintf(ptr_arquivo, "%.2f;", mtz_adjacente_cidades[l][c]) : fprintf(ptr_arquivo, "%.2f\n", mtz_adjacente_cidades[l][c]);
            }
        }
        result = 1;
    }

    fclose(ptr_arquivo);

    return result;
}