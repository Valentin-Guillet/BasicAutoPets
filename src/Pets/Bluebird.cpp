
#include "Pets/Bluebird.hpp"

#include <vector>

#include "utils.hpp"


Bluebird::Bluebird(Team* team, Shop* shop) : Pet("Bluebird", team, shop) {
    m_repr = "🐦";
    m_id = 4;
    m_pack = PACK_DLC1;
    m_tier = 1;
    m_attack = 2;
    m_life = 1;
    reset_stats();
}

Bluebird::~Bluebird() { }

void Bluebird::on_end_turn() {
    utils::vector_logs.push_back("End of turn, " + m_name + " buff !");
    std::vector<Pet*> team_pets = m_team->get_pets();

    int lvl = get_level();
    team_pets.back()->buff(lvl, 0, false);
}
