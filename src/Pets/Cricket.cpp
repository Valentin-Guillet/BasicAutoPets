
#include "Pets/Cricket.hpp"

#include "Pets/ZombieCricket.hpp"
#include "utils.hpp"


Cricket::Cricket(Team* team, Shop* shop) : Pet("cricket", team, shop) {
    id = 5;
    pack = PACK_STANDARD | PACK_DLC1;
    tier = 1;
    attack = 1;
    life = 2;
    reset_stats();
}

Cricket::~Cricket() { }

void Cricket::on_faint() {
    spdlog::debug("{} fainting !", name);

    int lvl = get_level();
    Pet* zombie = new ZombieCricket(team, shop, lvl);
    zombie->is_tmp = team->is_fighting();

    team->summon(this, zombie);
    Pet::on_faint();
}
