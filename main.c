#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define INF 10000.0

// definir as variáveis globais temporariamente

int n; // número de municipios
char nomes[MAX][50];
float A[MAX][MAX]; // matriz de adjacência
float D[MAX][MAX]; // matriz de distância mínimas
float P[MAX][MAX]; // matriz de prodecessores

// protótipos das minhas funções
void ler_arquivo_entrada(const char *nome_arquivo);
void salvar_arquivo_saida(const char *nome_arquivo);
void floyd_warshall();
void imprimir_matriz_float(float M[MAX][MAX]);
void imprimir_matriz_int(int M[MAX][MAX]);
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
            floydWarshall();
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

void ler_arquivo_entrada(const char *nome_arquivo)
{
    FILE *arq = fopen(nome_arquivo, "r");
    if (!arq)
    {
        printf("--> Erro ao abrir o arquivo. \n");
        return;
    }

    fscanf(arq, "%d\n", &n);
    for (int i = 0; i < n; i++)
    {
        fgets(nomes[i], 50, arq);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fscanf(arq, "%f;", &A[i][j]);
        }
    }

    fclose(arq);
}

void salvar_arquivo_saida(const char *nome_arquivo)
{
    FILE *arq = fopen(nome_arquivo, "w");
    if (!arq)
    {
        printf("Erro ao salvar o arquivo.\n");
        return;
    }

    fprintf(arq, "%d\n", n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fprintf(arq, "%.2f;", D[i][j]);
        }
        fprintf(arq, "\n");
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            fprintf(arq, "%d;", P[i][j]);
        fprintf(arq, "\n");
    }
    fclose(arq);
}

void floyd_warshall()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            D[i][j] = A[i][j];
            if (i == j)
            {
                P[i][j] = -1;
            }
            else if (A[i][j] < INF)
            {
                P[i][j] = i;
            }
            else
            {
                P[i][j] = -1;
            }
        }
    }

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (D[i][k] + D[k][j] < D[i][j])
                {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = P[k][j];
                }
            }
        }
    }
}

void imprimir_matriz_float(float M[MAX][MAX])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%.2f\t", M[i][j]);
        }
        printf("\n");
    }
}

void imprimir_matriz_int(int M[MAX][MAX])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d\t", M[i][j]);
        }
        printf("\n");
    }
}

void mostrar_caminho(int origem, int destino){
    if(D[origem][destino] >= INF){
        printf("Nao ha caminho disponivel entre os municipios.\n");
        return;
    }

    int caminho[MAX], tam = 0;
    int atual = destino;
    while(atual != origem){
        caminho[tam++] = atual;
        atual = P[origem][atual];
    }
    caminho[tam++] = origem;

    printf("Caminho:    ");
    for(int i = tam - 1; i >= 0; i--){
        printf("%s", nomes[caminho[i]]);
    }

}