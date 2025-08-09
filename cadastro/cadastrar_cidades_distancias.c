#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <dirent.h>

#include "cadastrar_cidades_distancias.h"

int cadastrarCidadesDistancias(int total_cidades_cadastradas, char vetor_cidades[][MAX_CARACTERES_NOMES_CIDADES], float mtz_adjacente_cidades[][MAX_TOTAL_CIDADES])
{
    int result = 1;
    float opcao = 0;
    // criar um for percorrendo a matriz toda;

    for (int l = 0; l < total_cidades_cadastradas; l++)
    {
        for (int c = 0; c < total_cidades_cadastradas; c++)
        {
            if (l == c)
            {
                mtz_adjacente_cidades[l][c] = 0.0;
            }
            else
            {

                printf("\nInforme a distancia em km entre [ %s ] - [ %s ]\n[digite -1 se elas nao tiverem ligacao direta] ", vetor_cidades[l], vetor_cidades[c]);
                scanf("%f", &opcao);

                if (opcao > 0)
                {

                    mtz_adjacente_cidades[l][c] = opcao;
                }
                else if (opcao < 0)
                {
                    mtz_adjacente_cidades[l][c] = INF;
                }
            }
        }
    }

    int salvar;
    char nome_arquivo[MAX_CARACTERES_NOMES_CIDADES];

    while (TRUE)
    {
        system("cls");
        printf("------------------------------------------------------------\n");
        printf("|      *** DESEJAR SALVAR AS CIDADES E DISTANCIAS ***      |");
        printf("\n------------------------------------------------------------");
        printf("\nCidades Cadastradas %i\n", total_cidades_cadastradas);
        printf("\n>>> 1: SIM ###");
        printf("\n### 0: NAO <<<\n");
        printf("\n------------------------------------------------------------\n");
        printf("Escolha uma das opcoes: ");
        scanf("%i", &salvar);

        if (salvar == 1)
        {
            scanf("%c", &nome_arquivo[0]);
            printf("Informe o nome do arquivo: ");
            scanf("%[^\n]", &nome_arquivo);
            if (salvarCidades(nome_arquivo, total_cidades_cadastradas, vetor_cidades, mtz_adjacente_cidades) == 1)
            {
                printf("ARQUIVO [ %s ] SALVO COM SUCESSO!!!\n\n", nome_arquivo);
                break;
            }
            else
            {
                printf("Error ao salvar o arquivo");
                continue;
            }
        }
        else if (salvar == 0)

            break;
        else
            continue;
    }

    return result;
}
