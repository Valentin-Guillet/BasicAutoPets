
#include "Pets/Cricket.hpp"

#include "Pets/ZombieCricket.hpp"
#include "utils.hpp"


Cricket::Cricket(Team* team, Shop* shop) : Pet("Cricket", team, shop) {
    repr = "🦗";
    id = 5;
    pack = PACK_STANDARD | PACK_DLC1;
    tier = 1;
    attack = 1;
    life = 2;
    reset_stats();
}

Cricket::~Cricket() { }

void Cricket::on_faint(Pos pos) {
    utils::vector_logs.push_back(name + " fainting !");

    int lvl = get_level();
    Pet* zombie = new ZombieCricket(team, shop, lvl);
    team->summon(pos, zombie);

    Pet::on_faint(pos);
}
