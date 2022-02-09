
#include "object.hpp"

#include <algorithm>
#include <iterator>
#include <utility>

#include "utils.hpp"
#include "Objects/all_objects.hpp"


Object* Object::create_new_object(std::string name, Team* team, Shop* shop) {
    return AllObjects::create_new_object(name, team, shop);
}

Object* Object::create_random_object(Team* team, Shop* shop, int max_tier) {
    std::string name = Object::get_random_name(max_tier);
    return AllObjects::create_new_object(name, team, shop);
}


Object::Object(std::string name, Team* team, Shop* shop, ObjType type) :
    name(name), team(team), shop(shop), type(type), attached_pet(nullptr), cost(3) {
}

Object::~Object() { };

int Object::get_cost() const {
    return cost;
}

void Object::set_pet(Pet* pet) {
    attached_pet = pet;
}

std::ostream& operator<<(std::ostream& os, Object const& object) {
    os << object.name;
    return os;
}


std::vector<Pet*>& Object::get_team_pets() const {
    if (team->is_fighting())
        return team->tmp_pets;
    return team->pets;
}

std::string Object::get_random_name(int max_tier) {
    std::vector<std::pair<int, std::string>> names;

    std::copy_if(AllObjects::OBJECT_LIST.begin(),
                 AllObjects::OBJECT_LIST.end(),
                 std::back_inserter(names),
                 [max_tier](std::pair<int, std::string> p){ return p.first <= max_tier; });

    return utils::choice(names)[0].second;
}
