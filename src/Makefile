all: main

main: file.o color.o image.o utils.o main.c
	@gcc main.c -o main file.o color.o image.o utils.o

file.o: file.c
	@gcc -c file.c

color.o: color.c
	@gcc -c color.c

image.o: image.c
	@gcc -c image.c

utils.o: utils.c
	@gcc -c utils.c

clean:
	rm -f *.o