#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
#define CONFIG "./data/config.txt"

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

int menuCidades(int total_cidades_cadastradas, char (*vetor_cidades)[MAX_CARACTERES_NOMES_CIDADES], float (*mtz_adjacente_cidades)[MAX_TOTAL_CIDADES]);

int cadastrarCidades(int total_cidades_cadastradas, char (*vetor_cidades)[MAX_CARACTERES_NOMES_CIDADES], float (*mtz_adjacente_cidades)[MAX_TOTAL_CIDADES]);
int salvarCidades(char *nome_arquivo, int total_cidades_cadastradas, char (*vetor_cidades)[MAX_CARACTERES_NOMES_CIDADES], float (*mtz_adjacente_cidades)[MAX_TOTAL_CIDADES]);
int carregarCidades();

void relatorioCidades(int total_cidades_cadastradas, char (*vetor_cidades)[MAX_CARACTERES_NOMES_CIDADES], float (*mtz_adjacente_cidades)[MAX_TOTAL_CIDADES]);
int salvarCidadess_distancias(int linha, int coluna, float distancia);
int cidadesDistancias(int total_cidades_cadastradas, char (*vetor_cidades)[MAX_CARACTERES_NOMES_CIDADES], float (*mtz_adjacente_cidades)[MAX_TOTAL_CIDADES]);

int listarArquivos(char (*vetor_arquivos_salvos)[MAX_CARACTERES_NOMES_CIDADES * 4]);
void menuArquivosSalvosCidades(int total_cidades_cadastradas, char (*vetor_cidades)[MAX_CARACTERES_NOMES_CIDADES], float (*mtz_adjacente_cidades)[MAX_TOTAL_CIDADES]);

void limpar_Terminal();
int salvarConfigListaArquivos(char *nomeArquivo);

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
        printf("| 1. Cidades [cadastro avulso]                 |\n");
        printf("| 1. Carregar dados atraves de arquivo         |\n");
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

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <locale.h>
// #include <ctype.h>

// #define MAX_TOTAL_CIDADES 50
// #define MAX_CARACTERES_NOMES_CIDADES 50
// #define INF 10000.0
// #define TRUE 1
// #define CONFIG "./data/config.txt"

int main()

