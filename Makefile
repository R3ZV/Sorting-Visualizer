CC := g++
CFLAGS := -Wall -Wextra
LDFLAGS := -lraylib
INCLUDES := -I/usr/local/include
LIBRARIES := -L/usr/local/lib

SRC_DIR := src
BUILD_DIR := build
EXECUTABLE := main
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

.PHONY: all run clean

all: run

run: $(BUILD_DIR) $(EXECUTABLE)
	@./$(EXECUTABLE)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(EXECUTABLE): $(OBJECTS)
	@$(CC) $(CFLAGS) $(LIBRARIES) -o $@ $^ $(LDFLAGS)

clean:
	@rm -rf $(BUILD_DIR) $(EXECUTABLE)
