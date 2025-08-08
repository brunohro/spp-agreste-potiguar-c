#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <dirent.h>
#include "leitura/leitura.h"
#include "salvar/salvar_arquivo.h"
#include "floyd_warshall/floyd_warshall.h"
#include "matriz/matriz_int.h"
#include "matriz/matriz_float.h"

#define MAX 100
#define INF 100.0

#define MAX_TOTAL_CIDADES 50
#define MAX_CARACTERES_NOMES_CIDADES 50
#define TRUE 1
#define CONFIG "./dados/"




void salvar_arquivo_saida(const char *nome_arquivo);

void floyd_warshall();

void imprimir_matriz_int(int M[MAX][MAX]);
void imprimir_matriz_float(float M[MAX][MAX]);
void mostrar_caminho(int origem, int destino);

int cadastrarCidades(int total_cidades_cadastradas, char (*vetor_cidades)[MAX_CARACTERES_NOMES_CIDADES], float (*mtz_adjacente_cidades)[MAX_TOTAL_CIDADES]);
int salvarCidades(char *nome_arquivo, int total_cidades_cadastradas, char (*vetor_cidades)[MAX_CARACTERES_NOMES_CIDADES], float (*mtz_adjacente_cidades)[MAX_TOTAL_CIDADES]);
int carregarCidades();

void relatorioCidades(int total_cidades_cadastradas, char (*vetor_cidades)[MAX_CARACTERES_NOMES_CIDADES], float (*mtz_adjacente_cidades)[MAX_TOTAL_CIDADES]);
int salvarCidadess_distancias(int linha, int coluna, float distancia);
int cadastrarCidadesDistancias(int total_cidades_cadastradas, char (*vetor_cidades)[MAX_CARACTERES_NOMES_CIDADES], float (*mtz_adjacente_cidades)[MAX_TOTAL_CIDADES]);

int listarArquivos(char (*vetor_arquivos_salvos)[MAX_CARACTERES_NOMES_CIDADES * 4]);

void limpar_Terminal();

