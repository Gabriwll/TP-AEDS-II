#include "menu.h" 

void begin(){
    int actualState = 1; // Variável para controlar o estado do menu
    /*actualState = 1 significa que o sistema ainda não acessou memória externa
    * actualState = 2 significa que o sistema já processou os documentos (significa que o sistema já inseriu na 
    * estrutura de dados escolhida pelo usuário e liberou a memória auxiliar usada pelo sistema)
    */

    while(initialMenu(/* &root, &hashTable */) != 5); // Enquanto a opção não for 5 (sair), continua no menu
}

int inicialMenu(/* ArvorePatricia* root, Hash* hashTable, */ int actualState){
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
    
    processOption(option);

    return option;
}

int verifyAvalableOptions(int actualState, int option){
    int isAvailable = 0; // Variável para verificar se a opção está disponível

    if(actualState == 1 && (option =! 1 || option =! 5)){
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
    printf("Documento %d carregado e indexado com sucesso!\n", idDoc);
    printf("Conteúdo do indice invertido:\n");
    printList(list);

    return list;
}

int processOption(int option /* ArvorePatricia* root, Hash* hastTable */){
    List* list;
    int docQuant = getdocQuant();

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