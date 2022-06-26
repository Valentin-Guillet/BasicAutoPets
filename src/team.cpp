
#include "team.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>

#include "utils.hpp"


static void clear_dead_pets(std::vector<Pet*>& pets) {
    for (auto it=pets.begin(); it!=pets.end(); ) {
        Pet* pet = *it;
        if (!pet->is_alive()) {
            pet->on_faint();
            if (pet->is_tmp)
                delete pet;
            it = pets.erase(it);
        } else {
            it++;
        }
    }
}


TeamList Team::team_list;

Team* Team::unserialize(std::string team_str) {
    Team* new_team = new Team();
    int index = team_str.find(' ');

    if (index == -1) {
        new_team->turn = std::stoi(team_str);
        team_str.clear();
    } else {
        new_team->turn = std::stoi(team_str.substr(0, index));
        team_str = team_str.substr(index);
    }

    while (!team_str.empty()) {
        index = team_str.find(')');
        std::string pet_str = team_str.substr(2, index-2);
        team_str = team_str.substr(index+1);

        new_team->_add(Pet::unserialize(new_team, pet_str));
    }
    new_team->tmp_pets = new_team->pets;
    new_team->in_fight = false;

    return new_team;
}

Team* Team::get_random_team(int turn) {
    if (Team::team_list.empty())
        Team::load_teams();

    int opp_turn = turn;
    while (team_list[opp_turn].empty())
        opp_turn--;

    Team* opp_team = utils::choice(team_list[opp_turn])[0];
    opp_team->in_fight = true;
    return opp_team;
}

void Team::clear_team_list() {
    for (auto [turn, teams] : Team::team_list) {
        for (Team* team : teams)
            delete team;
    }
    Team::team_list.clear();
}


Team::Team() : turn(0) { }

Team::~Team() {
    for (Pet* pet : pets)
        delete pet;
}

size_t Team::get_nb_pets() const {
    return pets.size();
}

void Team::can_combine(size_t index, std::string other_pet) const {
    check_size("COMBINE", index);
    if (pets[index]->name != other_pet)
        throw InvalidAction("[COMBINE]: trying to combine different pets");
}

void Team::can_combine(size_t src_index, size_t dst_index) const {
    check_size("COMBINE", src_index);
    if (src_index == dst_index)
        throw InvalidAction("[COMBINE]: same source (" + std::to_string(src_index+1) + ")" + \
                            " and destination (" + std::to_string(dst_index+1) + ")");
    can_combine(dst_index, pets[src_index]->name);
}

bool Team::is_fighting() const {
    return in_fight;
}

std::vector<Pet*>& Team::get_pets() {
    if (in_fight)
        return tmp_pets;
    return pets;
}

void Team::begin_turn() {
    turn++;
    for (Pet* pet : pets)
        pet->on_start_turn();
}

void Team::order(size_t order[5]) {
    std::vector<Pet*> ordered_pets;
    for (size_t i=0; i<5; i++) {
        if (order[i] < pets.size())
            ordered_pets.push_back(pets[order[i]]);
    }

    pets = ordered_pets;
}

void Team::end_turn() {
    for (Pet* pet : pets)
        pet->on_end_turn();
    tmp_pets = pets;
}

void Team::reset() {
    in_fight = false;

    for (Pet* pet : tmp_pets) {
        if (pet->is_tmp)
            delete pet;
    }

    tmp_pets = pets;
    for (Pet* pet : pets)
        pet->reset_stats();
}

void Team::add(Pet* new_pet) {
    new_pet->on_buy();
    for (Pet* pet : pets)
        pet->on_friend_bought(new_pet);
    _add(new_pet);
}

void Team::combine(size_t index, Pet* other_pet, bool activate_on_buy) {
    Pet* dst = pets[index];
    dst->combine(other_pet);
    if (activate_on_buy)
        dst->on_buy();
    delete other_pet;
}

void Team::combine(size_t src_index, size_t dst_index) {
    can_combine(src_index, dst_index);

    Pet* src = pets[src_index];
    combine(dst_index, src, false);
    pets.erase(pets.begin() + src_index);
}

int Team::sell(size_t index) {
    check_size("SELL_PET", index);

    Pet* pet = pets[index];
    int lvl = pet->get_level();
    pets.erase(pets.begin() + index);

    pet->on_sell();
    delete pet;

    return lvl;
}

void Team::summon(Pet* base_pet, Pet* new_pet) {
    utils::vector_logs.push_back("New pet summoned: " + new_pet->name);
    if (pets.size() >= 6) {
        utils::vector_logs.push_back("Already 5 pets in team, aborting");
        delete new_pet;
        return;
    }

    std::vector<Pet*>* team_pets;
    if (in_fight)
        team_pets = &tmp_pets;
    else
        team_pets = &pets;
    auto it = std::find(team_pets->begin(), team_pets->end(), base_pet);
    team_pets->insert(it+1, new_pet);

    for (Pet* pet : *team_pets) {
        if (pet == new_pet)
            continue;
        pet->on_friend_summoned(new_pet);
    }
}

void Team::faint(size_t index) {
    Pet* pet = pets[index];
    pet->on_faint();
    pets.erase(pets.begin() + index);
    delete pet;
}

void Team::give_object(size_t index, Object* obj) {
    check_size("GIVE_OBJECT", index);

    if (obj->type == ObjType::ITEM)
        pets[index]->equip_object(obj);

    pets[index]->on_object(obj);
    for (size_t i=0; i<pets.size(); i++) {
        pets[i]->on_object_bought(index, obj);
    }
}

