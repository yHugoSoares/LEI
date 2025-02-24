# Directories
SRC_DIR = src
BIN_DIR = bin

# Compiler
JAVAC = javac

# Default rule (does nothing)
all:
	@echo "Usage: make <filename> (without .java)"

# Rule to compile a specific Java file
%: $(SRC_DIR)/%.java
	@mkdir -p $(BIN_DIR)
	$(JAVAC) -d $(BIN_DIR) $<
	@echo "Compiled $<"
	@java -cp $(BIN_DIR) $*

# Clean up class files
clean:
	rm $(BIN_DIR)/*.class
