#ifndef HEADER_OBJECTS_ALL_OBJECTS
#define HEADER_OBJECTS_ALL_OBJECTS

#include <string>
#include <utility>
#include <vector>

#include "object.hpp"

#include "Objects/Items/Honey.hpp"
#include "Objects/Items/Weak.hpp"
#include "Objects/Foods/Apple.hpp"
#include "Objects/Foods/Cupcake.hpp"
#include "Objects/Foods/Pill.hpp"


namespace AllObjects {

    std::vector<std::pair<int, std::string>> const OBJECT_LIST = {
        {1, "honey"},
        {-1, "weak"},
        {1, "apple"},
        {2, "cupcake"},
        {2, "pill"},
    };

    Object* create_new_object(std::string name, Team* team, Shop* shop);

};


#endif // HEADER_OBJECTS_ALL_OBJECTS
