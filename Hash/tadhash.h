#ifndef tadhash_h
#define tadhash_h

#define HASH_SIZE 1000

typedef struct OcurrenceList{
    int idDoc; 
    int qtde;
    struct OcurrenceList* next; 
}OcurrenceList;

typedef struct{
    char* word; 
    OcurrenceList* occurrences; 
    WordEntry* next; 
}WordEntry;

typedef struct{
    WordEntry* table[HASH_SIZE]; 
}HashTable;

#endif // tadhash_h