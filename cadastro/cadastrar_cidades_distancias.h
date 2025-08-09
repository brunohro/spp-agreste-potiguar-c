#ifndef CADASTRAR_CIDADES_DISTANCIAS_H
#define CADASTRAR_CIDADES_DISTANCIAS_H

#include "../rotas.h"

int cadastrarCidadesDistancias(int total_cidades_cadastradas, char vetor_cidades[][MAX_CARACTERES_NOMES_CIDADES], float mtz_adjacente_cidades[][MAX_TOTAL_CIDADES]);

int salvarCidades(char *nome_arquivo, int total_cidades_cadastradas, char vetor_cidades[][MAX_CARACTERES_NOMES_CIDADES], float mtz_adjacente_cidades[][MAX_TOTAL_CIDADES]);

#endif