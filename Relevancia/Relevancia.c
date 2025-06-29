/**
 * @file Relevancia.c
 * @brief Implementa o cálculo da relevância de documentos com base no modelo TF-IDF.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Relevancia.h"

/**
 * @brief Limpa o buffer do teclado (stdin).
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

/**
 * @brief Inicializa o vetor de quantidades de palavras por documento com zeros.
 */
void iniciar_qtd_pala_arq(qtd_pala_arq *qtd) {
    for (int i = 0; i < TAM; i++) {
        qtd->v_qtd[i] = 0;
    }
}

/**
 * @brief Insere o peso de uma palavra em todos os documentos.
 */
void inserir_peso(relevancia *rel, int indice_arq, Arvore t, char *palavra, W *p_w) {
    for (int i = 0; i < TAM; i++) {
        p_w->v_W[i] += peso_W(t, palavra, i + 1);
    }
}

/**
 * @brief Define o número de termos distintos no documento.
 */
void inserir_qtd_pala_arq(qtd_pala_arq *qtd, int indice_arq, int qtd_pala) {
    qtd->v_qtd[indice_arq] = qtd_pala;
}

/**
 * @brief Retorna o número de ocorrências de uma palavra em um documento (f_{j,i}).
 */

int repeticao_pala_arq(Arvore t, char *palavra, int indice_arq) {
    Arvore i = Pesquisa(palavra, &t);
    if (i != NULL) {
        for (int j = 0; j < M; j++) {
            if (i->V[j].arquivo == indice_arq) {
                return i->V[j].repeticao;
            }
        }
    }
    return 0;
}

/**
 * @brief Retorna o número de documentos que contêm a palavra (d_j).
 */
int repeticao_pala_total(Arvore t, char *palavra) {
    Arvore i = Pesquisa(palavra, &t);
    int cont = 0;
    if (i != NULL) {
        for (int j = 0; j < TAM; j++) {
            if (i->V[j].arquivo != 0)
                cont++;
        }
    }
    return cont;
}

/**
 * @brief Calcula o peso W do termo para o documento usando TF-IDF com log base 2.
 * @return Peso W.
 */
double peso_W(Arvore t, char *palavra, int indice_arq) {
    int f = repeticao_pala_arq(t, palavra, indice_arq);
    int d = repeticao_pala_total(t, palavra);
    double W = 0;
    

    if (f != 0 && d != 0)
        W = f * (log2((double)TAM / d));  ///< log base 2 conforme enunciado
    printf("DEBUG: %s no doc %d -> f=%d, d=%d, W=%.3f\n", palavra, indice_arq, f, d, W);    
    return W;
}

/**
 * @brief Inicializa o vetor de pesos com zero.
 */
void iniciar_W(W *w) {
    for (int i = 0; i < TAM; i++) {
        w->v_W[i] = 0;
    }
}

/**
 * @brief Preenche o vetor de relevâncias de cada documento.
 * @details Aplica a fórmula: r(i) = (1 / n_i) * soma(w_{j,i})
 */
void preencher_relevancia(relevancia *rel, W w, qtd_pala_arq qtd) {
    for (int i = 0; i < TAM; i++) {
        if (qtd.v_qtd[i] != 0)
            rel->re[i] = (1.0 / qtd.v_qtd[i]) * w.v_W[i];
        else
            rel->re[i] = 0;
    }
}