int main()
{

    float mtzAdjacenteCidades[MAX_TOTAL_CIDADES][MAX_TOTAL_CIDADES];
    char vetorCidades[MAX_TOTAL_CIDADES][MAX_CARACTERES_NOMES_CIDADES];
    char vetorArquivosSalvos[MAX_TOTAL_CIDADES * 2][MAX_CARACTERES_NOMES_CIDADES * 4];

    int opcao, indiceVetorArquivosSalvos, origem, destino, totalCidadesCadastradas = 0;
    char nome_arquivo[100];
    limpar_Terminal();

    do
    {
        printf("\n");
        printf("+==================================================+\n");
        printf("| OLA, SEJA BEM-VINDO(A) AO ROTAS AGRESTE-POTIGUAR |\n");
        printf("+==================================================+\n");
        printf("| 1. Cidades [cadastro avulso]                     |\n");
        printf("| 2. Carregar dados atraves de arquivo             |\n");
        printf("| 3. Mostrar matriz de distancias                  |\n");
        printf("| 4. Mostrar matriz de predecessores               |\n");
        printf("| 5. Mostrar caminho entre dois municipios         |\n");
        printf("| 6. Relatario das cidades                         |\n");
        printf("| 7. Salvar resultados em arquivo                  |\n");
        printf("| 0. Sair do programa                              |\n");
        printf("+==================================================+\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            cadastrarCidades(0, vetorCidades, mtzAdjacenteCidades);
            break;
        case 2:
            limpar_Terminal();
            printf("+==================================================+\n");
            printf("|             *** SELECIONAR ARQUIVOS ***          |\n");
            printf("+==================================================+\n");
          
            totalCidadesCadastradas = listarArquivos(vetorArquivosSalvos);

            if (totalCidadesCadastradas > 0)
            {
                for (int i = 0; i < totalCidadesCadastradas; i++)
                {
                    printf("\n%i - %s", i + 1, vetorArquivosSalvos[i]);
                    printf("\n......................................................................");
                }
                printf("\n\n0 - Menu Anterior ");
                printf("\n\n************************************************************");
                printf("\nEscolha uma opcao: ");
                scanf("%i", &indiceVetorArquivosSalvos);

                if (indiceVetorArquivosSalvos >= 0 && indiceVetorArquivosSalvos < totalCidadesCadastradas)
                {
                    if (indiceVetorArquivosSalvos == 0)
                    {
                        break;
                    }
                    else
                    {
                        //preciso que a função  preencha as matrizes por ponteiro e retorne  o total_de_cidades_cadastradas para serem utilizadas no relatorio;
                        //O erro é que as matrizes entre as funções são distintas e não estão se comunicando....
                        //ler_arquivo_entrada(vetorArquivosSalvos[indiceVetorArquivosSalvos - 1], vetorCidades, mtzAdjacenteCidades);
                        floyd_warshall();
                       
                    }
                }
            }
            else
            {
                printf("\n------------------------------------------------------------");
                printf("\nNenhum arquivo encontrado!!!! ");
                printf("\n------------------------------------------------------------\n\n");
                system("pause");
                continue;
            }
            /*printf("Nome do arquivo de entrada: ");
            scanf("%s", nome_arquivo);
            ler_arquivo_entrada(nome_arquivo);
            floyd_warshall();*/
            break;
        case 3:
            imprimir_matriz_float(M_DISTANCIA_M);
            break;
        case 4:
            imprimir_matriz_int(M_PRODECESSORES);
            break;
        case 5:
            printf("indice do municipio de origem: ");
            scanf("%d", &origem);
            printf("indice do municipio de destino: ");
            scanf("%d", &destino);
            mostrar_caminho(origem, destino);
            break;
        case 6:
            relatorioCidades(totalCidadesCadastradas, vetorCidades, mtzAdjacenteCidades);
            break;
        case 7:
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

void limpar_Terminal()
{
    system("cls");
}

int cadastrarCidades(int total_cidades_cadastradas, char (*vetor_cidades)[MAX_CARACTERES_NOMES_CIDADES], float (*mtz_adjacente_cidades)[MAX_TOTAL_CIDADES])
{

    int opcao = 0, i = 0;
    char temp_nome_cidades[MAX_CARACTERES_NOMES_CIDADES], aux_caractere_enter;

    while (TRUE)
    {
        scanf("%c", &aux_caractere_enter);
        if (i == 0)
        {
            limpar_Terminal();
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

                limpar_Terminal();
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
                limpar_Terminal();
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

            limpar_Terminal();
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
    limpar_Terminal();
    return total_cidades_cadastradas;
}

int cadastrarCidadesDistancias(int total_cidades_cadastradas, char (*vetor_cidades)[MAX_CARACTERES_NOMES_CIDADES], float (*mtz_adjacente_cidades)[MAX_TOTAL_CIDADES])
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
        limpar_Terminal();
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

int salvarCidades(char *nome_arquivo, int total_cidades_cadastradas, char (*vetor_cidades)[MAX_CARACTERES_NOMES_CIDADES], float (*mtz_adjacente_cidades)[MAX_TOTAL_CIDADES])
{
    FILE *ptr_arquivo = NULL;
    int result = 0;
    char arquivo[100] = CONFIG;

    strcat(arquivo, nome_arquivo);
    strcat(arquivo, ".txt");

    ptr_arquivo = fopen(arquivo, "w");

    if (ptr_arquivo != NULL)
    {
        limpar_Terminal();
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

int listarArquivos(char (*vetor_arquivos_salvos)[MAX_CARACTERES_NOMES_CIDADES * 4])
{
    DIR *dir;
    struct dirent *entry;
    char *dir_path = CONFIG;
    int i = 0; // Define o diretório atual

    dir = opendir(dir_path);

    if (dir == NULL)
    {
        perror("Erro ao abrir o diretório");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            strcpy(vetor_arquivos_salvos[i], entry->d_name);
            i++;
        }
    }

    closedir(dir);

    return i;
}

void relatorioCidades(int total_cidades_cadastradas, char (*vetor_cidades)[MAX_CARACTERES_NOMES_CIDADES], float (*mtz_adjacente_cidades)[MAX_TOTAL_CIDADES])
{
    limpar_Terminal();
    printf("------------------------------------------------------------\n");
    printf("|               >>> RELATARIO DAS CIDADES <<<              |");
    printf("\n------------------------------------------------------------\n\n");
    if (total_cidades_cadastradas > 0)
    {

        for (int i = 0; i < total_cidades_cadastradas; i++)
        {
            printf("\n%.2i: %s", i + 1, vetor_cidades[i]);
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
    limpar_Terminal();
}
