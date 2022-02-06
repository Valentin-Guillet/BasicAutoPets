
#include "Animals/Ant.hpp"

#include <algorithm>
#include <iterator>
#include <vector>

#include "utils.hpp"


Ant::Ant(Team* team, Shop* shop) : Animal("ant", team, shop) {
    id = 1;
    pack = PACK_STANDARD | PACK_DLC1;
    tier = 1;
    attack = 2;
    life = 1;
    reset_stats();
};

Ant::~Ant() { }

void Ant::on_faint() {
    std::vector<Animal*> team_animals = get_team_animals();
    std::vector<Animal*> living_animals;

    std::copy_if(team_animals.begin(), team_animals.end(),
                 std::back_inserter(living_animals),
                 [](Animal* animal) { return animal->is_alive(); });

    if (living_animals.empty())
        return;

    Animal* target = utils::choice(living_animals)[0];
    int lvl = get_level();
    target->buff(2*lvl, 1*lvl, team->is_fighting());
}
