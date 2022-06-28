
#include "Objects/Items/Weak.hpp"

#include "utils.hpp"


Weak::Weak(Team* team, Shop* shop) : Object("Weak", team, shop, ObjType::ITEM) {
    repr = "🦠";
    id = 5;
    tier = -1;
    target_all = false;
}

Weak::~Weak() { }

int Weak::on_damages(int value) {
    utils::vector_logs.push_back(attached_pet->name + " is " + name + ", it takes 3 damages more");
    return value + 3;
}
