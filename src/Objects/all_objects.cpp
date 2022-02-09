
#include "Objects/all_objects.hpp"

#include <iostream>


Object* AllObjects::create_new_object(std::string name, Team* team, Shop* shop) {
    if (name == "honey")
        return new Honey(team, shop);

    else if (name == "apple")
        return new Apple(team, shop);

    else if (name == "pill")
        return new Pill(team, shop);

    std::cerr << "No such object (" << name << "), returning an Apple instead" << std::endl;
    return new Apple(team, shop);
}

