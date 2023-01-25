
#include "Pets/Bat.hpp"

#include <string>

#include "Objects/Items/Weak.hpp"
#include "utils.hpp"


Bat::Bat(Team* team, Shop* shop) : Pet("Bat", team, shop) {
    m_repr = "🦇";
    m_id = 14;
    m_pack = PACK_DLC1;
    m_tier = 2;
    m_attack = 1;
    m_life = 2;
    reset_stats();
}

Bat::~Bat() { }

void Bat::on_start_battle() {
    int lvl = get_level();
    utils::vector_logs.push_back("Start of battle: " + m_name + " makes " + std::to_string(lvl) + " enemy pets weak.");

    std::vector<Pet*> adv_pets = m_adv_team->get_pets();
    std::vector<Pet*> living_pets;

    std::copy_if(adv_pets.begin(), adv_pets.end(),
                 std::back_inserter(living_pets),
                 [this](Pet* pet) { return pet->is_alive(); });

    std::vector<Pet*> targets = utils::choice(living_pets, lvl);

    for (Pet* target : targets) {
        Object* weak = new Weak(m_team, m_shop);
        target->equip_object(weak);
    }
}
