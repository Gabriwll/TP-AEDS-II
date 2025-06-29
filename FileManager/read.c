#include "read.h"

Arvore raiz = NULL; 
int qtd_palavras = 0; // É incrementado toda vez que uma nova palavra diferente é inserida (não duplicada)

List* readFile(int idDoc /* LinkedList list */){
    FILE* file;
    List* list;
    char fileName[24];

    strcpy(fileName, setFileName(fileName, idDoc));
    
    initializeList(&list);

    file = fopen(fileName, "r");
    if(file == NULL){
        printf("Failed to open file:\n%s\n", fileName);
    }

    while(!feof(file)){
        readWord(file, list, &raiz, idDoc, &qtd_palavras);
        // Além da lista encadeada, usei tmb a árvore PATRICIA para indexação invertida.
    }

    fclose(file);

    return list;
}

void readWord(FILE* file, List* list, Arvore *raiz, int idDoc, int *qtd_pala){
    Cell buffer;
    Cell* foundCell;

    fscanf(file, "%s", buffer.item.word);
    cleanString(buffer.item.word);

    // Patricia
    if(strlen(buffer.item.word) == 0) return;
    Insere(buffer.item.word, raiz, idDoc, qtd_pala);


    // Lista encadeada
    foundCell = searchCellByWord(list, buffer.item);
    if(foundCell == NULL){ //Palavra não encontrada na lista, adiciona nova célula na lista e inicializa Parâmetros importantes
        foundCell = addCell(list, buffer.item);

        foundCell->item.searchTerm.idDoc = idDoc;
        foundCell->item.searchTerm.qtde = 1;
    }else{ //Palavra já encontrada na lista, incrementa o contador de ocorrências
        foundCell->item.searchTerm.qtde++;
    }
}

void cleanString(char *originalWord){
    char *currentChar = originalWord;
    char *positionWrite = originalWord;

    // Percorre cada caractere da string original
    while (*currentChar != '\0'){
        if (isalpha((unsigned char)*currentChar) || (*currentChar == '\'')) {
            // Converte para minúscula e guarda na posição atual
            *positionWrite = tolower(*currentChar);
            positionWrite++;
        }

        currentChar++;
    }
    
    // Adiciona o terminador nulo no final da string filtrada
    *positionWrite = '\0';
}

int getdocQuant(){
    FILE* file;
    int docQuant;

    file = fopen("./Files/In/entrada.txt", "r");
    if(file == NULL){
        printf("Failed to open file:\n./Files/In/entrada.txt\n");
    }

    fscanf(file, "%d", &docQuant);
    fclose(file);

    return docQuant;
}

char* setFileName(char fileName[], int idDoc){
    sprintf(fileName, "./Files/In/arquivo%d.txt", idDoc);

    return fileName;
}

//Ambiente de testes destinado a esse TAD
/*FIXME: remover esse ambiente de testes assim que o funcionamento total desse TAD seja comprovado
* Uma alternativa seria manter esse ambiente em um branch secundário, a fim de uso na entrevista
*/
int main(){
    List* list;
    int docQuant = getdocQuant();

    printf("Quantidade de documentos: %d\n", docQuant);

    for(int i = 0; i < docQuant; i++){
        list = readFile(i + 1);
        printList(*list);
        freeList(list);
    }

    printf("\n\n=IMPRIMINDO ARVORE PATRICIA=\n");
    ordena(raiz);

    return 0;
}
