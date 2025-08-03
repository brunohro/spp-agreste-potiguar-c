#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitura/leitura.h"
#include "salvar/salvar_arquivo.h"
#include "floyd_warshall/floyd_warshall.h"
#include "matriz/matriz_int.h"
#include "matriz/matriz_float.h"

#define MAX 100
#define INF 10000.0

// definir as vari�veis globais temporariamente

int n;
char nomes[MAX][50];
float M_ADJACENCIA[MAX][MAX];
float M_DISTANCIA_M[MAX][MAX];
int M_PRODECESSORES[MAX][MAX];

void ler_arquivo_entrada(const char *nome_arquivo);
void salvar_arquivo_saida(const char *nome_arquivo);

void floyd_warshall();

void imprimir_matriz_int(int M[MAX][MAX]);
void imprimir_matriz_float(float M[MAX][MAX]);
void mostrar_caminho(int origem, int destino);

int main()
{

    int opcao, origem, destino;
    char nome_arquivo[100];

    do
    {
        printf("\n");
        printf("+==============================================+\n");
        printf("|         SISTEMA DE ROTAS MUNICIPAIS          |\n");
        printf("+==============================================+\n");
        printf("| 1. Carregar dados do arquivo                 |\n");
        printf("| 2. Mostrar matriz de distancias              |\n");
        printf("| 3. Mostrar matriz de predecessores           |\n");
        printf("| 4. Mostrar caminho entre dois municipios     |\n");
        printf("| 5. Salvar resultados em arquivo              |\n");
        printf("| 0. Sair do programa                          |\n");
        printf("+==============================================+\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Nome do arquivo de entrada: ");
            scanf("%s", nome_arquivo);
            ler_arquivo_entrada(nome_arquivo);
            floyd_warshall();
            break;
        case 2:
            imprimir_matriz_float(M_DISTANCIA_M);
            break;
        case 3:
            imprimir_matriz_int(M_PRODECESSORES);
            break;
        case 4:
            printf("indice do municipio de origem: ");
            scanf("%d", &origem);
            printf("indice do municipio de destino: ");
            scanf("%d", &destino);
            mostrar_caminho(origem, destino);
            break;
        case 5:
            printf("Nome do arquivo de saida: ");
            scanf("%s", nome_arquivo);
            salvar_arquivo_saida(nome_arquivo);
            break;
        case 0:
            printf("Encerrando programa...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}