
#include "UI/user_interface.hpp"

#include "UI/cli.hpp"
#include "UI/gui.hpp"


UserInterface* UserInterface::create_ui(Game* game, bool use_cli) {
    if (use_cli)
        return new CLI(game);
    return new GUI(game);
}

UserInterface::UserInterface(Game* game) : m_game(game) { }

UserInterface::~UserInterface() { }


int UserInterface::get_money() const {
    return m_game->m_money;
}

int UserInterface::get_life() const {
    return m_game->m_life;
}

int UserInterface::get_victories() const {
    return m_game->m_victories;
}

int UserInterface::get_turn() const {
    return m_game->m_turn;
}

size_t UserInterface::nb_pets_in_shop() const {
    return Shop::get_max_pets(m_game->m_turn);
}

size_t UserInterface::nb_objs_in_shop() const {
    return Shop::get_max_objects(m_game->m_turn);
}

Pet const* UserInterface::get_team_pet(size_t index) const {
    if (m_game->m_fight_status != FIGHT_STATUS::None) {
        if (index < m_game->m_fighting_team->m_pets.size())
            return m_game->m_fighting_team->m_pets[index];
    } else {
        for (size_t i=0; i<m_game->m_team->m_pets.size(); i++) {
            if (m_game->m_team->m_order[i] == index)
                return m_game->m_team->m_pets[i];
        }
    }
    return nullptr;
}

Pet const* UserInterface::get_shop_pet(size_t index) const {
    if (index < m_game->m_shop->m_pets.size())
        return m_game->m_shop->m_pets[index];
    return nullptr;
}

Pet const* UserInterface::get_adv_pet(size_t index) const {
    if (index < m_game->m_adv_team->m_pets.size())
        return m_game->m_adv_team->m_pets[index];
    return nullptr;
}

Object const* UserInterface::get_shop_object(size_t index, bool human_index) const {
    // If 6 pets in shop, the first object is at index 0 BUT should be
    // accessible through the '0' key in UI (i.e. index 1)
    if (human_index && m_game->m_shop->m_pets.size() == 6) {
        if (index == 0)
            return nullptr;
        index--;
    }

    if (index < m_game->m_shop->m_objects.size())
        return m_game->m_shop->m_objects[index];
    return nullptr;
}

bool UserInterface::is_pet_frozen(size_t index) const {
    return m_game->m_shop->m_frozen_pets[index];
}

bool UserInterface::is_obj_frozen(size_t index) const {
    return m_game->m_shop->m_frozen_objects[index];
}

std::string UserInterface::get_repr(Pet const* pet) const {
    return pet->m_repr;
}

std::string UserInterface::get_object_repr(Pet const* pet) const {
    if (pet->m_object)
        return pet->m_object->m_repr;
    return "";
}

bool UserInterface::has_attack_buff(Pet const* pet) const {
    return pet->m_attack_buff > 0;
}

bool UserInterface::has_life_buff(Pet const* pet) const {
    return pet->m_life_buff > 0;
}

int UserInterface::get_attack(Pet const* pet) const {
    return pet->get_attack();
}

int UserInterface::get_life(Pet const* pet) const {
    return pet->get_life();
}

std::string UserInterface::get_repr(Object const* obj) const {
    return obj->m_repr;
}

int UserInterface::get_cost(Object const* obj) const {
    return obj->m_cost;
}
