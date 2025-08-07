#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <dirent.h>

#define MAX_TOTAL_CIDADES 50
#define MAX_CARACTERES_NOMES_CIDADES 50
#define INF 10000.0
#define TRUE 1
#define CONFIG "./dados/"

int cadastrarCidades(int total_cidades_cadastradas, char (*vetor_cidades)[MAX_CARACTERES_NOMES_CIDADES], float (*mtz_adjacente_cidades)[MAX_TOTAL_CIDADES]);
int salvarCidades(char *nome_arquivo, int total_cidades_cadastradas, char (*vetor_cidades)[MAX_CARACTERES_NOMES_CIDADES], float (*mtz_adjacente_cidades)[MAX_TOTAL_CIDADES]);
int carregarCidades();
void relatorioCidades(int total_cidades_cadastradas, char (*vetor_cidades)[MAX_CARACTERES_NOMES_CIDADES], float (*mtz_adjacente_cidades)[MAX_TOTAL_CIDADES]);
int salvarCidadess_distancias(int linha, int coluna, float distancia);
int cidadesDistancias(int total_cidades_cadastradas, char (*vetor_cidades)[MAX_CARACTERES_NOMES_CIDADES], float (*mtz_adjacente_cidades)[MAX_TOTAL_CIDADES]);
int listarArquivos(char (*vetor_arquivos_salvos)[MAX_CARACTERES_NOMES_CIDADES * 4]);
void limpar_Terminal();

int main()

{
    float mtzAdjacenteCidades[MAX_TOTAL_CIDADES][MAX_TOTAL_CIDADES];
    char vetorCidades[MAX_TOTAL_CIDADES][MAX_CARACTERES_NOMES_CIDADES];
    char vetorArquivosSalvos[MAX_TOTAL_CIDADES * 2][MAX_CARACTERES_NOMES_CIDADES * 4];

    int opcao, indiceVetorArquivosSalvos, origem, destino, totalCidadesCadastradas = 0;

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
        printf("3. Relatario das cidades\n");
        printf("4. Mostrar matriz de distancias\n");
        printf("5. Mostrar matriz de predecessores\n");
        printf("6. Mostrar caminho entre dois municipios\n");
        printf("7. Salvar resultados em arquivo\n");
        printf("0. Sair\n");

        if (totalCidadesCadastradas > 0)
        {
            if (opcao == 1)
                printf("\n>>   usuario ");
            else if (opcao == 2)
                if (indiceVetorArquivosSalvos > 0)
                    printf("\n>>   Arquivo: %s", vetorArquivosSalvos[indiceVetorArquivosSalvos - 1]);
            ;
            printf("------------------------------------------------------------\n\n>>>> Cidades Cadastrada: %i \n", totalCidadesCadastradas);
        }
        printf("\n------------------------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%i", &opcao);

        switch (opcao)
        {
        case 0:
            break;
        case 1:
            totalCidadesCadastradas = cadastrarCidades(0, vetorCidades, mtzAdjacenteCidades);
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
                printf("\n\n0 - Menu Anterior ");
                printf("\n\n------------------------------------------------------------");
                printf("\nEscolha uma opcao: ");
                scanf("%i", &indiceVetorArquivosSalvos);

                if (indiceVetorArquivosSalvos >= 0 && indiceVetorArquivosSalvos < totalCidadesCadastradas)
                {
                      //Como o primeiro se garante que o intervalo vai ser entre os valores validos;                 
                    if (indiceVetorArquivosSalvos == 0)
                    {
                        totalCidadesCadastradas = 0;
                
                    }else{
                        //Aqui direciona para a função de ler os dados de um arquivo
                        
                    }
                }
            }
            else
            {
                printf("\n------------------------------------------------------------");
                printf("\nNenhum arquivo encontrado!!!! ");
                printf("\n------------------------------------------------------------\n\n");
                system("pause");
            }

            break;
        case 3:
            relatorioCidades(totalCidadesCadastradas, vetorCidades, mtzAdjacenteCidades);
            break;
        default:

            break;
        }

    } while (opcao != 0);

    printf("\nPrograma finalizado com sucesso, VOLTE SEMPRE!!!\n\n");

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
                if (cidadesDistancias(total_cidades_cadastradas, vetor_cidades, mtz_adjacente_cidades) == 0)
                    printf("Erro ao salvar as distancias");
            }

            break;
        }
    }
    limpar_Terminal();
    return total_cidades_cadastradas;
}

int cidadesDistancias(int total_cidades_cadastradas, char (*vetor_cidades)[MAX_CARACTERES_NOMES_CIDADES], float (*mtz_adjacente_cidades)[MAX_TOTAL_CIDADES])
{
    int result = 1, salvarNoArquivo;
    float ditanciaKM = 0;
    char nome_arquivo[MAX_CARACTERES_NOMES_CIDADES];

    for (int l = 0; l < total_cidades_cadastradas; l++)
    {
        for (int c = 0; c < total_cidades_cadastradas; c++)
        {
            if (l == c)
            {
                mtz_adjacente_cidades[l][c] = 0.00;
            }
            else
            {

                printf("\nInforme a distancia em km entre [ %s ] - [ %s ]\n[digite -1 se elas nao tiverem ligacao direta] ", vetor_cidades[l], vetor_cidades[c]);
                scanf("%f", &ditanciaKM);

                if (ditanciaKM > 0)
                {
                    mtz_adjacente_cidades[l][c] = ditanciaKM;
                }
                else if (ditanciaKM < 0)
                {
                    mtz_adjacente_cidades[l][c] = INF;
                }
            }
        }
    }

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
        scanf("%i", &salvarNoArquivo);

        if (salvarNoArquivo == 1)
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
                result = 0;
                continue;
            }
        }
        else if (salvarNoArquivo == 0)
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

    // precisa acrescetar a biblioteca <dirent.h>

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
