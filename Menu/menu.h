#ifndef MENU_H
#define MENU_H

#include <stdio.h>

#include "../FileManager/read.h"
//#include "../Relevancia/Relevancia.h"
//#include "../Patricia/Patricia.h"
#include "../Hash/tadhash.h"

// ANSI cores
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define CYAN    "\033[1;36m"
#define YELLOW  "\033[1;33m"
#define WHITE   "\033[1;37m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"

//TODO: terminar a implementação baseada nas estruturas
void begin();
int initialMenu(/* ArvorePatricia* root, Hash* hashTable, */ int actualState);
int verifyAvalableOptions(int actualState, int option);
List* loadDocument(int idDoc);
int processOption(int option, int* actualState /* ArvorePatricia* root, Hash* hastTable */);
int IprocessOption(int option, int* actualState, List* list /* ArvorePatricia* root, Hash* hashTable */);

#ifdef _WIN32
#define clearTerminal() system("cls") // Para Windows

#elif __linux__
#define clearTerminal() system("clear") // Para Linux/Unix

#endif

#endif