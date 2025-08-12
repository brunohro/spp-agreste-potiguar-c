#include <stdio.h>
#include <string.h>
#include "leitura.h"

int ler_arquivo_cidades(int total_cidades_cadastradas,  char nome_arquivo[], char vetor_cidades[][MAX_CARACTERES_NOMES_CIDADES],float mtz_adjacente_cidades[][MAX_TOTAL_CIDADES])
{
    char pasta_arquivo[MAX_LISTAR_ARQUIVOS] = CONFIG; // caminho
    strcat(pasta_arquivo,nome_arquivo); // junta nome da pasta + nome do arquivo
    
    FILE *arq = fopen(pasta_arquivo, "r"); // modo leitura
     // retorna um ponteiro para abrir um arquivo
    if (!arq)
    {
        return 0;
    }

    fscanf(arq, "%d\n", &total_cidades_cadastradas); // lendo o numero de municipios da primeira linha do arquivo

    for (int i = 0; i < total_cidades_cadastradas; i++) // lendo o nome das cidades
    {
        fgets(vetor_cidades[i], 50, arq); 
    }

    for (int i = 0; i < total_cidades_cadastradas; i++)
    {
        for (int j = 0; j < total_cidades_cadastradas; j++)
        {
            fscanf(arq, "%f;", &mtz_adjacente_cidades[i][j]); // lendo minha matriz de adjacencia
        }
    }

    fclose(arq);
    printf("\nArquivo carregado com sucesso!\n\n");
    
    return total_cidades_cadastradas;// caso o arquivo tenha sido lido corretamente, executará também o algoritmo de Floyd-Warshall
}
