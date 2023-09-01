CXX = g++
CXXFLAGS = -std=c++17 -I ~/vcpkg/installed/x64-linux/include

SRC_DIR = .
OUTPUT_DIR = ./output

all: $(OUTPUT_DIR)/main

$(OUTPUT_DIR)/main: $(SRC_DIR)/main.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(OUTPUT_DIR):
	mkdir -p $@

clean:
	rm -rf $(OUTPUT_DIR)

.PHONY: all clean

