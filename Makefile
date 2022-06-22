CC = gcc
CFLAGS = -Wall -Werror -pedantic

all: mapper

mapper: mapper.c
	$(CC) $(CFLAGS) mapper.c -o mapper

clean:
	rm mapper