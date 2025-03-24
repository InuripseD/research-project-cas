CC = gcc
CFLAGS = -Wall -g
OBJ_DIR = ../obj
BIN_DIR = ../bin

SRC = test_main.c reusable_barrier.c test_add_row.c test_modify_row.c
OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

BIN = $(BIN_DIR)/tests

all: $(BIN)

$(BIN): $(OBJ) $(OBJ_DIR)/database.o $(OBJ_DIR)/table.o $(OBJ_DIR)/row.o $(OBJ_DIR)/timer.o
	$(CC) $^ -o $@

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(BIN)
