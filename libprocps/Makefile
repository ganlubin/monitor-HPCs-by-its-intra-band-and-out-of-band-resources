CC = g++
CFLAGS = -Wall -Wextra -pedantic -std=c++17
LDFLAGS = -lprocps

TARGET_DIR = output
TARGET = $(TARGET_DIR)/test

SRCS = test.cpp
.PHONY: all clean

all: $(TARGET_DIR) $(TARGET)

$(TARGET_DIR):
	mkdir -p $(TARGET_DIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(TARGET) $(OBJS)
