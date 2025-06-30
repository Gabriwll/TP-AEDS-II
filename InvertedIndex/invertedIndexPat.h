#ifndef INVERTED_INDEX_PAT_H
#define INVERTED_INDEX_PAT_H

#define MAX_DOCS 5

/**
 * @struct InvertedIndex
 * @brief Representa a frequência de uma palavra em um documento.
 */
typedef struct {
    int idDoc;   ///< Número do documento
    int qtde;    ///< Quantidade de ocorrências da palavra
} InvertedIndex;

/**
 * @struct Word
 * @brief Representa uma palavra e seu índice invertido.
 */
typedef struct {
    char word[50];                     ///< Palavra
    InvertedIndex searchTerm[MAX_DOCS]; ///< Vetor com a ocorrência da palavra por documento
} Word;

/**
 * @brief Inicializa o índice invertido para uma nova palavra
 * @param w Ponteiro para a estrutura Word
 * @param palavra Palavra a ser armazenada
 */
void inicializaWord(Word *w, const char *palavra);

/**
 * @brief Incrementa a contagem de ocorrências de uma palavra em um documento
 * @param w Ponteiro para a estrutura Word
 * @param idDoc Identificador do documento
 */
void incrementaOcorrencia(Word *w, int idDoc);

/**
 * @brief Imprime o índice invertido de uma palavra
 * @param w Ponteiro para a estrutura Word
 */
void imprimeWord(const Word *w);

#endif
