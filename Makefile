# Define directories
CC = gcc
CFLAGS = -Wall -g
SRC_DIR = cas-db
OBJ_DIR = obj
BIN_DIR = bin
TST_DIR = tests

# Define source files
SRC_MAIN = $(SRC_DIR)/main.c
SRC_DB = $(SRC_DIR)/database.c
SRC_TB = $(SRC_DIR)/table.c
SRC_RW = $(SRC_DIR)/row.c
# SRC_SERVER = $(SRC_DIR)/server.c
SRC_TST = $(TST_DIR)/testaddrow.c

# Define object files
OBJ_MAIN = $(OBJ_DIR)/main.o
OBJ_DB = $(OBJ_DIR)/database.o
OBJ_TB = $(OBJ_DIR)/table.o
OBJ_RW = $(OBJ_DIR)/row.o
# OBJ_SERVER = $(OBJ_DIR)/server.o
OBJ_TST = $(OBJ_DIR)/tests.o

# Final executable
BIN_MAIN = $(BIN_DIR)/db_server
BIN_TEST_ADD = $(BIN_DIR)/testaddrow

# Default target: build the main program
all: $(BIN_MAIN)

# Build the main program
$(BIN_MAIN): $(OBJ_MAIN) $(OBJ_DB) $(OBJ_TB) $(OBJ_RW)
	$(CC) $(OBJ_MAIN) $(OBJ_DB) $(OBJ_TB) $(OBJ_RW) -o $@

# Build the test program
testaddrow: $(BIN_TEST_ADD)

# Build the test program
$(BIN_TEST_ADD): $(OBJ_TST) $(OBJ_DB) $(OBJ_TB) $(OBJ_RW)
	$(CC) $(OBJ_TST) $(OBJ_DB) $(OBJ_TB) $(OBJ_RW) -o $@

# Compile main source file into object file
$(OBJ_MAIN): $(SRC_MAIN)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile test source file into object file
$(OBJ_TST): $(SRC_TST)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile database source file into object file
$(OBJ_DB): $(SRC_DB)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile table source file into object file
$(OBJ_TB): $(SRC_TB)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile row source file into object file
$(OBJ_RW): $(SRC_RW)
	$(CC) $(CFLAGS) -c $< -o $@

# # Compile server source file into object file
# $(OBJ_SERVER): $(SRC_SERVER)
# 	echo "Building the server object file..."
# 	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/*

.PHONY: all clean
