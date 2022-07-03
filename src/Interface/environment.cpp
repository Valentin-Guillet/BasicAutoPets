
#include "Interface/environment.hpp"

#include "object.hpp"
#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"
#include "utils.hpp"


Environment::Environment() {
    game = new Game();
}

Environment::~Environment() {
    delete game;
}

void Environment::reset() {
    game->reset();
}

bool Environment::is_done() const {
    return game->is_over();
}

State Environment::get_state() const {
    State state = {};
    state.turn = game->turn;
    state.life = game->life;
    state.victories = game->victories;
    state.money = game->money;

    for (size_t i=0; i<5; i++) {
        if (!game->team->has_pet(i))
            continue;

        size_t index = game->team->pos_to_index(i);
        Pet* pet = game->team->pets[index];
        state.team_id[i] = pet->id;
        state.team_tier[i] = pet->tier;
        state.team_attack[i] = pet->attack;
        state.team_attack_buff[i] = pet->attack_buff;
        state.team_life[i] = pet->life;
        state.team_life_buff[i] = pet->life_buff;
        state.team_xp[i] = pet->xp;
    }

    state.shop_attack_buff = game->shop->attack_buff;
    state.shop_life_buff = game->shop->life_buff;

    size_t nb_pets = game->shop->pets.size();
    for (size_t i=0; i<nb_pets; i++) {
        Pet* pet = game->shop->pets[i];
        state.shop_type[i] = 1;
        state.shop_id[i] = pet->id;
        state.shop_tier[i] = pet->tier;
        state.shop_attack[i] = pet->attack;
        state.shop_life[i] = pet->life;
        state.shop_cost[i] = 3;
        state.shop_frozen[i] = game->shop->frozen_pets[i];
    }

    size_t nb_objs = game->shop->objects.size();
    for (size_t i=0; i<nb_objs; i++) {
        size_t index = (nb_pets == 6 || i == 1) ? 6 : 5;
        Object* obj = game->shop->objects[i];
        state.shop_type[index] = 2;
        state.shop_id[index] = obj->id;
        state.shop_tier[index] = obj->tier;
        state.shop_cost[index] = obj->cost;
        state.shop_frozen[index] = game->shop->frozen_objects[i];
    }

    return state;
}

int Environment::step(Action action) {
    game->save_state();
    // Roll
    if (action == 0) {
        game->roll();
        return 0;
    }
    action -= 1;

    // Buy from shop to team
    if (action < 7 * 5) {
        size_t shop_pos = action / 5;
        size_t team_pos = action % 5;

        size_t nb_pets = game->shop->pets.size();
        if (shop_pos < nb_pets) {
            game->buy_pet(shop_pos, team_pos);
        } else {
            size_t obj_pos = (shop_pos == 6 && nb_pets < 6) ? 1 : 0;
            game->buy_object(obj_pos, team_pos);
        }

        return 0;
    }
    action -= 7 * 5;

    // Sell pet
    if (action < 5) {
        game->sell(action);
        return 0;
    }
    action -= 5;

    // Combine team pets
    if (action < 5 * 4) {
        int pet_pos_1 = action / 4;
        int pet_pos_2 = action % 4;

        // Skip when ids are identical (hence the 20 actions instead of 25)
        pet_pos_2 += (pet_pos_2 >= pet_pos_1);

        game->combine(pet_pos_1, pet_pos_2);
        return 0;
    }
    action -= 5 * 4;

    // Swap pets
    if (action < 5 * 4) {
        int pet_pos_1 = action / 4;
        int pet_pos_2 = action % 4;

        // Skip when ids are identical (hence the 20 actions instead of 25)
        pet_pos_2 += (pet_pos_2 >= pet_pos_1);

        game->move(pet_pos_1, pet_pos_2);
        return 0;
    }
    action -= 5 * 4;

    // Freeze shop
    if (action < 7) {
        if (action < game->shop->pets.size())
            game->freeze_pet(action);
        else if (game->shop->pets.size() == 6 && action == 6)
            game->freeze_object(0);
        else if (action >= 5)
            game->freeze_object(action - 5);
        return 0;
    }
    action -= 7;

    // End turn
    game->end_turn();
    game->start_fight();
    while(game->fight_step()) { }
    return game->end_fight();
}

Mask Environment::get_mask() const {
    Mask mask;
    size_t index = 0;

    // Roll
    mask[index++] = (game->money >= 1);

    // Buy
    for (size_t i=0; i<7*5; i++) {
        size_t shop_pos = i / 5;
        size_t team_pos = i % 5;

        size_t nb_pets = game->shop->pets.size();
        // Buy pet
        if (shop_pos < nb_pets) {
            if (game->money < 3) {
                mask[index++] = false;
                continue;
            }

            // Combine
            if (game->team->has_pet(team_pos)) {
                size_t pet_ind = game->team->pos_to_index(team_pos);
                mask[index++] = (game->team->pets[pet_ind]->name == game->shop->pets[shop_pos]->name);
                continue;
            }

            // Buy new pet
            mask[index++] = (game->team->pets.size() < 5);

        // Buy object
        } else if (shop_pos >= 5) {
            size_t nb_objs = game->shop->objects.size();
            size_t obj_index = (shop_pos == 6 && nb_pets < 6) ? 1 : 0;
            if (obj_index >= nb_objs) {
                mask[index++] = false;
                continue;
            }

            int cost = game->shop->objects[obj_index]->cost;
            if (game->money < cost) {
                mask[index++] = false;
                continue;
            }

            mask[index++] = (game->shop->objects[obj_index]->target_all || game->team->has_pet(team_pos));

        } else {
            mask[index++] = false;
        }
    }

    // Sell
    for (size_t i=0; i<5; i++)
        mask[index++] = game->team->has_pet(i);

    // Combine
    for (size_t i=0; i<5*4; i++) {
        size_t pos1 = i / 4;
        size_t pos2 = i % 4;
        pos2 += (pos2 >= pos1);

        if (!game->team->has_pet(pos1) || !game->team->has_pet(pos2)) {
            mask[index++] = false;
            continue;
        }
        size_t ind1 = game->team->pos_to_index(pos1);
        size_t ind2 = game->team->pos_to_index(pos2);

        mask[index++] = (game->team->pets[ind1]->name == game->team->pets[ind2]->name);
    }

    // Swap
    for (size_t i=0; i<5*4; i++) {
        int pet_pos_1 = i / 4;
        int pet_pos_2 = i % 4;
        pet_pos_2 += (pet_pos_2 >= pet_pos_1);

        mask[index++] = (game->team->has_pet(pet_pos_1) && game->team->has_pet(pet_pos_2));
    }

    // Freeze
    size_t nb_pets = game->shop->pets.size();
    size_t nb_objs = game->shop->objects.size();
    for (size_t i=0; i<5; i++)
        mask[index++] = (i < nb_pets);

    // Can freeze index 5 if there are at least 6 pets or there's at least 1 object
    mask[index++] = (nb_pets >= 6 || nb_objs > 0);

    // Can freeze index 6 if there are 7 pets, 6 pets and an object or 2 objects
    mask[index++] = (nb_pets == 7 || (nb_pets == 6 && nb_objs == 1) || nb_objs >= 2);

    // End turn
    mask[index++] = true;

    return mask;
}
