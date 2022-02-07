
.PHONY: all memory_leak clean

MAKEFLAGS := --jobs=$(shell nproc)

CC := g++
# CFLAGS := -std=c++2a -Wall -Wextra -Werror -Wno-unused-parameter
CFLAGS := -std=c++2a
CFLAGS += -I./src

HEADERS := $(shell find src/ -name *.hpp)
SOURCES := $(shell find src/ -name *.cpp)
OBJECTS := $(SOURCES:src/%.cpp=build/%.o)


all: main

main: $(OBJECTS)
	@ mkdir -p build/Animals/
	@ mkdir -p build/Objects/Foods
	@ mkdir -p build/Objects/Items
	@ $(CC) $(CFLAGS) $^ $(LFLAGS) -o $@

memory_leak: main
	@ valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./main < test_input.txt  && vim valgrind-out.txt && rm valgrind-out.txt


build/%.o: src/%.cpp src/Animals/all_animals.hpp src/Objects/all_objects.hpp $(HEADERS)
	@ mkdir -p build/Animals/
	@ mkdir -p build/Objects/Foods
	@ mkdir -p build/Objects/Items
	@ $(CC) -c $(CFLAGS) -o $@ $<

src/Animals/all_animals.hpp: src/Animals/*.cpp
	@ cd src/Animals && ./generate_all_animals_header.sh

src/Objects/all_objects.hpp: src/Objects/*/*.cpp
	@ cd src/Objects && ./generate_all_objects_header.sh


clean:
	rm -rf build/
	rm -f main
	rm -f src/Animals/all_animals.hpp
