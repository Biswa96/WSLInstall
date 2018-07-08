#Compile every single C file

CC = gcc
CFLAGS=-Wall -Werror -Wextra
SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c,%,$(SRCS))

all: $(PROGS)

%: %.c

	$(CC) $(CFLAGS) -o $@ $<
