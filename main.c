#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <dirent.h>

// libs próprias
// cadastro
#include "cadastro/cadastrar_cidades.h"
#include "cadastro/cadastrar_cidades_distancias.h"

// arquivos
#include "leitura/leitura.h"
#include "salvar/salvar_arquivo.h"
#include "salvar/salvar_cidades.h"

// algoritmo
#include "floyd_warshall/floyd_warshall.h"

// exibir
#include "matriz/matriz_int.h"
#include "matriz/matriz_float.h"
#include "caminho/mostrar_caminho.h"
#include "listar_arquivos/listar_arquivos.h"
#include "relatorio/relatorio_cidades.h"

// protótipo das funções
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
