
.PHONY: all memory_leak clean

MAKEFLAGS := --jobs=$(shell nproc)

CC := g++
CFLAGS := -std=c++2a -Wall -Wextra -Werror -Wno-unused-parameter
CFLAGS += -I./src
LFLAGS := -lncursesw

HEADERS := $(shell find src/ -name *.hpp ! -name user_interface.hpp)
SOURCES := $(shell find src/ -name *.cpp)
OBJECTS := $(SOURCES:src/%.cpp=build/%.o)

TEST_OBJ := $(filter-out build/main.o, $(OBJECTS))
TEST_OBJ += test/main_test_battles.cpp

PETS_SOURCES := $(shell find src/Pets/ -name *.cpp ! -name all_pets.cpp)


all: main

main: $(OBJECTS)
	@ mkdir -p build/Pets/
	@ mkdir -p build/Objects/Foods
	@ mkdir -p build/Objects/Items
	$(CC) $(CFLAGS) $^ $(LFLAGS) -o $@

memory_leak: main
	@ valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./main -c && vim valgrind-out.txt && rm valgrind-out.txt

memory_leak_input: main
	@ valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./main -c < test_input.txt && vim valgrind-out.txt && rm valgrind-out.txt

test_battles: test/main_test

test/main_test: $(TEST_OBJ)
	$(CC) $(CFLAGS) $^ $(LFLAGS) -o test/main_test

build/user_interface.o: src/user_interface.cpp src/user_interface.hpp $(HEADERS)
	$(CC) -c $(CFLAGS) -o $@ $<

build/%.o: src/%.cpp $(HEADERS)
	@ mkdir -p build/Pets/
	@ mkdir -p build/Objects/Foods
	@ mkdir -p build/Objects/Items
	@ mkdir -p build/UI/
	@ mkdir -p build/Interface/
	$(CC) -c $(CFLAGS) -o $@ $<

src/Pets/all_pets.hpp: $(PETS_SOURCES)
	cd src/Pets && ./generate_all_pets_header.sh

src/Objects/all_objects.hpp: src/Objects/*/*.cpp
	cd src/Objects && ./generate_all_objects_header.sh


clean:
	rm -rf build/
	rm -f main
	rm -f src/Pets/all_pets.*
	rm -f src/Objects/all_objects.*
