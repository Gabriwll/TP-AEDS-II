/***************************************************
 * Universidade Federal de Viçosa - Campus Florestal
 * Disciplina: Algoritmos e Estruturas de Dados II
 * Período: 2025/1
 * Trabalho Prático I - Índice Invertido com PATRICIA e HASH
 *
 * Integrantes:
 * - Helom Felipe Marques Alves - 5892
 * - Maria Eduarda Oliveira - 5365
 * - Gabriel Luiz Magalhães Amorim - 5560
 * - Raíssa Tayná Xavier dos Santos - 5790
 ***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>

// Patricia
#include "./Patricia/Patricia.h"
#include "./Relevancia/Relevancia.h"
#include "./InvertedIndex/InvertedIndexPat.h"
#include "./Patricia/trata_arquivo.h"

// Hash
#include "./FileManager/read.h"
#include "./Hash/tadhash.h"

#define comp 0.000001
#define MAX_DOCS 5
#define TAM MAX_DOCS

// ANSI cores
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define CYAN    "\033[1;36m"
#define YELLOW  "\033[1;33m"
#define WHITE   "\033[1;37m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"

Arvore arvore = NULL;
TipoDicionario tabela;
TipoPesos pesos;
qtd_pala_arq qtd;
relevancia rel;
W w;

int N_arquivos = 0;
extern int comparacoes_hash;
extern int comparacoes_patricia;

void limparTela() {
    system("cls"); // use system("clear"); para Linux/Mac
}

void cabecalho() {
    printf(CYAN "============================================\n" RESET);
    printf(WHITE "  TRABALHO PRATICO DE AEDS 2 - PATRICIA/HASH\n" RESET);
    printf(CYAN "============================================\n\n" RESET);
}

void pausa() {
    printf(YELLOW "\nPressione Enter para continuar..." RESET);
    getchar();
}

void mostrarQuantidadeArquivos() {
    N_arquivos = getdocQuant();
    if (N_arquivos > 0) {
        printf(GREEN "Quantidade de arquivos lida: %d\n" RESET, N_arquivos);
    } else {
        printf(RED "Erro ao ler quantidade de arquivos.\n" RESET);
    }
}


// Índice invertido com Patricia
void construirPatricia() {
    int docQuant = getdocQuant();
    FILE *TXT;
    char linha[100], *palavra, nomeArq[100];
    int qtd_pala = 0;

    iniciar_qtd_pala_arq(&qtd);
    iniciar_W(&w);
    memset(&rel, 0, sizeof(rel));

    for (int i = 1; i <= docQuant && i <= TAM; i++) {
        sprintf(nomeArq, "Files/In/arquivo%d.txt", i);
        TXT = fopen(nomeArq, "r");
        if (!TXT) {
            printf(RED "Erro ao abrir %s\n" RESET, nomeArq);
            continue;
        }

        while (fgets(linha, sizeof(linha), TXT)) {
            palavra = strtok(linha, " ");
            while (palavra) {
                palavra = minusculo(palavra);
                palavra = trata_N(palavra);
                palavra = trata_P(palavra);
                arvore = Insere(palavra, &arvore, i - 1, &qtd_pala);
                palavra = strtok(NULL, " ");
            }
        }
        fclose(TXT);
        inserir_qtd_pala_arq(&qtd, i - 1, qtd_pala);
        qtd_pala = 0;
    }
    printf(GREEN "Indice invertido com Patricia construido!\n" RESET);
}


// Imprime Patricia
void imprimirPatricia() {
    if (arvore == NULL) {
        printf(RED "Arvore Patricia vazia.\n" RESET);
        return;
    }
    printf(GREEN "Indice Invertido (Patricia):\n" RESET);
    ordena(arvore);
}

// Busca com TF-IDF (Patricia)
void buscaPatricia() {
    char texto[100];
    printf(YELLOW "Digite os termos de busca: " RESET);
    fgets(texto, sizeof(texto), stdin);
    texto[strcspn(texto, "\n")] = '\0';

    iniciar_W(&w);
    char *token = strtok(texto, " ");
    while (token) {
        inserir_peso(&rel, N_arquivos, arvore, token, &w);
        token = strtok(NULL, " ");
    }

    preencher_relevancia(&rel, w, qtd);

    double ordenado[TAM];
    for (int i = 0; i < TAM; i++) ordenado[i] = rel.re[i];

    for (int i = 1; i < TAM; i++) {
        double aux = ordenado[i];
        int j = i - 1;
        while (j >= 0 && ordenado[j] < aux) {
            ordenado[j + 1] = ordenado[j];
            j--;
        }
        ordenado[j + 1] = aux;
    }

    for (int k = 0; k < TAM; k++) {
        for (int d = 0; d < TAM; d++) {
            if (fabs(ordenado[k] - rel.re[d]) < comp && rel.re[d] > 0) {
                printf("arquivo%d.txt = %f\n", d + 1, rel.re[d]);
                break;
            }
        }
    }
}

// Índice invertido com Hash
void construirHash() {
    comparacoes_hash = 0;
    int docQuant = getdocQuant();
    List* lista;
    Inicializa(tabela);
    GeraPesos(pesos);

    for (int i = 1; i <= docQuant; i++) {
        lista = readFile(i);
        InsereHash(*lista, pesos, tabela);
        freeList(lista);
    }
}

void imprimirHash() {
    printf(GREEN "Imprimindo tabela hash:\n" RESET);
    Imprime(tabela);
}

// Comparar desempenho
void compararDesempenho() {
    printf(YELLOW "Comparacoes realizadas:\n" RESET);
    printf(" - Patricia: %d comparacoes\n", comparacoes_patricia);
    printf(" - Hash:     %d comparacoes\n", comparacoes_hash);
}

// MAIN COM MENU COLORIDO
int main() {
    int opcao;
    do {
        limparTela();
        cabecalho();

        printf(BLUE "1. Ler entrada.txt\n" RESET);
        printf(BLUE "2. Construir indice invertido (PATRICIA)\n" RESET);
        printf(BLUE "3. Imprimir indice invertido (PATRICIA)\n" RESET);
        printf(BLUE "4. Buscar termo na arvore PATRICIA (TF-IDF)\n" RESET);
        printf(BLUE "5. Construir indice com HASH\n" RESET);
        printf(BLUE "6. Imprimir indice invertido (HASH)\n" RESET);
        printf(BLUE "7. Comparar desempenho PATRICIA x HASH\n" RESET);
        printf(BLUE "8. Sair\n\n" RESET);

        printf(CYAN "Escolha uma opcao: " RESET);
        scanf("%d", &opcao);
        getchar(); // limpar buffer

        switch (opcao) {
            case 1: mostrarQuantidadeArquivos(); break;
            case 2: construirPatricia(); break;
            case 3: imprimirPatricia(); break;
            case 4: buscaPatricia(); break;
            case 5: construirHash(); break;
            case 6: imprimirHash(); break;
            case 7: compararDesempenho(); break;
            case 8: printf(GREEN "Encerrando...\n" RESET); break;
            default: printf(RED "Opcao invalida.\n" RESET); break;
        }

        if (opcao != 8) pausa();
    } while (opcao != 8);

    return 0;
}
