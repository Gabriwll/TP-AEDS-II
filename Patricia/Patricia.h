/**
 * @file Patricia.h
 * @brief Definições para a estrutura de dados Árvore Patricia
 */

#ifndef PATRICIA_H
#define PATRICIA_H

#include <stdlib.h> 
#include <stdio.h>
#include <sys/time.h>

/**
 * @def M
 * @brief Número máximo de arquivos que podem ser indexados
 */
#define M 5

/**
 * @typedef boolean
 * @brief Tipo booleano (short int)
 */
typedef short boolean;

/**
 * @typedef ChaveTipo 
 * @brief Tipo das chaves armazenadas na árvore (unsigned char*)
 */
typedef unsigned char *ChaveTipo;

/**
 * @typedef IndexAmp
 * @brief Tipo para índice ampliado (unsigned char)
 */
typedef unsigned char IndexAmp;

/**
 * @typedef Dib
 * @brief Tipo para dígito binário (unsigned char)
 */
typedef unsigned char Dib;

/**
 * @enum TipoNo
 * @brief Enumeração dos tipos de nó da árvore
 */
typedef enum {
  Interno,  ///< Nó interno (de decisão)
  Externo   ///< Nó externo (folha)
} TipoNo;

/**
 * @struct id
 * @brief Estrutura para armazenar informações de documentos
 */
typedef struct id {
  int repeticao; ///< Número de ocorrências da palavra no documento
  int arquivo;   ///< Identificador do documento
} id;

/**
 * @typedef Arvore
 * @brief Tipo ponteiro para nó da árvore Patricia
 */
typedef struct PatNo* Arvore;

/**
 * @struct PatNo
 * @brief Estrutura de nó da árvore Patricia
 */
typedef struct PatNo {
  TipoNo nt; ///< Tipo do nó (Interno/Externo)
  
  union {
    struct {
      int indice;     ///< Índice para comparação
      char caractere; ///< Caractere para comparação
      Arvore Esq;     ///< Subárvore esquerda
      Arvore Dir;     ///< Subárvore direita
    } NInterno;       ///< Estrutura para nó interno
    
    char folha[50];    ///< Chave armazenada em nó externo
  } NO;                ///< União dos tipos de nó

  id V[M];             ///< Vetor de informações por documento
} PatNo;

/* Protótipos de funções */

/**
 * @brief Obtém o caractere em uma posição específica da chave
 * @param i Posição do caractere
 * @param k Ponteiro para a chave
 * @return Caractere na posição i
 */
char Caractere(short i, char* k);

/**
 * @brief Compara dois caracteres
 * @param a Primeiro caractere
 * @param b Segundo caractere
 * @return Verdadeiro se a <= b, falso caso contrário
 */
boolean MenorIgual(char a, char b);

/**
 * @brief Cria um novo nó externo (folha)
 * @param k Chave a ser armazenada
 * @param p Ponteiro para o novo nó
 * @param N_arquivo Número do arquivo associado
 * @return Ponteiro para o nó criado
 */
Arvore CriaNoExt(ChaveTipo k, Arvore *p, int N_arquivo);

/**
 * @brief Cria um novo nó interno
 * @param Esq Ponteiro para subárvore esquerda
 * @param Dir Ponteiro para subárvore direita
 * @param i Índice para comparação
 * @param c Caractere para comparação
 * @return Ponteiro para o nó interno criado
 */
Arvore CriaNoInt(Arvore *Esq, Arvore *Dir, int i, char c);

/**
 * @brief Pesquisa uma chave na árvore
 * @param k Chave a ser pesquisada
 * @param t Ponteiro para a raiz da árvore
 * @return Ponteiro para o nó encontrado ou NULL
 */
Arvore Pesquisa(ChaveTipo k, Arvore *t);

/**
 * @brief Insere um novo nó em posição intermediária
 * @param k Chave a ser inserida
 * @param t Ponteiro para a raiz da subárvore
 * @param i Índice para comparação
 * @param diferente Caractere diferente que define a divisão
 * @param N_arquivo Número do arquivo associado
 * @return Ponteiro para a árvore atualizada
 */
Arvore InsereEntre(char *k, Arvore *t, short i, char diferente, int N_arquivo);

/**
 * @brief Insere uma nova chave na árvore
 * @param k Chave a ser inserida
 * @param t Ponteiro para a raiz da árvore
 * @param N_arquivo Número do arquivo associado
 * @param qtd_pala Ponteiro para contador de palavras (atualizado se nova palavra)
 * @return Ponteiro para a árvore atualizada
 */
Arvore Insere(char *k, Arvore *t, int N_arquivo, int *qtd_pala);

/**
 * @brief Imprime as informações de um nó folha
 * @param t Ponteiro para o nó a ser impresso
 */
void imprime(Arvore t);

/**
 * @brief Percorre a árvore em ordem imprimindo os nós folha
 * @param t Ponteiro para a raiz da árvore
 */
void ordena(Arvore t);

#endif