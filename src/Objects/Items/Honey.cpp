
#include "Objects/Items/Honey.hpp"

#include "Pets/all_pets.hpp"
#include "utils.hpp"


Honey::Honey(Team* team, Shop* shop) : Object("honey", team, shop, ObjType::ITEM) {
    repr = "🍯";
    id = 2;
    tier = 1;
    target_all = false;
}

Honey::~Honey() { }

void Honey::on_faint() {
    utils::vector_logs.push_back(name + " summons a bee !");

    Pet* bee = AllPets::create_new_pet("bee", team, shop);
    bee->is_tmp = team->is_fighting();

    team->summon(attached_pet, bee);
}
