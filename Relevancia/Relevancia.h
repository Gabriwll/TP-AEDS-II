#ifndef RELEVANCIA_H
#define RELEVANCIA_H

#include "PATRICIA.h"

#define TAM 5 //quantidade de arquivos


typedef struct relevancia{
    double re[TAM];
}relevancia;

typedef struct qtd_pala_arq{
    int v_qtd[TAM];
}qtd_pala_arq;

typedef struct W{
    double v_W[TAM];
}W;

void iniciar_qtd_pala_arq(qtd_pala_arq *qtd);
void inserir_peso(relevancia *rel, int indice_arq, Arvore t, char *palavra, W *p_w);
void inserir_qtd_pala_arq(qtd_pala_arq *qtd, int qtd_pala, int indice_arq);
int repeticao_pala_arq(Arvore t, char *, int); 
int repeticao_pala_total(Arvore t, char *);
double peso_W(Arvore t, char *, int); 
void iniciar_W(W *w);
void preencher_relevancia(relevancia *rel, W w, qtd_pala_arq qtd);
void limparBuffer();

#endif