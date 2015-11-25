CC = gcc
CFLAGS = -std=c99

TARGETS = vhs

all: $(TARGETS)

chess: vhs.c
	$(CC) $(CFLAGS) vhs.c -o $@

clean:
	$(RM) $(TARGETS)
