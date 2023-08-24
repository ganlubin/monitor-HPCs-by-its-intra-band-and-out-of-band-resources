CC = g++
CFLAGS = -Wall -Wextra -pedantic -std=c++17 -O2
LDFLAGS = -lsystemd -lprocps

TARGET_DIR = ./output
TARGET = $(TARGET_DIR)/send_process_to_DBus

all: ./$(TARGET)

$(TARGET): send_process_to_DBus.cpp
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(TARGET)
