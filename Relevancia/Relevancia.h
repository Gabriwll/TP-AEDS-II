/**
 * @file relevancia.h
 * @brief Definições para cálculo de relevância de palavras
 */

#ifndef RELEVANCIA_H
#define RELEVANCIA_H

#include "../Patricia/Patricia.h"

/**
 * @def TAM
 * @brief Quantidade máxima de arquivos/documents a serem processados
 */
#define TAM 5

/**
 * @struct relevancia
 * @brief Armazena os valores de relevância para cada arquivo
 */
typedef struct relevancia {
    double re[TAM]; ///< Vetor de valores de relevância por arquivo
} relevancia;

/**
 * @struct qtd_pala_arq
 * @brief Armazena a quantidade de palavras por arquivo
 */
typedef struct qtd_pala_arq {
    int v_qtd[TAM]; ///< Vetor com quantidade de palavras por arquivo
} qtd_pala_arq;

/**
 * @struct W
 * @brief Armazena os pesos das palavras
 */
typedef struct W {
    double v_W[TAM]; ///< Vetor de pesos por arquivo
} W;

/**
 * @brief Inicializa a estrutura de contagem de palavras por arquivo
 * @param qtd Ponteiro para a estrutura a ser inicializada
 */
void iniciar_qtd_pala_arq(qtd_pala_arq *qtd);

/**
 * @brief Insere o peso de uma palavra em um arquivo específico
 * @param rel Ponteiro para a estrutura de relevância
 * @param indice_arq Índice do arquivo (0 a TAM-1)
 * @param t Ponteiro para a árvore Patricia
 * @param palavra Palavra a ser processada
 * @param p_w Ponteiro para a estrutura de pesos
 */
void inserir_peso(relevancia *rel, int indice_arq, Arvore t, char *palavra, W *p_w);

/**
 * @brief Insere a quantidade total de palavras de um arquivo
 * @param qtd Ponteiro para a estrutura de contagem
 * @param qtd_pala Quantidade total de palavras no arquivo
 * @param indice_arq Índice do arquivo (0 a TAM-1)
 */
void inserir_qtd_pala_arq(qtd_pala_arq *qtd, int qtd_pala, int indice_arq);

/**
 * @brief Obtém a frequência de uma palavra em um arquivo específico
 * @param t Ponteiro para a árvore Patricia
 * @param palavra Palavra a ser pesquisada
 * @param indice_arq Índice do arquivo (0 a TAM-1)
 * @return Número de ocorrências da palavra no arquivo
 */
int repeticao_pala_arq(Arvore t, char *palavra, int indice_arq); //fij

/**
 * @brief Obtém a frequência total de uma palavra em todos os arquivos
 * @param t Ponteiro para a árvore Patricia
 * @param palavra Palavra a ser pesquisada
 * @return Número total de ocorrências da palavra
 */
int repeticao_pala_total(Arvore t, char *palavra); //dj

/**
 * @brief Calcula o peso de uma palavra em um arquivo específico
 * @param t Ponteiro para a árvore Patricia
 * @param palavra Palavra a ser processada
 * @param indice_arq Índice do arquivo (0 a TAM-1)
 * @return Valor do peso calculado (Wij)
 */
double peso_W(Arvore t, char *palavra, int indice_arq); //Wij

/**
 * @brief Inicializa a estrutura de pesos
 * @param w Ponteiro para a estrutura de pesos a ser inicializada
 */
void iniciar_W(W *w);

/**
 * @brief Preenche a estrutura de relevância com base nos pesos e contagens
 * @param rel Ponteiro para a estrutura de relevância a ser preenchida
 * @param w Estrutura com os pesos calculados
 * @param qtd Estrutura com as contagens de palavras
 */
void preencher_relevancia(relevancia *rel, W w, qtd_pala_arq qtd);

/**
 * @brief Limpa o buffer de entrada
 */
void limparBuffer();

#endif