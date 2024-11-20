# Define directories and files
BUILD_DIR := ./build
SRC_DIR := ./src
LUA_SRC_DIR := ./lib/lua/src
MAIN_FILE := $(SRC_DIR)/main.c
OUTPUT_FILE := $(BUILD_DIR)/program

# Compilation flags
CFLAGS := -Wall -Wextra -std=c2x -O2

# Lua source files (find all .c files in the Lua source directory)
LUA_SRC_FILES := $(wildcard $(LUA_SRC_DIR)/*.c)

# Create build directory
$(BUILD_DIR):
	@echo "Creating build directory..."
	@mkdir -p $(BUILD_DIR)

# Default target: Compile and run the program
all: $(OUTPUT_FILE)
	@echo "Running the program..."
	@$(OUTPUT_FILE)

# Link the object files to create the final executable
$(OUTPUT_FILE): $(MAIN_FILE) $(LUA_SRC_FILES) | $(BUILD_DIR)
	@echo "Compiling $(MAIN_FILE) with Lua sources..."
	@gcc $(CFLAGS) $(LUA_SRC_FILES) $(MAIN_FILE) -o $(OUTPUT_FILE)

# Clean the build directory
clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILD_DIR)

.PHONY: all clean
