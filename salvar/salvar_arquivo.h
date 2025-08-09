#ifndef SALVAR_H
#define SALVAR_H
#include "../rotas.h"

int salvar_arquivo_saida(int total_cidades_cadastradas,char nome_arquivo[MAX_LISTAR_ARQUIVOS],float (*mtz_distancias_minimas)[MAX_TOTAL_CIDADES],  int (*mtz_predecessores_cidades)[MAX_TOTAL_CIDADES]);

#endif