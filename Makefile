CC = g++

COMPILER_FLAGS = -Wall -Wextra -pedantic-errors
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf
SRC = $(wildcard core/*.cpp) main.cpp
OBJ = $(SRC:.cpp=.o)

OBJ_NAME = app

all: clear $(OBJ)
	$(CC) $(OBJ) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clear:
	rm -rf $(OBJ) $(OBJ_NAME)
