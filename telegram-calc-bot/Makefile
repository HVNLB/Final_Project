CC=gcc
CFLAGS=-Wall -Iinclude -g
SRC=src/main.c src/formula.c src/parser.c
OUT=bot

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)
