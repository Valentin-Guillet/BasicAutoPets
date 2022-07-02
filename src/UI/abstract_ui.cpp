
#include "UI/abstract_ui.hpp"


UserInterface::UserInterface(Game* game) : game(game) { }

UserInterface::~UserInterface() { }


int UserInterface::get_money() const {
    return game->money;
}

int UserInterface::get_life() const {
    return game->life;
}

int UserInterface::get_victories() const {
    return game->victories;
}

int UserInterface::get_turn() const {
    return game->turn;
}

int UserInterface::nb_pets_in_shop() const {
    return game->shop->pets.size();
}

int UserInterface::nb_objs_in_shop() const {
    return game->shop->objects.size();
}

Pet const* UserInterface::get_team_pet(size_t index) const {
    if (game->fight_status != FIGHT_STATUS::None) {
        if (index < game->fighting_team->pets.size())
            return game->fighting_team->pets[index];
    } else {
        for (size_t i=0; i<game->team->pets.size(); i++) {
            if (game->team->order[i] == index)
                return game->team->pets[i];
        }
    }
    return nullptr;
}

Pet const* UserInterface::get_shop_pet(size_t index) const {
    if (index < game->shop->pets.size())
        return game->shop->pets[index];
    return nullptr;
}

Pet const* UserInterface::get_adv_pet(size_t index) const {
    if (index < game->adv_team->pets.size())
        return game->adv_team->pets[index];
    return nullptr;
}

Object const* UserInterface::get_shop_object(size_t index, bool human_index) const {
    // If 6 pets in shop, the first object is at index 0 BUT should be
    // accessible through the 0 index in UI (i.e. index 1)
    if (human_index && game->shop->pets.size() == 6) {
        if (index == 0)
            return nullptr;
        index--;
    }
    return game->shop->objects[index];
}

bool UserInterface::is_pet_frozen(size_t index) const {
    return game->shop->frozen_pets[index];
}

bool UserInterface::is_obj_frozen(size_t index) const {
    return game->shop->frozen_objects[index];
}

std::string UserInterface::get_repr(Pet const* pet) const {
    return pet->repr;
}

std::string UserInterface::get_object_repr(Pet const* pet) const {
    if (pet->object)
        return pet->object->repr;
    return "";
}

bool UserInterface::has_attack_buff(Pet const* pet) const {
    return pet->attack_buff > 0;
}

bool UserInterface::has_life_buff(Pet const* pet) const {
    return pet->life_buff > 0;
}

int UserInterface::get_attack(Pet const* pet) const {
    return pet->get_attack();
}

int UserInterface::get_life(Pet const* pet) const {
    return pet->get_life();
}

std::string UserInterface::get_repr(Object const* obj) const {
    return obj->repr;
}

int UserInterface::get_cost(Object const* obj) const {
    return obj->cost;
}
