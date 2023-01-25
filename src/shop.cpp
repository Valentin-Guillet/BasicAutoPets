
#include "shop.hpp"

#include <algorithm>

#include "pet.hpp"
#include "utils.hpp"


Shop* Shop::unserialize(Team* team, std::string shop_str) {
    Shop* new_shop = new Shop(team);

    size_t index = shop_str.find(' ');
    new_shop->m_turn = std::stoi(shop_str.substr(0, index));
    shop_str = shop_str.substr(index);

    index = shop_str.find('/');
    std::string pets_str = shop_str.substr(0, index-1);
    shop_str = shop_str.substr(index+2);
    while (!pets_str.empty()) {
        index = pets_str.find(')');
        std::string pet_str = pets_str.substr(2, index-2);
        pets_str = pets_str.substr(index+1);
        new_shop->m_pets.push_back(Pet::unserialize(team, new_shop, pet_str));
    }

    index = shop_str.find('/');
    std::string frozen_pets_str = shop_str.substr(0, index-1);
    shop_str = shop_str.substr(index+2);
    for (size_t i=0; i<new_shop->m_pets.size(); i++)
        new_shop->m_frozen_pets.push_back(frozen_pets_str[i] == '1');

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
        new_shop->m_objects.push_back(Object::create_new_object(obj_str, team, new_shop));
    }

    index = shop_str.find('/');
    std::string frozen_objs_str = shop_str.substr(0, index-1);
    shop_str = shop_str.substr(index+2);
    for (size_t i=0; i<new_shop->m_objects.size(); i++)
        new_shop->m_frozen_objects.push_back(frozen_objs_str[i] == '1');

    index = shop_str.find(' ');
    new_shop->m_attack_buff = std::stoi(shop_str.substr(0, index));
    new_shop->m_life_buff = std::stoi(shop_str.substr(index+1));

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

Shop::Shop(Team* team) : m_team(team), m_turn(0), m_attack_buff(0), m_life_buff(0) { }

Shop::~Shop() {
    for (Pet* pet : m_pets)
        delete pet;

    for (Object* object : m_objects)
        delete object;
}

int Shop::get_cost_object(size_t index) const {
    if (index >= m_objects.size())
        throw InvalidAction("[BUY_OBJECT]: no object at index " + std::to_string(index+1));
    return m_objects[index]->get_cost();
}

std::string Shop::get_pet_name(size_t index) const {
    if (index >= m_pets.size())
        throw InvalidAction("[COMBINE]: no pet in shop at index " + std::to_string(index+1));
    return m_pets[index]->m_name;
}

void Shop::begin_turn() {
    m_turn++;
    roll();
}

void Shop::roll() {
    std::vector<Pet*> tmp_pets;
    for (size_t i=0; i<m_pets.size(); i++) {
        if (m_frozen_pets[i])
            tmp_pets.push_back(m_pets[i]);
        else
            delete m_pets[i];
    }
    m_pets = tmp_pets;
    m_frozen_pets = std::vector<bool>(m_pets.size(), true);

    for (size_t i=m_pets.size(); i<get_max_pets(m_turn); i++) {
        m_pets.push_back(create_pet());
        m_frozen_pets.push_back(false);
    }

    std::vector<Object*> tmp_objs;
    for (size_t i=0; i<m_objects.size(); i++) {
        if (m_frozen_objects[i])
            tmp_objs.push_back(m_objects[i]);
        else
            delete m_objects[i];
    }
    m_objects = tmp_objs;
    m_frozen_objects = std::vector<bool>(m_objects.size(), true);

    size_t nb_to_add = std::min(get_max_objects(m_turn), 7 - m_pets.size() - m_objects.size());
    for (size_t i=0; i<nb_to_add; i++) {
        m_objects.push_back(create_object());
        m_frozen_objects.push_back(false);
    }
}

void Shop::create_bonus_pet() {
    utils::vector_logs.push_back("Creating bonus pet !");
    if (m_pets.size() + m_objects.size() == 7) {
        utils::vector_logs.push_back("No empty spot for a bonus pet !");
        return;
    }

    int tier = std::min(6, (m_turn + 1) / 2 + 1);
    Pet* pet = Pet::create_random_pet(m_team, this, tier, true);
    if (m_attack_buff > 0 || m_life_buff > 0)
        pet->buff(m_attack_buff, m_life_buff, false);

    m_pets.push_back(pet);
    m_frozen_pets.push_back(false);
}

Pet* Shop::buy_pet(size_t index) {
    check_size_pets("BUY_PET", index);

    Pet* pet = m_pets[index];
    m_pets.erase(m_pets.begin() + index);
    m_frozen_pets.erase(m_frozen_pets.begin() + index);
    return pet;
}

void Shop::buy_object(size_t index, size_t index_target) {
    check_size_objects("BUY_OBJECT", index);

    Object* object = m_objects[index];
    if (object->m_type == ObjType::FOOD) {
        object->on_buy(index_target);
        m_team->give_object(index_target, object);
        delete object;
    } else {
        m_team->give_object(index_target, object);
    }
    m_objects.erase(m_objects.begin() + index);
    m_frozen_objects.erase(m_frozen_objects.begin() + index);
}

void Shop::freeze_pet(size_t index) {
    check_size_pets("FREEZE_PET", index);
    m_frozen_pets[index] = !m_frozen_pets[index];
}

void Shop::freeze_object(size_t index) {
    check_size_objects("FREEZE_OBJ", index);
    m_frozen_objects[index] = !m_frozen_objects[index];
}

void Shop::upgrade(int attack, int life, bool tmp) {
    utils::vector_logs.push_back("Upgrading shop by +" + std::to_string(attack) + "/+" + std::to_string(life));
    for (Pet* pet : m_pets)
        pet->buff(attack, life, false);

    if (!tmp) {
        m_attack_buff += attack;
        m_life_buff += life;
    }
}

std::string Shop::serialize() const {
    std::string shop_str;

    for (Pet* pet : m_pets)
        shop_str += pet->serialize() + " ";

    shop_str += "/ ";
    for (bool frozen : m_frozen_pets)
        shop_str += (frozen ? "1" : "0");

    shop_str += " / ";
    for (Object* obj : m_objects)
        shop_str += obj->m_name + " ";
    if (m_objects.empty())
        shop_str += " ";

    shop_str += "/ ";
    for (bool frozen : m_frozen_objects)
        shop_str += (frozen ? "1" : "0");

    shop_str += " / " + std::to_string(m_attack_buff) + " " + std::to_string(m_life_buff);
    return shop_str;
}


Pet* Shop::create_pet() {
    Pet* pet = Pet::create_random_pet(m_team, this, std::min(6, (m_turn + 1) / 2));
    if (m_attack_buff > 0 || m_life_buff > 0)
        pet->buff(m_attack_buff, m_life_buff, false);
    return pet;
}

Object* Shop::create_object() {
    Object* object = Object::create_random_object(m_team, this, std::min(6, (m_turn + 1) / 2));
    return object;
}

void Shop::check_size_pets(std::string action, size_t index) const {
    if (index >= m_pets.size())
        throw InvalidAction("[" + action + "]: invalid shop index " + std::to_string(index+1));
}

void Shop::check_size_objects(std::string action, size_t index) const {
    if (index >= m_objects.size())
        throw InvalidAction("[" + action + "]: invalid shop index " + std::to_string(index+1));
}
