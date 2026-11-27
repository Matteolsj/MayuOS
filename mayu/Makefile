CC := clang

CPPFLAGS := -Isrc

CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -g -O0

BUILD_DIR := build

MAYUC := $(BUILD_DIR)/mayuc
TEST_RUNNER := $(BUILD_DIR)/mayu_tests

MAYU_SOURCES := $(wildcard src/*.c)
MAYU_HEADERS := $(wildcard src/*.h)

TEST_SOURCES := $(wildcard tests/*.c)
LIB_SOURCES := $(filter-out src/main.c,$(MAYU_SOURCES))

.PHONY: all run test clean

all: $(MAYUC)

$(MAYUC): $(MAYU_SOURCES) $(MAYU_HEADERS) | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(MAYU_SOURCES) -o $@

$(TEST_RUNNER): $(TEST_SOURCES) $(LIB_SOURCES) $(MAYU_HEADERS) | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(TEST_SOURCES) $(LIB_SOURCES) -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run: all
	./$(MAYUC)

test: $(TEST_RUNNER)
	./$(TEST_RUNNER)

clean:
	rm -rf $(BUILD_DIR)