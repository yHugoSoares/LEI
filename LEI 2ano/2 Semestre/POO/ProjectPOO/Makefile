# Makefile for SpotifUM

# Variables
SRC_DIR = src
BIN_DIR = bin
MAIN_CLASS = main.Main
JAR_NAME = SpotifUM.jar


# Compile all Java files
compile:
	@echo "Compiling Java sources..."
	@mkdir -p $(BIN_DIR)
	@javac -d $(BIN_DIR) -sourcepath $(SRC_DIR) $(shell find $(SRC_DIR) -name "*.java")
	@echo "Compilation complete."

# Run the application
run: compile
	@echo "Starting SpotifUM..."
	@java -cp $(BIN_DIR) $(MAIN_CLASS)

# Clean compiled files and JAR
clean:
	@echo "Cleaning up..."
	@rm -r $(BIN_DIR)
	@rm $(JAR_NAME)
	@echo "Cleanup complete."

# Create executable JAR
jar: compile
	@echo "Building JAR..."
	@jar cfe $(JAR_NAME) $(MAIN_CLASS) -C $(BIN_DIR) .
	@echo "JAR created: $(JAR_NAME)"



# Help message
help:
	@echo "Usage: make [target]"
	@echo ""
	@echo "Targets:"
	@echo "  compile   Compile the Java project"
	@echo "  run       Compile and run the application"
	@echo "  clean     Remove compiled files and JAR"
	@echo "  jar       Create an executable JAR"
	@echo "  help      Display this help message"

.PHONY: compile run clean jar help