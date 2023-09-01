CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17 -I ~/vcpkg/installed/x64-linux/include
LDFLAGS = -lprocps

SRC_DIR = .
OUTPUT_DIR = ./output

all: $(OUTPUT_DIR)/main

$(OUTPUT_DIR)/main: $(SRC_DIR)/main.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) $< $(LDFLAGS) -o $@

$(OUTPUT_DIR):
	mkdir -p $@

clean:
	rm -rf $(OUTPUT_DIR)

.PHONY: all clean

