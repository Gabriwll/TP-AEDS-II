#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "./Patricia/Patricia.h"

// ANSI cores
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define CYAN    "\033[1;36m"
#define YELLOW  "\033[1;33m"
#define WHITE   "\033[1;37m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"

// Limite de documentos
#define MAX_DOCS 100


Arvore arvorePatricia = NULL;

void limparTela() {
    system("cls"); // Para Windows
    // system("clear"); // Para Linux/Unix
}

void cabecalho() {
    printf(CYAN "============================================\n" RESET);
    printf(WHITE  "     TRABALHO PRATICO DE AEDS 2    \n" RESET);
    printf(CYAN "============================================\n\n" RESET);
}

void pausa() {
    printf(YELLOW "\nPressione Enter para continuar..." RESET);
    getchar();
}

int main() {
    int opcao;
    do {
        limparTela();
        cabecalho();

        printf(RED "1. [NAO IMPLEMENTADO] Ler entrada.txt e carregar arquivos\n" RESET);
        printf(RED "2. [NAO IMPLEMENTADO] Construir indice invertido (PATRICIA)\n" RESET);
        printf(RED "3. [NAO IMPLEMENTADO] Imprimir indice invertido (PATRICIA)\n" RESET);
        printf(RED "4. [NAO IMPLEMENTADO] Buscar termo na arvore PATRICIA\n" RESET);
        printf(RED "5. [NAO IMPLEMENTADO] Construir indice com HASH\n" RESET);
        printf(RED "6. [NAO IMPLEMENTADO] Imprimir indice invertido (HASH)\n" RESET);
        printf(RED "7. [NAO IMPLEMENTADO] Realizar busca com TF-IDF\n" RESET);
        printf(RED "8. [NAO IMPLEMENTADO] Comparar desempenho PATRICIA x HASH\n" RESET);
        printf("9. Sair\n" RESET);

        printf(CYAN "\nEscolha uma opcao: " RESET);
        scanf("%d", &opcao);
        getchar(); // limpar buffer

        switch (opcao) {
            case 1:
                printf(RED "Funcao ainda nao implementada.\n" RESET);
                break;
            case 2:
                printf(RED "Funcao ainda nao implementada.\n" RESET);
                break;
            case 3:
                printf(RED "Funcao ainda nao implementada.\n" RESET);
                break;
            case 4:
                printf(RED "Funcao ainda nao implementada.\n" RESET);
                break;
            case 5:
            printf(RED "Funcao ainda nao implementada.\n" RESET);
                break;
            case 6:
            printf(RED "Funcao ainda nao implementada.\n" RESET);
                break;
            case 7:
            printf(RED "Funcao ainda nao implementada.\n" RESET);
                break;
            case 8:
                printf(RED "Funcao ainda nao implementada.\n" RESET);
                break;
            case 9:
                printf(GREEN "Encerrando...\n" RESET);
                break;
            default:
                printf(RED "Opcao invalida.\n" RESET);
                break;
        }

        if (opcao != 9) pausa();

    } while (opcao != 9);

    return 0;
}
