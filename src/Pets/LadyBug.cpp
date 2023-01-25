
#include "Pets/LadyBug.hpp"

#include "utils.hpp"


LadyBug::LadyBug(Team* team, Shop* shop) : Pet("LadyBug", team, shop) {
    m_repr = "🐞";
    m_id = 9;
    m_pack = PACK_DLC1;
    m_tier = 1;
    m_attack = 1;
    m_life = 3;
    reset_stats();
}

LadyBug::~LadyBug() { }

void LadyBug::on_object_bought(size_t index, Object* obj) {
    utils::vector_logs.push_back("Object bought, " + m_name + " is getting temporary buffed !");

    int lvl = get_level();
    buff(lvl, lvl, true);
}
