#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitura/leitura.h" // chamando as funções
#include "salvar/salvar_arquivo.h"
#include "floyd_warshall/floyd_warshall.h"
#include "matriz/matriz_int.h"
#include "matriz/matriz_float.h"

#define MAX 100
#define INF 10000.0

// definir as variáveis globais temporariamente

int n; // número de municipios
char nomes[MAX][50];
float A[MAX][MAX]; // matriz de adjacência
float D[MAX][MAX]; // matriz de distância mínimas
int P[MAX][MAX];   // matriz de prodecessores

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
        printf("\n--- MENU ---\n");
        printf("1. Carregar dados do arquivo\n");
        printf("2. Executar Floyd-Warshall\n");
        printf("3. Mostrar matriz de distâncias\n");
        printf("4. Mostrar matriz de predecessores\n");
        printf("5. Mostrar caminho entre dois municípios\n");
        printf("6. Salvar resultados em arquivo\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Nome do arquivo de entrada: ");
            scanf("%s", nome_arquivo);
            ler_arquivo_entrada(nome_arquivo);
            break;
        case 2:
            floyd_warshall();
            printf("Algoritmo executado com sucesso!\n");
            break;
        case 3:
            imprimir_matriz_float(D);
            break;
        case 4:
            imprimir_matriz_int(P);
            break;
        case 5:
            printf("Índice do município de origem: ");
            scanf("%d", &origem);
            printf("Índice do município de destino: ");
            scanf("%d", &destino);
            mostrar_caminho(origem, destino);
            break;
        case 6:
            printf("Nome do arquivo de saída: ");
            scanf("%s", nome_arquivo);
            salvar_arquivo_saida(nome_arquivo);
            break;
        case 0:
            printf("Encerrando programa...\n");
            break;
        default:
            printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}