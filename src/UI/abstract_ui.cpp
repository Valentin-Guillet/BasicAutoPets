
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
    std::vector<Pet*>* pets;
    if (game->team->is_fighting())
        pets = &game->team->tmp_pets;
    else
        pets = &game->team->pets;

    if (index < pets->size())
        return (*pets)[index];
    return nullptr;
}

Pet const* UserInterface::get_shop_pet(size_t index) const {
    return game->shop->pets[index];
}

Pet const* UserInterface::get_adv_pet(size_t index) const {
    if (index < game->adv_team->tmp_pets.size())
        return game->adv_team->tmp_pets[index];
    return nullptr;
}

Object const* UserInterface::get_shop_object(size_t index) const {
    return game->shop->objects[index];
}

bool UserInterface::is_pet_frozen(size_t index) const {
    return game->shop->frozen_pets[index];
}

bool UserInterface::is_obj_frozen(size_t index) const {
    return game->shop->frozen_objects[index];
}

std::string UserInterface::get_name(Pet const* pet) const {
    return pet->repr;
}

std::string UserInterface::get_object_name(Pet const* pet) const {
    if (pet->object)
        return pet->object->repr;
    return "";
}

bool UserInterface::has_attack_buff(Pet const* pet) const {
    return pet->attack != pet->tmp_attack;
}

bool UserInterface::has_life_buff(Pet const* pet) const {
    return pet->life != pet->tmp_life;
}

int UserInterface::get_attack(Pet const* pet) const {
    return pet->tmp_attack;
}

int UserInterface::get_life(Pet const* pet) const {
    return pet->tmp_life;
}

std::string UserInterface::get_name(Object const* obj) const {
    return obj->repr;
}

int UserInterface::get_cost(Object const* obj) const {
    return obj->cost;
}

std::string UserInterface::team_get_pet_name(size_t index) const {
    if (index < game->team->pets.size())
        return game->team->pets[index]->name;
    return "";
}

Object* UserInterface::shop_get_object(size_t index) const {
    return game->shop->objects[index];
}
