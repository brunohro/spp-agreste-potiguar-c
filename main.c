#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#define MAX_TOTAL_CIDADES 15
#define MAX_CARACTERES_NOMES_CIDADES 50
#define INF 10000.0
#define TRUE 1
#define DADOS_CIDADES "data/cidades.txt"
#define DADOS_cidadesDistancias "data/cidadesDistancias.txt"

// FUNCOES
int menuCidades(int total_cidades_cadastradas, char (*vetor_cidades)[MAX_CARACTERES_NOMES_CIDADES], float (*mtz_adjacente_cidades)[MAX_TOTAL_CIDADES]);

void cadastrarCidades(int total_cidades_cadastradas, char (*vetor_cidades)[MAX_CARACTERES_NOMES_CIDADES], float (*mtz_adjacente_cidades)[MAX_TOTAL_CIDADES]);
int salvarCidades(char *nome_arquivo, int total_cidades_cadastradas, char (*vetor_cidades)[MAX_CARACTERES_NOMES_CIDADES], float (*mtz_adjacente_cidades)[MAX_TOTAL_CIDADES]);

// O USO DO VETOR DE CARACTERES (STRING) COM ESTA SINTAXE SIGNIFICA IMPLICITAMENTE QUE ESTOU PASSANDO UM VALOR POR REFERENCIA
//  podendo ser substituido por
// int carregarCidades(char *(cidade)[MAX_CARACTERES_NOMES_CIDADES]);
int carregarCidades();
void relatorioCidades();
int salvarCidadess_distancias(int linha, int coluna, float distancia);
int cidadesDistancias();

void limpar_Terminal();

int main()

{
    float mtzAdjacenteCidades[MAX_TOTAL_CIDADES][MAX_TOTAL_CIDADES];
    char vetorCidades[MAX_TOTAL_CIDADES][MAX_CARACTERES_NOMES_CIDADES];

    int opcao, origem, destino, totalCidadesCadastradas = 0;

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
        printf("3. Logistica\n");
        printf("0. Sair\n");
        printf("\n------------------------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%i", &opcao);

        switch (opcao)
        {
        case 0:
            printf("\nPrograma finalizado com sucesso, VOLTE SEMPRE!!!\n\n");
            break;
        case 1:
            menuCidades(totalCidadesCadastradas, vetorCidades, mtzAdjacenteCidades);
            break;
        default:
            continue;
            break;
        }
    } while (opcao != 0);

    return 0;
}

int menuCidades(int total_cidades_cadastradas, char (*vetor_cidades)[MAX_CARACTERES_NOMES_CIDADES], float (*mtz_adjacente_cidades)[MAX_TOTAL_CIDADES])
{

    int opcao = 0;
    while (TRUE)
    {
        limpar_Terminal();
        printf("------------------------------------------------------------\n");
        printf("|                  *** Menu CIDADE(s) ***                  |");
        printf("\n------------------------------------------------------------\n");
        printf("Voce possui %.3i Cadastros\n\n", total_cidades_cadastradas);
        printf("1. Cadastrar Cidades\n");
        printf("2. Relatario das cidades\n");
        // printf("3. Pesquisar uma cidade\n");
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

            cadastrarCidades(0, vetor_cidades, mtz_adjacente_cidades);
        }
        else if (opcao == 2)
        {
            // relatorioCidades();
        }
        else
        {
            continue;
        }
    }

    return 0;
}
void limpar_Terminal()
{
    system("clear");
}

