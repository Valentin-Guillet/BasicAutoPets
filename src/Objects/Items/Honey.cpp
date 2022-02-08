
#include "Objects/Items/Honey.hpp"

#include "Pets/all_pets.hpp"


Honey::Honey(Team* team, Shop* shop) : Object("honey", team, shop, ObjType::ITEM) {
    id = 1;
    pack = PACK_STANDARD | PACK_DLC1;
    tier = 1;
}

Honey::~Honey() { }

void Honey::on_faint() {
    Pet* bee = AllPets::create_new_pet("bee", team, shop);
    bee->is_tmp = true;

    attached_pet->summon(bee);
}
