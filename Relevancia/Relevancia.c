#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Relevancia.h"

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
} 

void iniciar_qtd_pala_arq(qtd_pala_arq *qtd){
    int i;
    for(i=0;i<TAM;i++){
        qtd->v_qtd[i] = 0;
    }
}

void inserir_peso(relevancia *rel, int indice_arq, Arvore t, char *palavra, W *p_w){
    double R;
    int i;
    for(i=0;i<TAM;i++){
        p_w->v_W[i] += peso_W(t,palavra,i+1);
        //printf("total W%d = %f\n\n",i+1,p_w->v_W[i]);
    }
    return;
}

void inserir_qtd_pala_arq(qtd_pala_arq *qtd, int indice_arq, int qtd_pala){
    qtd->v_qtd[indice_arq] = qtd_pala;
}

int repeticao_pala_arq(Arvore t, char *palavra, int indice_arq){ //fij
    Arvore i;
    int j;
    i = Pesquisa(palavra,&t);
    if(i!=NULL){
        for(j=0;j<M;j++){
            if(i->V[j].arquivo == indice_arq){
                //printf("repeticao_pala_arq = %d\n",i->V[j].repeticao);
                return i->V[j].repeticao;
            }
        }
    }
    //printf("repeticao_pala_arq = 0\n");
    return 0;
}

int repeticao_pala_total(Arvore t, char *palavra){ //dj
    Arvore i;
    int cont=0,j;
    i = Pesquisa(palavra,&t);
    if(i!=NULL){
        for(j=0;j<TAM;j++){
            if(i->V[j].arquivo != 0)
                cont++;
        }
    }
    //printf("quant_de_arq_tem_pala = %d\n",cont);
    return cont;
}

double peso_W(Arvore t, char *palavra, int indice_arq){
    //printf("indice_arq = %d\n",indice_arq);
    int f = repeticao_pala_arq(t,palavra,indice_arq), d = repeticao_pala_total(t,palavra);
    double W = 0;
    if(f != 0 && d != 0)
        W = f * (log10(TAM)/d);
    //printf("W = %f\n",W);
    return W;
}

void iniciar_W(W *w){
    int i;
    for(i=0;i<TAM;i++){
        w->v_W[i] = 0;
    }
}

void preencher_relevancia(relevancia *rel, W w, qtd_pala_arq qtd){
    int i;
    for(i=0;i<TAM;i++){
        if(qtd.v_qtd[i] != 0)

            rel->re[i] = (1.0/qtd.v_qtd[i]) * w.v_W[i];
        else
            rel->re[i] = 0;
    }
}