void cadastrarCidades(int total_cidades_cadastradas, char (*vetor_cidades)[MAX_CARACTERES_NOMES_CIDADES], float (*mtz_adjacente_cidades)[MAX_TOTAL_CIDADES])
{
    // pedir para cadastrar a cidade - OK
    // salvar no arquivo txt - OK
    // incrementar quantas cidades tem cadastradas - ok
    // verificar as vizinhas - PENDENTE
    // precisa cadastrar e depois verificar se existe outros dados para ir salvando no arquivo de texto - PENDENTES

    // char cidades[100];
    int opcao = 0, i = 0;
    char temp_nome_cidades[MAX_CARACTERES_NOMES_CIDADES], temp_nome;

    while (TRUE)
    {
        fflush(stdin);
        scanf("%c", &temp_nome);
        if (i == 0)
        {
            limpar_Terminal();
        }

        printf("------------------------------------------------------------\n");
        printf("|                 *** CADASTRAR CIDADES ***                 |");
        printf("\n------------------------------------------------------------");
        printf("\nENCERRAR O CADASTRO >> pressione a tecla 0 + [enter] <<");
        printf("\n>>Ao encerrar o cadastro informe o preenchimento das distancias em km entre as cidades <<\n");
        printf("\n\n------------------------------------------------------------");
        printf("\nCidades Cadastradas %i", total_cidades_cadastradas);

        printf("\nDIGITE O NOME DA CIDADE [sem acentuacao]: ");
        scanf("%[^\n]", &temp_nome_cidades[0]);

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

                total_cidades_cadastradas += 1;
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

                printf("\nInforme a distancia em km entre as cidades [ %s ]-[ %s ]\n[digite -1 se elas nao tiverem ligacao direta] ", vetor_cidades[l], vetor_cidades[c]);
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
        printf("\n>>1: SIM. <<  >>");
        printf("0: NAO. <<\n");
        printf("\n------------------------------------------------------------\n");
        printf("Escolha uma das opcoes");
        scanf("%i", &salvar);

        if (salvar == 1){
           scanf("%c", &nome_arquivo[0]);
            printf("Informe o nome do arquivo: ");
            scanf("%[^\n]", &nome_arquivo[0]);
            if (salvarCidades(nome_arquivo,total_cidades_cadastradas, vetor_cidades, mtz_adjacente_cidades) == 1) {
                printf("ARQUIVO [ %s ] SALVO COM SUCESSO!!!\n\n", nome_arquivo);                
                break;
            }
            else {
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
    char arquivo[100] = "./data";

    strcat(arquivo, nome_arquivo);
    strcat(arquivo,".txt");

    ptr_arquivo = fopen(arquivo, "a");

    if (ptr_arquivo != NULL)
    {
        printf("\nsalvando...\n");
        fprintf(ptr_arquivo, "%i\n", total_cidades_cadastradas);
        for (int i = 0; i < total_cidades_cadastradas; i++)
        {
            fprintf(ptr_arquivo, "%s\n", vetor_cidades[i]);
        }
        for (int l = 0; l < total_cidades_cadastradas; l++)
        {
            for (int c = 0; c < total_cidades_cadastradas; c++)
            {
                (c != total_cidades_cadastradas - 1) ? fprintf(ptr_arquivo, "%f", mtz_adjacente_cidades[l][c]) : fprintf(ptr_arquivo, "%f\n", mtz_adjacente_cidades[l][c]);
            }
        }

        result = 1;
    }

    fclose(ptr_arquivo);

    return result;
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

void relatorioCidades()
{
    limpar_Terminal();
    printf("------------------------------------------------------------\n");
    printf("|               >>> RELATARIO DAS CIDADES <<<              |");
    printf("\n------------------------------------------------------------\n");
    if (*ptr_total_cidades_cadastradas >= 1)
    {
        // logica para listar todas as cidades....
        printf("\nTotal de cidades cadastradas: %i", *ptr_total_cidades_cadastradas);
        printf("\n----------------------------------------------\n\n");
        for (int i = 0; i < *ptr_total_cidades_cadastradas; i++)
        {
            printf("%.2i: %s", i + 1, mtz_adjacente_distancias[i]);
        }
    }
    else
    {
        printf("\n\nNao existe nenhuma cidade Cadastrada!\n");
    }
    printf("\n------------------------------------------------------------\n\n");
    system("pause");
}



// falta finalizar
int salvarCidadess_distancias(int linha, int coluna, float distancia)
{
    int result = 0;

    FILE *ptr_arquivo = NULL;
    char arquivo[100] = "./";

    strcat(arquivo, DADOS_cidadesDistancias);

    ptr_arquivo = fopen(arquivo, "a");

    mtz_adjacente_distancias[linha][coluna] = distancia;

    if (ptr_arquivo != NULL)
    {
        fprintf(ptr_arquivo, "%f", mtz_adjacente_distancias[linha][coluna]);
        result = 1;
    }

    fclose(ptr_arquivo);
    return result;
}

// falta finalizar
int cidadesDistancias()
{
    int result = 1, opcao;
    // criar um for percorrendo a matriz toda;
    for (int l = 0; l < *ptr_total_cidades_cadastradas; l++)
    {
        for (int c = 0; c < *ptr_total_cidades_cadastradas; c++)
        {
            if (l == c)
            {
                mtz_adjacente_distancias[l][c] = 0.0;
            }
            else
            {
                printf("\n------------------------------------------------------------");
                printf("\nA cidade %s possui ligacao direta com a cidade %s? 1:[sim] ou 0:[nao] ");
                scanf("%i", opcao);

                switch (opcao)
                {
                case 0:
                    mtz_adjacente_distancias[l][c] = INF;
                    break;
                case 1:
                    printf("\n------------------------------------------------------------");
                    printf("\nInforme a distancia entre as duas cidades ");
                    scanf("%.2f", &mtz_adjacente_distancias[l][c]);
                    break;
                default:
                    break;
                }
            }
        }
    }

    return result;
}
*/