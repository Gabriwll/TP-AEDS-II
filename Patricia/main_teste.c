#include <math.h>
#include "Patricia.h"                        
#include "../Relevancia/Relevancia.h"       
#include "../InvertedIndex/InvertedIndexPat.h"
#include "../Patricia/trata_arquivo.h"

#define comp 0.000001

int main() {
    Arvore p = NULL;
    relevancia rel;
    qtd_pala_arq qtd;
    relevancia relev;
    W p_w;

    int N_arquivo = 0, op = 9, i, j, qtd_pala = 0;
    char linha_artigo[100], *palavra, arq[100];

    FILE *TXTartigo, *entradaTXT;

    printf("MENU:\n"
           "1 = Ler Arquivos\n"
           "0 = Encerrar\n\n");

    while (op != 0) {
        scanf("%d", &op);
        system("cls");
        switch (op) {
            case 1:
                entradaTXT = fopen("Files/In/entrada.txt", "r");
                if (entradaTXT == NULL) {
                    printf("Erro ao abrir entrada.txt\n");
                    exit(1);
                }

                fscanf(entradaTXT, "%d", &N_arquivo);
                fclose(entradaTXT);

                iniciar_qtd_pala_arq(&qtd); // inicializa qtd_pala_arq
                iniciar_W(&p_w); // inicializa pesos
                memset(&relev, 0, sizeof(relev));  // limpa relevância

                for (int idDoc = 0; idDoc < N_arquivo && idDoc < TAM; idDoc++) {
                    sprintf(arq, "Files/In/arquivo%d.txt", idDoc + 1);
                    TXTartigo = fopen(arq, "r");

                    if (TXTartigo == NULL) {
                        printf("Erro ao abrir %s\n", arq);
                        continue;
                    }

                    while (fgets(linha_artigo, sizeof(linha_artigo), TXTartigo)) {
                        palavra = strtok(linha_artigo, " ");
                        while (palavra) {
                            palavra = minusculo(palavra);
                            palavra = trata_N(palavra);
                            palavra = trata_P(palavra);

                            p = Insere(palavra, &p, idDoc, &qtd_pala);

                            palavra = strtok(NULL, " ");
                        }
                    }

                    fclose(TXTartigo);
                    inserir_qtd_pala_arq(&qtd, idDoc, qtd_pala);
                    qtd_pala = 0;
                }

                while (op != 0) {
                    printf("\nMENU:\n"
                           "2 = Ordenar\n"
                           "3 = Pesquisar\n"
                           "0 = Encerrar\n\n");
                    printf("Digite sua opcao: ");
                    scanf("%d", &op);
                    system("cls");
                    switch (op) {
                        case 2:
                            printf("Imprimindo:\n");
                            ordena(p);
                            break;
                        case 3:
                            iniciar_W(&p_w);
                            char texto[100];
                            printf("\nFaca uma pesquisa: \n");
                            limparBuffer();
                            fgets(texto, sizeof(texto), stdin);
                            texto[strcspn(texto, "\n")] = '\0';

                            const char delimitador[] = " ";
                            char *token;

                            token = strtok(texto, delimitador);

                            while (token != NULL) {
                                inserir_peso(&relev, N_arquivo, p, token, &p_w);
                                token = strtok(NULL, delimitador);
                            }

                            preencher_relevancia(&relev, p_w, qtd);
                            double relevaux[5], aux;
                            for (i = 0; i < M; i++) {
                                relevaux[i] = relev.re[i];
                            }
                            for (i = 1; i < M; i++) {
                                aux = relevaux[i];
                                j = i - 1;

                                while (j >= 0 && relevaux[j] < aux) {
                                    relevaux[j + 1] = relevaux[j];
                                    j = j - 1;
                                }
                                relevaux[j + 1] = aux;
                            }

                            int k, d;
                            for (k = 0; k < M; k++) {
                                for (d = 0; d < M; d++) {
                                    if ((fabs(relevaux[k]) > comp) && (fabs(relev.re[d]) > comp)) {
                                        if (fabs(relevaux[k] - relev.re[d]) < comp) {
                                            printf("arquivo%d.txt = %f\n", d + 1, relev.re[d]);
                                            break;
                                        }
                                    }
                                }
                            }
                            break;
                        case 0:
                            printf("\nEncerrando...\n");
                            break;
                        default:
                            printf("Opcao invalida, por favor tente novamente!\n");
                            break;
                    }
                }
                break;
            case 0:
                printf("\nEncerrando...\n");
                break;
            default:
                printf("Opcao invalida, por favor tente novamente!\n");
                break;
        }
    }
    return 0;
}
