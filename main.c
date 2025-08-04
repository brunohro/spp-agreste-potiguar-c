#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include <ctype.h>

#define MAX_TOTAL_CIDADES 15
#define MAX_CARACTERES_NOMES_CIDADES 50
#define INF 10000.0
#define TRUE 1
#define DADOS_CIDADES "data/cidades.txt"
#define DADOS_CIDADES_DISTANCIAS "data/cidades_distancias.txt"

// definir as variáveis globais temporariamente

// ponteiros globais
int *ptr_total_cidades_cadastradas;

// LISTA DE MATRIZES
float mtz_cidades_distancias[MAX_TOTAL_CIDADES][MAX_TOTAL_CIDADES]; // matriz onde ira ficar armazenado todo o valor das distancia entre as cidades

// VETORES
char vetor_cidades[MAX_TOTAL_CIDADES][MAX_CARACTERES_NOMES_CIDADES]; // Como eu vou utilizar esse vetor em muitos locais, prefere-se criar uma variavel global para facilitar a construção do site;

// FUNÇÕES
void menu_principal();
void menu_cidades();
void Cadastrar_cidades();
int Salvar_cidade(char *dado);
// O USO DO VETOR DE CARACTERES (STRING) COM ESTA SINTAXE SIGNIFICA IMPLICITAMENTE QUE ESTOU PASSANDO UM VALOR POR REFERENCIA
//  podendo ser substituido por
// int Carregar_cidades(char *(cidade)[MAX_CARACTERES_NOMES_CIDADES]);
int Carregar_cidades();
void Relatorio_cidades();
void converter_Maisculas(char *texto);
int salvar_cidades_distancias(int linha, int coluna, float distancia);
int cidades_distancias();

void limpar_Terminal();

int main()

{
    setlocale(LC_ALL, "portuguese");
    int opcao, origem, destino, totalMunicipiosCadastrados = 0, menu_cidades;

    ptr_total_cidades_cadastradas = &totalMunicipiosCadastrados;

    totalMunicipiosCadastrados = Carregar_cidades(vetor_cidades);

    if (totalMunicipiosCadastrados != 0)
    {
    }

    menu_principal();

    return 0;
}

void menu_principal()
{

    int opcao = 0;
    do
    {
        limpar_Terminal();
        printf("                    <<<<<<<<<<>>>>>>>>>>");
        printf("\n  /// OLÁ, SEJA BEM-VINDO(A) AO ROTAS AGRESTE-POTIGUAR ///");
        printf("\n============================================================");
        printf("\n             Total de cidades cadastradas: %.3i", *ptr_total_cidades_cadastradas);

        printf("\n\n------------------------------------------------------------\n");
        printf("|                  *** Menu PRINCIPAL ***                  |");
        printf("\n------------------------------------------------------------\n");
        printf("1. Cidades\n");
        printf("2. Logistica\n");
        printf("0. Sair\n");
        printf("\n------------------------------------------------------------\n");
        printf("Escolha uma opção: ");
        scanf("%i", &opcao);

        switch (opcao)
        {
        case 0:
            printf("\nPrograma finalizado com sucesso, VOLTE SEMPRE!!!\n\n");
            break;
        case 1:
            menu_cidades();
            break;
        default:
            continue;
            break;
        }
    } while (opcao != 0);
}

void menu_cidades()
{

    int opcao = 0;
    while (TRUE)
    {
        limpar_Terminal();
        printf("------------------------------------------------------------\n");
        printf("|                  *** Menu CIDADE(s) ***                  |");
        printf("\n------------------------------------------------------------\n");
        printf("Você possui %.3i Cadastros\n\n", *ptr_total_cidades_cadastradas);
        printf("1. Cadastrar Cidades\n");
        printf("2. Relatário das cidades\n");
        // printf("3. Pesquisar uma cidade\n");
        printf("0. Menu Anterior\n");
        printf("\n-----------------------------------------------\n");
        printf("Escolha uma opção: ");
        scanf("%i", &opcao);

        if (opcao == 0)
        {
            break;
        }
        else if (opcao == 1)
        {
            Cadastrar_cidades();
        }
        else if (opcao == 2)
        {
            Relatorio_cidades(vetor_cidades);
        }
        else
        {
            continue;
        }
    }
}

