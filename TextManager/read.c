#include <stdio.h>
#include <stdlib.h>

typedef struct FileData{
    FILE* file;
    
    int quantWord;
    Word* fileData;
}FileData;

//TODO: usar uma lista encadeada para essa estrutura, devido o comportamento variável de palavras
typedef struct Word{
    char* word;
    InvertedIndex searchTerm;
}Word;

typedef struct InvertedIndex{
    int idDoc; //Document identifier
    int qtde; //Times that the word appear in the document
}InvertedIndex;

//FIXME: é necessário saber quantos documentos existem na leitura para inicializar a struct FileData;

void initializeFileData(FileData* fileData, int docQuant);
//void initializeWord(Word* word);
int countWords(FileData* fileData, FILE* file);

void initializeFileData(FileData* fileData, int docQuant){
    fileData = (FileData*)malloc(sizeof(FileData) * docQuant);

    for(int i = 0; i < docQuant; i++){
        //TODO: initializeWord(){ malloc(sizeof(Word) * quantWord); }

        fileData[i].fileData->searchTerm.idDoc = (i+1);
    }
}

/*
void initializeWord(Word* word){
    word = (Word*)malloc(sizeof(Word));
}
*/

int countWords(FileData* fileData, FILE* file){

}

//Ambiente de testes destinado a esse TAD
/*FIXME: remover esse ambiente de testes assim que o funcionamento total desse TAD seja comprovado
* Uma alternativa seria manter esse ambiente em um branch secundário, a fim de uso na entrevista
*/
int main(){

}