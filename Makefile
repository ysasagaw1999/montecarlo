CC = g++


all: solid.o distance

solid.o: geometry.cpp solid.cpp
	g++ solid.cpp geometry.cpp -o solid.o

distance: geometry.cpp distance.cpp
	g++ distance.cpp geometry.cpp -o distance

clean:
	rm distance
	rm solid.o