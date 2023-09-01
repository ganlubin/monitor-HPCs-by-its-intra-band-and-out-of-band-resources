# Makefile for compiling main.cpp

# Compiler
CXX = g++

# Compilation flags
CXXFLAGS = -std=c++17

# Source directory
SRC_DIR = ~/Desktop/Records

# Output directory
OUT_DIR = $(SRC_DIR)/output

# Executable name
EXECUTABLE = $(OUT_DIR)/main

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Object files (one for each source file)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OUT_DIR)/%.o,$(SRCS))

# Target: all (default target)
all: $(EXECUTABLE)

# Linking rule for the executable
$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilation rule for source files
$(OUT_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Create output directory if it doesn't exist
$(OUT_DIR):
	mkdir -p $(OUT_DIR)

# Target: clean
clean:
	rm -f $(EXECUTABLE)

# Target: clean-all (cleans everything including object files)
clean-all:
	rm -rf $(OUT_DIR)

