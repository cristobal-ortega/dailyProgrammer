CC = gcc
CFLAGS = -std=c99

TARGETS = chess

all: $(TARGETS)

chess: chess.c
	$(CC) $(CFLAGS) chess.c -o $@

clean:
	$(RM) $(TARGETS)
