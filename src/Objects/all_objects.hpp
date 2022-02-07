#ifndef HEADER_ALL_OBJECTS
#define HEADER_ALL_OBJECTS

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "object.hpp"

#include "Objects/Items/Honey.hpp"
#include "Objects/Foods/Apple.hpp"


namespace AllObjects {

    std::vector<std::pair<int, std::string>> const OBJECT_LIST = {
        {1, "honey"},
        {1, "apple"},
    };

    Object* create_new_object(std::string name, Team* team, Shop* shop) {
        if (name == "honey")
            return new Honey(team, shop);

        else if (name == "apple")
            return new Apple(team, shop);

        std::cerr << "No such object (" << name << "), returning an Apple instead" << std::endl;
        return new Apple(team, shop);
    }
};


#endif // HEADER_ALL_OBJECTS
