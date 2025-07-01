#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include "tadhash.h"

void FLVazia(TipoLista *Lista)
{
    Lista->Primeiro = (TipoCelula *)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
}

short Vazia(TipoLista Lista)
{
    return (Lista.Primeiro == Lista.Ultimo);
}

void Ins(Word x, TipoLista *Lista)
{
    Lista->Ultimo->Prox = (TipoCelula *)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->word = x;
    Lista->Ultimo->Prox = NULL;
}

void Ret(TipoApontador p, TipoLista *Lista, Word *Item)
{
    TipoApontador q;
    if (Vazia(*Lista) || p == NULL || p->Prox == NULL)
    {
        printf(" Erro Lista vazia ou posicao nao existe\n");
        return;
    }
    q = p->Prox;
    *Item = q->word;
    p->Prox = q->Prox;
    if (p->Prox == NULL)
        Lista->Ultimo = p;
    free(q);
}

void GeraPesos(TipoPesos p)
{
    int i, j;
    struct timeval semente;
    gettimeofday(&semente, NULL);
    srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));
    for (i = 0; i < N; i++)
        for (j = 0; j < TAMALFABETO; j++)
            p[i][j] = 1 + (int)(10000.0 * rand() / (RAND_MAX + 1.0));
}

TipoIndice h(TipoChave Chave, TipoPesos p)
{
    int i;
    unsigned int Soma = 0;
    int comp = strlen(Chave);
    for (i = 0; i < comp; i++)
        Soma += p[i][(unsigned int)Chave[i]];
    return (Soma % M);
}

void Inicializa(TipoDicionario T)
{
    int i;
    for (i = 0; i < M; i++)
        FLVazia(&T[i]);
}

TipoApontador Pesquisa(TipoChave Ch, TipoPesos p, TipoDicionario T, int idDoc)
{
    TipoIndice i = h(Ch, p);
    TipoApontador Ap;

    if (Vazia(T[i]))
        return NULL;

    Ap = T[i].Primeiro;
    while (Ap->Prox != NULL)
    {
        if (strncmp(Ch, Ap->Prox->word.word, sizeof(TipoChave)) == 0 &&
            Ap->Prox->word.searchTerm.idDoc == idDoc)
        {
            return Ap;
        }
        Ap = Ap->Prox;
    }

    return NULL;
}

void Insere(List lista, TipoPesos p, TipoDicionario T)
{
    Cell *atual = lista.begin;

    while (atual != NULL)
    {
        if (Pesquisa(atual->item.word, p, T, atual->item.searchTerm.idDoc) == NULL)
            Ins(atual->item, &T[h(atual->item.word, p)]);

        else
            printf(" Registro ja esta presente\n");

        atual = atual->next;
    }
}

void Retira(List* lista, TipoPesos p, TipoDicionario T)
{
    TipoApontador Ap;
    Ap = Pesquisa(lista->begin->item.word, p, T, lista->begin->item.searchTerm.idDoc);
    if (Ap == NULL)
        printf(" Registro nao esta presente\n");
    else
        Ret(Ap, &T[h(lista->begin->item.word, p)], &lista->begin->item);
}

void Imp(TipoLista Lista) {
    TipoApontador Aux = Lista.Primeiro->Prox;
    while (Aux != NULL) {
        printf("%.*s [DocID: %d, Qtde: %d] ", 
            N, Aux->word.word, 
            Aux->word.searchTerm.idDoc, 
            Aux->word.searchTerm.qtde);
        Aux = Aux->Prox;
    }
}


void Imprime(TipoDicionario Tabela)
{
    int i;
    for (i = 0; i < M; i++)
    {
        printf("%d: ", i);
        if (!Vazia(Tabela[i]))
            Imp(Tabela[i]);
        putchar('\n');
    }
}

void LerPalavra(char *p, int Tam)
{
    char c;
    int i, j;
    fflush(stdin);
    j = 0;
    while (((c = getchar()) != '\n') && j < Tam - 1)
        p[j++] = c;
    p[j] = '\0';
    while (c != '\n')
        c = getchar();
    for (i = j - 1; (i >= 0 && p[i] == ' '); i--)
        p[i] = '\0';
}
