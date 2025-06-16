#include <stdio.h>

typedef struct FileData{
    FILE* file;
    
    int quantWord;
    Word* fileData; //TODO: initializeFileData(){ malloc(sizeof(Word) * quantWord); }
}FileData;

typedef struct Word{
    char* word;
    InvertedIndex searchTerm;
}Word;

typedef struct InvertedIndex{
    int idDoc; //Document identifier
    int qtde; //Times that the word appear in the document
}InvertedIndex;


//Ambiente de testes destinado a esse TAD
/*FIXME: remover esse ambiente de testes assim que o funcionamento total desse TAD seja comprovado
* Uma alternativa seria manter esse ambiente em um branch secundário, a fim de uso na entrevista
*/
int main(){

}