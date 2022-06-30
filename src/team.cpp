
#include "team.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>

#include "game.hpp"
#include "utils.hpp"


TeamList Team::team_list;

Team* Team::unserialize(Game* game, std::string team_str) {
    Team* new_team = new Team(game);
    int index = team_str.find(' ');

    if (index == -1) {
        new_team->turn = std::stoi(team_str);
        return new_team;
    }

    new_team->turn = std::stoi(team_str.substr(0, index));
    team_str = team_str.substr(index);

    while (!team_str.empty()) {
        index = team_str.find(')');
        std::string pet_str = team_str.substr(2, index-2);
        team_str = team_str.substr(index+1);

        new_team->append_pet(Pet::unserialize(new_team, pet_str));
    }
    new_team->reset();

    return new_team;
}

Team* Team::get_random_team(int turn) {
    if (Team::team_list.empty())
        Team::load_teams();

    int opp_turn = turn;
    while (team_list[opp_turn].empty())
        opp_turn--;

    Team* opp_team = utils::choice(team_list[opp_turn])[0];
    return Team::copy_team(opp_team);
}

Team* Team::copy_team(Team const* team) {
    Team* new_team = new Team(team->game);
    new_team->turn = team->turn;

    for (Pet* pet : team->pets)
        new_team->append_pet(Pet::copy_pet(pet, new_team, nullptr));

    return new_team;
}

void Team::clear_team_list() {
    for (auto [turn, teams] : Team::team_list) {
        for (Team* team : teams)
            delete team;
    }
    Team::team_list.clear();
}

FIGHT_STATUS Team::fight_step(Team* team, Team* adv_team) {
    // Start of battle
    if (!team->in_fight) {
        team->in_fight = true;
        utils::vector_logs.push_back("Starting fight !");
        return start_of_battle(team, adv_team);
    }

    utils::vector_logs.push_back("Another step");

    Pet* pet = team->pets.front();
    Pet* adv_pet = adv_team->pets.front();

    if (pet->get_attack() > adv_pet->get_attack()) {
        pet->attacks(adv_pet);
        adv_pet->attacks(pet);
    } else {
        adv_pet->attacks(pet);
        pet->attacks(adv_pet);
    }

    if (!pet->is_alive()) {
        pet->on_faint();
        delete pet;
        team->remove_pet(0);
    }
    if (!adv_pet->is_alive()) {
        adv_pet->on_faint();
        delete adv_pet;
        adv_team->remove_pet(0);
    }

    return Team::check_end_of_battle(team, adv_team);
}


Team::Team(Game* game) : game(game), turn(0) { }

Team::~Team() {
    for (Pet* pet : pets)
        delete pet;
}

size_t Team::get_nb_pets() const {
    return pets.size();
}

