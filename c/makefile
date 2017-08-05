CC=gcc-7
CFLAGS=-Wall -Werror -std=c99 -O3 -g -I.
DEPS=vec3.h ray.h sphere.h world.h
OBJ=vec3.o ray.o sphere.o world.o main.o 
TESTS=vec3test.o raytest.o spheretest.o worldtest.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: main test

main: $(OBJ)
	$(CC) -o main $(OBJ) -I.

test: vec3.o ray.o sphere.o world.o $(TESTS)
	$(CC) -o vectest vec3.o vec3test.o -I.
	$(CC) -o raytest vec3.o ray.o raytest.o -I.
	$(CC) -o spheretest vec3.o ray.o sphere.o spheretest.o -I.
	$(CC) -o worldtest vec3.o ray.o sphere.o world.o worldtest.o -I.



debug: main
	./main > output.txt


run: main
	./main > output.ppm
	convert output.ppm output.png

clean:
	rm -rf *.o *.dSYM main raytest vectest
