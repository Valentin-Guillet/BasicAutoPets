
#include "shop.hpp"

#include <iostream>
#include <string>

#include "animal.hpp"


Shop::Shop(Team* team) : team(team), nb_turns(0), max_animals(4), max_objects(2) { }

Shop::~Shop() {
    for (Animal* animal : animals)
        delete animal;

    for (Object* object : objects)
        delete object;
}

Animal* Shop::buy_animal(int index) {
    Animal* animal = animals[index];
    animals[index] = nullptr;
    return animal;
}

Object* Shop::buy_object(int index, int index_target) {
    Object* object = objects[index];
    objects[index] = nullptr;

    if (object->type == ObjType::FOOD) {
        object->on_buy(index_target);
        delete object;
        return nullptr;
    }
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

    for (Object* object : objects)
        delete object;
    objects.clear();

    for (int i=0; i<max_objects; i++)
        objects.push_back(create_object());
}

void Shop::draw() const {
    std::cout << "Animals: \n";
    for (size_t i=0; i<animals.size(); i++) {
        std::cout << "  " << i+1 << ". ";
        if (animals[i])
            std::cout << *animals[i];
        else
            std::cout << "Empty";
        std::cout << std::endl;
    }

    std::cout << "Objects: \n";
    for (size_t i=0; i<objects.size(); i++) {
        std::cout << "  " << i+1 << ". ";
        if (objects[i])
            std::cout << *objects[i];
        else
            std::cout << "Empty";
        std::cout << std::endl;
    }
}


Animal* Shop::create_animal() {
    Animal* animal = Animal::create_random_animal(team, this, 1);
    return animal;
}

Object* Shop::create_object() {
    Object* object = Object::create_random_object(team, this, 1);
    return object;
}
