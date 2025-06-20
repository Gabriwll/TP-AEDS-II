#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

typedef struct Word{
    char word[50];
    InvertedIndex searchTerm;
}Word;

typedef struct InvertedIndex{
    int idDoc; //Document identifier
    int qtde; //Times that the word appear in the document
}InvertedIndex;

#endif