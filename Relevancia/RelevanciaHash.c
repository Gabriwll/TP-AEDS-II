/**
 * @file relevanciaHash.c
 * @brief Implementacao do calculo de relevancia para estrutura de Hash
 */

#include "relevanciaHash.h"

void iniciar_qtd_pala_arq_hash(qtd_pala_arq_hash *qtd) {
    for (int i = 0; i < TAM; i++) qtd->v_qtd[i] = 0;
}

void iniciar_W_hash(WHash *w) {
    for (int i = 0; i < TAM; i++) w->v_W[i] = 0.0;
}

void inserir_qtd_pala_arq_hash(qtd_pala_arq_hash *qtd, int qtd_pala, int indice_arq) {
    qtd->v_qtd[indice_arq] = qtd_pala;
}

int repeticao_pala_arq_hash(TipoDicionario ht, TipoPesos p, char *palavra, int indice_arq) {
    TipoApontador ap = Pesquisa(palavra, p, ht, indice_arq);
    if (ap != NULL) {
        return ap->Prox->word.searchTerm.qtde;
    }
    return 0;
}

int repeticao_pala_total_hash(TipoDicionario ht,TipoPesos p, char *palavra) {
    int count = 0;
    for (int docId = 1; docId <= TAM; docId++) {
        TipoApontador ap = Pesquisa(palavra, p, ht, docId);
        if (ap != NULL) count++;
    }
    return count;
}

double peso_W_hash(TipoDicionario ht, TipoPesos p, char *palavra, int indice_arq) {
    int f = repeticao_pala_arq_hash(ht, p, palavra, indice_arq);
    int d = repeticao_pala_total_hash(ht, p, palavra);
    if (f == 0 || d == 0) return 0.0;
    return f * (log2(TAM) / d);
}

void inserir_peso_hash(relevanciaHash *rel, int indice_arq, TipoDicionario ht, TipoPesos p, char *palavra, WHash *p_w) {
    for (int i = 0; i < TAM; i++) {
        p_w->v_W[i] += peso_W_hash(ht, p, palavra, i + 1);
    }
}

void preencher_relevancia_hash(relevanciaHash *rel, WHash w, qtd_pala_arq_hash qtd) {
    for (int i = 0; i < TAM; i++) {
        if (qtd.v_qtd[i] != 0)
            rel->re[i] = (1.0 / qtd.v_qtd[i]) * w.v_W[i];
        else
            rel->re[i] = 0.0;
    }
}
