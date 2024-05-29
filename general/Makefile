
CUR_DIR := .
BIN_DIR := $(CUR_DIR)/bin
LIB_DIR := $(CUR_DIR)/lib
OBJ_DIR := $(CUR_DIR)/obj
SRC_DIR := $(CUR_DIR)/src
INC_DIR := $(CUR_DIR)/inc
INC_FLAG := -I $(INC_DIR)
CC := gcc
LIB_NAME := Name
LIB_SHARE := $(LIB_DIR)/share

mk_objs:
	$(CC) -c -fPIC $(CUR_DIR)/main.c -o $(OBJ_DIR)/main.o $(INC_FLAG)
	$(CC) -c -fPIC $(SRC_DIR)/hello1.c -o $(OBJ_DIR)/hello1.o $(INC_FLAG)
	$(CC) -c -fPIC $(SRC_DIR)/hello2.c -o $(OBJ_DIR)/hello2.o $(INC_FLAG)
mk_shared:
	$(CC) -shared $(OBJ_DIR)/hello1.o $(OBJ_DIR)/hello2.o -o $(LIB_SHARE)/lib$(LIB_NAME).so

install:
	cp -f $(LIB_SHARE)/lib$(LIB_NAME).so /usr/lib

all:    mk_objs mk_shared  install
	$(CC) $(OBJ_DIR)/main.o -L$(LIB_SHARE) -l$(LIB_NAME) -o $(BIN_DIR)/runfile
clean:
	rm -rf $(BIN_DIR)/*
	rm -rf $(LIB_SHARE)/*
	rm -rf $(OBJ_DIR)/*


