
#include "animal.hpp"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <utility>

#include "utils.hpp"
#include "Animals/all_animals.hpp"


Animal* Animal::create_random_animal(Team* team, Shop* shop, int max_tier) {
    std::string name = Animal::get_random_name(max_tier);
    return AllAnimals::create_new_animal(name, team, shop);
}

Animal* Animal::unserialize(Team* team, std::string animal_str) {
    std::istringstream iss(animal_str);
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

    Animal* animal = AllAnimals::create_new_animal(name, team, nullptr);
    animal->life = life;
    animal->attack = attack;
    animal->xp = xp;
    animal->reset_stats();

    Object* object = nullptr;
    if (object_name != "none")
        object = Object::create_new_object(object_name, team, nullptr);
    animal->give_object(object);

    return animal;
}

Animal::Animal(std::string name, Team* team, Shop* shop) :
        name(name), team(team), shop(shop), xp(0), object(nullptr), tmp_animal(false) {
    reset_stats();
}

Animal::~Animal() {
    delete object;
}

std::string Animal::disp_stats() const {
    return "[" + std::to_string(tmp_attack) + "/" + std::to_string(tmp_life) + "]";
}

void Animal::give_object(Object* obj) {
    object = obj;
}

void Animal::reset_stats() {
    tmp_life = life;
    tmp_attack = attack;
}

int Animal::get_xp() const {
    return xp;
}

int Animal::get_level() const {
    if (xp == 2)
        return 3;
    else if (xp >= 2)
        return 2;
    else
        return 1;
}

void Animal::attacks(Animal* other) {
    std::cout << name << " attacks " << other->name << " for " << attack << " damages" << std::endl;
    other->tmp_life -= attack;
}

void Animal::buff(int buff_attack, int buff_life, bool in_fight) {
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

bool Animal::is_alive() const {
    return tmp_life > 0;
}

bool Animal::is_tmp() const {
    return tmp_animal;
}

std::ostream& operator<<(std::ostream& os, Animal const& animal) {
    os << animal.name << ": [";
    os << animal.tmp_attack << "/" << animal.tmp_life << "]";
    os << ", " << animal.xp << "xp";
    return os;
}

std::vector<Animal*> Animal::get_team_animals() const {
    if (team->is_fighting())
        return team->tmp_animals;
    return team->animals;
}


std::string Animal::get_random_name(int max_tier) {
    std::vector<std::pair<int, std::string>> names;

    std::copy_if(AllAnimals::ANIMAL_LIST.begin(),
                 AllAnimals::ANIMAL_LIST.end(),
                 std::back_inserter(names),
                 [max_tier](std::pair<int, std::string> p){ return p.first <= max_tier; });

    return utils::choice(names)[0].second;
}
