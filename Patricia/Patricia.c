#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Patricia.h"

/**
 * @brief Verifica se um nó da árvore PATRICIA é externo (folha).
 * 
 * @param p Ponteiro para o nó a ser verificado.
 * @return short Retorna 1 se for nó externo, 0 caso contrário.
 * @author Raíssa Tayná
 */
short EExterno(Arvore p){
  assert(p != NULL); // Garante que o ponteiro não é nulo
  return (p->nt == Externo); // Retorna verdadeiro se o tipo do nó for Externo
}

/**
 * @brief Cria um novo nó interno da árvore PATRICIA.
 * 
 * Um nó interno é usado para decidir o caminho na árvore com base em um caractere da chave.
 * 
 * @param Esq Ponteiro para a subárvore esquerda.
 * @param Dir Ponteiro para a subárvore direita.
 * @param i Índice do caractere a ser testado na chave.
 * @param c Caractere usado para a comparação no índice i.
 * @return Arvore Retorna o ponteiro para o novo nó interno criado.
 */
Arvore CriaNoInt(Arvore *Esq, Arvore *Dir, int i, char c){
  Arvore p;

  p = (Arvore)malloc(sizeof(PatNo)); // Aloca memória para o novo nó
  p->nt = Interno; // Define o tipo como nó interno

  p->NO.NInterno.Esq = *Esq; // Define o filho esquerdo
  p->NO.NInterno.Dir = *Dir; // Define o filho direito
  p->NO.NInterno.indice = i; // Índice do caractere a ser testado
  p->NO.NInterno.caractere = c; // Caractere que será comparado nesse índice

  return p; // Retorna o ponteiro para o novo nó interno
}

/**
 * @brief Cria um novo nó externo (folha) na árvore PATRICIA.
 * 
 * Um nó externo armazena a chave e um vetor indicando em quais arquivos essa chave ocorre.
 * 
 * @param k Chave (string) a ser armazenada no nó.
 * @param p Ponteiro para o ponteiro onde será criado o nó.
 * @param N_arquivo Índice do arquivo onde a chave foi encontrada (1-based).
 * @return Arvore Retorna o ponteiro para o novo nó externo criado.
 */
Arvore CriaNoExt(ChaveTipo k, Arvore *p, int N_arquivo){
  int i;
  *p = (Arvore)malloc(sizeof(PatNo)); // Aloca memória para o novo nó
  (*p)->nt = Externo; // Define como nó externo (folha)

  strcpy((*p)->NO.folha, k); // Copia a chave (ex: palavra) para o campo folha

  // Inicializa o vetor de ocorrências em arquivos
  for(i = 0; i < M; i++){
      (*p)->V[i].arquivo = i + 1; // Define número do arquivo (1 até M)
      (*p)->V[i].repeticao = 0;  // Inicializa com 0 repetições
  }

  // Marca uma repetição da chave no arquivo N_arquivo
  (*p)->V[N_arquivo - 1].repeticao = 1;

  return *p; // Retorna o ponteiro para o novo nó externo
}


/**
 * @brief Pesquisa uma chave na árvore PATRICIA.
 * 
 * @param k Chave a ser pesquisada.
 * @param t Ponteiro para o nó raiz da árvore ou subárvore.
 * 
 * @return Arvore Ponteiro para o nó encontrado com a chave ou NULL se não encontrado.
 */
Arvore Pesquisa(ChaveTipo k, Arvore *t){ 
  if ((*t)->nt == Externo) {
    if (strcmp(k,(*t)->NO.folha) == 0)
      return (*t); ///< Nó folha com a chave encontrada.
    else
      return NULL; ///< Chave não encontrada.
  }
  // Se nó interno, decide ir para filho esquerdo ou direito baseado na comparação
  if (k[(*t)->NO.NInterno.indice] < (*t)->NO.NInterno.caractere)
    return Pesquisa(k, &(*t)->NO.NInterno.Esq);
  else
    return Pesquisa(k, &(*t)->NO.NInterno.Dir);
}


/**
 * @brief Insere uma chave entre dois nós na árvore, criando um nó interno novo.
 * 
 * @param k Chave a ser inserida.
 * @param t Ponteiro para o nó atual.
 * @param i Índice do caractere onde ocorre a primeira diferença entre as chaves.
 * @param diferente Caractere de diferença para comparação no novo nó interno.
 * @param N_arquivo Número do arquivo para atualizar ocorrência.
 * 
 * @return Arvore Ponteiro para o nó resultante da inserção.
 */
