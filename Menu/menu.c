#include "menu.h"

int inicialMenu(/* ArvorePatricia* root, Hash* hashTable */){
    int option;

    printf("Menu de Opções:\n\n");
    printf("Como deseja processar os documentos?\n");
    printf("\t1. Processar usando Patricia.\n");
    printf("\t2. Processar usando Hash.\n");
    printf("\t3. Sair.\n");

    scanf("%d", &option);
    processOption(option);

    return option;
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
    printf("Documento %d carregado e indexado com sucesso!\n", idDoc);
    printf("Conteúdo do indice invertido:\n");
    printList(list);

    return list;
}

int processOption(int option /* ArvorePatricia* root, Hash* hastTable */){
    List* list;
    int docQuant = getdocQuant();

    clearTerminal(); // Limpa o terminal antes de processar a opção
    switch(option){
        case 1:
            IprocessOption(option, list /* root, hashTable */);

            //TODO: Imprime a árvore Patricia

            break;
        
        case 2:
            IprocessOption(option, list /* root, hashTable */);

            //TODO: Imprime a tabela hash

            break;
    
        case 3:
            printf("Saindo do programa...\n");
        
            return 0; // Sair do programa

        default:
            printf("Opção inválida. Tente novamente.\n");
            inicialMenu(); // Volta ao menu inicial
    }

    return 1; // Retorna 1 para indicar que o processamento foi bem-sucedido
}

int IprocessOption(int option, List* list /* ArvorePatricia* root, Hash* hashTable */){
    char structure[10];
    int docQuant = getdocQuant();

    if(option == 1) strcpy(structure, "Patricia");

    else if(option == 2) strcpy(structure, "Hash");

    for(int i = 1; i <= docQuant; i++){
        printf("Carregando documento %d...\n", i);
        list = loadDocument(i);
        if(list == NULL) return 0; // Se falhar, sai da função

        if(option == 1)
            printf("Processando documento %d usando Patricia...\n", i);

            //TODO: chamar a função que insere na Patricia (lá ele)
        else if(option == 2){
            printf("Processando documento %d usando Hash...\n", i);
            
            //TODO: chamar a função que insere na Hash (lá ele)
        }

        freeList(list);
    }

    //clearTerminal(); // Limpa o terminal após processar todos os documentos
    printf("Todos os documentos foram processados usando %s.\n", structure);
}

int main(){
    // ArvorePatricia* root = NULL;
    // Hash* hashTable = NULL;

    switch(inicialMenu(/* &root, &hashTable */)){  // Chama a função inicialMenu e processa a opção retornada
    case 1:
        //freePatricia(&root); // Libera a memória da árvore Patricia
        //root = NULL; // Reseta o ponteiro da árvore
        break;
    
    case 2:
        //freeHashTable(&hashTable); // Libera a memória da tabela hash
        //hashTable = NULL; // Reseta o ponteiro da tabela hash
        break;

    default:
        break;
    }
    inicialMenu(/* root, hashTable */);

    return 0;
}