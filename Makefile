CC = g++
OBJ = ./obj/
INC = ./include
SRC = ./src/
CFLAGS = -Wall -Werror -fopenmp --std=c++11 -I$(INC)

all: main methods
	$(CC) $(OBJ)*.o -o main $(CFLAGS)

main: methods
	$(CC) -c $(SRC)main.cpp -o $(OBJ)main.o $(CFLAGS)

methods:
	$(CC) -c $(SRC)methods.cpp -o $(OBJ)methods.o $(CFLAGS)
