
#include "Pets/Badger.hpp"

#include "utils.hpp"


Badger::Badger(Team* team, Shop* shop) : Pet("Badger", team, shop) {
    repr = "🦡";
    id = 28;
    pack = PACK_STANDARD;
    tier = 3;
    attack = 5;
    life = 4;
    reset_stats();
}

Badger::~Badger() { }

void Badger::on_faint(Pos pos) {
    utils::vector_logs.push_back(name + " fainting, hurting pets around");

    int damages = get_level() * get_attack();

    std::vector<Pet*> pets = team->get_pets();
    Pet* back_pet = nullptr;
    for (size_t after_pos=pos+1; after_pos <= 5 && !back_pet; after_pos++) {
        if (!team->has_pet(after_pos))
            continue;

        size_t index = team->pos_to_index(after_pos);
        if (pets[index]->is_alive())
            back_pet = pets[index];
    }

    Pet* front_pet = nullptr;
    for (size_t before_pos=pos-1; before_pos != (size_t)-1 && !front_pet; before_pos--) {
        if (!team->has_pet(before_pos))
            continue;

        size_t index = team->pos_to_index(before_pos);
        if (pets[index]->is_alive())
            front_pet = pets[index];
    }

    if (!front_pet && adv_team) {
        std::vector<Pet*> adv_pets = adv_team->get_pets();
        for (size_t adv_pos=0; adv_pos < 5  && !front_pet; adv_pos++) {
            if (!adv_team->has_pet(adv_pos))
                continue;

            size_t index = adv_team->pos_to_index(adv_pos);
            if (adv_pets[index]->is_alive())
                front_pet = adv_pets[index];
        }
    }


    if (front_pet)
        front_pet->take_damage(damages, false);
    if (back_pet)
        back_pet->take_damage(damages, false);

    if (front_pet && front_pet->is_alive())
        front_pet->on_hurt();
    if (back_pet && back_pet->is_alive())
        back_pet->on_hurt();

    Pet::on_faint(pos);
}
