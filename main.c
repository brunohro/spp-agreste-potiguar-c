#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <dirent.h>

// libs próprias
#include "leitura/leitura.h"
#include "salvar/salvar_arquivo.h"
#include "floyd_warshall/floyd_warshall.h"
#include "matriz/matriz_int.h"
#include "matriz/matriz_float.h"
#include "caminho/mostrar_caminho.h"
#include "cadastro/cadastrar_cidades.h"

int cadastrarCidades(int total_cidades_cadastradas, char vetor_cidades[][MAX_CARACTERES_NOMES_CIDADES], float mtz_adjacente_cidades[][MAX_TOTAL_CIDADES]);

int salvarCidades(char *nome_arquivo, int total_cidades_cadastradas, char vetor_cidades[][MAX_CARACTERES_NOMES_CIDADES], float mtz_adjacente_cidades[][MAX_TOTAL_CIDADES]);
int carregarCidades();

void relatorioCidades(int total_cidades_cadastradas, char vetor_cidades[][MAX_CARACTERES_NOMES_CIDADES]);
int salvarCidadess_distancias(int linha, int coluna, float distancia);
int cadastrarCidadesDistancias(int total_cidades_cadastradas, char vetor_cidades[][MAX_CARACTERES_NOMES_CIDADES], float mtz_adjacente_cidades[][MAX_TOTAL_CIDADES]);

int listarArquivos(char vetor_arquivos_salvos[][MAX_CARACTERES_NOMES_CIDADES * 4]);

void limpar_Terminal();

