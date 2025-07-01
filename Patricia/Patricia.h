/**
 * @file Patricia.h
 * @brief Definições para a estrutura de dados Árvore Patricia
 */

#ifndef PATRICIA_H
#define PATRICIA_H

#include <stdlib.h> 
#include <stdio.h>
#include <sys/time.h>
#include "../InvertedIndex/InvertedIndexPat.h"

#define M 100

extern int comparacoes_patricia; //pode ser usada em outros arquivos

typedef unsigned char *ChaveTipo;

typedef enum {
  Interno,  ///< Nó interno (de decisão)
  Externo   ///< Nó externo (folha)
} TipoNo;

typedef struct PatNo* Arvore;

typedef struct PatNo {
  TipoNo nt; ///< Tipo do nó (Interno/Externo)
  
  union {
    struct {
      int indice;     ///< Índice para comparação
      char caractere; ///< Caractere para comparação
      Arvore Esq;     ///< Subárvore esquerda
      Arvore Dir;     ///< Subárvore direita
    } NInterno;       ///< Estrutura para nó interno
    
     PatWord termo;       ///< Palavra e índice invertido
  } NO;                ///< União dos tipos de nó
} PatNo;

Arvore CriaNoExt(ChaveTipo k, Arvore *p, int idDoc);
Arvore CriaNoInt(Arvore *Esq, Arvore *Dir, int i, char c);
Arvore Pesquisa(ChaveTipo k, Arvore *t);
Arvore InsereEntre(char *k, Arvore *t, short i, char diferente, int idDoc);
Arvore Insere(char *k, Arvore *t, int idDoc, int *qtd_pala);
void imprime(Arvore t);
void ordena(Arvore t);

#endif