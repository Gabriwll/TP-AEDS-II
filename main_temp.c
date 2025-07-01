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
#include <stdlib.h>
#include <string.h>

#include "./FileManager/read.h"    // Para getdocQuant e readFile
#include "./Hash/tadhash.h"        // Para Insere, TipoDicionario

extern int comparacoes_hash;
int main() {
    comparacoes_hash = 0; // Inicializa contador de comparações
    int docQuant = getdocQuant(); // lê quantidade de documentos
    List* lista;
    TipoDicionario tabela;
    TipoPesos pesos;

    printf("Quantidade de documentos: %d\n\n", docQuant);

    Inicializa(tabela);     // Inicializa tabela hash
    GeraPesos(pesos);       // Gera pesos aleatórios para hashing universal

    for (int i = 1; i <= docQuant; i++) {
        printf("Lendo documento %d...\n", i);
        lista = readFile(i); // lê lista encadeada com palavras do documento
        InsereHash(*lista, pesos, tabela); // insere lista na hash
 // insere lista na hash
        freeList(lista); // libera memória da lista
    }

    printf("\nTabela Hash Final:\n");
    Imprime(tabela); // imprime tabela hash/ espera usuário pressionar uma tecla antes de fechar
    printf("\nTotal de comparações na tabela hash: %d\n", comparacoes_hash);
    
    getchar();
    return 0; // espera usuário pressionar uma tecla antes de fechar
}
