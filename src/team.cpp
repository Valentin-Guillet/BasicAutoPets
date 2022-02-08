
#include "team.hpp"

#include <fstream>
#include <iostream>
#include <string>

#include "utils.hpp"


TeamList Team::team_list;

std::pair<int, Team*> Team::unserialize(std::string team_str) {
    Team* new_team = new Team();
    int index = team_str.find(' ');
    int turn = std::stoi(team_str.substr(0, index));
    team_str = team_str.substr(index);

    while (!team_str.empty()) {
        index = team_str.find(')');
        std::string pet_str = team_str.substr(2, index-2);
        team_str = team_str.substr(index+1);

        new_team->_add(Pet::unserialize(new_team, pet_str));
    }

    return {turn, new_team};
}

Team* Team::get_random_team(int turn) {
    if (Team::team_list.empty())
        Team::load_teams();

    int opp_turn = turn;
    while (team_list[opp_turn].empty())
        opp_turn--;

    Team* opp_team = utils::choice(team_list[opp_turn])[0];
    return opp_team;
}

void Team::clear_team_list() {
    for (auto [turn, teams] : Team::team_list) {
        for (Team* team : teams)
            delete team;
    }
    Team::team_list.clear();
}


Team::~Team() {
    for (Pet* pet : pets)
        delete pet;
}

void Team::begin_turn() {
    for (Pet* pet : pets)
        pet->on_start_turn();
}

void Team::order(int order[5]) {
    std::vector<Pet*> ordered_pets;
    for (size_t i=0; i<5; i++) {
        if (order[i] < pets.size())
            ordered_pets.push_back(pets[order[i]]);
    }

    pets = ordered_pets;
}

void Team::add(Pet* pet) {
    _add(pet);
}

void Team::upgrade(int index, Pet* other_pet) {

}

int Team::sell(int index) {
    Pet* pet = pets[index];
    int lvl = pet->get_level();
    pets.erase(pets.begin() + index);

    pet->on_sell();
    delete pet;

    return lvl;
}

void Team::equip_item(int index, Object* item) {
    pets[index]->give_object(item);
}

int Team::fight(Team* other_team) {
    in_fight = true;
    reset_pets();
    other_team->reset_pets();

    while (!tmp_pets.empty() && !other_team->tmp_pets.empty()) {
        Pet* pet = tmp_pets.front();
        Pet* other_pet = other_team->tmp_pets.front();

        while (pet->is_alive() && other_pet->is_alive()) {
            if (pet->get_attack() > other_pet->get_attack()) {
                pet->attacks(other_pet);
                other_pet->attacks(pet);
            } else {
                other_pet->attacks(pet);
                pet->attacks(other_pet);
            }
        }

        if (!pet->is_alive()) {
            pet->on_faint();
            tmp_pets.erase(tmp_pets.begin());
            if (pet->is_tmp)
                delete pet;
        }
        if (!other_pet->is_alive()) {
            other_pet->on_faint();
            other_team->tmp_pets.erase(other_team->tmp_pets.begin());
            if (other_pet->is_tmp)
                delete other_pet;
        }

        disp_fight(other_team);
    }

    int output;
    if (tmp_pets.empty() && other_team->tmp_pets.empty())
        output = 0;
    else if (tmp_pets.empty())
        output = -1;
    else
        output = 1;

    in_fight = false;
    reset_pets();
    other_team->reset_pets();
    return output;
}

void Team::disp_fight(Team const* const other_team) const {
    std::string pets_name;
    std::string stats;

    for (int i=tmp_pets.size()-1; i>=0; i--) {
        if (!tmp_pets[i]->is_alive()) continue;

        pets_name += utils::pad(tmp_pets[i]->name, 10);
        stats += utils::pad(tmp_pets[i]->disp_stats(), 10);
    }

    pets_name += "  ///  ";
    stats += "  ///  ";

    for (size_t i=0; i<other_team->tmp_pets.size(); i++) {
        if (!other_team->tmp_pets[i]->is_alive()) continue;

        pets_name += utils::pad(other_team->tmp_pets[i]->name, 10);
        stats += utils::pad(other_team->tmp_pets[i]->disp_stats(), 10);
    }

    std::cout << pets_name << "\n" << stats << std::endl;
}

bool Team::is_fighting() const {
    return in_fight;
}

void Team::draw() const {
    if (pets.empty()) {
        std::cout << "Empty" << std::endl;
        return;
    }

    std::string pets_name;
    std::string stats;
    std::string objects;

    for (int i=pets.size()-1; i>=0; i--) {
        pets_name += utils::pad(pets[i]->name, 10);
        stats += utils::pad(pets[i]->disp_stats(), 10);
        objects += utils::pad(pets[i]->get_object_name(), 10);
    }

    std::cout << pets_name << "\n" << stats << "\n" << objects << std::endl;
}


void Team::load_teams() {
    std::ifstream team_file("data/saved_teams.txt");
    std::string team_str;
    while (getline(team_file, team_str)) {
        auto [turn, new_team] = Team::unserialize(team_str);
        new_team->in_fight = true;
        Team::team_list[turn].push_back(new_team);
    }
}

void Team::reset_pets() {
    tmp_pets = pets;
    for (Pet* pet : pets)
        pet->reset_stats();
}

void Team::_add(Pet* pet) {
    pets.push_back(pet);
}
