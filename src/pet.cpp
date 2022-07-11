
#include "pet.hpp"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <utility>

#include "utils.hpp"
#include "Pets/all_pets.hpp"


Pet* Pet::create_random_pet(Team* team, Shop* shop, int max_tier, bool strict_tier) {
    std::string name = Pet::get_random_name(max_tier, strict_tier);
    return AllPets::create_new_pet(name, team, shop);
}

Pet* Pet::unserialize(Team* team, Shop* shop, std::string pet_str) {
    std::istringstream iss(pet_str);
    std::string token;

    std::string name, object_name;
    int attack, life, xp;
    int attack_buff = 0, life_buff = 0;
    getline(iss, name, ' ');

    getline(iss, token, ' ');
    size_t index = token.find(':');
    if (index != std::string::npos) {
        attack = std::stoi(token.substr(0, index));
        attack_buff = std::stoi(token.substr(index+1));
    } else {
        attack = std::stoi(token);
    }

    getline(iss, token, ' ');
    index = token.find(':');
    if (index != std::string::npos) {
        life = std::stoi(token.substr(0, index));
        life_buff = std::stoi(token.substr(index+1));
    } else {
        life = std::stoi(token);
    }

    getline(iss, token, ' ');
    xp = std::stoi(token);

    getline(iss, object_name, ' ');

    name = utils::to_lower(name);
    object_name = utils::to_lower(object_name);

    Pet* pet = AllPets::create_new_pet(name, team, shop);
    pet->attack = attack;
    pet->attack_buff = attack_buff;
    pet->life = life;
    pet->life_buff = life_buff;
    pet->xp = xp;

    Object* object = nullptr;
    if (object_name != "none")
        object = Object::create_new_object(object_name, team, shop);
    pet->equip_object(object);

    return pet;
}

Pet* Pet::copy_pet(Pet const* pet, Team* team, Shop* shop) {
    std::string name = utils::to_lower(pet->name);
    Pet* new_pet = AllPets::create_new_pet(name, team, shop);
    new_pet->attack = pet->attack;
    new_pet->life = pet->life;
    new_pet->xp = pet->xp;
    if (pet->object) {
        Object* new_obj = Object::create_new_object(pet->object->name, team, shop);
        new_obj->set_pet(new_pet);
        new_pet->object = new_obj;
    }
    new_pet->attack_buff = pet->attack_buff;
    new_pet->life_buff = pet->life_buff;
    return new_pet;
}

Pet::Pet(std::string name, Team* team, Shop* shop) :
        name(name), team(team), adv_team(nullptr), shop(shop), xp(0), object(nullptr) {
    reset_stats();
}

Pet::~Pet() {
    delete object;
}

void Pet::bind(Team* adv_team) {
    this->adv_team = adv_team;
}

void Pet::bind(Shop* shop) {
    this->shop = shop;
}

Team* Pet::get_adv_team() const {
    return adv_team;
}

int Pet::get_attack() const {
    return std::min(50, attack + attack_buff);
}

int Pet::get_life() const {
    return std::min(50, life + life_buff);
}

int Pet::get_xp() const {
    return xp;
}

int Pet::get_level() const {
    if (xp == 5)
        return 3;
    else if (xp >= 2)
        return 2;
    return 1;
}

bool Pet::is_alive() const {
    return (life + life_buff) > 0;
}

void Pet::reset_stats() {
    attack_buff = 0;
    life_buff = 0;
}

void Pet::equip_object(Object* obj) {
    if (!obj)
        return;
    utils::vector_logs.push_back("Giving " + obj->name + " to " + name);

    delete object;
    object = Object::copy_object(obj, team, shop);
    object->set_pet(this);
}

void Pet::attacks(Pet* adv_pet) const {
    utils::vector_logs.push_back(name + " attacks " + adv_pet->name + " for " + std::to_string(get_attack()) + " damages");

    adv_pet->take_damage(get_attack(), false);
}

void Pet::take_damage(int value, bool activate_hurt) {
    if (object)
        value = object->on_damages(value);

    life -= std::max(0, value - life_buff);
    life_buff = std::max(0, life_buff - value);
    utils::vector_logs.push_back(name + " takes " + std::to_string(value) + " damages");

    if (activate_hurt && is_alive())
        on_hurt();
}

void Pet::buff(int buff_attack, int buff_life, bool is_tmp) {
    utils::vector_logs.push_back(name + " is getting buffed (+" + std::to_string(buff_attack) + "/+" + std::to_string(buff_life) + ")");
    if (is_tmp) {
        attack_buff += buff_attack;
        life_buff += buff_life;
    } else {
        attack = std::min(attack + buff_attack, 50);
        life = std::min(life + buff_life, 50);
    }
}

void Pet::gain_xp(int amount) {
    utils::vector_logs.push_back(name + " gains " + std::to_string(amount) + " xp");
    for (int x=0; x<amount && xp<5; x++) {
        xp++;
        if (xp == 5 || xp == 2) {
            utils::vector_logs.push_back(name + " levels up !");
            on_level_up();
            shop->create_bonus_pet();
        }
    }
}

void Pet::combine(Pet* const other) {
    int min_xp = std::min(xp, other->xp);
    int new_attack = std::max(attack, other->attack) + min_xp + 1;
    int new_life = std::max(life, other->life) + min_xp + 1;
    buff(new_attack - attack, new_life - life, false);
    gain_xp(other->xp+1);
    equip_object(other->object);
}

void Pet::kill() {
    life = -100;
    life_buff = -100;
}


void Pet::on_friend_bought(Pet* new_pet) {
    on_friend_summoned(new_pet);
}

void Pet::on_faint(size_t index) {
    if (object)
        object->on_faint(index);
}

std::string Pet::serialize() const {
    std::string pet_str = "(";
    pet_str += name + " ";
    pet_str += std::to_string(attack);
    if (attack_buff > 0)
        pet_str += ":" + std::to_string(attack_buff);
    pet_str += " ";
    pet_str += std::to_string(life);
    if (life_buff > 0)
        pet_str += ":" + std::to_string(life_buff);
    pet_str += " ";
    pet_str += std::to_string(xp) + " ";
    pet_str += (object ? object->name : "none") + ")";
    return pet_str;
}


std::string Pet::get_random_name(int max_tier, bool strict_tier) {
    std::vector<std::pair<int, std::string>> names;

    int min_tier = (strict_tier ? max_tier : 0);
    std::copy_if(AllPets::PET_LIST.begin(),
                 AllPets::PET_LIST.end(),
                 std::back_inserter(names),
                 [min_tier, max_tier](std::pair<int, std::string> p) {
                    return (min_tier <= p.first && p.first <= max_tier
                            && p.second != "sloth");
                 });

    return utils::choice(names)[0].second;
}
