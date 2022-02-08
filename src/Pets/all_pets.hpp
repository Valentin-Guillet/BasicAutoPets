#ifndef HEADER_ALL_PETS
#define HEADER_ALL_PETS

#include <string>
#include <utility>
#include <vector>

#include "pet.hpp"

#include "Pets/Ant.hpp"
#include "Pets/Beaver.hpp"
#include "Pets/Bee.hpp"


namespace AllPets {

    std::vector<std::pair<int, std::string>> const PET_LIST = {
        {1, "ant"},
        {1, "beaver"},
        {-1, "bee"},
    };

    Pet* create_new_pet(std::string name, Team* team, Shop* shop);

};


#endif // HEADER_ALL_PETS
