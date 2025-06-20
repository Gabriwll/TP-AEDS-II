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
