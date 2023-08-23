CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = `pkg-config --cflags --libs libsystemd`
OUTPUT_DIR = output

.PHONY: all clean

all: ./$(OUTPUT_DIR)/signalListener ./$(OUTPUT_DIR)/signalSender ./$(OUTPUT_DIR)/sleepSignalListener

$(OUTPUT_DIR)/signalListener: signalListener.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

$(OUTPUT_DIR)/signalSender: signalSender.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

$(OUTPUT_DIR)/sleepSignalListener: sleepSignalListener.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -rf $(OUTPUT_DIR)/*
