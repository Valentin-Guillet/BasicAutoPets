
#include "Interface/environment.hpp"


Environment::Environment(Game* game) : game(game) {

}

Environment::~Environment() {

}

void Environment::get_state() const {

}

void Environment::take_action(Action action) {
    // Roll
    if (action == 0) {
        game->roll();
        return;
    }
    action -= 1;

    // Buy from shop to team
    if (action < 7 * 5) {
        int shop_id = action / 5;
        int team_id = action % 5;

        // Buy new pet
    }
}


std::array<bool, ACTION_SIZE> Environment::get_mask() const {
    return {};
}
