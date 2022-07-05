
#include "Pets/Peacock.hpp"

#include "utils.hpp"


Peacock::Peacock(Team* team, Shop* shop) : Pet("Peacock", team, shop) {
    repr = "🦚";
    id = 21;
    pack = PACK_STANDARD | PACK_DLC1;
    tier = 2;
    attack = 1;
    life = 5;
    reset_stats();
}

Peacock::~Peacock() { }

void Peacock::on_start_battle() {
    remaining_buffs = get_level();
}

void Peacock::on_hurt() {
    if (remaining_buffs <= 0)
        return;
    utils::vector_logs.push_back(name + " hurt, gaining 50% more attack");

    int attack_buff = (get_attack() + 1) / 2;
    buff(attack_buff, 0, false);
    remaining_buffs--;
}