std::vector<Pet*>& Team::get_pets() {
    return pets;
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

void Team::begin_turn() {
    turn++;
    for (Pet* pet : pets)
        pet->on_start_turn();
}

void Team::move(size_t src_index, size_t dst_index) {
    for (size_t i=0; i<order.size(); i++) {
        if (order[i] == src_index)
            order[i] = dst_index;
        else if (order[i] == dst_index)
            order[i] = src_index;
    }
    sort();
}

void Team::end_turn() {
    for (Pet* pet : pets)
        pet->on_end_turn();
}

void Team::reset() {
    for (Pet* pet : pets)
        pet->reset_stats();
}

void Team::add(Pet* new_pet) {
    new_pet->on_buy();
    for (Pet* pet : pets)
        pet->on_friend_bought(new_pet);
    append_pet(new_pet);
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

    combine(dst_index, pets[src_index], false);
    remove_pet(src_index);
}

int Team::sell(size_t index) {
    check_size("SELL_PET", index);

    Pet* pet = pets[index];
    int lvl = pet->get_level();
    remove_pet(index);

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

    auto it = std::find(pets.begin(), pets.end(), base_pet);
    pets.insert(it+1, new_pet);

    for (Pet* pet : pets) {
        if (pet == new_pet)
            continue;
        pet->on_friend_summoned(new_pet);
    }
}

void Team::faint(size_t index) {
    pets[index]->on_faint();
    delete pets[index];
    remove_pet(index);
}

void Team::give_object(size_t index, Object* obj) {
    check_size("GIVE_OBJECT", index);

    if (obj->type == ObjType::ITEM)
        pets[index]->equip_object(obj);

    pets[index]->on_object(obj);
    for (size_t i=0; i<pets.size(); i++)
        pets[i]->on_object_bought(index, obj);
}

void Team::earn_money(int amount) const {
    game->earn_money(amount);
}

std::tuple<int, std::string, std::string> Team::get_fight_str(Team* other_team) {
    in_fight = true;

    while (!pets.empty() && !other_team->pets.empty()) {
        Pet* pet = pets.front();
        Pet* other_pet = other_team->pets.front();

        while (pet->is_alive() && other_pet->is_alive()) {
            if (pet->get_attack() > other_pet->get_attack()) {
                pet->attacks(other_pet);
                other_pet->attacks(pet);
            } else {
                other_pet->attacks(pet);
                pet->attacks(other_pet);
            }
        }

        if (!pet->is_alive())
            pet->on_faint();
        if (!other_pet->is_alive())
            other_pet->on_faint();
    }

    int output;
    if (pets.empty() && other_team->pets.empty())
        output = 0;
    else if (pets.empty())
        output = -1;
    else
        output = 1;

    std::string team_str1 = serialize();
    std::string team_str2 = other_team->serialize();

    in_fight = false;
    reset();
    other_team->reset();
    return {output, team_str1, team_str2};
}

std::string Team::serialize() const {
    std::string team_str;

    for (Pet* pet : pets) {
        if (pet->is_alive())
            team_str += pet->serialize() + " ";
    }
    if (!team_str.empty())
        team_str.pop_back();
    return team_str;
}


void Team::load_teams() {
    std::ifstream team_file("data/saved_teams.txt");
    std::string team_str;
    while (getline(team_file, team_str)) {
        Team* new_team = Team::unserialize(nullptr, team_str);
        Team::team_list[new_team->turn].push_back(new_team);
    }
}

std::vector<Pet*> Team::order_pets(Team const* team, Team const* adv_team) {
    std::vector<Pet*> ordered_pets;
    while (ordered_pets.size() < team->pets.size() + adv_team->pets.size()) {
        Pet* curr_pet;
        int max_attack = 0;
        for (Pet* pet : team->pets) {
            bool done = (std::find(ordered_pets.begin(), ordered_pets.end(), pet) != ordered_pets.end());
            if (!done && pet->get_attack() > max_attack) {
                max_attack = pet->get_attack();
                curr_pet = pet;
            }
        }

        for (Pet* pet : adv_team->pets) {
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

FIGHT_STATUS Team::start_of_battle(Team* team, Team* adv_team) {
    std::vector<Pet*> ordered_pets = order_pets(team, adv_team);

    for (Pet* pet : ordered_pets) {
        if (pet->is_part(team))
            pet->on_start_battle(adv_team);
        else
            pet->on_start_battle(team);
    }

    team->remove_dead_pets();
    adv_team->remove_dead_pets();

    return check_end_of_battle(team, adv_team);
}

FIGHT_STATUS Team::check_end_of_battle(Team const* team, Team const* adv_team) {
    if (team->pets.empty() && adv_team->pets.empty()) {
        utils::vector_logs.push_back("Draw !");
        return FIGHT_STATUS::Draw;
    } else if (adv_team->pets.empty()) {
        utils::vector_logs.push_back("Win !");
        return FIGHT_STATUS::Win;
    } else if (team->pets.empty()) {
        utils::vector_logs.push_back("Loss...");
        return FIGHT_STATUS::Loss;
    }

    return FIGHT_STATUS::Fighting;
}

void Team::sort() {
    if (pets.size() < 2)
        return;

    std::vector<Pet*> ordered_pets;
    std::vector<size_t> new_order;
    for (size_t i=0; i<5; i++) {
        for (size_t j=0; j<pets.size(); j++) {
            if (order[j] == i) {
                ordered_pets.push_back(pets[j]);
                new_order.push_back(i);
                break;
            }
        }
    }
    pets = ordered_pets;
    order = new_order;
}

void Team::append_pet(Pet* new_pet) {
    size_t index;
    for (index=0; index<pets.size(); index++) {
        if (order[index] > index)
            break;
    }
    pets.push_back(new_pet);
    order.push_back(index);
    sort();
}

void Team::remove_pet(size_t index) {
    pets.erase(pets.begin() + index);
    order.erase(order.begin() + index);
}

void Team::check_size(std::string action, size_t index) const {
    if (index < pets.size()) return;
    throw InvalidAction("[" + action + "]: no pet in team at index " + std::to_string(index+1));
}

void Team::remove_dead_pets() {
    size_t i = 0;
    while (i < pets.size()) {
        Pet* pet = pets[i];
        if (!pet->is_alive()) {
            pet->on_faint();
            delete pet;
            remove_pet(i);
        } else {
            i++;
        }
    }
}
