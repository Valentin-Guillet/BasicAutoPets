
#include "shop.hpp"

#include <iostream>
#include <string>

#include "pet.hpp"
#include "utils.hpp"


Shop::Shop(Team* team) : team(team), turns(0) { }

Shop::~Shop() {
    for (Pet* pet : pets)
        delete pet;

    for (Object* object : objects)
        delete object;
}

int Shop::get_cost_object(int index) const {
    if (index >= objects.size() || !objects[index])
        throw InvalidAction("[BUY_OBJECT]: no object at index " + std::to_string(index));
    return objects[index]->get_cost();
}

void Shop::begin_turn() {
    turns++;
    roll();
}

Pet* Shop::buy_pet(int index) {
    Pet* pet = pets[index];
    if (!pet)
        throw InvalidAction("[BUY_PET]: no animal left in store at index " + std::to_string(index));

    pets[index] = nullptr;
    return pet;
}

void Shop::buy_object(int index, int index_target) {
    if (index >= objects.size() || !objects[index])
        throw InvalidAction("[BUY_OBJECT]: no object at index " + std::to_string(index));

    Object* object = objects[index];
    if (object->type == ObjType::FOOD) {
        object->on_buy(index_target);
        delete object;
    } else {
        team->equip_item(index_target, object);
    }
    objects[index] = nullptr;
}

void Shop::freeze_pet(int index) {

}

void Shop::freeze_object(int index) {

}

void Shop::roll() {
    for (Pet* pet : pets)
        delete pet;
    pets.clear();

    for (int i=0; i<get_max_pets(); i++)
        pets.push_back(create_pet());

    for (Object* object : objects)
        delete object;
    objects.clear();

    for (int i=0; i<get_max_objects(); i++)
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

int Shop::get_max_pets() const {
    if (turns < 5)
        return 3;
    else if (turns < 9)
        return 4;
    return 5;
}

int Shop::get_max_objects() const {
    if (turns < 3)
        return 1;
    return 2;
}
