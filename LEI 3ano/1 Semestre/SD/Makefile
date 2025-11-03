# Makefile to compile all Java files into a separate `bin` directory

JAVAC=javac
SRC=$(wildcard src/*.java)
# Place compiled classes in project-root `bin` directory (Makefile lives in `src`)
BIN=bin

.PHONY: all run clean

all:
	mkdir -p $(BIN)
	$(JAVAC) -d $(BIN) $(SRC)

# compile a single Java source from src/ to bin/
$(BIN)/%.class: src/%.java | $(BIN)
	$(JAVAC) -d $(BIN) $<

%: $(BIN)/%.class

$(BIN):
	mkdir -p $(BIN)

run: all
	java -cp $(BIN) BankTest

clean:
	rm -r $(BIN)/*.class	
