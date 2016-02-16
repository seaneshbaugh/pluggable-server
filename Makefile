CC=clang
CFLAGS=-std=c11 -Wall -Wextra -g

TARGET_NAME=pluggable-server

SOURCE_FILES=\
	src/main.c

INCLUDE_DIRECTORIES=

SYMBOLS=

all: clean default plugs

default: $(TARGET_NAME)

$(TARGET_NAME):
	mkdir -p build
	$(CC) $(CFLAGS) $(INCLUDE_DIRECTORIES) $(SYMBOLS) $(SOURCE_FILES) -o build/$(TARGET_NAME)

valgrind:
	which valgrind > /dev/null 2>&1
	if [ $$? -eq 0 ]; then valgrind --leak-check=full --show-leak-kinds=all build/$(TARGET_NAME); else echo "Valgrind not found."; fi

clean:
	rm -rf build

plugs:
	mkdir -p build/plugs
	$(CC) $(CFLAGS) -dynamiclib  src/plugs/test_plug.c -current_version 1.0 -compatibility_version 1.0 -fvisibility=hidden -o build/plugs/libTestPlug.A.dylib