int main()
{
    int mtzPredecessoresCidades[MAX_TOTAL_CIDADES][MAX_TOTAL_CIDADES];
    float mtzAdjacenciasCidades[MAX_TOTAL_CIDADES][MAX_TOTAL_CIDADES];
    float mtzDistanciasMinimas[MAX_TOTAL_CIDADES][MAX_TOTAL_CIDADES];
    char vetorCidades[MAX_TOTAL_CIDADES][MAX_CARACTERES_NOMES_CIDADES];
    char vetorArquivosSalvos[MAX_LISTAR_ARQUIVOS][MAX_CARACTERES_NOMES_CIDADES * 4];

    int opcao, indiceVetorArquivosSalvos, origem, destino, totalCidadesCadastradas = 0, totalArquivosCarregados = 0, tempTotalCidadesCadastradas = 0;
    char nome_arquivo[MAX_LISTAR_ARQUIVOS], mensagem[MAX_LISTAR_ARQUIVOS];
    limpar_Terminal();

    do
    {
        printf("\n");
        printf("+==================================================+\n");
        printf("| OLA, SEJA BEM-VINDO(A) AO ROTAS AGRESTE-POTIGUAR |\n");
        printf("+==================================================+\n");
        printf("| 1. Cidades [cadastro avulso]                     |\n");
        printf("| 2. Carregar dados atraves de arquivo             |\n");
        printf("| 3. Mostrar matriz de adjacencias                 |\n");
        printf("| 4. Mostrar matriz de distancias Minima           |\n");
        printf("| 5. Mostrar matriz de predecessores               |\n");
        printf("| 6. Mostrar caminho entre dois municipios         |\n");
        printf("| 7. Relatorio das cidades                         |\n");
        printf("| 8. Salvar resultados em arquivo                  |\n");
        printf("| 0. Sair do programa                              |\n");
        printf("+==================================================+\n");
        if (totalCidadesCadastradas > 0)
        {
            if (indiceVetorArquivosSalvos == 0)
            {
                if (opcao != 2)
                {

                    printf("\n%s ", mensagem);
                }
                else
                {
                    printf("\n%s ", mensagem);
                }
            }
            else if (indiceVetorArquivosSalvos > 0)
            {
                printf("\n%s ", mensagem);
            }

            printf(">>>> Cidades Cadastrada: %i \n ------------------------------------------------------------\n\n", totalCidadesCadastradas);
        }
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            // se não cadastrei nenhuma cidade, devo manter a listagem anterior
            // pois um cadastro não efetuado não apaga uma lista anterior;
            tempTotalCidadesCadastradas = cadastrarCidades(0, vetorCidades, mtzAdjacenciasCidades);
            if (tempTotalCidadesCadastradas > 0)
            {
                totalCidadesCadastradas = tempTotalCidadesCadastradas;
                indiceVetorArquivosSalvos = 0;
                floyd_warshall(totalCidadesCadastradas, mtzAdjacenciasCidades, mtzDistanciasMinimas, mtzPredecessoresCidades);
                strcpy(mensagem, "");
                strcat(mensagem, ">>   usuario ");
            }
            break;
        case 2:
            limpar_Terminal();
            printf("+==================================================+\n");
            printf("|             *** SELECIONAR ARQUIVOS ***          |\n");
            printf("+==================================================+\n");

            totalArquivosCarregados = listarArquivos(vetorArquivosSalvos);

            if (totalArquivosCarregados > 0)
            {
                for (int i = 0; i < totalArquivosCarregados; i++)
                {
                    printf("\n%i - %s", i + 1, vetorArquivosSalvos[i]);
                    printf("\n......................................................................");
                }
                printf("\n\n0 - Menu Anterior ");
                printf("\n\n************************************************************");
                printf("\nEscolha uma opcao: ");
                scanf("%i", &indiceVetorArquivosSalvos);

                if (indiceVetorArquivosSalvos >= 0 && indiceVetorArquivosSalvos < totalArquivosCarregados + 1)
                {

                    if (indiceVetorArquivosSalvos == 0)
                    {
                        printf("\n\nNenhum Arquivo selecionado!!!\n");
                    }
                    else
                    {
                        totalCidadesCadastradas = ler_arquivo_entrada(0, vetorArquivosSalvos[indiceVetorArquivosSalvos - 1], vetorCidades, mtzAdjacenciasCidades);
                        floyd_warshall(totalCidadesCadastradas, mtzAdjacenciasCidades, mtzDistanciasMinimas, mtzPredecessoresCidades);
                        strcpy(mensagem, "");
                        strcat(mensagem, ">>   Arquivo:");
                        strcat(mensagem, vetorArquivosSalvos[indiceVetorArquivosSalvos - 1]);
                    }
                }
            }
            else
            {
                printf("\n------------------------------------------------------------");
                printf("\nNenhum arquivo encontrado!!!! ");
                printf("\n+==================================================+\n\n");

                system("pause");
                continue;
            }
            break;
        case 3:
            if (totalCidadesCadastradas > 0)
            {
                printf("\nMATRIZ ADJACENCIAS\n\n");
                imprimir_matriz_float(totalCidadesCadastradas, mtzAdjacenciasCidades);
            }
            else
            {
                printf("\nATENCAO, total de cidades cadastradas [ %.3i ]", totalCidadesCadastradas);
                printf("\nCadastre as cidades [opcao 1] ou carregue um arquivo [opcao 2]");
                printf("\n+============================================================+\n\n");
                system("pause");
            }
            break;
        case 4:
            if (totalCidadesCadastradas > 0)
            {
                printf("\nMATRIZ DISTANCIAS MINIMAS\n\n");
                imprimir_matriz_float(totalCidadesCadastradas, mtzDistanciasMinimas);
            }
            else
            {
                printf("\nATENCAO, total de cidades cadastradas [ %.3i ]", totalCidadesCadastradas);
                printf("\nCadastre as cidades [opcao 1] ou carregue um arquivo [opcao 2]");
                printf("\n+============================================================+\n\n");
                system("pause");
            }
            break;
        case 5:
            if (totalCidadesCadastradas > 0)
            {
                printf("\nMATRIZ PREDECESSORES\n\n");
                imprimir_matriz_int(totalCidadesCadastradas, mtzPredecessoresCidades);
            }
            else
            {
                printf("\nATENCAO, total de cidades cadastradas [ %.3i ]", totalCidadesCadastradas);
                printf("\nCadastre as cidades [opcao 1] ou carregue um arquivo [opcao 2]");
                printf("\n+============================================================+\n\n");
                system("pause");
            }

            break;
        case 6:
            if (totalCidadesCadastradas > 0)
            {
                printf("indice do municipio de origem: ");
                scanf("%d", &origem);
                printf("indice do municipio de destino: ");
                scanf("%d", &destino);
                mostrar_caminho(origem, destino, mtzDistanciasMinimas, mtzPredecessoresCidades, vetorCidades);
            }
            else
            {
                printf("\nATENCAO, total de cidades cadastradas [ %.3i ]", totalCidadesCadastradas);
                printf("\nCadastre as cidades [opcao 1] ou carregue um arquivo [opcao 2]");
                printf("\n+============================================================+\n\n");
                system("pause");
            }

            break;
        case 7:
            relatorioCidades(totalCidadesCadastradas, vetorCidades);
            break;
        case 8:
            if (totalCidadesCadastradas > 0)
            {
                printf("Nome do arquivo de saida: ");
                scanf("%s", nome_arquivo);
                salvar_arquivo_saida(totalCidadesCadastradas, nome_arquivo, mtzDistanciasMinimas, mtzPredecessoresCidades);
            }
            else
            {
                printf("\nATENCAO, total de cidades cadastradas [ %.3i ]", totalCidadesCadastradas);
                printf("\nCadastre as cidades [opcao 1] ou carregue um arquivo [opcao 2]");
                printf("\n+============================================================+\n\n");
                system("pause");
            }

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

int salvarCidades(char *nome_arquivo, int total_cidades_cadastradas, char vetor_cidades[][MAX_CARACTERES_NOMES_CIDADES], float mtz_adjacente_cidades[][MAX_TOTAL_CIDADES])
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

int listarArquivos(char vetor_arquivos_salvos[][MAX_CARACTERES_NOMES_CIDADES * 4])
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

void relatorioCidades(int total_cidades_cadastradas, char vetor_cidades[][MAX_CARACTERES_NOMES_CIDADES])
{

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
    // limpar_Terminal();
    // Deixar visivel para acompanhar na origem e no destino
}
