CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -g

.PHONY: test clean

linkedList: linkedList.o
	$(CC) $(CFLAGS) $< -o $@

linkedList.o: linkedList.c
	$(CC) $(CFLAGS) $< -c -o $@

test:
	./linkedList

clean:
	rm -f linkedList *.o
