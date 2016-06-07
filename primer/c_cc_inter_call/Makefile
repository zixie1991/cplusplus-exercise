CC = gcc
CXX = g++

hello.o: hello.c
	$(CC) -c hello.c

test_hello.o: test_hello.cc
	$(CXX) -c test_hello.cc

test_hello: test_hello.o hello.o
	$(CXX) -o test_hello test_hello.o hello.o

world.o: world.cc
	$(CXX) -c world.cc

test_wolrd.o: test_world.c
	$(CC) -c test_world.c

test_world: test_world.o world.o
	$(CC) -o test_world test_world.o world.o

all: test_hello test_world


clean:
	rm -f *.o test_hello test_world
