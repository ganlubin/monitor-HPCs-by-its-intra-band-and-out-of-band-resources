CC = g++
CFLAGS = -Wall -Wextra -pedantic -std=c++17
LDFLAGS = -lsystemd -lprocps

TARGET_DIR = ./output
TARGET = $(TARGET_DIR)/send_process_to_DBus
TARGET2 = $(TARGET_DIR)/proc_getter

all: $(TARGET) $(TARGET2)

$(TARGET): send_process_to_DBus.cpp
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

$(TARGET2): proc_getter.cpp
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(TARGET) $(TARGET2)
