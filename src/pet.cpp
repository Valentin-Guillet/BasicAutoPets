
#include "pet.hpp"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <utility>

#include "utils.hpp"
#include "Pets/all_pets.hpp"


Pet* Pet::create_random_pet(Team* team, Shop* shop, int max_tier) {
    std::string name = Pet::get_random_name(max_tier);
    return AllPets::create_new_pet(name, team, shop);
}

Pet* Pet::unserialize(Team* team, std::string pet_str) {
    std::istringstream iss(pet_str);
    std::string token;

    std::string name, object_name;
    int life, attack, xp;
    getline(iss, name, ' ');

    getline(iss, token, ' ');
    attack = std::stoi(token);

    getline(iss, token, ' ');
    life = std::stoi(token);

    getline(iss, token, ' ');
    xp = std::stoi(token);

    getline(iss, object_name, ' ');

    Pet* pet = AllPets::create_new_pet(name, team, nullptr);
    pet->life = life;
    pet->attack = attack;
    pet->xp = xp;
    pet->reset_stats();

    Object* object = nullptr;
    if (object_name != "none")
        object = Object::create_new_object(object_name, team, nullptr);
    pet->give_object(object);

    return pet;
}

Pet::Pet(std::string name, Team* team, Shop* shop) :
        name(name), team(team), shop(shop), xp(0), object(nullptr), is_tmp(false) {
    reset_stats();
}

Pet::~Pet() {
    delete object;
}

std::string Pet::disp_stats() const {
    return "[" + std::to_string(tmp_attack) + "/" + std::to_string(tmp_life) + "]";
}

void Pet::give_object(Object* obj) {
    object = obj;
    if (object)
        object->set_pet(this);
}

void Pet::reset_stats() {
    tmp_life = life;
    tmp_attack = attack;
}

int Pet::get_attack() const {
    return tmp_attack;
}

int Pet::get_xp() const {
    return xp;
}

int Pet::get_level() const {
    if (xp == 2)
        return 3;
    else if (xp >= 2)
        return 2;
    else
        return 1;
}

std::string Pet::get_object_name() const {
    if (object)
        return object->name;
    return "";
}

void Pet::attacks(Pet* other) {
    std::cout << name << " attacks " << other->name << " for " << tmp_attack << " damages" << std::endl;
    other->tmp_life -= tmp_attack;
    if (other->is_alive())
        other->on_hurt();
}

void Pet::buff(int buff_attack, int buff_life, bool in_fight) {
    std::cout << name << " is getting buffed ! (" << buff_attack << ", " << buff_life << ")" << std::endl;
    if (in_fight) {
        tmp_attack += buff_attack;
        tmp_life += buff_life;
    } else {
        attack += buff_attack;
        life += buff_life;
        reset_stats();
    }
}

void Pet::summon(Pet* new_pet) {
    std::vector<Pet*>& curr_team = get_team_pets();
    auto it = std::find(curr_team.begin(), curr_team.end(), this);
    curr_team.insert(it+1, new_pet);
}

bool Pet::is_alive() const {
    return tmp_life > 0;
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


std::vector<Pet*>& Pet::get_team_pets() const {
    if (team->is_fighting())
        return team->tmp_pets;
    return team->pets;
}


std::string Pet::get_random_name(int max_tier) {
    std::vector<std::pair<int, std::string>> names;

    std::copy_if(AllPets::PET_LIST.begin(),
                 AllPets::PET_LIST.end(),
                 std::back_inserter(names),
                 [max_tier](std::pair<int, std::string> p) {
                    return 0 <= p.first && p.first <= max_tier;
                 });

    return utils::choice(names)[0].second;
}
