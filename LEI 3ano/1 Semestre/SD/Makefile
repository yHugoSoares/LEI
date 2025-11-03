# Makefile to compile all Java files into a separate `bin` directory

JAVAC=javac
SRC=$(wildcard *.java)
# Place compiled classes in project-root `bin` directory (Makefile lives in `src`)
BIN=bin

.PHONY: all run clean

all:
	mkdir -p $(BIN)
	$(JAVAC) -d $(BIN) $(SRC)

run: all
	java -cp $(BIN) BankTest

clean:
	rm -r $(BIN)/*.class	
