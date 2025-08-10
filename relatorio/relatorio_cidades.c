#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <dirent.h>

#include "relatorio_cidades.h"

void relatorioCidades(int total_cidades_cadastradas, char vetor_cidades[][MAX_CARACTERES_NOMES_CIDADES])
{

    printf("------------------------------------------------------------\n");
    printf("|               >>> RELATORIO DAS CIDADES <<<              |");
    printf("\n------------------------------------------------------------\n\n");
    if (total_cidades_cadastradas > 0)
    {
        printf("\nID: Lista das Cidades");
        printf("\n------------------------------------------------------------");
        for (int i = 0; i < total_cidades_cadastradas; i++)
        {
            printf("\n%.2i: %s", i, vetor_cidades[i]);
            printf("\n............................................................");
        }
    }
    else
    {
        printf("\n\nNao existe nenhuma cidade Cadastrada!\n");
    }
    printf("\n\n\nTotal de cidades cadastradas: %i", total_cidades_cadastradas);
    printf("\n************************************************************\n\n");
    system("pause");
}