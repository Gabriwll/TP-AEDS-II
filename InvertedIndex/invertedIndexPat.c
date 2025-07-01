/***************************************************
 * Universidade Federal de Viçosa - Campus Florestal
 * Disciplina: Algoritmos e Estruturas de Dados II
 * Período: 2025/1
 * Trabalho Prático I - Índice Invertido com PATRICIA e HASH
 
 * Integrantes:
 * -Helom Felipe Marques Alves - 5892
 * -Maria Eduarda Oliveira - 5365
 * -Gabriel Luiz Magalhães Amorim - 5560 
 * -Raíssa Tayná Xavier dos Santos - 5790 

 ***************************************************/
#include <stdio.h>
#include <string.h>
#include "InvertedIndexPat.h"

void inicializaWord(PatWord *w, const char *palavra) {
    strcpy(w->word, palavra);
    for (int i = 0; i < MAX_DOCS; i++) {
        w->searchTerm[i].idDoc = i + 1;
        w->searchTerm[i].qtde = 0;
    }
}

void incrementaOcorrencia(PatWord *w, int idDoc) {
    if (idDoc >= 1 && idDoc <= MAX_DOCS) {
        w->searchTerm[idDoc - 1].qtde++;
    }
}

void imprimeWord(const PatWord *w) {
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
