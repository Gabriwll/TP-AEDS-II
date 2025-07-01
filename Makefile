all:
	gcc -o programa main.c Patricia/Patricia.c Patricia/trata_arquivo.c Relevancia/Relevancia.c Relevancia/RelevanciaHash.c InvertedIndex/InvertedIndexPat.c Hash/Hash.c FileManager/read.c LinkedList/linkedlist.c -lm
	./programa

#gcc -o menu.exe ./Menu/menu.c ./LinkedList/linkedList.c ./InvertedIndex/invertedIndex.c ./FileManager/read.c