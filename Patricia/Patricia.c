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
/**
 * @file Patricia.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Patricia/Patricia.h"

/**
 * @brief Verifica se um nó é externo (folha)
 * 
 * @param p Ponteiro para o nó Patricia a ser verificado
 * @return short Retorna 1 se o nó é externo, 0 caso contrário
 */
short EExterno(Arvore p) {
    return (p->nt == Externo);
}

/**
 * @brief Cria um novo nó interno
 * 
 * @param Esq Ponteiro para a subárvore esquerda
 * @param Dir Ponteiro para a subárvore direita
 * @param i Índice para comparação
 * @param c Caractere para comparação no índice i
 * @return Arvore Retorna o novo nó interno criado
 */
Arvore CriaNoInt(Arvore *Esq, Arvore *Dir, int i, char c) {
    Arvore p;
    p = (Arvore)malloc(sizeof(PatNo));
    p->nt = Interno;
    p->NO.NInterno.Esq = *Esq;
    p->NO.NInterno.Dir = *Dir;
    p->NO.NInterno.indice = i;
    p->NO.NInterno.caractere = c;
    return p;
} 

/**
 * @brief Cria um novo nó externo (folha)
 * 
 * @param k Chave a ser armazenada no nó
 * @param p Ponteiro para o nó a ser criado
 * @param idDoc Número do arquivo onde a chave foi encontrada
 * @return Arvore Retorna o novo nó externo criado
 */
Arvore CriaNoExt(ChaveTipo k, Arvore *p, int idDoc) {
    *p = (Arvore)malloc(sizeof(PatNo));
    (*p)->nt = Externo;
    inicializaWord(&(*p)->NO.termo, (char*)k);
    incrementaOcorrencia(&(*p)->NO.termo, idDoc);
    return *p;
}  


int comparacoes_patricia = 0;  // Contador global de comparações para análise de desempenho

/**
 * @brief Pesquisa uma chave na árvore Patricia
 * 
 * @param k Chave a ser pesquisada
 * @param t Ponteiro para a raiz da árvore
 * @return Arvore Retorna o nó encontrado ou NULL se não existir
 */
Arvore Pesquisa(ChaveTipo k, Arvore *t) {
    if (t == NULL) {
        return NULL;
    }
    if ((*t)->nt == Externo) {
        comparacoes_patricia++; // comparação final da chave
        if (strcmp((char *)k, (*t)->NO.termo.word) == 0)
            return (*t);
        else
            return NULL;
    }
    comparacoes_patricia++;  // comparação de índice na árvore
    if (k[(*t)->NO.NInterno.indice] < (*t)->NO.NInterno.caractere)
        Pesquisa(k, &(*t)->NO.NInterno.Esq);
    else
        Pesquisa(k, &(*t)->NO.NInterno.Dir);
}

/**
 * @brief Insere um novo nó em uma posição intermediária da árvore
 * 
 * @param k Chave a ser inserida
 * @param t Ponteiro para a raiz da subárvore onde será feita a inserção
 * @param i Índice de comparação
 * @param diferente Caractere diferente que determina a divisão
 * @param N_arquivo Número do arquivo onde a chave foi encontrada
 * @return Arvore Retorna a nova árvore com o nó inserido
 */
Arvore InsereEntre(char *k, Arvore *t, short i, char diferente, int idDoc) {
    Arvore p;
    CriaNoExt((ChaveTipo)k, &p, idDoc);

    if (EExterno(*t)) {
        comparacoes_patricia++; // comparação de igualdade de chaves
        if(strcmp((*t)->NO.termo.word, k) < 0) {
            return (CriaNoInt(t, &p, i, diferente));
        } else if(strcmp((*t)->NO.termo.word, k) > 0) {
            return(CriaNoInt(&p, t, i, diferente));
        }
        return NULL;
    } else if(i < (*t)->NO.NInterno.indice) {
        comparacoes_patricia++; // comparação de índice na árvore
        CriaNoExt(k, &p, idDoc);
        comparacoes_patricia++; // comparação de caractere na árvore
        if(k[i] < diferente) {
            return (CriaNoInt(&p, t, i, diferente));
        } else {
            return(CriaNoInt(t, &p, i, diferente));
        }
    } else {
        comparacoes_patricia++; // comparação de índice na árvore
        if (k[(*t)->NO.NInterno.indice] < (*t)->NO.NInterno.caractere)
            (*t)->NO.NInterno.Esq = InsereEntre(k, &(*t)->NO.NInterno.Esq, i, diferente, idDoc);
        else
            (*t)->NO.NInterno.Dir = InsereEntre(k, &(*t)->NO.NInterno.Dir, i, diferente, idDoc);
        return (*t);
    }
}

/**
 * @brief Insere uma nova chave na árvore Patricia
 * 
 * @param k Chave a ser inserida
 * @param t Ponteiro para a raiz da árvore
 * @param idDoc Número do arquivo onde a chave foi encontrada
 * @param qtd_pala Ponteiro para contador de palavras (será incrementado se nova palavra for inserida)
 * @return Arvore Retorna a árvore atualizada
 */
Arvore Insere(char *k, Arvore *t, int idDoc, int *qtd_pala) {
    Arvore p;
    int i, j;
    char caux, cdif;

    if ((*t) == NULL) {
        return (CriaNoExt(k, t, idDoc));
    } else {
        p = (*t);
        while (!EExterno(p)) {
            comparacoes_patricia++; // comparação de índice na árvore
            caux = k[p->NO.NInterno.indice];
            if (caux < p->NO.NInterno.caractere)
                p = p->NO.NInterno.Esq;
            else if(caux >= p->NO.NInterno.caractere) 
                p = p->NO.NInterno.Dir;
            else
                p = p->NO.NInterno.Esq;
        }
        
        comparacoes_patricia++; // comparação de igualdade de chaves
        if(strcmp(p->NO.termo.word, k) == 0) {
            incrementaOcorrencia(&p->NO.termo, idDoc);
            return (*t);
        } else {
            int tam = (strlen(k) < strlen(p->NO.termo.word)) ? strlen(k) : strlen(p->NO.termo.word);
            for(i = 0; i <= tam; i++) {
                comparacoes_patricia++; // comparação de caracteres
                if(k[i] != p->NO.termo.word[i]) {
                    cdif = (k[i] < p->NO.termo.word[i]) ? p->NO.termo.word[i] : k[i];
                    break;
                }
            }
            (*qtd_pala)++;
            return InsereEntre(k, t, i, cdif, idDoc);
        }
    }
}

/**
 * @brief Imprime as informações de um nó folha
 * 
 * @param t Ponteiro para o nó a ser impresso
 */
void imprime(Arvore t) {
    if (t == NULL) return;
    if (t->nt == Externo) {
        imprimeWord(&t->NO.termo);
    }
}

/**
 * @brief Percorre a árvore em ordem e imprime os nós folha
 * 
 * @param t Ponteiro para a raiz da árvore
 */
void ordena(Arvore t) {
    if (t == NULL) {
        return;
    }

    if (t->nt == Interno) {
        ordena(t->NO.NInterno.Esq);
    }

    imprime(t);

    if (t->nt == Interno) {
        ordena(t->NO.NInterno.Dir);
    }
}