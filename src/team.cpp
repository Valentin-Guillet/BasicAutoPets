
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
        std::string animal_str = team_str.substr(2, index-2);
        team_str = team_str.substr(index+1);

        new_team->_add(Animal::unserialize(new_team, animal_str));
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
    for (Animal* animal : animals)
        delete animal;
}

void Team::begin_turn() {
    for (Animal* animal : animals)
        animal->on_start_turn();
}

void Team::reset_animals() {
    for (Animal* animal : tmp_animals) {
        if (animal->is_tmp())
            delete animal;
    }

    tmp_animals = animals;
    for (Animal* animal : animals)
        animal->reset_stats();
}

void Team::order(int order[5]) {
    std::vector<Animal*> ordered_animals;
    for (size_t i=0; i<5; i++) {
        if (order[i] < animals.size())
            ordered_animals.push_back(animals[order[i]]);
    }

    animals = ordered_animals;
}

void Team::add(Animal* animal) {
    _add(animal);
}

void Team::upgrade(int index, Animal* other_animal) {

}

int Team::sell(int index) {
    Animal* animal = animals[index];
    int lvl = animal->get_level();
    animals.erase(animals.begin() + index);

    animal->on_sell();
    delete animal;

    return lvl;
}

int Team::fight(Team* other_team) {
    in_fight = true;
    reset_animals();
    other_team->reset_animals();

    int ind_this = 0;
    int ind_other = 0;
    while (ind_this < tmp_animals.size() && ind_other < other_team->tmp_animals.size()) {
        animals[ind_this]->attacks(other_team->tmp_animals[ind_other]);
        other_team->tmp_animals[ind_other]->attacks(animals[ind_this]);

        if (!tmp_animals[ind_this]->is_alive()) {
            tmp_animals[ind_this]->on_faint();
            ind_this++;
        }
        if (!other_team->tmp_animals[ind_other]->is_alive()) {
            other_team->tmp_animals[ind_other]->on_faint();
            ind_other++;
        }

        disp_fight(other_team);
    }

    int output;
    if (ind_this == tmp_animals.size() && ind_other == other_team->tmp_animals.size())
        output = 0;
    else if (ind_this == tmp_animals.size())
        output = -1;
    else
        output = 1;

    in_fight = false;
    reset_animals();
    other_team->reset_animals();
    return output;
}

void Team::disp_fight(Team const* const other_team) const {
    std::string animals_name;
    std::string stats;

    for (int i=animals.size()-1; i>=0; i--) {
        if (!animals[i]->is_alive()) continue;

        animals_name += utils::pad(animals[i]->name, 10);
        stats += utils::pad(animals[i]->disp_stats(), 10);
    }

    animals_name += "  ///  ";
    stats += "  ///  ";

    for (size_t i=0; i<other_team->animals.size(); i++) {
        if (!other_team->animals[i]->is_alive()) continue;

        animals_name += utils::pad(other_team->animals[i]->name, 10);
        stats += utils::pad(other_team->animals[i]->disp_stats(), 10);
    }

    std::cout << animals_name << "\n" << stats << std::endl;
}

bool Team::is_fighting() const {
    return in_fight;
}

void Team::draw() const {
    if (animals.empty()) {
        std::cout << "Empty" << std::endl;
        return;
    }

    std::string animals_name;
    std::string stats;

    for (int i=animals.size()-1; i>=0; i--) {
        animals_name += utils::pad(animals[i]->name, 10);
        stats += utils::pad(animals[i]->disp_stats(), 10);
    }

    std::cout << animals_name << "\n" << stats << std::endl;
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

void Team::_add(Animal* animal) {
    animals.push_back(animal);
}
