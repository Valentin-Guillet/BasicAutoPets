
.PHONY: all memory_leak clean

MAKEFLAGS := --jobs=$(shell nproc)

CC := g++
CFLAGS := -std=c++2a -Wall -Wextra -Werror -Wno-unused-parameter
CFLAGS += -I./src
LFLAGS := -lncursesw

HEADERS := $(shell find src/ -name *.hpp)
SOURCES := $(shell find src/ -name *.cpp ! -name main_*.cpp)
OBJECTS := build/Pets/all_pets.o build/Objects/all_objects.o
OBJECTS += $(SOURCES:src/%.cpp=build/%.o)

AGENT_OBJS := build/main_agents.o $(filter-out build/main.o, $(OBJECTS))

TEST_OBJ := $(filter-out build/main.o, $(OBJECTS))
TEST_OBJ += test/main_test_battles.cpp

PETS_HEADERS := $(shell find src/Pets/ -name *.hpp)


all: main

main: $(OBJECTS)
	$(CC) $(CFLAGS) $^ $(LFLAGS) -o $@

agent: $(AGENT_OBJS)
	$(CC) $(CFLAGS) $^ $(LFLAGS) -o $@


memory_leak: main
	@ valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./main -c && vim valgrind-out.txt && rm valgrind-out.txt

memory_leak_input: main
	@ valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./main -c < test_input.txt && vim valgrind-out.txt && rm valgrind-out.txt


test_battles: test/main_test

test/main_test: $(TEST_OBJ)
	$(CC) $(CFLAGS) $^ $(LFLAGS) $@


build/%.o: src/%.cpp $(HEADERS)
	@ mkdir -p build/Pets/
	@ mkdir -p build/Objects/Foods
	@ mkdir -p build/Objects/Items
	@ mkdir -p build/UI/
	@ mkdir -p build/Interface/
	@ mkdir -p build/Interface/Agents
	$(CC) -c $(CFLAGS) -o $@ $<


# Dependency is here to update file each time a pet file is modified
src/Pets/all_pets.cpp: $(PETS_HEADERS)
	cd src/Pets && ./generate_all_pets_header.sh

src/Objects/all_objects.cpp: src/Objects/*/*.hpp
	cd src/Objects && ./generate_all_objects_header.sh


clean:
	rm -rf build/
	rm -f main
	rm -f src/Pets/all_pets.*
	rm -f src/Objects/all_objects.*
