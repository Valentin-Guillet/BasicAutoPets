
#include "Animals/Beaver.hpp"

#include <vector>

#include "utils.hpp"


Beaver::Beaver(Team* team, Shop* shop) : Animal("beaver", team, shop) {
    id = 2;
    pack = PACK_STANDARD | PACK_DLC1;
    tier = 1;
    attack = 2;
    life = 2;
    reset_stats();
};

Beaver::~Beaver() { }

void Beaver::on_sell() {
    std::vector<Animal*> team_animals = get_team_animals();

    int lvl = get_level();
    std::vector<Animal*> targets = utils::choice(team_animals, 2);
    for (Animal* target : targets)
        target->buff(0, lvl, false);
}
