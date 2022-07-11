
#include "Pets/Spider.hpp"

#include "utils.hpp"


Spider::Spider(Team* team, Shop* shop) : Pet("Spider", team, shop) {
    repr = "🕷";
    id = 24;
    pack = PACK_STANDARD | PACK_DLC1;
    tier = 2;
    attack = 2;
    life = 2;
    reset_stats();
}

Spider::~Spider() { }

void Spider::on_faint(Pos pos) {
    utils::vector_logs.push_back(name + " fainting: summoning a tier 3 2/2 pet");

    Pet* new_pet = Pet::create_random_pet(team, shop, 3, true);
    new_pet->set_stats(2, 2, xp);
    new_pet->bind(adv_team);
    team->summon(pos, new_pet);

    Pet::on_faint(pos);
}
