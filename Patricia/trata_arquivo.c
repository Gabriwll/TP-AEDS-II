#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* trata_N(char *palavra){
    palavra[strcspn(palavra, "\n")] = '\0';
    return palavra;
}

char* minusculo(char *palavra){
    int j = 0;
    char *s2 = malloc(strlen(palavra) + 1); // Aloca memória para s2
    
    while(palavra[j] != '\0'){
        s2[j] = tolower(palavra[j]);
        j++;
    }

    s2[j] = '\0';
    return s2;
}

char* trata_P(char *palavra){
    int result = strlen(palavra);
    if(palavra[result-1] == ','){
        palavra[strcspn(palavra, ",")] = '\0';
    }
    if(palavra[result-1] == '.'){
        palavra[strcspn(palavra, ".")] = '\0';
    }
    return palavra;
}
