#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Patricia.h"

int main() {
    Arvore raiz = NULL;
    int qtd_palavras = 0;

    // Palavras de teste simulando entradas de arquivos
    char *palavrasArquivo1[] = {"banana", "abacaxi", "uva", "banana", "goiaba"};
    char *palavrasArquivo2[] = {"uva", "banana", "kiwi", "abacate", "abacaxi"};

    int tam1 = sizeof(palavrasArquivo1) / sizeof(palavrasArquivo1[0]);
    int tam2 = sizeof(palavrasArquivo2) / sizeof(palavrasArquivo2[0]);

    // Inserção das palavras do arquivo 1 (N_arquivo = 1)
    for (int i = 0; i < tam1; i++) {
        raiz = Insere(palavrasArquivo1[i], &raiz, 1, &qtd_palavras);
    }

    // Inserção das palavras do arquivo 2 (N_arquivo = 2)
    for (int i = 0; i < tam2; i++) {
        raiz = Insere(palavrasArquivo2[i], &raiz, 2, &qtd_palavras);
    }

    // Impressão em ordem
    printf("\n=== Árvore Patricia (em ordem) ===\n");
    ordena(raiz);

    // Pesquisa de algumas palavras
    printf("\n=== Pesquisa de palavras ===\n");
    char *buscas[] = {"banana", "abacaxi", "morango"};
    for (int i = 0; i < 3; i++) {
        printf("Pesquisando: %s\n", buscas[i]);
        Arvore resultado = Pesquisa(buscas[i], &raiz);
        if (resultado != NULL) {
            imprime(resultado);
        } else {
            printf("Palavra não encontrada!\n");
        }
    }

    printf("\nTotal de palavras distintas inseridas: %d\n", qtd_palavras);
    return 0;
}
