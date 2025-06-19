#ifndef patricia.h
#define patricia.h

#define M 5 //nº de arquivos

typedef  short boolean;
typedef unsigned char *ChaveTipo;/* a definir, dependendo da aplicacao */
typedef unsigned char IndexAmp;
typedef unsigned char Dib;

typedef enum {
  Interno, //contém informações de navegação (índice e caractere)
  Externo //contém a chave (string) e informações sobre repetições
} TipoNo;

typedef struct id{
  int repeticao; // Número de vezes que a palavra apareceu
  int arquivo;  // Número do arquivo onde ela apareceu
}id;

typedef struct PatNo* Arvore; // Arvore é ponteiro para PatNo

typedef struct PatNo{
  TipoNo nt; // Se é Interno ou Externo
  
  union{
    struct{
      int indice; // índice do caractere de comparação
      char caractere; // caractere usado para comparar
      Arvore Esq, Dir; // subárvore esquerda e direita
    }NInterno;
      char folha[50]; // palavra armazenada (em nós externos)
  }NO;
  id V[M]; // Vetor com informação de ocorrências da palavra em até M arquivos
}PatNo;

Arvore CriaNoExt(ChaveTipo k,Arvore *p,int N_arquivo);
Arvore CriaNoInt(Arvore *Esq,  Arvore *Dir,int i, char c);
Arvore Pesquisa(ChaveTipo k, Arvore *t);
Arvore InsereEntre(char *k, Arvore *t, short i,char,int);
Arvore Insere(char *k, Arvore *t,int,int *);
void imprime(Arvore t);
void ordena(Arvore t);

#endif  // patricia.h