void Cadastrar_cidades()
{
    // pedir para cadastrar a cidade - OK
    // salvar no arquivo txt - OK
    // incrementar quantas cidades tem cadastradas - ok
    // verificar as vizinhas - PENDENTE
    // precisa cadastrar e depois verificar se existe outros dados para ir salvando no arquivo de texto - PENDENTES

    // char cidades[100];
    int opcao = 0, i = 0;
    char temp_nome_cidades[MAX_CARACTERES_NOMES_CIDADES];

    while (TRUE)
    {
        fflush(stdin);
         scanf("%c",&temp_nome_cidades);
        if (i == 0)
            limpar_Terminal();
        printf("------------------------------------------------------------\n");
        printf("|                 *** CADASTRAR CIDADES ***                 |");
        printf("\n------------------------------------------------------------");
        printf("\nMENU ANTERIOR >> pressione a tecla 0 + [enter] <<\n");
        printf("\n\n------------------------------------------------------------");
        printf("\nCidades Cadastradas %i", *ptr_total_cidades_cadastradas);

        printf("\nDIGITE O NOME DA CIDADE [sem acentuação]: ");
        scanf("%[^\n]", &temp_nome_cidades);

        if (strcmp(temp_nome_cidades, "0") != 0)
        {
            i = 1;
            printf("Olhando a cidade");
            if (*ptr_total_cidades_cadastradas < MAX_TOTAL_CIDADES)
            {
                converter_Maisculas(temp_nome_cidades);

                if (Salvar_cidade(temp_nome_cidades) == 1)
                {
                    limpar_Terminal();
                    printf("\nCIDADE CADASTRADA COM SUCESSO!");
                    printf("\n%s\n\n", temp_nome_cidades);
                    // ocorrendo o sucesso inseri as informações no vetor
                    strcpy(vetor_cidades[*ptr_total_cidades_cadastradas], temp_nome_cidades);
                    /*
                        Criar a função responsavel por inserir a distancia entre
                        os municiapios e salvar em uma matriz de distancias e salvar em txt;

                    */
                    *ptr_total_cidades_cadastradas += 1;
                    cidades_distancias();
                }
                else
                {
                    printf("\n\nErro ao salvar a cidade! \n\n");
                }
            }
            else
            {
                limpar_Terminal();
                printf("************************************************************");
                printf("\nERROR AO CADASTRAR [ %s ],\nQuantidade máxima de [ %.3i ] cadastro(s) atingida.\n\n", temp_nome_cidades, *ptr_total_cidades_cadastradas);
                continue;
            }
        }
        else
        {
            break;
        }
    }
}

int Salvar_cidade(char dado[100])
{
    FILE *ptr_arquivo = NULL;
    int result = 0;
    char arquivo[100] = "./";

    strcat(arquivo, DADOS_CIDADES);

    ptr_arquivo = fopen(arquivo, "a");

    if (ptr_arquivo != NULL)
    {
        printf("\nsalvando...");
        fprintf(ptr_arquivo, "%s\n", dado);
        result = 1;
    }

    fclose(ptr_arquivo);

    return result;
}

int Carregar_cidades()
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
            strcpy(vetor_cidades[i], texto_txt);
            i++;
        }
    }

    // aqui vai ser adicionado dentro de um array de cidades;

    fclose(ptr_arquivo);

    return i;
}

void Relatorio_cidades()
{
    limpar_Terminal();
    printf("------------------------------------------------------------\n");
    printf("|               >>> RELATÓRIO DAS CIDADES <<<              |");
    printf("\n------------------------------------------------------------\n");
    if (*ptr_total_cidades_cadastradas >= 1)
    {
        // logica para listar todas as cidades....
        printf("\nTotal de cidades cadastradas: %i", *ptr_total_cidades_cadastradas);
        printf("\n----------------------------------------------\n\n");
        for (int i = 0; i < *ptr_total_cidades_cadastradas; i++)
        {
            printf("%.2i: %s", i + 1, vetor_cidades[i]);
        }
    }
    else
    {
        printf("\n\nNão existe nenhuma cidade Cadastrada!\n");
    }
    printf("\n------------------------------------------------------------\n\n");
    system("pause");
}

void limpar_Terminal()
{
    system("cls");
}

void converter_Maisculas(char *texto)
{
    int i = 0;

    while (texto[i] != '\0')
    {
        texto[i] = toupper((unsigned char)texto[i]);
        i++;
    }
}

//falta finalizar
int salvar_cidades_distancias(int linha, int coluna, float distancia)
{
    int result = 0;

    FILE *ptr_arquivo = NULL;
    char arquivo[100] = "./";

    strcat(arquivo, DADOS_CIDADES_DISTANCIAS);

    ptr_arquivo = fopen(arquivo, "a");

    mtz_cidades_distancias[linha][coluna] = distancia;

    if (ptr_arquivo != NULL)
    {
        fprintf(ptr_arquivo, "%f", mtz_cidades_distancias[linha][coluna]);
        result = 1;
    }

    fclose(ptr_arquivo);
    return result;
}

//falta finalizar
int cidades_distancias()
{
    int result = 1, opcao;
    // criar um for percorrendo a matriz toda;
    for (int l = 0; l < *ptr_total_cidades_cadastradas; l++)
    {
        for (int c = 0; c < *ptr_total_cidades_cadastradas; c++)
        {
            if (l == c)
            {
                mtz_cidades_distancias[l][c] = 0.0;
            }
            else
            {
                printf("\n------------------------------------------------------------");
                printf("\nA cidade %s possui ligação direta com a cidade %s? 1:[sim] ou 0:[não] ");
                scanf("%i", opcao);

                switch (opcao)
                {
                case 0:
                    mtz_cidades_distancias[l][c] = INF;
                    break;
                case 1:
                    printf("\n------------------------------------------------------------");
                    printf("\nInforme a distância entre as duas cidades ");
                    scanf("%.2f", &mtz_cidades_distancias[l][c]);
                    break;
                default:
                    break;
                }
            }
        }
    }

    return result;
}
