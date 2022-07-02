
#include "Interface/environment.hpp"

#include <iostream>

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
    return 0;
}

int Environment::step(Action action) {
    game->save_state();
    std::cout << "[ENV] Taking action " << action << std::endl;
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

        std::cout << "Buying from " << shop_pos << " to " << team_pos << std::endl;

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
        int pet_id_1 = action / 4;
        int pet_id_2 = action % 4;

        // Skip when ids are identical (hence the 20 actions instead of 25)
        pet_id_2 += (pet_id_2 >= pet_id_1);

        game->combine(pet_id_1, pet_id_2);
        return 0;
    }
    action -= 5 * 4;

    // Swap pets
    if (action < 5 * 4) {
        int pet_id_1 = action / 4;
        int pet_id_2 = action % 4;

        // Skip when ids are identical (hence the 20 actions instead of 25)
        pet_id_2 += (pet_id_2 >= pet_id_1);

        game->move(pet_id_1, pet_id_2);
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
        try {
            // Buy Pet
            if (shop_pos < nb_pets) {
                game->check_money("", 3);

                // Combine
                if (game->team->has_pet(team_pos)) {
                    std::string shop_pet_name = game->shop->get_pet_name(shop_pos);
                    game->team->can_combine(team_pos, shop_pet_name);

                    game->shop->check_size_pets("", shop_pos);
                }

                // Buy new pet
                else {
                    if (game->team->get_nb_pets() == 5)
                        throw InvalidAction("");
                    game->shop->check_size_pets("", shop_pos);
                }

            // Buy object
            } else if (shop_pos >= 5) {
                size_t obj_index = (shop_pos == 6 && nb_pets < 6) ? 1 : 0;
                int cost = game->shop->get_cost_object(obj_index);
                game->check_money("", cost);

                game->team->pos_to_index(team_pos);
                game->shop->check_size_objects("", obj_index);
            } else {
                throw InvalidAction("");
            }

            mask[index++] = true;

        } catch (InvalidAction& e) {
            mask[index++] = false;
        }
    }

    // Sell
    for (size_t i=0; i<5; i++)
        mask[index++] = game->team->has_pet(i);

    // Combine
    for (size_t i=0; i<5*4; i++) {
        int pet_id_1 = i / 4;
        int pet_id_2 = i % 4;
        pet_id_2 += (pet_id_2 >= pet_id_1);

        try {
            game->team->can_combine(pet_id_1, pet_id_2);
            mask[index++] = true;
        } catch (InvalidAction& e) {
            mask[index++] = false;
        }

    }

    // Swap
    for (size_t i=0; i<5*4; i++) {
        int pet_id_1 = i / 4;
        int pet_id_2 = i % 4;
        pet_id_2 += (pet_id_2 >= pet_id_1);

        mask[index++] = (game->team->has_pet(pet_id_1) && game->team->has_pet(pet_id_2));
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
