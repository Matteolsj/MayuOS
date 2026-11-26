CC := clang

CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -g -O0

BUILD_DIR := build
TARGET := $(BUILD_DIR)/mayuc

SOURCES := $(wildcard src/*.c)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SOURCES) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run: all
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)