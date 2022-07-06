
#include "Pets/Rat.hpp"

#include <string>

#include "Pets/DirtyRat.hpp"
#include "utils.hpp"


Rat::Rat(Team* team, Shop* shop) : Pet("Rat", team, shop) {
    repr = "🐀";
    id = 22;
    pack = PACK_STANDARD | PACK_DLC1;
    tier = 2;
    attack = 4;
    life = 5;
    reset_stats();
}

Rat::~Rat() { }

void Rat::on_faint(Pos pos) {
    if (!adv_team)
        return;

    int lvl = get_level();
    utils::vector_logs.push_back(name + " faints, summon " + std::to_string(lvl) + " Dirty Rat !");

    for (int i=0; i<lvl; i++) {
        Pet* dirty_rat = new DirtyRat(adv_team, nullptr);
        adv_team->summon(-1, dirty_rat);
    }
}
