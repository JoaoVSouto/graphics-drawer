all: main

main: file.o color.o image.o utils.o main.c
	@gcc main.c -o main file.o color.o image.o utils.o

file.o: file/file.c
	@gcc -c file/file.c

color.o: color/color.c
	@gcc -c color/color.c

image.o: image/image.c
	@gcc -c image/image.c

utils.o: utils/utils.c
	@gcc -c utils/utils.c

clean:
	rm -f *.o
