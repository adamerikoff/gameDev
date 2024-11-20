# File names
ASM_FILE = clearmem.asm
OBJ_FILE = build/clearmem.o
NES_FILE = build/clearmem.nes

# Tools
CA65 = ca65
LD65 = ld65
FCEUX = fceux

# NES Configuration file
NES_CFG = nes.cfg

# Compilation flags
CA65_FLAGS = 
LD65_FLAGS = -C $(NES_CFG)

# Build directory
BUILD_DIR = build

# Ensure build directory exists
$(shell mkdir -p $(BUILD_DIR))

# Default target
all: $(NES_FILE)

# Rule to assemble the .asm file into an object file
$(OBJ_FILE): $(ASM_FILE)
	$(CA65) $(CA65_FLAGS) $(ASM_FILE) -o $(OBJ_FILE)

# Rule to link the object file into a .nes file
$(NES_FILE): $(OBJ_FILE)
	$(LD65) $(LD65_FLAGS) $(OBJ_FILE) -o $(NES_FILE)

# Rule to run the NES file with fceux
run: $(NES_FILE)
	$(FCEUX) $(NES_FILE)

# Clean up generated files
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run clean
