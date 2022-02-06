
#include "shop.hpp"

#include <iostream>
#include <string>

#include "animal.hpp"


Shop::Shop(Team* team) : team(team), nb_turns(0), max_animals(4), max_items(2) { }

Shop::~Shop() {
    for (Animal* animal : animals)
        delete animal;
}

Animal* Shop::buy_animal(int index) {
    Animal* animal = animals[index];
    animals[index] = nullptr;
    return animal;
}

Item* Shop::buy_item(int index) {
    Item* item = items[index];
    items[index] = nullptr;
    return item;
}

void Shop::freeze_animal(int index) {

}

void Shop::freeze_item(int index) {

}

void Shop::roll() {

    for (Animal* animal : animals)
        delete animal;
    animals.clear();

    for (int i=0; i<max_animals; i++)
        animals.push_back(create_animal());
}

void Shop::draw() const {
    for (size_t i=0; i<animals.size(); i++) {
        std::cout << i+1 << ". ";
        if (animals[i])
            std::cout << *animals[i];
        else
            std::cout << "Empty";
        std::cout << std::endl;
    }
}


Animal* Shop::create_animal() {
    Animal* animal = Animal::create_random_animal(team, this, 1);
    return animal;
}
