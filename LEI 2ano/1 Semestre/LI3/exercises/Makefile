CC=gcc
CFLAGS=-Wall -Wextra -Ibin -Isrc
LDFLAGS=

all: program

program: src/deque.o src/main.o src/deque.o
	$(CC) $^ -o  bin/$@ $(CFLAGS)
	@rm src/*.o

# command_parser: src/command_parser.o src/deque.o
# 	$(CC) $^ -o  bin/$@ $(CFLAGS)
# 	@rm src/*.o

src/deque.o: src/deque.c

src/main.o: src/main.c

src/command_parser.o: src/command_parser.c

clean:
	@rm src/*.o