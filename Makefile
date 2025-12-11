SRC ?= main.c
TARGET_SRC ?= my_program.out
DIAG_FLAGS = -fdiagnostics-color=always -fmessage-length=0 -Wformat-diag
FILE_LUA ?= hello.lua
LUA_LIBRARY_PATH = -I/usr/include/lua5.4

.PHONY: all run run-gcc hello-lua compile-lua help

all: compile-lua run
 

compile-lua:
	gcc -std=c99 -Wall -Wextra -Wformat -Werror -Wconversion -Wformat=2 -Wformat-security $(DIAG_FLAGS) ${LUA_LIBRARY_PATH} -O0 ${SRC} -o $(TARGET_SRC) -llua5.4 -lm -ldl
 
run:
	./$(TARGET_SRC)

run-gcc:
	valgrind --leak-check=full --track-origins=yes ./$(TARGET_SRC)


hello-lua:
	lua ${FILE_LUA}

help:
	@echo "Use:"
	@echo "  make                  - compile lua and run"
	@echo "  make hello-lua        - compile lua script example"
	@echo "  make compile-lua      - compile lua"
 
	
# Use:
#
# make
# make FILE=test.c