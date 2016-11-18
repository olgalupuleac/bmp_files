all: main

main: bin/main.o bin/bmp.o
	gcc bin/main.o bin/bmp.o -o hw1

bin/main.o: src/main.c
	gcc -I./include -c src/main.c -o bin/main.o

bin/position.o: src/bmp.c
	gcc -I./include -c src/bmp.c -o bin/bmp.o

clean: 
	rm -f bin/*.o
