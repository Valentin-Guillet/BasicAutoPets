
#include "Pets/Dog.hpp"

#include "utils.hpp"


Dog::Dog(Team* team, Shop* shop) : Pet("Dog", team, shop) {
    repr = "🐕";
    id = 27;
    pack = PACK_STANDARD | PACK_DLC1;
    tier = 3;
    attack = 2;
    life = 2;
    reset_stats();
}

Dog::~Dog() { }

void Dog::on_friend_bought(Pet* new_pet) {
    utils::vector_logs.push_back("Friend bought: " + name + " is getting buffed");
    random_buff();
}

void Dog::on_friend_summoned(Pet* new_pet) {
    utils::vector_logs.push_back("Friend summoned: " + name + " is getting buffed");
    random_buff();
}

void Dog::random_buff() {
    int lvl = get_level();
    if (utils::randint(1) == 0)
        buff(lvl, 0, false);
    else
        buff(0, lvl, false);
}
