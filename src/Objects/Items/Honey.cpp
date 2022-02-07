
#include "Objects/Items/Honey.hpp"


Honey::Honey(Team* team, Shop* shop) : Object("honey", team, shop, ObjType::ITEM) {
    id = 1;
    pack = PACK_STANDARD | PACK_DLC1;
    tier = 1;
}

Honey::~Honey() { }
