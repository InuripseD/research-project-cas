CC = gcc
CFLAGS = -Wall -g
OBJ_DIR = ../obj
BIN_DIR = ../bin

SRC = main.c database.c table.c row.c
OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

BIN = $(BIN_DIR)/cas_db_main

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $^ -o $@

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(BIN)
