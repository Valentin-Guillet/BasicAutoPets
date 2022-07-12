
#include "Objects/Items/MeatBone.hpp"

#include "utils.hpp"


MeatBone::MeatBone(Team* team, Shop* shop) : Object("MeatBone", team, shop, ObjType::ITEM) {
    repr = "🍖";
    id = 6;
    tier = 2;
}

MeatBone::~MeatBone() { }

int MeatBone::on_attack(int value) {
    utils::vector_logs.push_back(attached_pet->name + " has " + name + ", it deals 5 damages more");
    return value + 5;
}
