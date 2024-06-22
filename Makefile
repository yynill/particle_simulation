CC = gcc
CFLAGS = -I/opt/homebrew/Cellar/sdl2/2.30.4/include/SDL2
LDFLAGS = -L/opt/homebrew/lib -lSDL2

SRC_DIR = src
BUILD_DIR = build

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
EXEC = particle_simulation

all: $(BUILD_DIR)/$(EXEC)

$(BUILD_DIR)/$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/$(EXEC)

.PHONY: all clean
