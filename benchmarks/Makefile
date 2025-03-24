CC = gcc
CFLAGS = -Wall -g
OBJ_DIR = ../obj
BIN_DIR = ../bin

SRC = benchmark_main.c timer.c update_row_benchmark_classic.c mark7.c mark7_adapted.c up_row_ben_adapt.c
OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

BIN = $(BIN_DIR)/benchmarks

all: $(BIN)

$(BIN): $(OBJ) $(OBJ_DIR)/database.o $(OBJ_DIR)/table.o $(OBJ_DIR)/row.o $(OBJ_DIR)/reusable_barrier.o
	$(CC) $^ -o $@ -lm

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(BIN)
