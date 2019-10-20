all: main

main: file.o image.o utils.o main.c
	@gcc main.c -o main file.o image.o utils.o

file.o: file.c
	@gcc -c file.c

image.o: image.c
	@gcc -c image.c

utils.o: utils.c
	@gcc -c utils.c

clean:
	rm -f *.o