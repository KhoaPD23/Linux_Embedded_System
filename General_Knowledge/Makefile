CUR_DIR := .
INC_DIR := $(CUR_DIR)/inc
SRC_DIR := $(CUR_DIR)/src
BIN_DIR := $(CUR_DIR)/bin
OBJ_DIR := $(CUR_DIR)/obj
LIB_DIR := $(CUR_DIR)/lib
LIB_STATIC_DIR := $(LIB_DIR)/static
LIB_SHARED_DIR := $(LIB_DIR)/shared

static:
	gcc -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o -I $(INC_DIR)
	gcc -c $(SRC_DIR)/bstrutils.c -o $(OBJ_DIR)/bstrutils.o -I $(INC_DIR)
	ar rc $(LIB_STATIC_DIR)/libbstrutils.a $(OBJ_DIR)/bstrutils.o
	gcc $(OBJ_DIR)/main.o -L$(LIB_STATIC_DIR) -lbstrutils -o $(BIN_DIR)/main_static

shared:
	gcc -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o -I $(INC_DIR)
	gcc -c -fPIC $(SRC_DIR)/bstrutils.c -o $(OBJ_DIR)/bstrutils.o -I $(INC_DIR)
	gcc -shared $(OBJ_DIR)/bstrutils.o -o $(LIB_SHARED_DIR)/libbstrutils.so
	gcc $(OBJ_DIR)/main.o -L$(LIB_SHARED_DIR) -lbstrutils -o $(BIN_DIR)/main_shared

all:	static	shared

run_static:
	./$(BIN_DIR)/main_static

run_shared:
	LD_LIBRARY_PATH=./lib/shared ./bin/main_shared

clean:
	rm -rf $(OBJ_DIR)/*
	rm -rf $(BIN_DIR)/*
	rm -rf $(LIB_STATIC_DIR)/*
	rm -rf $(LIB_SHARED_DIR)/*
