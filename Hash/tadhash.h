#ifndef TADHASH_H
#define TADHASH_H

#include "../InvertedIndex/invertedIndex.h" 
#include "../LinkedList/linkedList.h"

#define M 100
#define N 100
#define TAMALFABETO 256

extern int comparacoes_hash;

typedef char TipoChave[N];
typedef unsigned TipoPesos[N][TAMALFABETO];

typedef struct TipoItem {
    Word palavra;
} TipoItem;

typedef unsigned int TipoIndice;
typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula {
    Word word;
    TipoApontador Prox;
} TipoCelula;

typedef struct TipoLista {
    TipoCelula *Primeiro, *Ultimo;
} TipoLista;

typedef TipoLista TipoDicionario[M];

// Funções
void FLVazia(TipoLista *Lista);
short Vazia(TipoLista Lista);
void Ins(Word x, TipoLista *Lista);
void Ret(TipoApontador p, TipoLista *Lista, Word *Item);
void GeraPesos(TipoPesos p);
TipoIndice h(TipoChave Chave, TipoPesos p);
void Inicializa(TipoDicionario T);
TipoApontador PesquisaHash(TipoChave Ch, TipoPesos p, TipoDicionario T, int idDoc);
void InsereHash(List lista, TipoPesos p, TipoDicionario T);
void Retira(List* lista, TipoPesos p, TipoDicionario T);
void Imp(TipoLista Lista);
void Imprime(TipoDicionario Tabela);
void LerPalavra(char *p, int Tam);

#endif
