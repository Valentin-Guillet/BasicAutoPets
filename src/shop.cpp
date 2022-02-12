
#include "shop.hpp"

#include <iostream>

#include "pet.hpp"
#include "utils.hpp"


Shop::Shop(Team* team) : team(team), turns(0), buff_life(0), buff_attack(0) { }

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
    check_size_pets("BUY_PET", index);

    Pet* pet = pets[index];
    pets[index] = nullptr;
    return pet;
}

void Shop::buy_object(int index, int index_target) {
    check_size_objects("BUY_OBJECT", index);

    Object* object = objects[index];
    if (object->type == ObjType::FOOD) {
        team->give_object(index_target, object);
        object->on_buy(index_target);
        delete object;
    } else {
        team->give_object(index_target, object);
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

void Shop::upgrade(int attack, int life, bool tmp) {
    spdlog::debug("Upgrading shop by +{}/+{}", attack, life);
    for (Pet* pet : pets) {
        if (!pet) continue;
        pet->buff(attack, life, false);
    }
    if (!tmp) {
        buff_attack += attack;
        buff_life += life;
    }
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
    if (buff_attack > 0 || buff_life > 0)
        pet->buff(buff_attack, buff_life, false);
    return pet;
}

Object* Shop::create_object() {
    Object* object = Object::create_random_object(team, this, 1);
    return object;
}

void Shop::check_size_pets(std::string action, int index) const {
    if (index >= pets.size())
        throw InvalidAction("[" + action + "]: invalid shop index " + std::to_string(index));
    if (!pets[index])
        throw InvalidAction("[" + action + "]: no pet left in shop at index " + std::to_string(index));
}

void Shop::check_size_objects(std::string action, int index) const {
    if (index >= objects.size())
        throw InvalidAction("[" + action + "]: invalid shop index " + std::to_string(index));
    if (!objects[index])
        throw InvalidAction("[" + action + "]: no object left in shop at index " + std::to_string(index));
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
