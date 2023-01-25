
#include "Pets/Flamingo.hpp"

#include "utils.hpp"


Flamingo::Flamingo(Team* team, Shop* shop) : Pet("Flamingo", team, shop) {
    m_repr = "🦩";
    m_id = 19;
    m_pack = PACK_STANDARD | PACK_DLC1;
    m_tier = 2;
    m_attack = 3;
    m_life = 1;
    reset_stats();
}

Flamingo::~Flamingo() { }

void Flamingo::on_faint(Pos pos) {
    utils::vector_logs.push_back(m_name + " faints ! Buffing two pets behind");

    int lvl = get_level();
    std::vector<Pet*> team_pets = m_team->get_pets();

    int nb_buffs = 0;
    for (Pos after_pos=pos+1; after_pos<5 && nb_buffs<2; after_pos++) {
        if (m_team->has_pet(after_pos)) {
            size_t index = m_team->pos_to_index(after_pos);
            if (!team_pets[index]->is_alive())
                continue;
            team_pets[index]->buff(lvl, lvl, false);
            nb_buffs++;
        }
    }

    Pet::on_faint(pos);
}
