#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <dirent.h>

#include "listar_arquivos.h"

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