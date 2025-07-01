all:
	gcc -o exe main_relevancia.c Patricia/Patricia.c Relevancia/Relevancia.c
	./exe

#gcc -o menu.exe ./Menu/menu.c ./LinkedList/linkedList.c ./InvertedIndex/invertedIndex.c ./FileManager/read.c