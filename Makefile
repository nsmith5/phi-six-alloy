CC = nvcc
OBJ = ./obj/
INC = ./include
SRC = ./src/
CFLAGS = -I$(INC) -target-cpu-arch ARM -ccbin arm-linux-gnueabihf-g++-4.8 -m32

all: main methods
	$(CC) $(OBJ)*.o -o main $(CFLAGS)

main: methods
	$(CC) -c $(SRC)main.cpp -o $(OBJ)main.o $(CFLAGS)

methods:
	$(CC) -c $(SRC)methods.cpp -o $(OBJ)methods.o $(CFLAGS)
