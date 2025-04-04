JFLAGS = -g
JC = javac
SRC = src
BIN = bin
MAIN = Main

# Automatically detect all Java source files
SOURCES = $(wildcard $(SRC)/*.java)
CLASS_FILES = $(patsubst $(SRC)/%.java,$(BIN)/%.class,$(SOURCES))

.PHONY: default classes run clean

# Default target to compile all classes
default: classes

# Rule to compile .java files into .class files in the bin directory
$(BIN)/%.class: $(SRC)/%.java
	@mkdir -p $(BIN)
	$(JC) $(JFLAGS) -d $(BIN) $<

# Compile all classes
classes: $(CLASS_FILES)

# Rule to execute the main class
run: classes
	@if [ -f $(BIN)/$(MAIN).class ]; then \
		java -cp $(BIN) $(MAIN); \
	else \
		echo "Error: Main class '$(MAIN)' not found."; \
	fi

# Clean up the bin directory
clean:
	rm -r $(BIN)/*.class