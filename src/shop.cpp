
#include "shop.hpp"

#include <string>

#include "animal.hpp"


Shop::Shop(Team* team) : nb_turns(0), max_animals(4), max_objects(2) {
    roll();
}

Animal* Shop::buy_animal(int index) {
    Animal* animal = animals[index];
    animals[index] = nullptr;
    return animal;
}

Object* Shop::buy_object(int index) {
    Object* object = objects[index];
    objects[index] = nullptr;
    return object;
}

void Shop::freeze_animal(int index) {

}

void Shop::freeze_object(int index) {

}

void Shop::roll() {
    for (Animal* animal : animals)
        delete animal;
    animals.clear();

    for (int i=0; i<max_animals; i++)
        animals.push_back(create_animal());
}

void Shop::draw() const {
}


Animal* Shop::create_animal() {
    Animal* animal = Animal::create_random_animal(team, this, 0);
    return animal;
}
