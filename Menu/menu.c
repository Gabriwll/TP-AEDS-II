#include "menu.h" 
#include "../Hash/tadhash.h"

void begin(){
    int actualState = 1; // Variável para controlar o estado do menu
    /*actualState = 1 significa que o sistema ainda não acessou memória externa, nem processou os documentos e elaborou
    * o índice invertido. Dessa maneira, não pode utilizar funções relacionadas a Patricia e Hash.
    * actualState = 0 significa que o sistema já processou os documentos e elaborou o índice invertido, podendo utilizar
    * funções relacionadas a Patricia e Hash.
    */
    //Patricia* root;
    //Hash* hashTable;

    while(actualState != 5) actualState = initialMenu(actualState/* &root, &hashTable */); // Enquanto a opção não for 5 (sair), continua no menu
}

int initialMenu(/* ArvorePatricia* root, Hash* hashTable, */ int actualState){
    int option;

    do{
        printf(CYAN "============================================\n" RESET);
        printf(WHITE  "     TRABALHO PRATICO DE AEDS 2    \n" RESET);
        printf(CYAN "============================================\n\n" RESET);
        
        printf("Menu de Opções:\n\n");
        printf("Como deseja processar os documentos?\n");
        printf("\t1. Processar os arquivos.\n");
        printf("\t2. Imprimir tabela Hash.\n");
        printf("\t3. Imprimir árvore Patricia.\n");
        printf("\t4. Buscar por palavra ou termo (Hash e Patricia).\n");
        printf("\t5. Sair\n");

        scanf("%d", &option);
        clearTerminal();

    }while(!verifyAvalableOptions(actualState, option));

    processOption(option, &actualState /* &root, &hashTable */);

    return option == 5 ? option : actualState; // Retorna 5 para sair ou o novo estado do menu
}

int verifyAvalableOptions(int actualState, int option){
    int isAvailable = 0; // Variável para verificar se a opção está disponível

    if(actualState == 1 && (option != 1 && option != 5)){
        printf(RED "Opção inválida. Tente novamente.\n" RESET);
        return 0; // Opção inválida
    }

    return 1; // Opção válida
}

List* loadDocument(int idDoc){
    List* list;

    printf("Carregando documento %d\n", idDoc);
    list = readFile(idDoc);
    if(list == NULL){
        printf("Erro ao carregar o documento %d.\n", idDoc);
        return NULL;
    }

    //TODO: bloco desenvolvido com intuito de teste. Remover quando não for mais necessário
    /*
    printf("Documento %d carregado e indexado com sucesso!\n", idDoc);
    printf("Conteúdo do indice invertido:\n");
    printList(*list);
    */

    return list;
}

int processOption(int option, int* actualState /* ArvorePatricia* root, Hash* hastTable */){
    List* list;
    int docQuant = getdocQuant();

    if(option == 5){
        return 1; // Sair do programa
    }

    IprocessOption(option, actualState, list /* root, hashTable */);

    return 1; // Retorna 1 para indicar que o processamento foi bem-sucedido
}

int IprocessOption(int option, int* actualState, List* list /* ArvorePatricia* root, Hash* hashTable */){
    int docQuant = getdocQuant();
    static TipoDicionario tabela;
    static TipoPesos pesos;
    static int initialized = 0;

    if(!initialized){
        Inicializa(tabela);
        GeraPesos(pesos);
        initialized = 1; // Marca que a tabela e pesos foram inicializados
    }

    if(option == 1){
        for(int i = 1; i <= docQuant; i++){
            list = loadDocument(i);

            if(list == NULL){
                printf("Erro ao carregar o documento %d.\n", i);
                continue; // Pula para o próximo documento se houver erro
            }
        }

        *actualState = 0; //Libera acesso a funções relacionadas a Patricia e Hash

        return 1; // Retorna 1 para indicar que o processamento foi bem-sucedido
    }
    
    if(option == 2){
        //TODO: chamar a função que insere na Patricia (lá ele)
        freeList(list); //FIXME: liberar memória da lista aqui não fará com que todas as listas sejam liberadas,
                        //uma vez que essa função possui acesso a uma lista apenas.
    
    }else if(option == 3){
        InsereHash(*list, pesos, tabela);
        Imprime(tabela);
        freeList(list);
    }
}

int main(){
    begin();

    return 0;
}