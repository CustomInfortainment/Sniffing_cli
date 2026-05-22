CC = gcc
CFLAGS = -Iinclude

BUILD_DIR = build

main.out : $(BUILD_DIR)/main.o $(BUILD_DIR)/file.o $(BUILD_DIR)/sniffing.o $(BUILD_DIR)/utility.o $(BUILD_DIR)/handler.o
	mkdir -p $(BUILD_DIR)
	$(CC) -o $(BUILD_DIR)/main.out $(BUILD_DIR)/main.o $(BUILD_DIR)/file.o $(BUILD_DIR)/sniffing.o $(BUILD_DIR)/utility.o $(BUILD_DIR)/handler.o

$(BUILD_DIR)/main.o : src/main.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/main.o src/main.c

$(BUILD_DIR)/file.o : include/file.h src/file.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/file.o src/file.c

$(BUILD_DIR)/handler.o : include/handler.h src/handler.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/handler.o src/handler.c

$(BUILD_DIR)/sniffing.o : include/sniffing.h src/sniffing.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/sniffing.o src/sniffing.c

$(BUILD_DIR)/utility.o : include/utility.h src/utility.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/utility.o src/utility.c

clean:
	rm -rf $(BUILD_DIR)