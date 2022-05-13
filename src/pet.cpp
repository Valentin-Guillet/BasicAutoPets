
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

Pet* Pet::unserialize(Team* team, std::string pet_str) {
    std::istringstream iss(pet_str);
    std::string token;

    std::string name, object_name;
    int attack, life, xp;
    getline(iss, name, ' ');

    getline(iss, token, ' ');
    attack = std::stoi(token);

    getline(iss, token, ' ');
    life = std::stoi(token);

    getline(iss, token, ' ');
    xp = std::stoi(token);

    getline(iss, object_name, ' ');

    Pet* pet = AllPets::create_new_pet(name, team, nullptr);
    pet->attack = attack;
    pet->life = life;
    pet->xp = xp;
    pet->reset_stats();

    Object* object = nullptr;
    if (object_name != "none")
        object = Object::create_new_object(object_name, team, nullptr);
    pet->equip_object(object);

    return pet;
}

Pet::Pet(std::string name, Team* team, Shop* shop) :
        name(name), is_tmp(false), team(team), shop(shop), xp(0), object(nullptr) {
    reset_stats();
}

Pet::~Pet() {
    delete object;
}

int Pet::get_attack() const {
    return tmp_attack;
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
    return tmp_life > 0;
}

std::string Pet::disp_stats() const {
    return "[" + std::to_string(tmp_attack) + "/" + std::to_string(tmp_life) + "]";
}

void Pet::reset_stats() {
    tmp_attack = attack;
    tmp_life = life;
}

void Pet::equip_object(Object* obj) {
    if (obj)
        utils::vector_logs.push_back("Giving " + obj->name + " to " + name);
    if (object)
        delete object;

    object = obj;
    if (object)
        object->set_pet(this);
}

void Pet::attacks(Pet* other) {
    utils::vector_logs.push_back(name + " attacks " + other->name + " for " + std::to_string(tmp_attack) + " damages");
    other->tmp_life -= tmp_attack;
    if (other->is_alive())
        other->on_hurt();
}

void Pet::buff(int buff_attack, int buff_life, bool in_fight) {
    utils::vector_logs.push_back(name + " is getting buffed (+" + std::to_string(buff_attack) + "/+" + std::to_string(buff_life) + ")");
    if (in_fight) {
        tmp_attack = std::min(tmp_attack + buff_attack, 50);
        tmp_life  = std::min(tmp_life + buff_life, 50);
    } else {
        int tmp_attack_buff = tmp_attack - attack;
        int tmp_life_buff = tmp_life - life;
        attack = std::min(attack + buff_attack, 50);
        life = std::min(life + buff_life, 50);
        tmp_attack = std::min(attack + tmp_attack_buff, 50);
        tmp_life = std::min(life + tmp_life_buff, 50);
    }
}

void Pet::gain_xp(int amount) {
    utils::vector_logs.push_back(name + " gains " + std::to_string(amount) + " xp");
    for (int x=0; x<amount && xp<5; x++) {
        xp++;
        if (xp == 5 || xp == 2) {
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
    if (other->object)
        equip_object(other->object);
}


std::ostream& operator<<(std::ostream& os, Pet const& pet) {
    os << pet.name << ": [";
    os << pet.tmp_attack << "/" << pet.tmp_life << "]";
    os << ", " << pet.xp << "xp";
    if (pet.object)
        os << " with " << pet.object->name;
    return os;
}

void Pet::on_faint() {
    if (object)
        object->on_faint();
}

std::string Pet::serialize() const {
    std::string pet_str = "(";
    pet_str += name + " ";
    pet_str += std::to_string(tmp_attack) + " ";
    pet_str += std::to_string(tmp_life) + " ";
    pet_str += std::to_string(xp) + " ";
    pet_str += (object ? object->name : "none") + ")";
    return pet_str;
}


std::vector<Pet*>& Pet::get_team_pets() const {
    if (team->is_fighting())
        return team->tmp_pets;
    return team->pets;
}


std::string Pet::get_random_name(int max_tier, bool strict_tier) {
    std::vector<std::pair<int, std::string>> names;

    int min_tier = (strict_tier ? max_tier : 0);
    std::copy_if(AllPets::PET_LIST.begin(),
                 AllPets::PET_LIST.end(),
                 std::back_inserter(names),
                 [min_tier, max_tier](std::pair<int, std::string> p) {
                    return min_tier <= p.first && p.first <= max_tier;
                 });

    return utils::choice(names)[0].second;
}
