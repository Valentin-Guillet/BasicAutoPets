
#include "game.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

#include "object.hpp"
#include "utils.hpp"


static int life_per_turn(int turn) {
    if (turn < 3)
        return 1;
    else if (turn < 5)
        return 2;
    return 3;
}


Game::Game() : m_life(10), m_victories(0), m_turn(0) {
    m_team = new Team(this);
    m_shop = new Shop(m_team);
    begin_turn();
    m_fight_status = FIGHT_STATUS::None;
};

Game::~Game() {
    Team::clear_team_list();
    delete m_team;
    delete m_shop;
}

void Game::reset() {
    m_life = 10;
    m_victories = 0;
    m_turn = 0;

    delete m_team;
    delete m_shop;
    m_team = new Team(this);
    m_shop = new Shop(m_team);

    begin_turn();
}


void Game::begin_turn() {
    m_money = 10;
    m_shop->begin_turn();
    m_team->begin_turn();
    m_turn++;
}

void Game::move(Pos src_pos, Pos dst_pos) {
    m_team->move(src_pos, dst_pos);
}

void Game::end_turn() {
    m_team->end_turn();
}

bool Game::is_over() const {
    return !(m_life > 0 && m_victories < 10);
}

void Game::start_fight() {
    m_fighting_team = Team::copy_team(m_team);
    m_adv_team = Team::get_random_team(m_turn);
    m_fight_status = FIGHT_STATUS::Fighting;

    m_fighting_team->bind(m_adv_team);
    m_adv_team->bind(m_fighting_team);
}

bool Game::fight_step() {
    m_fight_status = Team::fight_step(m_fighting_team, m_adv_team);
    return in_fight();
}

int Game::end_fight() {
    int output = 0;
    if (m_fight_status == FIGHT_STATUS::Win) {
        m_victories++;
        output = 1;
    } else if (m_fight_status == FIGHT_STATUS::Loss) {
        m_life -= life_per_turn(m_turn);
        output = -1;
    }

    delete m_fighting_team;
    delete m_adv_team;
    m_fighting_team = nullptr;
    m_adv_team = nullptr;

    if (m_life > 0)
        begin_turn();

    m_team->reset();
    m_fight_status = FIGHT_STATUS::None;

    return output;
}

bool Game::in_fight() const {
    return m_fight_status == FIGHT_STATUS::Fighting;
}

void Game::buy_pet(Pos src_pos, Pos dst_pos) {
    check_money("BUY_PET", 3);
    if (m_team->has_pet(dst_pos)) {
        combine_from_shop(src_pos, dst_pos);
        return;
    }

    if (m_team->get_nb_pets() == 5)
        throw InvalidAction("[BUY_PET]: already have 5 pets in the team !");
    Pet* pet = m_shop->buy_pet(src_pos);
    m_team->add(pet, dst_pos);
    m_money -= 3;
}

void Game::buy_object(size_t obj_index, Pos pet_pos) {
    int cost = m_shop->get_cost_object(obj_index);
    check_money("BUY_OBJECT", cost);

    size_t pet_index = m_team->pos_to_index(pet_pos);
    m_shop->buy_object(obj_index, pet_index);
    m_money -= cost;
}

void Game::combine(Pos src_pos, Pos dst_pos) {
    m_team->combine(src_pos, dst_pos);
}

void Game::sell(Pos pos) {
    m_money += m_team->sell(pos);
}

void Game::roll() {
    check_money("ROLL", 1);

    m_shop->roll();
    m_money--;
}

void Game::freeze_pet(size_t index) {
    m_shop->freeze_pet(index);
}

void Game::freeze_object(size_t index) {
    m_shop->freeze_object(index);
}

void Game::earn_money(int amount) {
    m_money += amount;
}

std::string Game::serialize() const {
    std::string state = std::to_string(m_turn) + " ";
    state += std::to_string(m_life) + " ";
    state += std::to_string(m_victories) + " ";
    state += std::to_string(m_money) + "\n";
    state += m_team->serialize() + "\n";
    state += m_shop->serialize();
    return state;
}

void Game::unserialize(std::string game_str) {
    std::stringstream stream(game_str);
    std::string line;

    std::getline(stream, line, '\n');
    size_t index = line.find(' ');
    m_turn = std::stoi(line.substr(0, index));
    line = line.substr(index+1);

    index = line.find(' ');
    m_life = std::stoi(line.substr(0, index));
    line = line.substr(index+1);

    index = line.find(' ');
    m_victories = std::stoi(line.substr(0, index));
    line = line.substr(index+1);

    index = line.find(' ');
    m_money = std::stoi(line.substr(0, index));

    std::string turn_str = std::to_string(m_turn) + " ";
    delete m_team;
    std::getline(stream, line, '\n');
    m_team = Team::unserialize(this, turn_str + line);

    delete m_shop;
    std::getline(stream, line, '\n');
    m_shop = Shop::unserialize(m_team, turn_str + line);

    m_team->bind(m_shop);
}

void Game::save_state() const {
    std::string state = serialize();
    std::ofstream file("data/game_save");
    if (!file) {
        std::cout << "Couldn't save file" << std::endl;
        return;
    }

    file << state;
    file.close();
}

void Game::load_state() {
    std::ifstream file("data/game_save");
    if (!file) {
        std::cout << "Couldn't load file" << std::endl;
        return;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string state = buffer.str();
    file.close();

    unserialize(state);
}

void Game::cheat() {
    m_money += 1000;
}


void Game::combine_from_shop(size_t shop_index, Pos pet_pos) {
    std::string shop_pet_name = m_shop->get_pet_name(shop_index);
    m_team->can_combine(pet_pos, shop_pet_name);

    Pet* pet = m_shop->buy_pet(shop_index);
    m_team->combine(pet_pos, pet);
    m_money -= 3;
}

void Game::check_money(std::string action, int amount) const {
    if (m_money >= amount)
        return;

    std::string msg = "[" + action + "]: not enough money to do this action";
    msg += " (" + std::to_string(m_money) + " gold left)";
    throw InvalidAction(msg);
}
