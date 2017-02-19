CXX=clang++-3.8
CXXFLAGS=`sdl2-config --cflags` -g -std=c++11 -Wall -pedantic
BIN=main

SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)

all: $(OBJ)
	$(CXX) -o $(BIN) `sdl2-config --libs` $^

%.o: %.c
	$(CXX) $@ -c $<

clean:
	rm -f *.o
	rm $(BIN)

