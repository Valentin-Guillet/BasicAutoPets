
#include "Pets/TabbyCat.hpp"

#include "utils.hpp"


TabbyCat::TabbyCat(Team* team, Shop* shop) : Pet("TabbyCat", team, shop) {
    repr = "🐈";
    id = 26;
    pack = PACK_DLC1;
    tier = 2;
    attack = 5;
    life = 3;
    reset_stats();
}

TabbyCat::~TabbyCat() { }

void TabbyCat::on_object(Object* object) {
    utils::vector_logs.push_back(name + " fed, buffing friends !");
    int lvl = get_level();

    for (Pet* pet : team->get_pets()) {
        if (pet != this)
            pet->buff(lvl, 0, true);
    }
}
