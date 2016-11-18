CFLAGS=-std=c99 -Wall -Werror
all: main
main: bin/main.o bin/bmp.o
    gcc bin/main.o bin/bmp.o -o main
bin/main.o: src/main.c
    mkdir -p bin
    gcc -I./include -c $(CFLAGS) src/main.c -o bin/main.o
bin/bmp.o: src/bmp.c
    mkdir -p bin
    gcc -I./include -c $(CFLAGS) src/bmp.c -o bin/bmp.o
clean:
    rm -f bin/*.o
