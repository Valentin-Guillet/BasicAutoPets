
#include "shop.hpp"

#include <iostream>
#include <string>

#include "pet.hpp"


Shop::Shop(Team* team) : team(team), nb_turns(0), max_pets(4), max_objects(2) { }

Shop::~Shop() {
    for (Pet* pet : pets)
        delete pet;

    for (Object* object : objects)
        delete object;
}

Pet* Shop::buy_pet(int index) {
    Pet* pet = pets[index];
    pets[index] = nullptr;
    return pet;
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

void Shop::freeze_pet(int index) {

}

void Shop::freeze_object(int index) {

}

void Shop::roll() {
    for (Pet* pet : pets)
        delete pet;
    pets.clear();

    for (int i=0; i<max_pets; i++)
        pets.push_back(create_pet());

    for (Object* object : objects)
        delete object;
    objects.clear();

    for (int i=0; i<max_objects; i++)
        objects.push_back(create_object());
}

void Shop::draw() const {
    std::cout << "Pets: \n";
    for (size_t i=0; i<pets.size(); i++) {
        std::cout << "  " << i+1 << ". ";
        if (pets[i])
            std::cout << *pets[i];
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


Pet* Shop::create_pet() {
    Pet* pet = Pet::create_random_pet(team, this, 1);
    return pet;
}

Object* Shop::create_object() {
    Object* object = Object::create_random_object(team, this, 1);
    return object;
}
