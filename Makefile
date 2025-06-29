all:
	gcc -o exe main_relevancia.c Patricia/Patricia.c Relevancia/Relevancia.c
	./exe