# Makefile for WslFunctions in WslInstall project
# Compile every single C file

CC = gcc
CFLAGS=-O2 -Wall -Werror -Wextra -Wundef
LFLAGS=-L"../lib" -lwslapi
SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c,%,$(SRCS))

all: $(PROGS)

%: %.c

	$(CC) $(CFLAGS) -o $@ $< $(LFLAGS)