{
    float mtzAdjacenteCidades[MAX_TOTAL_CIDADES][MAX_TOTAL_CIDADES];
    char vetorCidades[MAX_TOTAL_CIDADES][MAX_CARACTERES_NOMES_CIDADES];
    char vetorArquivosSalvos[MAX_TOTAL_CIDADES * 2][MAX_CARACTERES_NOMES_CIDADES * 4];

    int opcao, subMenuOpcao, origem, destino, totalCidadesCadastradas = 0;

    do
    {
        limpar_Terminal();
        printf("                    <<<<<<<<<<>>>>>>>>>>");
        printf("\n  /// OLA, SEJA BEM-VINDO(A) AO ROTAS AGRESTE-POTIGUAR ///");
        printf("\n============================================================");

        printf("\n\n------------------------------------------------------------\n");
        printf("|                  *** Menu PRINCIPAL ***                  |");
        printf("\n------------------------------------------------------------\n");
        printf("1. Cidades [cadastro avulso]\n");
        printf("2. Carregar arquivos salvos: \n");
        printf("0. Sair\n");
        printf("\n------------------------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%i", &opcao);

        switch (opcao)
        {
        case 0:
            break;
        case 1:
            menuCidades(0, vetorCidades, mtzAdjacenteCidades);
            break;
        case 2:
            limpar_Terminal();
            printf("\n\n------------------------------------------------------------\n");
            printf("|              *** Menu CARREGAR ARQUIVOS ***             |");
            printf("\n------------------------------------------------------------\n");
            totalCidadesCadastradas = listarArquivos(vetorArquivosSalvos);

            if (totalCidadesCadastradas > 0)
            {
                for (int i = 0; i < totalCidadesCadastradas; i++)
                {
                    printf("\n%i - %s", i + 1, vetorArquivosSalvos[i]);
                    printf("\n......................................................................");
                }
                printf("\n0 - Menu Anterior ");
                printf("\n\n************************************************************");
                printf("\nEscolha uma opcao: ");
                scanf("%i", &subMenuOpcao);

                if (subMenuOpcao >= 0 && subMenuOpcao < totalCidadesCadastradas)
                {
                    if (subMenuOpcao == 0)
                    {
                        break;
                    }
                    menuArquivosSalvosCidades(totalCidadesCadastradas, vetorCidades, mtzAdjacenteCidades);
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

            break;
        default:
            continue;
            break;
        }
    } while (opcao != 0);

    printf("\nPrograma finalizado com sucesso, VOLTE SEMPRE!!!\n\n");

    return 0;
}

int menuCidades(int total_cidades_cadastradas, char (*vetor_cidades)[MAX_CARACTERES_NOMES_CIDADES], float (*mtz_adjacente_cidades)[MAX_TOTAL_CIDADES])
{
    int opcao = 0, i = 0;

    while (TRUE)
    {
        if (i == 0)
        {
            limpar_Terminal();
        }
        printf("------------------------------------------------------------\n");
        printf("|                  *** Menu CIDADE(s) ***                  |");
        printf("\n------------------------------------------------------------\n");
        printf("1. Cadastrar Cidades\n");
        printf("2. Relatario das cidades\n");
        printf("3. Mostrar matriz de distâncias\n");
        printf("4. Mostrar matriz de predecessores\n");
        printf("5. Mostrar caminho entre dois municípios\n");
        printf("6. Salvar resultados em arquivo\n");
        printf("0. Menu Anterior\n");
        printf("\n-----------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%i", &opcao);

        if (opcao == 0)
        {
            break;
        }
        else if (opcao == 1)
        {
            total_cidades_cadastradas = cadastrarCidades(0, vetor_cidades, mtz_adjacente_cidades);
        }
        else if (opcao == 2)
        {
            relatorioCidades(total_cidades_cadastradas, vetor_cidades, mtz_adjacente_cidades);
        }
        else
        {
            continue;
        }
        i = 1;
    }

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

        printf("------------------------------------------------------------\n");
        printf("|                 *** CADASTRAR CIDADES ***                 |");
        printf("\n------------------------------------------------------------");

        (total_cidades_cadastradas == 0) ? printf("\nVOLTAR AO MENU ANTERIOR << pressione a tecla 0 + [enter] <<") : printf("\n >> *** CADASTRAR DISTANCIAS *** << pressione a tecla 0 + [enter] <<");
        printf("\n\n------------------------------------------------------------");
        printf("\nCidades Cadastradas %i", total_cidades_cadastradas);

        printf("\nDIGITE O NOME DA CIDADE [sem acentuacao]: ");
        scanf("%[^\n]", &temp_nome_cidades);

        if (strcmp(temp_nome_cidades, "0") != 0)
        {
            printf("\n%s\n\n", temp_nome_cidades);
            i = 1;

            if (total_cidades_cadastradas < MAX_TOTAL_CIDADES)
            {

                limpar_Terminal();
                printf("\nCIDADE CADASTRADA COM SUCESSO!");
                printf("\n%s\n\n", temp_nome_cidades);
                // ocorrendo o sucesso inseri as informa��es no vetor
                strcpy(vetor_cidades[total_cidades_cadastradas], temp_nome_cidades);

                /*Criar a fun��o responsavel por inserir a distancia entre
                os municiapios e salvar em uma matriz de distancias e salvar em txt;
                */

                total_cidades_cadastradas++;
                // cidadesDistancias();
            }
            else
            {
                limpar_Terminal();
                printf("************************************************************");
                printf("\nERROR AO CADASTRAR [ %s ],\nQuantidade maxima de [ %.3i ] cadastro(s) atingida.\n\n", temp_nome_cidades, total_cidades_cadastradas);
                continue;
            }
        }
        else
        {

            limpar_Terminal();
            if (total_cidades_cadastradas > 0)
            {
                printf("------------------------------------------------------------\n");
                printf("|                 *** CADASTRAR DISTANCIAS ***                 |");
                printf("\n------------------------------------------------------------");
                printf("\npara FINALIZAR o cadastro, preencha todas as informacoes abaixo: <<\n");
                printf("\n------------------------------------------------------------\n");
                cidadesDistancias(total_cidades_cadastradas, vetor_cidades, mtz_adjacente_cidades);
            }

            break;
        }
    }
    limpar_Terminal();
    return total_cidades_cadastradas;
}

int cidadesDistancias(int total_cidades_cadastradas, char (*vetor_cidades)[MAX_CARACTERES_NOMES_CIDADES], float (*mtz_adjacente_cidades)[MAX_TOTAL_CIDADES])
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
                if (salvarConfigListaArquivos(nome_arquivo) == 0)
                    printf("\n Erro ao salvar o arquivo config");
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

int carregarArquivosCidades(char (*vetor_cidades)[MAX_CARACTERES_NOMES_CIDADES], float (*mtz_adjacente_cidades)[MAX_TOTAL_CIDADES])
{
    // existe forma diferentes de efetuar a listar arquivos
    // pensando nisso a melhor maneira é salvar tudo em um config.txt;
    FILE *ptr_arquivo = NULL;
    int i = 0, total_arquivos_salvos;

    char arquivo[100] = CONFIG;

    ptr_arquivo = fopen(arquivo, "r");

    if (ptr_arquivo != NULL)
    {
    }

    fclose(ptr_arquivo);

    return total_arquivos_salvos;
}

int salvarCidades(char *nome_arquivo, int total_cidades_cadastradas, char (*vetor_cidades)[MAX_CARACTERES_NOMES_CIDADES], float (*mtz_adjacente_cidades)[MAX_TOTAL_CIDADES])
{
    FILE *ptr_arquivo = NULL;
    int result = 0;
    char arquivo[100] = "./data/";

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

int salvarConfigListaArquivos(char *nome_arquivo)
{
    FILE *ptr_arquivo = NULL;
    int result = 0;
    char arquivo[100] = CONFIG;

    ptr_arquivo = fopen(arquivo, "a");

    if (ptr_arquivo != NULL)
    {
        fprintf(ptr_arquivo, "%s.txt", nome_arquivo);
        result = 1;
    }

    fclose(ptr_arquivo);

    return result;
}

int listarArquivos(char (*vetor_arquivos_salvos)[MAX_CARACTERES_NOMES_CIDADES * 4])
{
    FILE *ptr_arquivo = NULL;

    char arquivo[100] = CONFIG, temp_linha_texto[200];

    ptr_arquivo = fopen(arquivo, "r");

    char aux_nome;
    int i = 0;

    while (fgets(temp_linha_texto, MAX_CARACTERES_NOMES_CIDADES, ptr_arquivo) != NULL)
    {
        strcpy(vetor_arquivos_salvos[i], temp_linha_texto);
        i++;
    }

    return i;
}

void relatorioCidades(int total_cidades_cadastradas, char (*vetor_cidades)[MAX_CARACTERES_NOMES_CIDADES], float (*mtz_adjacente_cidades)[MAX_TOTAL_CIDADES])
{
    limpar_Terminal();
    printf("------------------------------------------------------------\n");
    printf("|               >>> RELATORIO DAS CIDADES <<<              |");
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

void menuArquivosSalvosCidades(int total_cidades_cadastradas, char (*vetor_cidades)[MAX_CARACTERES_NOMES_CIDADES], float (*mtz_adjacente_cidades)[MAX_TOTAL_CIDADES])
{
    // antes de exibir o menu eu preciso carrregar os dados do arquivo para os vetores e matrizes
    int opcao = 0, i = 0;

    while (TRUE)
    {
        if (i == 0)
        {
            limpar_Terminal();
        }
        printf("------------------------------------------------------------\n");
        printf("|        *** Menu CIDADE(s) salvas em arquivos ***        |");
        printf("\n------------------------------------------------------------\n");
        printf("1. Relatario das cidades\n");
        printf("2. Mostrar matriz de distâncias\n");
        printf("3. Mostrar matriz de predecessores\n");
        printf("4. Mostrar caminho entre dois municípios\n");
        printf("5. Salvar resultados em arquivo\n");
        printf("0. Menu Anterior\n");
        printf("\n-----------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%i", &opcao);

        if (opcao == 0)
        {
            break;
        }
        else if (opcao == 1)
        {
        }
        else if (opcao == 2)
        {
            relatorioCidades(total_cidades_cadastradas, vetor_cidades, mtz_adjacente_cidades);
        }
        else
        {
            continue;
        }
        i = 1;
    }
}

/*


int carregarCidades()
{
    // Atualizar para a constante depois;
    FILE *ptr_arquivo = NULL;
    int i = 0;
    char arquivo[MAX_CARACTERES_NOMES_CIDADES] = "./", texto_txt[MAX_CARACTERES_NOMES_CIDADES];

    strcat(arquivo, DADOS_CIDADES);

    ptr_arquivo = fopen(arquivo, "r");

    // leitura de arquivo de texto ou csv configurando e carregando em um array

    if (ptr_arquivo != NULL)
    {
        while (fgets(texto_txt, MAX_CARACTERES_NOMES_CIDADES, ptr_arquivo) != NULL)
        {
            strcpy(mtz_adjacente_distancias[i], texto_txt);
            i++;
        }
    }

    // aqui vai ser adicionado dentro de um array de cidades;

    fclose(ptr_arquivo);

    return i;
}

*/