#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "../Patricia/Patricia.h"
#include "Relevancia.h"

int main() {
    setlocale(LC_ALL, "Portuguese");

    Arvore raiz = NULL;
    W pesos;
    qtd_pala_arq qtd;
    relevancia rel;
    int qtd_palavras_doc[TAM] = {0};

    iniciar_W(&pesos);
    iniciar_qtd_pala_arq(&qtd);

    // Documentos simulados com palavras diferentes para dar relevância real
    char *doc_palavras[TAM][3] = {
        {"maçã", "banana", "uva"},     // Doc 1
        {"maçã", "pera", "goiaba"},    // Doc 2
        {"banana", "caju", "goiaba"},  // Doc 3
        {"uva", "laranja", "manga"},   // Doc 4
        {"melão", "mamão", "maçã"}     // Doc 5
    };

    // Insere todas as palavras em todos os documentos
    for (int doc = 0; doc < TAM; doc++) {
        for (int j = 0; j < 3; j++) {
            raiz = Insere(doc_palavras[doc][j], &raiz, doc + 1, &qtd_palavras_doc[doc]);
        }
        inserir_qtd_pala_arq(&qtd, doc, qtd_palavras_doc[doc]);
    }

    // Termos buscados
    char *termos[] = {"maçã", "goiaba"};

    // Calcula o peso de cada termo nos documentos
    for (int i = 0; i < 2; i++) {
        inserir_peso(&rel, i, raiz, termos[i], &pesos);
        printf("Inserido peso para termo '%s'\n", termos[i]);
    }

    // Preenche relevância com base nos pesos e quantidade de termos distintos
    preencher_relevancia(&rel, pesos, qtd);

    // Mostra pesos finais
    printf("DEBUG - Vetor de pesos finais:\n");
    for (int i = 0; i < TAM; i++) {
        printf("rel.re[%d] = %.5f\n", i, rel.re[i]);
    }

    // Exibe relevância por documento
    printf("\nRelevâncias:\n");
    for (int i = 0; i < TAM; i++) {
        printf("Doc %d: %.5f\n", i + 1, rel.re[i]);
    }

    return 0;
}
