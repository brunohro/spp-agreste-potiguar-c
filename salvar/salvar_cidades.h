#ifndef SALVAR_CIDADES_H
#define SALVAR_CIDADES_H
#include "../rotas.h"

int salvarCidades(char *nome_arquivo, int total_cidades_cadastradas, char vetor_cidades[][MAX_CARACTERES_NOMES_CIDADES], float mtz_adjacente_cidades[][MAX_TOTAL_CIDADES]);

#endif