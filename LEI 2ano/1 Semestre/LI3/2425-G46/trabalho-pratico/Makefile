# Compiler and flags
CC = gcc
INCLUDE_DIRS = $(shell find $(INCLUDE_DIR) -type d)
CFLAGS = -Wall $(patsubst %, -I%, $(INCLUDE_DIRS)) `pkg-config --cflags glib-2.0` -fopenmp
LDFLAGS = `pkg-config --libs glib-2.0` -fopenmp -lm -lncurses lib/recomendador-linux-x86_64.o

# Directories
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include
RESULT_DIR = resultados

# Source files
SRC_FILES = \
	$(SRC_DIR)/utils/parser.c \
	$(SRC_DIR)/utils/utils.c \
	$(SRC_DIR)/utils/data_container.c \
	$(SRC_DIR)/utils/string_pool.c \
	$(SRC_DIR)/utils/hashing_algorithms.c \
	$(SRC_DIR)/database/entities/artist.c \
	$(SRC_DIR)/database/entities/music.c \
	$(SRC_DIR)/database/entities/user.c \
	$(SRC_DIR)/database/entities/album.c \
	$(SRC_DIR)/database/entities/history.c \
	$(SRC_DIR)/database/entities/validation/fields_validation.c \
	$(SRC_DIR)/database/entities/validation/syntatic_validation.c \
	$(SRC_DIR)/database/entities/validation/logic_validation.c \
	$(SRC_DIR)/database/repositories/repository_artist.c \
	$(SRC_DIR)/database/repositories/repository_music.c \
	$(SRC_DIR)/database/repositories/repository_user.c \
	$(SRC_DIR)/database/repositories/repository_album.c \
	$(SRC_DIR)/database/repositories/repository_history.c \
	$(SRC_DIR)/database/repositories/repository_data.c \
	$(SRC_DIR)/database/data_operations.c \
	$(SRC_DIR)/database/preprocessing/preprocess.c \
	$(SRC_DIR)/database/preprocessing/histories_preprocess.c \
	$(SRC_DIR)/database/preprocessing/musics_preprocess.c \
	$(SRC_DIR)/database/preprocessing/users_preprocess.c \
	$(SRC_DIR)/database/database.c \
	$(SRC_DIR)/io/load.c \
	$(SRC_DIR)/io/output.c \
	$(SRC_DIR)/io/interface.c \
	$(SRC_DIR)/queries/input_validation.c \
	$(SRC_DIR)/queries/interpreter.c \
	$(SRC_DIR)/queries/query1.c \
	$(SRC_DIR)/queries/query2.c \
	$(SRC_DIR)/queries/query3.c \
	$(SRC_DIR)/queries/query4.c \
	$(SRC_DIR)/queries/query5.c \
	$(SRC_DIR)/queries/query6.c \
	$(SRC_DIR)/modes/batch.c \
	$(SRC_DIR)/modes/interactive.c \
	$(SRC_DIR)/test/test.c

# Object files
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))
OBJ_FILES_PRINCIPAL = $(filter-out $(BUILD_DIR)/modes/interactive.o $(BUILD_DIR)/test/test.o, $(OBJ_FILES))
OBJ_FILES_INTERATIVO = $(filter-out $(BUILD_DIR)/modes/batch.o $(BUILD_DIR)/test/test.o, $(OBJ_FILES))
OBJ_FILES_TESTES = $(filter-out $(BUILD_DIR)/modes/batch.o $(BUILD_DIR)/modes/interactive.o, $(OBJ_FILES)) \
	$(BUILD_DIR)/test/interpreter_timed.o \
	$(BUILD_DIR)/test/query_metrics.o

# Executables
TARGET_PRINCIPAL = programa-principal
TARGET_INTERATIVO = programa-interativo
TARGET_TESTES = programa-testes

# Build rules
all: $(TARGET_PRINCIPAL) $(TARGET_TESTES) $(TARGET_INTERATIVO)

$(TARGET_PRINCIPAL): $(OBJ_FILES_PRINCIPAL)
	$(CC) $(OBJ_FILES_PRINCIPAL) -o $@ $(LDFLAGS)

$(TARGET_INTERATIVO): $(OBJ_FILES_INTERATIVO)
	$(CC) $(OBJ_FILES_INTERATIVO) -o $@ $(LDFLAGS)

$(TARGET_TESTES): $(OBJ_FILES_TESTES)
	$(CC) $(OBJ_FILES_TESTES) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

interativo: src/modes/interactive.c
	$(CC) $(CFLAGS) src/modes/interactive.c -o $(TARGET_INTERATIVO) $(LDFLAGS)

valgrind: $(TARGET_PRINCIPAL)
	@echo "[VALGRIND] Running Valgrind memcheck on $(TARGET_PRINCIPAL)."
	valgrind --leak-check=full --track-origins=yes --log-file="log.txt" ./$(TARGET_PRINCIPAL) files/fase2/small/dataset/com_erros files/fase2/small/inputs-small.txt

valgrind-testes: $(TARGET_PRINCIPAL)
	@echo "[VALGRIND] Running Valgrind memcheck on $(TARGET_TESTES)."
	valgrind --leak-check=full --track-origins=yes ./$(TARGET_TESTES) files/fase2-small/dataset/sem_erros files/fase2-small/inputs-small.txt resultados-esperados

clean:
	@echo "[CLEAN] Cleaning build directory."
	rm -rf $(BUILD_DIR) $(TARGET_PRINCIPAL) $(TARGET_TESTES)
	@echo "[CLEAN] Cleaning resultados directory."
	rm -rf $(RESULT_DIR)/*

.PHONY: all clean valgrind
