#ifndef INVERTED_INDEX_PAT_H
#define INVERTED_INDEX_PAT_H

#define MAX_DOCS 5


typedef struct {
    int idDoc;   ///< Número do documento
    int qtde;    ///< Quantidade de ocorrências da palavra
} PatInvertedIndex;


typedef struct {
    char word[50];                     ///< Palavra
    PatInvertedIndex searchTerm[MAX_DOCS]; ///< Vetor com a ocorrência da palavra por documento
} PatWord;


void inicializaWord(PatWord *w, const char *palavra);
void incrementaOcorrencia(PatWord *w, int idDoc);
void imprimeWord(const PatWord *w);

#endif

