
.PHONY: all clean

CC := g++
# CFLAGS := -std=c++2a -Wall -Wextra -Werror -Wno-unused-parameter
CFLAGS := -std=c++2a
CFLAGS += -I./src

HEADERS := $(shell find src/ -name *.hpp)
SOURCES := $(shell find src/ -name *.cpp)
OBJECTS := $(SOURCES:src/%.cpp=build/%.o)


all: main

main: $(OBJECTS)
	@ mkdir -p build/
	@ mkdir -p build/Animals/
	@ $(CC) $(CFLAGS) $^ $(LFLAGS) -o $@

build/%.o: src/%.cpp $(HEADERS)
	@ mkdir -p build/
	@ mkdir -p build/Animals/
	@ $(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -rf build/
	rm main
