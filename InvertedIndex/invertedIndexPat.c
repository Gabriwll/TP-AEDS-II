#include <stdio.h>
#include <string.h>
#include "InvertedIndexPat.h"

void inicializaWord(Word *w, const char *palavra) {
    strcpy(w->word, palavra);
    for (int i = 0; i < MAX_DOCS; i++) {
        w->searchTerm[i].idDoc = i + 1;
        w->searchTerm[i].qtde = 0;
    }
}

void incrementaOcorrencia(Word *w, int idDoc) {
    if (idDoc >= 1 && idDoc <= MAX_DOCS) {
        w->searchTerm[idDoc - 1].qtde++;
    }
}

void imprimeWord(const Word *w) {
    printf("Palavra: %s\n", w->word);
    for (int i = 0; i < MAX_DOCS; i++) {
        if (w->searchTerm[i].qtde > 0) {
            printf("<%d, %d>\n",
                w->searchTerm[i].qtde,   
                w->searchTerm[i].idDoc);
        }
    }
    printf("---------------------------------------\n");
}
