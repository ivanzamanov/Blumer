
FLAGS= -Wall -std=c++11 -g
CC=g++
CMD=$(CC) $(FLAGS)

all: clean
	mkdir bin
	cd src && \
	$(CMD) DAWG.cpp main.cpp -o ../bin/main
	cd ..

clean:
	rm -rf bin

