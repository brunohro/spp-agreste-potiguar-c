#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>

#define MAX 100
#define MAX_NOMES_CIDADES 50
#define INF 10000.0
#define TRUE 1
#define PASTADADOS "data"
#define ARQUIVOROTAS "rotas.txt"

// definir as variáveis globais temporariamente

struct Cidades
{
    int indice;
    char nome_cidade[MAX_NOMES_CIDADES];
};

// ponteiros globais
int *ptr_total_cidades_cadastradas;

// LISTA DE MATRIZES

void menu_principal();
void menu_secundario();
void Cadastrar_cidades();
void Gerar_relatorio_todas_cidades();
int Salvar_cidade(char dado[MAX_NOMES_CIDADES]);
int Carregar_cidades(struct Cidades *cidade);
void Relatorio_cidades();

int main()

{

    setlocale(LC_ALL, "portuguese");
    int opcao, origem, destino, totalMunicipiosCadastrados = 0, menu_secundario;

    struct Cidades cidades;
    struct Cidades *ptr_cidades;

    ptr_cidades = &cidades;
    ptr_total_cidades_cadastradas = &totalMunicipiosCadastrados;

    totalMunicipiosCadastrados = Carregar_cidades(ptr_cidades);

    if (totalMunicipiosCadastrados != 0)
    {
    }

    menu_principal();

    return 0;
}

void menu_principal()
{

    int opcao = 0;
    while (TRUE)
    {
        system("cls");
        printf("\n\n            <<<<<<<<<<>>>>>>>>>>");
        printf("\n  /// OLá, SEJA BEM-VINDO(A) AO SISTEMA ///");
        printf("\n      Total de Cidades Cadastradas: %i", *ptr_total_cidades_cadastradas);
        printf("\n =============================================================");

        printf("\n\n-----------------------------------------------\n");
        printf("|              *** Menu PRINCIPAL ***             |");
        printf("\n-----------------------------------------------\n");
        printf("1. Cidades\n");
        printf("2. Logistica\n");
        printf("0. Sair\n");
        printf("\n-----------------------------------------------\n");
        printf("Escolha uma opção: ");
        scanf("%i", &opcao);

        if (opcao == 0)
        {
            break;
        }
        else if (opcao == 1)
        {
            menu_secundario();
        }
        else if (opcao == 2)
        {
        }
        else
        {
            continue;
        }
    }
}

void menu_secundario()
{

    int opcao = 0;
    while (TRUE)
    {
        system("cls");
        printf("\n\n-----------------------------------------------\n");
        printf("\n  *** Menu CIDADE(s) *** \n");
        printf("Você possui %i cadastradas", *ptr_total_cidades_cadastradas);
        printf("\n-----------------------------------------------\n");
        printf("1. Cadastrar Cidades\n");
        printf("2. Relatário das cidades\n");
        printf("3. Pesquisar uma cidade\n");
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
            Relatorio_cidades();
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

    char cidades[100];
    int opcao = 1, ch;

    while (TRUE)
    {
        fflush(stdin);

        printf("\n-----------------------------------------------\n");
        printf("\nPara Sair pressione no teclado a tecla ESC \n");
        printf("\nCidade(s) cadastrada(s) : %i", *ptr_total_cidades_cadastradas);
        printf("\nDIGITE O NOME DA CIDADE: ");
        ch = getch();
        if (ch == 27)
        {
            break;
        }
        scanf("%[^\n]", &cidades);

        if (Salvar_cidade(cidades) == 1)
        {
            printf("\n\nCIDADE CADASTRADA COM SUCESSO! \n\n");
            *ptr_total_cidades_cadastradas += 1;
        }
        else
        {
            printf("\n\nErro ao salvar a cidade! \n\n");
        }
        
        if (opcao == 0)
        {
            break;
        }
    }
}

void Gerar_relatorio_todas_cidades()
{
    // se cidades for igua a 0, apresentar a mensagem de nenhuma cidade cadastrada -> se n?o exibir todas as cidades cadastradas;
}

int Salvar_cidade(char dado[100])
{
    FILE *ptr_arquivo = NULL;
    int result = 0;
    char arquivo[100] = "./";

    strcat(arquivo, PASTADADOS);
    strcat(arquivo, "/");
    strcat(arquivo, ARQUIVOROTAS);

    ptr_arquivo = fopen(arquivo, "a");

    if (ptr_arquivo != NULL)
    {
        printf("salvando...");
        fprintf(ptr_arquivo, "%s\n", dado);
        result = 1;
    }

    fclose(ptr_arquivo);

    return result;
}

int Carregar_cidades(struct Cidades *cidade)
{
    // Atualizar para a constante depois;
    FILE *ptr_arquivo = NULL;
    int i = 0;
    char arquivo[100] = "./", texto_txt[100];

    strcat(arquivo, PASTADADOS);
    strcat(arquivo, "/");
    strcat(arquivo, ARQUIVOROTAS);

    ptr_arquivo = fopen(arquivo, "r");

    // leitura de arquivo de texto ou csv configurando e carregando em um array

    if (ptr_arquivo != NULL)
    {
        while (fgets(texto_txt, MAX_NOMES_CIDADES, ptr_arquivo) != NULL)
        {
            (cidade)->indice = i;
            strcpy((cidade)->nome_cidade, texto_txt);

            i++;
        }
    }

    // aqui vai ser adicionado dentro de um array de cidades;

    fclose(ptr_arquivo);

    return i;
}

void Relatorio_cidades()
{
    if(*ptr_total_cidades_cadastradas >= 1){
        //logica para listar todas as cidades....
    }else{
        printf("\n\nNão existe nenhuma cidade Cadastrada!\n");
        
    }
    
    system("pause");

}


