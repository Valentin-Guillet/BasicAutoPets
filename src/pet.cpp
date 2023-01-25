
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
    pet->m_attack = attack;
    pet->m_attack_buff = attack_buff;
    pet->m_life = life;
    pet->m_life_buff = life_buff;
    pet->m_xp = xp;

    Object* object = nullptr;
    if (object_name != "none")
        object = Object::create_new_object(object_name, team, shop);
    pet->equip_object(object);

    return pet;
}

Pet* Pet::copy_pet(Pet const* pet, Team* team, Shop* shop) {
    std::string name = utils::to_lower(pet->m_name);
    Pet* new_pet = AllPets::create_new_pet(name, team, shop);
    new_pet->m_attack = pet->m_attack;
    new_pet->m_life = pet->m_life;
    new_pet->m_xp = pet->m_xp;
    if (pet->m_object) {
        Object* new_obj = Object::create_new_object(pet->m_object->m_name, team, shop);
        new_obj->set_pet(new_pet);
        new_pet->m_object = new_obj;
    }
    new_pet->m_attack_buff = pet->m_attack_buff;
    new_pet->m_life_buff = pet->m_life_buff;
    return new_pet;
}

Pet::Pet(std::string name, Team* team, Shop* shop) :
        m_name(name), m_team(team), m_adv_team(nullptr), m_shop(shop), m_xp(0), m_object(nullptr) {
    reset_stats();
}

Pet::~Pet() {
    delete m_object;
}

void Pet::bind(Team* adv_team) {
    m_adv_team = adv_team;
}

void Pet::bind(Shop* shop) {
    m_shop = shop;
}

Team* Pet::get_adv_team() const {
    return m_adv_team;
}

int Pet::get_attack() const {
    return std::min(50, m_attack + m_attack_buff);
}

int Pet::get_life() const {
    return std::min(50, m_life + m_life_buff);
}

int Pet::get_xp() const {
    return m_xp;
}

int Pet::get_level() const {
    if (m_xp == 5)
        return 3;
    else if (m_xp >= 2)
        return 2;
    return 1;
}

bool Pet::is_alive() const {
    return (m_life + m_life_buff) > 0;
}

void Pet::set_stats(int attack, int life, int xp) {
    m_attack = attack;
    m_life = life;
    m_xp = xp;
}

void Pet::reset_stats() {
    m_attack_buff = 0;
    m_life_buff = 0;
}

void Pet::equip_object(Object* object) {
    if (!object)
        return;
    utils::vector_logs.push_back("Giving " + object->m_name + " to " + m_name);

    delete m_object;
    m_object = Object::copy_object(object, m_team, m_shop);
    m_object->set_pet(this);
}

void Pet::attacks(Pet* adv_pet) const {
    utils::vector_logs.push_back(m_name + " attacks " + adv_pet->m_name + " for " + std::to_string(get_attack()) + " damages");

    int value = get_attack();
    if (m_object)
        value = m_object->on_attack(value);
    adv_pet->take_damage(value, false);
}

void Pet::take_damage(int value, bool activate_hurt) {
    if (m_object)
        value = m_object->on_damages(value);

    m_life -= std::max(0, value - m_life_buff);
    m_life_buff = std::max(0, m_life_buff - value);
    utils::vector_logs.push_back(m_name + " takes " + std::to_string(value) + " damages");

    if (activate_hurt && is_alive())
        on_hurt();
}

void Pet::buff(int buff_attack, int buff_life, bool is_tmp) {
    utils::vector_logs.push_back(m_name + " is getting buffed (+" + std::to_string(buff_attack) + "/+" + std::to_string(buff_life) + ")");
    if (is_tmp) {
        m_attack_buff += buff_attack;
        m_life_buff += buff_life;
    } else {
        m_attack = std::min(m_attack + buff_attack, 50);
        m_life = std::min(m_life + buff_life, 50);
    }
}

void Pet::gain_xp(int amount) {
    utils::vector_logs.push_back(m_name + " gains " + std::to_string(amount) + " xp");
    for (int x=0; x<amount && m_xp<5; x++) {
        m_xp++;
        if (m_xp == 5 || m_xp == 2) {
            utils::vector_logs.push_back(m_name + " levels up !");
            on_level_up();
            m_shop->create_bonus_pet();
        }
    }
}

void Pet::combine(Pet* const other) {
    int min_xp = std::min(m_xp, other->m_xp);
    int new_attack = std::max(m_attack, other->m_attack) + min_xp + 1;
    int new_life = std::max(m_life, other->m_life) + min_xp + 1;
    buff(new_attack - m_attack, new_life - m_life, false);
    gain_xp(other->m_xp+1);
    equip_object(other->m_object);
}

void Pet::kill() {
    m_life = -100;
    m_life_buff = -100;
}


void Pet::on_friend_bought(Pet* new_pet) {
    on_friend_summoned(new_pet);
}

void Pet::on_faint(size_t index) {
    if (m_object)
        m_object->on_faint(index);
}

std::string Pet::serialize() const {
    std::string pet_str = "(";
    pet_str += m_name + " ";
    pet_str += std::to_string(m_attack);
    if (m_attack_buff > 0)
        pet_str += ":" + std::to_string(m_attack_buff);
    pet_str += " ";
    pet_str += std::to_string(m_life);
    if (m_life_buff > 0)
        pet_str += ":" + std::to_string(m_life_buff);
    pet_str += " ";
    pet_str += std::to_string(m_xp) + " ";
    pet_str += (m_object ? m_object->m_name : "none") + ")";
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
