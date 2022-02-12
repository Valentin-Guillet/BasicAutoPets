
#include "Objects/Items/Honey.hpp"

#include "Pets/all_pets.hpp"
#include "utils.hpp"


Honey::Honey(Team* team, Shop* shop) : Object("honey", team, shop, ObjType::ITEM) {
    id = 1;
    pack = PACK_STANDARD | PACK_DLC1;
    tier = 1;
}

Honey::~Honey() { }

void Honey::on_faint() {
    spdlog::debug("{} summons a bee !", name);

    Pet* bee = AllPets::create_new_pet("bee", team, shop);
    bee->is_tmp = team->is_fighting();

    team->summon(attached_pet, bee);
}
