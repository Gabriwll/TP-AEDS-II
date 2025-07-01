/**
 * @file relevanciaHash.h
 * @brief Cálculo de relevância para estrutura de Hash
 */

#ifndef RELEVANCIA_HASH_H
#define RELEVANCIA_HASH_H

#include "../Hash/tadhash.h"
#include <math.h>
#include <string.h>

#define TAM 5

typedef struct relevanciaHash {
    double re[TAM]; ///< Relevância por documento
} relevanciaHash;

typedef struct qtd_pala_arq_hash {
    int v_qtd[TAM]; ///< Quantidade de palavras por documento
} qtd_pala_arq_hash;

typedef struct WHash {
    double v_W[TAM]; ///< Peso por documento
} WHash;

void iniciar_qtd_pala_arq_hash(qtd_pala_arq_hash *qtd);
void iniciar_W_hash(WHash *w);
void inserir_qtd_pala_arq_hash(qtd_pala_arq_hash *qtd, int qtd_pala, int indice_arq);
int repeticao_pala_arq_hash(TipoDicionario ht, TipoPesos p, char *palavra, int indice_arq);
int repeticao_pala_total_hash(TipoDicionario ht,TipoPesos p, char *palavra);
double peso_W_hash(TipoDicionario ht, TipoPesos p, char *palavra, int indice_arq);
void inserir_peso_hash(relevanciaHash *rel, int indice_arq, TipoDicionario ht, TipoPesos p, char *palavra, WHash *p_w);
void preencher_relevancia_hash(relevanciaHash *rel, WHash w, qtd_pala_arq_hash qtd);

#endif
