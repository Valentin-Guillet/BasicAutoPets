
#include "object.hpp"

#include <algorithm>
#include <iterator>
#include <utility>

#include "utils.hpp"
#include "Objects/all_objects.hpp"


Object* Object::create_new_object(std::string name, Team* team, Shop* shop) {
    name = utils::to_lower(name);
    return AllObjects::create_new_object(name, team, shop);
}

Object* Object::create_random_object(Team* team, Shop* shop, int max_tier) {
    std::string name = Object::get_random_name(max_tier);
    return AllObjects::create_new_object(name, team, shop);
}

Object* Object::copy_object(Object const* obj, Team* team, Shop* shop) {
    std::string name = utils::to_lower(obj->name);
    return AllObjects::create_new_object(name, team, shop);
}


Object::Object(std::string name, Team* team, Shop* shop, ObjType type) :
    name(name), type(type), team(team), shop(shop), attached_pet(nullptr), cost(3) {
}

Object::~Object() { };

int Object::get_cost() const {
    return cost;
}

void Object::set_pet(Pet* pet) {
    attached_pet = pet;
}


std::string Object::get_random_name(int max_tier) {
    std::vector<std::pair<int, std::string>> names;

    std::copy_if(AllObjects::OBJECT_LIST.begin(),
                 AllObjects::OBJECT_LIST.end(),
                 std::back_inserter(names),
                 [max_tier](std::pair<int, std::string> p) {
                    return p.first != -1 && p.first <= max_tier;
                    });

    return utils::choice(names)[0].second;
}
