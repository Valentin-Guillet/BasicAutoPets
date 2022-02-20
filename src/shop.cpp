
#include "shop.hpp"

#include <algorithm>
#include <iostream>

#include "pet.hpp"
#include "utils.hpp"


Shop::Shop(Team* team) : team(team), turn(0), buff_attack(0), buff_life(0) { }

Shop::~Shop() {
    for (Pet* pet : pets)
        delete pet;

    for (Object* object : objects)
        delete object;
}

int Shop::get_cost_object(size_t index) const {
    if (index >= objects.size() || !objects[index])
        throw InvalidAction("[BUY_OBJECT]: no object at index " + std::to_string(index+1));
    return objects[index]->get_cost();
}

std::string Shop::get_pet_name(size_t index) const {
    if (index >= pets.size() || !pets[index])
        throw InvalidAction("[COMBINE]: no pet in shop at index " + std::to_string(index+1));
    return pets[index]->name;
}

void Shop::begin_turn() {
    turn++;
    roll();
}

void Shop::roll() {
    std::vector<Pet*> tmp_pets;
    for (size_t i=0; i<pets.size(); i++) {
        if (frozen_pets[i])
            tmp_pets.push_back(pets[i]);
        else
            delete pets[i];
    }
    pets = tmp_pets;
    frozen_pets = std::vector<bool>(pets.size(), true);

    for (size_t i=pets.size(); i<get_max_pets(); i++) {
        pets.push_back(create_pet());
        frozen_pets.push_back(false);
    }

    std::vector<Object*> tmp_objs;
    for (size_t i=0; i<objects.size(); i++) {
        if (frozen_objects[i])
            tmp_objs.push_back(objects[i]);
        else
            delete objects[i];
    }
    objects = tmp_objs;
    frozen_objects = std::vector<bool>(objects.size(), true);

    for (size_t i=objects.size(); i<get_max_objects(); i++) {
        objects.push_back(create_object());
        frozen_objects.push_back(false);
    }
}

void Shop::create_bonus_pet() {
    spdlog::debug("Creating bonus pet! ");
    if (pets.size() + objects.size() == 7) {
        spdlog::debug("No empty spot for a bonus pet !");
        return;
    }

    int tier = std::min(6, (turn + 1) / 2 + 1);
    Pet* pet = Pet::create_random_pet(team, this, tier, true);
    if (buff_attack > 0 || buff_life > 0)
        pet->buff(buff_attack, buff_life, false);
    pets.push_back(pet);
    frozen_pets.push_back(false);
}

Pet* Shop::buy_pet(size_t index) {
    check_size_pets("BUY_PET", index);

    Pet* pet = pets[index];
    pets[index] = nullptr;
    frozen_pets[index] = false;
    return pet;
}

void Shop::buy_object(size_t index, size_t index_target) {
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
    frozen_objects[index] = false;
}

void Shop::freeze_pet(size_t index) {
    check_size_pets("FREEZE_PET", index);
    frozen_pets[index] = !frozen_pets[index];
}

void Shop::freeze_object(size_t index) {
    check_size_objects("FREEZE_OBJ", index);
    frozen_objects[index] = !frozen_objects[index];
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


Pet* Shop::create_pet() {
    Pet* pet = Pet::create_random_pet(team, this, std::min(6, (turn + 1) / 2));
    if (buff_attack > 0 || buff_life > 0)
        pet->buff(buff_attack, buff_life, false);
    return pet;
}

Object* Shop::create_object() {
    Object* object = Object::create_random_object(team, this, std::min(6, (turn + 1) / 2));
    return object;
}

void Shop::check_size_pets(std::string action, size_t index) const {
    if (index >= pets.size())
        throw InvalidAction("[" + action + "]: invalid shop index " + std::to_string(index+1));
    if (!pets[index])
        throw InvalidAction("[" + action + "]: no pet left in shop at index " + std::to_string(index+1));
}

void Shop::check_size_objects(std::string action, size_t index) const {
    if (index >= objects.size())
        throw InvalidAction("[" + action + "]: invalid shop index " + std::to_string(index+1));
    if (!objects[index])
        throw InvalidAction("[" + action + "]: no object left in shop at index " + std::to_string(index+1));
}

size_t Shop::get_max_pets() const {
    if (turn < 5)
        return 3;
    else if (turn < 9)
        return 4;
    return 5;
}

size_t Shop::get_max_objects() const {
    return (turn < 3 ? 1 : 2);
}
