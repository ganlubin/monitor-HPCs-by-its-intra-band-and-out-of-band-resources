CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17
SRC_DIR = src
OUTPUT_DIR = output

all: sender getter

sender: $(SRC_DIR)/sender.cpp
	mkdir -p $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -o $(OUTPUT_DIR)/sender $(SRC_DIR)/sender.cpp

getter: $(SRC_DIR)/getter.cpp
	mkdir -p $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -o $(OUTPUT_DIR)/getter $(SRC_DIR)/getter.cpp

clean:
	rm -rf $(OUTPUT_DIR)

.PHONY: all clean

