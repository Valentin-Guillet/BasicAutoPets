
#include "shop.hpp"

#include <algorithm>
#include <iostream>

#include "pet.hpp"
#include "utils.hpp"


Shop* Shop::unserialize(Team* team, std::string shop_str) {
    Shop* new_shop = new Shop(team);

    size_t index = shop_str.find(' ');
    new_shop->turn = std::stoi(shop_str.substr(0, index));
    shop_str = shop_str.substr(index);

    index = shop_str.find('/');
    std::string pets_str = shop_str.substr(0, index-1);
    shop_str = shop_str.substr(index+2);
    while (!pets_str.empty()) {
        index = pets_str.find(')');
        std::string pet_str = pets_str.substr(2, index-2);
        pets_str = pets_str.substr(index+1);

        if (pet_str == "Empty")
            continue;
        new_shop->pets.push_back(Pet::unserialize(team, pet_str));
    }

    index = shop_str.find('/');
    std::string frozen_pets_str = shop_str.substr(0, index-1);
    shop_str = shop_str.substr(index+2);
    for (size_t i=0; i<new_shop->pets.size(); i++)
        new_shop->frozen_pets.push_back(frozen_pets_str[i] == '1');

    index = shop_str.find('/');
    std::string objects_str = shop_str.substr(0, index-1);
    shop_str = shop_str.substr(index+2);
    while (!objects_str.empty()) {
        index = objects_str.find(' ');
        std::string obj_str;
        if (index == std::string::npos) {
            obj_str = objects_str;
            objects_str.clear();
        } else {
            obj_str = objects_str.substr(0, index);
            objects_str = objects_str.substr(index+1);
        }
        if (obj_str == "Empty")
            continue;
        new_shop->objects.push_back(Object::create_new_object(obj_str, team, new_shop));
    }

    index = shop_str.find('/');
    std::string frozen_objs_str = shop_str.substr(0, index-1);
    shop_str = shop_str.substr(index+2);
    for (size_t i=0; i<new_shop->objects.size(); i++)
        new_shop->frozen_objects.push_back(frozen_objs_str[i] == '1');

    index = shop_str.find(' ');
    new_shop->attack_buff = std::stoi(shop_str.substr(0, index));
    new_shop->life_buff = std::stoi(shop_str.substr(index+1));

    return new_shop;
}

size_t Shop::get_max_pets(int turn) {
    if (turn < 5)
        return 3;
    else if (turn < 9)
        return 4;
    return 5;
}

size_t Shop::get_max_objects(int turn) {
    return (turn < 3 ? 1 : 2);
}

Shop::Shop(Team* team) : team(team), turn(0), attack_buff(0), life_buff(0) { }

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

    for (size_t i=pets.size(); i<get_max_pets(turn); i++) {
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

    size_t nb_to_add = std::min(get_max_objects(turn), 7 - pets.size() - objects.size());
    for (size_t i=objects.size(); i<nb_to_add; i++) {
        objects.push_back(create_object());
        frozen_objects.push_back(false);
    }
}

void Shop::create_bonus_pet() {
    utils::vector_logs.push_back("Creating bonus pet !");
    if (pets.size() + objects.size() == 7) {
        utils::vector_logs.push_back("No empty spot for a bonus pet !");
        return;
    }

    int tier = std::min(6, (turn + 1) / 2 + 1);
    Pet* pet = Pet::create_random_pet(team, this, tier, true);
    if (attack_buff > 0 || life_buff > 0)
        pet->buff(attack_buff, life_buff, false);

    pets.push_back(pet);
    frozen_pets.push_back(false);
}

Pet* Shop::buy_pet(size_t index) {
    check_size_pets("BUY_PET", index);

    Pet* pet = pets[index];
    pets.erase(pets.begin() + index);
    frozen_pets.erase(frozen_pets.begin() + index);
    return pet;
}

void Shop::buy_object(size_t index, size_t index_target) {
    check_size_objects("BUY_OBJECT", index);

    Object* object = objects[index];
    if (object->type == ObjType::FOOD) {
        object->on_buy(index_target);
        team->give_object(index_target, object);
        delete object;
    } else {
        team->give_object(index_target, object);
    }
    objects.erase(objects.begin() + index);
    frozen_objects.erase(frozen_objects.begin() + index);
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
    utils::vector_logs.push_back("Upgrading shop by +" + std::to_string(attack) + "/+" + std::to_string(life));
    for (Pet* pet : pets) {
        if (pet)
            pet->buff(attack, life, false);
    }
    if (!tmp) {
        attack_buff += attack;
        life_buff += life;
    }
}

std::string Shop::serialize() const {
    std::string shop_str;

    for (Pet* pet : pets) {
        if (pet)
            shop_str += pet->serialize() + " ";
        else
            shop_str += "(Empty) ";
    }

    shop_str += "/ ";
    for (bool frozen : frozen_pets)
        shop_str += (frozen ? "1" : "0");

    shop_str += " / ";
    for (Object* obj : objects) {
        if (obj)
            shop_str += obj->name + " ";
        else
            shop_str += "Empty ";
    }

    shop_str += "/ ";
    for (bool frozen : frozen_objects)
        shop_str += (frozen ? "1" : "0");

    shop_str += " / " + std::to_string(attack_buff) + " " + std::to_string(life_buff);
    return shop_str;
}


Pet* Shop::create_pet() {
    Pet* pet = Pet::create_random_pet(team, this, std::min(6, (turn + 1) / 2));
    if (attack_buff > 0 || life_buff > 0)
        pet->buff(attack_buff, life_buff, false);
    return pet;
}

Object* Shop::create_object() {
    Object* object = Object::create_random_object(team, this, std::min(6, (turn + 1) / 2));
    return object;
}

void Shop::check_size_pets(std::string action, size_t index) const {
    if (index >= pets.size())
        throw InvalidAction("[" + action + "]: invalid shop index " + std::to_string(index+1));
}

void Shop::check_size_objects(std::string action, size_t index) const {
    if (index >= objects.size())
        throw InvalidAction("[" + action + "]: invalid shop index " + std::to_string(index+1));
}
