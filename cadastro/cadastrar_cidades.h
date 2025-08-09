#ifndef CADASTRAR_CIDADES_H
#define CADASTRAR_CIDADES_H

#include "../rotas.h"

int cadastrarCidades(int total_cidades_cadastradas, char vetor_cidades[][MAX_CARACTERES_NOMES_CIDADES], float mtz_adjacente_cidades[][MAX_TOTAL_CIDADES]);

int cadastrarCidadesDistancias(int total_cidades_cadastradas, char vetor_cidades[][MAX_CARACTERES_NOMES_CIDADES], float mtz_adjacente_cidades[][MAX_TOTAL_CIDADES]);

#endif