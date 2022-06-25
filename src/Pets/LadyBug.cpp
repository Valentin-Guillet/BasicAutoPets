
#include "Pets/LadyBug.hpp"

#include "utils.hpp"


LadyBug::LadyBug(Team* team, Shop* shop) : Pet("LadyBug", team, shop) {
    repr = "🐞";
    id = 9;
    pack = PACK_DLC1;
    tier = 1;
    attack = 1;
    life = 3;
    reset_stats();
}

LadyBug::~LadyBug() { }

void LadyBug::on_object_bought(size_t index, Object* obj) {
    utils::vector_logs.push_back("Object bought, " + name + " is getting temporary buffed !");

    int lvl = get_level();
    buff(lvl, lvl, true);
}
