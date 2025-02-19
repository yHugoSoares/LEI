SRC_DIR = src
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)
BINS = $(SRCS:$(SRC_DIR)/%.c=$(BIN_DIR)/%)

CC = gcc
CFLAGS = -Wall -g

# Default target
all: $(BINS)

# Compile specific program
program: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/%: $(BIN_DIR)/%.o | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $<
	rm $<

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR) $(BIN_DIR)

.PHONY: all clean program

# Specific target for mycat
mycat: $(BIN_DIR)/mycat

$(BIN_DIR)/mycat: $(BIN_DIR)/mycat.o | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $<
	rm $<