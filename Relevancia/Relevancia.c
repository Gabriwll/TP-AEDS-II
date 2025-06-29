/**
 * @file relevancia.c
 * @brief Implementação das funções para cálculo de relevância de palavras
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../Relevancia/Relevancia.h"

/**
 * @brief Limpa o buffer de entrada do teclado
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

/**
 * @brief Inicializa a estrutura de contagem de palavras por arquivo com zeros
 * @param qtd Ponteiro para a estrutura qtd_pala_arq a ser inicializada
 */
void iniciar_qtd_pala_arq(qtd_pala_arq *qtd) {
    int i;
    for(i = 0; i < TAM; i++) {
        qtd->v_qtd[i] = 0;
    }
}

/**
 * @brief Calcula e insere os pesos de uma palavra para todos os arquivos
 * @param rel Ponteiro para a estrutura de relevância
 * @param indice_arq Índice do arquivo atual (1 a TAM)
 * @param t Ponteiro para a árvore Patricia
 * @param palavra Palavra a ser processada
 * @param p_w Ponteiro para a estrutura de pesos W
 */
void inserir_peso(relevancia *rel, int indice_arq, Arvore t, char *palavra, W *p_w) {
    double R;
    int i;
    for(i = 0; i < TAM; i++) {
        p_w->v_W[i] += peso_W(t, palavra, i+1);
        printf("total W%d = %f\n\n", i+1, p_w->v_W[i]);
    }
    return;
}

/**
 * @brief Armazena a quantidade total de palavras de um arquivo
 * @param qtd Ponteiro para a estrutura de contagem
 * @param indice_arq Índice do arquivo (0 a TAM-1)
 * @param qtd_pala Quantidade total de palavras no arquivo
 */
void inserir_qtd_pala_arq(qtd_pala_arq *qtd, int indice_arq, int qtd_pala) {
    qtd->v_qtd[indice_arq] = qtd_pala;
}

/**
 * @brief Obtém a frequência de uma palavra em um arquivo específico
 * @param t Ponteiro para a árvore Patricia
 * @param palavra Palavra a ser pesquisada
 * @param indice_arq Índice do arquivo (1 a TAM)
 * @return Número de ocorrências da palavra no arquivo
 */
int repeticao_pala_arq(Arvore t, char *palavra, int indice_arq) {
    Arvore i;
    int j;
    i = Pesquisa(palavra, &t);
    if(i != NULL) {
        for(j = 0; j < M; j++) {
            if(i->V[j].arquivo == indice_arq) {
                printf("repeticao_pala_arq = %d\n", i->V[j].repeticao);
                return i->V[j].repeticao;
            }
        }
    }
    printf("repeticao_pala_arq = 0\n");
    return 0;
}

/**
 * @brief Calcula em quantos arquivos a palavra aparece
 * @param t Ponteiro para a árvore Patricia
 * @param palavra Palavra a ser pesquisada
 * @return Número de arquivos que contêm a palavra
 */
int repeticao_pala_total(Arvore t, char *palavra) {
    Arvore i;
    int cont = 0, j;
    i = Pesquisa(palavra, &t);
    if(i != NULL) {
        for(j = 0; j < TAM; j++) {
            if(i->V[j].arquivo != 0)
                cont++;
        }
    }
    printf("quant_de_arq_tem_pala = %d\n", cont);
    return cont;
}

/**
 * @brief Calcula o peso (Wij) de uma palavra em um arquivo
 * @param t Ponteiro para a árvore Patricia
 * @param palavra Palavra a ser processada
 * @param indice_arq Índice do arquivo (1 a TAM)
 * @return Valor do peso calculado
 */
double peso_W(Arvore t, char *palavra, int indice_arq) {
    printf("indice_arq = %d\n", indice_arq);
    int f = repeticao_pala_arq(t, palavra, indice_arq);
    int d = repeticao_pala_total(t, palavra);
    double W = 0;
    if(f != 0 && d != 0)
        W = f * (log2(TAM)/d);
    printf("W = %f\n", W);
    return W;
}

/**
 * @brief Inicializa a estrutura de pesos com zeros
 * @param w Ponteiro para a estrutura W a ser inicializada
 */
void iniciar_W(W *w) {
    int i;
    for(i = 0; i < TAM; i++) {
        w->v_W[i] = 0;
    }
}

/**
 * @brief Calcula os valores de relevância para cada arquivo
 * @param rel Ponteiro para a estrutura de relevância a ser preenchida
 * @param w Estrutura com os pesos calculados
 * @param qtd Estrutura com as contagens de palavras por arquivo
 */
void preencher_relevancia(relevancia *rel, W w, qtd_pala_arq qtd) {
    int i;
    for(i = 0; i < TAM; i++) {
        if(qtd.v_qtd[i] != 0)
            rel->re[i] = (1.0/qtd.v_qtd[i]) * w.v_W[i];
        else
            rel->re[i] = 0;
    }
}