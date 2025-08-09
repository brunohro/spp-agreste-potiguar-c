#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <dirent.h>
#include "cadastrar_cidades.h"

int cadastrarCidades(int total_cidades_cadastradas, char vetor_cidades[][MAX_CARACTERES_NOMES_CIDADES], float mtz_adjacente_cidades[][MAX_TOTAL_CIDADES])
{

    int opcao = 0, i = 0;
    char temp_nome_cidades[MAX_CARACTERES_NOMES_CIDADES], aux_caractere_enter;

    while (TRUE)
    {
        scanf("%c", &aux_caractere_enter);
        if (i == 0)
        {
            system("cls");
        }

        printf("+==================================================+\n");
        printf("|             *** CADASTRAR CIDADES ***            |\n");
        printf("+==================================================+\n");

        if (total_cidades_cadastradas == 0)
            printf("| VOLTAR AO MENU ANTERIOR: pressione [0] + [ENTER] |\n");
        else
            printf("| CADASTRAR DISTANCIAS: pressione [0] + [ENTER]    |\n");

        printf("+==================================================+\n");
        printf("| Cidades cadastradas: %i |\n", total_cidades_cadastradas);
        printf("+--------------------------------------------------+\n");
        printf("| DIGITE O NOME DA CIDADE (sem acentuacao):        |\n");
        scanf("%[^\n]", &temp_nome_cidades);
        printf("+--------------------------------------------------+\n");
        printf(">> ");

        if (strcmp(temp_nome_cidades, "0") != 0)
        {
            printf("\n%s\n\n", temp_nome_cidades);
            i = 1;

            if (total_cidades_cadastradas < MAX_TOTAL_CIDADES)
            {

                system("cls");
                printf("+==================================================+\n");
                printf("|         CIDADE CADASTRADA COM SUCESSO!          |\n");
                printf("+==================================================+\n");
                printf("| %s |\n", temp_nome_cidades);
                printf("+==================================================+\n\n");
                strcpy(vetor_cidades[total_cidades_cadastradas], temp_nome_cidades);

                total_cidades_cadastradas++;
            }
            else
            {
                system("cls");
                printf("+==================================================+\n");
                printf("|        ERRO: LIMITE DE CIDADES ATINGIDO!         |\n");
                printf("+==================================================+\n");
                printf("| Nao foi possivel cadastrar: %s |\n", temp_nome_cidades);
                printf("| Maximo permitido: %.3i cidades                   |\n", MAX_TOTAL_CIDADES);
                printf("+==================================================+\n\n");
                continue;
            }
        }
        else
        {

            system("cls");
            if (total_cidades_cadastradas > 0)
            {
                printf("+==================================================+\n");
                printf("|           *** CADASTRAR DISTANCIAS ***           |\n");
                printf("+==================================================+\n");
                printf("| Para FINALIZAR o cadastro, informe as distancias |\n");
                printf("| entre todas as cidades cadastradas.              |\n");
                printf("+==================================================+\n\n");
                cadastrarCidadesDistancias(total_cidades_cadastradas, vetor_cidades, mtz_adjacente_cidades);
            }

            break;
        }
    }
    system("cls");

    return total_cidades_cadastradas;
}
