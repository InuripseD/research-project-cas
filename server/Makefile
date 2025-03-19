CC = gcc
CFLAGS = -Wall -g
OBJ_DIR = ../obj
BIN_DIR = ../bin

SRC = server_main.c server.c
OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

BIN = $(BIN_DIR)/server

all: $(BIN)

$(BIN): $(OBJ) $(OBJ_DIR)/database.o $(OBJ_DIR)/table.o $(OBJ_DIR)/row.o $(OBJ_DIR)/benchmark.o
	$(CC) $^ -o $@

$(OBJ_DIR)/%.o: %.c
	$(MAKE) -C ../cas-db
	$(MAKE) -C ../benchmarks
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(BIN)