Arvore InsereEntre(char *k, Arvore *t, short i,char diferente,int N_arquivo){
    Arvore p;
    char c;
    if (EExterno(*t)){
      CriaNoExt(k,&p,N_arquivo);

      // Decide se novo nó interno terá filho esquerdo ou direito
      if(strcmp((*t)->NO.folha,k) < 0){
        return (CriaNoInt(t,&p,i,diferente));

      } else if(strcmp((*t)->NO.folha,k) > 0){
        return (CriaNoInt(&p,t,i,diferente));
      }
      // Se as chaves são iguais, não insere nada
      // printf("Erro: chave ja esta na arvore: %s == %s\n",k,(*t)->NO.folha);
      return NULL;

    } else if(i < (*t)->NO.NInterno.indice){
      CriaNoExt(k,&p,N_arquivo);

      if(k[i] < diferente){
        return (CriaNoInt(&p,t,i,diferente));
      } else{
        return (CriaNoInt(t,&p,i,diferente));
      }
    } else {

      // Inserção recursiva nos filhos esquerdo ou direito do nó interno
      if (k[(*t)->NO.NInterno.indice] < (*t)->NO.NInterno.caractere)
        (*t)->NO.NInterno.Esq = InsereEntre(k,&(*t)->NO.NInterno.Esq,i,diferente,N_arquivo);
      else
        (*t)->NO.NInterno.Dir = InsereEntre(k,&(*t)->NO.NInterno.Dir,i,diferente,N_arquivo);
      return (*t);
    }
}

/**
 * @brief Insere uma chave na árvore PATRICIA.
 * 
 * Se a chave já existir, incrementa o contador de ocorrência para o arquivo indicado.
 * Caso contrário, realiza a inserção apropriada.
 * 
 * @param k Chave a ser inserida.
 * @param t Ponteiro para o nó raiz da árvore.
 * @param N_arquivo Número do arquivo para contabilizar ocorrências.
 * @param qtd_pala Ponteiro para contador de palavras inseridas na árvore.
 * 
 * @return Arvore Ponteiro para a raiz da árvore após inserção.
 */
Arvore Insere(char *k, Arvore *t,int N_arquivo, int *qtd_pala)
{
    Arvore p;
    int i,j;
    char caux,cdif;

    if ((*t) == NULL){
      // Árvore vazia: cria nó externo diretamente.
      return (CriaNoExt(k,t,N_arquivo));
    }
    else{
        p = (*t);
        // Desce até o nó folha onde a chave pode estar ou deve ser inserida
        while (!EExterno(p))
        {
            caux = k[p->NO.NInterno.indice];

            if (caux < p->NO.NInterno.caractere)
                p = p->NO.NInterno.Esq;
            else if(caux >= p->NO.NInterno.caractere) 
                p = p->NO.NInterno.Dir;
            else
              p = p->NO.NInterno.Esq;
        }

        // Se chave já está na árvore, incrementa contagem de repetição para arquivo
        /* acha o primeiro Caractere diferente */
        i = 0;
        if(strcmp(p->NO.folha,k) == 0){
          for(j=0;j<M;j++){
              if(j == (N_arquivo - 1)){
                p->V[j].repeticao++;
              }
          }
          return (*t);
        }
        else{
          // Encontra o primeiro índice onde as chaves diferem
          int tam = (strlen(k) < strlen(p->NO.folha))? strlen(k) : strlen(p->NO.folha);
          for(i=0;i<= tam;i++){
            if(k[i] != p->NO.folha[i]){
              if(k[i] < p->NO.folha[i]){
                cdif = p->NO.folha[i];
                break;
              } else{
                cdif = k[i];
                break;
              }
            }
          }
          (*qtd_pala)++; ///< Incrementa contador de palavras distintas inseridas.
          // Insere a chave na posição correta da árvore, criando um novo nó interno se necessário
          return (InsereEntre(k, t, i, cdif, N_arquivo));
        }
    }
}

/**
 * @brief Imprime as chaves (somente nós externos) da árvore e suas ocorrências.
 * 
 * @param t Ponteiro para o nó raiz da árvore ou subárvore.
 */
void imprime(Arvore t) {
  if (t == NULL) {
    return;
  }

  if (t->nt == Externo) {
    printf("chave: %s\n-------------------------------------------\nocorrencia: ", t->NO.folha);
    for (int i = 0; i < M; i++) {
      if (t->V[i].repeticao != 0) {
        printf("<%d,%d> ", t->V[i].repeticao, t->V[i].arquivo);
      }
    }
    printf("\n-------------------------------------------\n");
  }
}

/**
 * @brief Percorre a árvore em ordem e imprime todas as chaves (folhas).
 * 
 * @param t Ponteiro para o nó raiz da árvore ou subárvore.
 */
void ordena(Arvore t) {
  if (t == NULL) {
    return;
  }

  if (t->nt == Interno) {
    ordena(t->NO.NInterno.Esq); ///< Percorre filho esquerdo recursivamente.
  }

  imprime(t); ///< Imprime o nó atual (se for folha).

  if (t->nt == Interno) {
    ordena(t->NO.NInterno.Dir); ///< Percorre filho direito recursivamente.
  }
}