int Team::fight(Team* other_team) {
    in_fight = true;

    std::cout << "Team before attack:" << std::endl;
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
            if (pet->is_tmp)
                delete pet;
            tmp_pets.erase(tmp_pets.begin());
        }
        if (!other_pet->is_alive()) {
            other_pet->on_faint();
            if (other_pet->is_tmp)
                delete other_pet;
            other_team->tmp_pets.erase(other_team->tmp_pets.begin());
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

    if (output == 0)
        utils::vector_logs.push_back("Draw !");
    else if (output == 1)
        utils::vector_logs.push_back("Win !");
    else
        utils::vector_logs.push_back("Loss...");

    in_fight = false;
    reset();
    other_team->reset();
    return output;
}

int Team::fight_step(Team* adv_team) {
    // Start of battle
    if (!in_fight) {
        in_fight = true;
        utils::vector_logs.push_back("Starting fight !");

        std::vector<Pet*> ordered_pets = order_pets(adv_team);
        for (Pet* pet : ordered_pets)
            pet->on_start_battle(adv_team);

        clear_dead_pets(tmp_pets);
        clear_dead_pets(adv_team->tmp_pets);

        int output = check_end_of_battle(adv_team);
        return output;
    }

    utils::vector_logs.push_back("Another step");

    Pet* pet = tmp_pets.front();
    Pet* adv_pet = adv_team->tmp_pets.front();

    if (pet->get_attack() > adv_pet->get_attack()) {
        pet->attacks(adv_pet);
        adv_pet->attacks(pet);
    } else {
        adv_pet->attacks(pet);
        pet->attacks(adv_pet);
    }

    if (!pet->is_alive()) {
        pet->on_faint();
        if (pet->is_tmp)
            delete pet;
        tmp_pets.erase(tmp_pets.begin());
    }
    if (!adv_pet->is_alive()) {
        adv_pet->on_faint();
        if (adv_pet->is_tmp)
            delete adv_pet;
        adv_team->tmp_pets.erase(adv_team->tmp_pets.begin());
    }

    int output = check_end_of_battle(adv_team);
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

std::tuple<int, std::string, std::string> Team::get_fight_str(Team* other_team) {
    in_fight = true;

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
            if (pet->is_tmp)
                delete pet;
            tmp_pets.erase(tmp_pets.begin());
        }
        if (!other_pet->is_alive()) {
            other_pet->on_faint();
            if (other_pet->is_tmp)
                delete other_pet;
            other_team->tmp_pets.erase(other_team->tmp_pets.begin());
        }
    }

    int output;
    if (tmp_pets.empty() && other_team->tmp_pets.empty())
        output = 0;
    else if (tmp_pets.empty())
        output = -1;
    else
        output = 1;

    std::string team_str1 = serialize(true);
    std::string team_str2 = other_team->serialize(true);

    in_fight = false;
    reset();
    other_team->reset();
    return {output, team_str1, team_str2};
}

std::string Team::serialize(bool tmp) const {
    std::string team_str = std::to_string(turn) + " ";
    std::vector<Pet*> pets_list = pets;
    if (tmp)
        pets_list = tmp_pets;

    for (Pet* pet : pets_list) {
        if (!pet->is_alive()) continue;
        team_str += pet->serialize() + " ";
    }
    team_str.pop_back();
    return team_str;
}


void Team::load_teams() {
    std::ifstream team_file("data/saved_teams.txt");
    std::string team_str;
    while (getline(team_file, team_str)) {
        Team* new_team = Team::unserialize(team_str);
        new_team->in_fight = true;
        Team::team_list[new_team->turn].push_back(new_team);
    }
}

int Team::check_end_of_battle(Team* adv_team) const {
    int output;
    if (tmp_pets.empty() && adv_team->tmp_pets.empty())
        output = 0;
    else if (adv_team->tmp_pets.empty())
        output = 1;
    else if (tmp_pets.empty())
        output = 2;
    else
        output = -1;

    if (output == 0)
        utils::vector_logs.push_back("Draw !");
    else if (output == 1)
        utils::vector_logs.push_back("Win !");
    else if (output == 2)
        utils::vector_logs.push_back("Loss...");

    return output;
}

std::vector<Pet*> Team::order_pets(Team* adv_team) const {
    std::vector<Pet*> ordered_pets;
    while (ordered_pets.size() < tmp_pets.size() + adv_team->tmp_pets.size()) {
        Pet* curr_pet;
        int max_attack = 0;
        for (Pet* pet : tmp_pets) {
            bool done = (std::find(ordered_pets.begin(), ordered_pets.end(), pet) != ordered_pets.end());
            if (!done && pet->get_attack() > max_attack) {
                max_attack = pet->get_attack();
                curr_pet = pet;
            }
        }

        for (Pet* pet : adv_team->tmp_pets) {
            bool done = (std::find(ordered_pets.begin(), ordered_pets.end(), pet) != ordered_pets.end());
            if (!done && pet->get_attack() > max_attack) {
                max_attack = pet->get_attack();
                curr_pet = pet;
            }
        }

        ordered_pets.push_back(curr_pet);
    }

    return ordered_pets;
}

void Team::check_size(std::string action, size_t index) const {
    if (index < pets.size()) return;
    throw InvalidAction("[" + action + "]: no pet in team at index " + std::to_string(index+1));
}

void Team::_add(Pet* pet) {
    pets.push_back(pet);
}
