#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../Relevancia/Relevancia.h"
#include "../InvertedIndex/invertedIndexPat.h"

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
//  * @brief Obtém a frequência de uma palavra em um arquivo específico
 * @param t Ponteiro para a árvore Patricia
 * @param palavra Palavra a ser pesquisada
 * @param indice_arq Índice do arquivo (1 a TAM)
 * @return Número de ocorrências da palavra no arquivo
 */
int repeticao_pala_arq(Arvore t, char *palavra, int indice_arq) {
    // Verificação de segurança
    if (t == NULL || palavra == NULL || indice_arq < 1 || indice_arq > MAX_DOCS) {
        return 0;
    }
    // Pesquisa a palavra na árvore
    Arvore noEncontrado = Pesquisa(palavra, &t);
    
    if (noEncontrado != NULL) {
        // Acessa o termo
        PatWord *termo = &(noEncontrado->NO.termo);
        // Verifica o documento específico
        if (termo->searchTerm[indice_arq - 1].idDoc == indice_arq) {
            return termo->searchTerm[indice_arq - 1].qtde;
        }
    }
    return 0;
}

/**
 * @brief Calcula em quantos arquivos a palavra aparece
 * @param t Ponteiro para a árvore Patricia
 * @param palavra Palavra a ser pesquisada
 * @return Número de arquivos que contêm a palavra
 */
int repeticao_pala_total(Arvore t, char *palavra) {
    if (t == NULL || palavra == NULL) return 0;
    Arvore noEncontrado = Pesquisa(palavra, &t);
    if (noEncontrado == NULL) return 0;
    int cont = 0;
    PatWord *termo = &(noEncontrado->NO.termo);
    for (int j = 0; j < MAX_DOCS; j++) {
        if (termo->searchTerm[j].qtde > 0) {
            cont++;
        }
    }
    return cont;
}

/**
 * @brief Calcula o peso (Wij) de uma palavra em um arquivo
 * @param t Ponteiro para a árvore Patricia
 * @param palavra Palavra a ser processada
 * @param indice_arq Índice do arquivo (1 a MAX_DOCS)
 * @return Valor do peso calculado
 */
double peso_W(Arvore t, char *palavra, int indice_arq) {
    printf("indice_arq = %d\n", indice_arq);
    int f = repeticao_pala_arq(t, palavra, indice_arq);
    int d = repeticao_pala_total(t, palavra);
    double W = 0;
    if(f != 0 && d != 0)
        W = f * log2((double)MAX_DOCS / d);
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