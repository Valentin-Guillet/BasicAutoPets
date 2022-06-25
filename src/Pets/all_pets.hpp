#ifndef HEADER_ALL_PETS
#define HEADER_ALL_PETS

#include <string>
#include <utility>
#include <vector>

#include "pet.hpp"

#include "Pets/Ant.hpp"
#include "Pets/Beaver.hpp"
#include "Pets/Bee.hpp"
#include "Pets/Beetle.hpp"
#include "Pets/Bluebird.hpp"
#include "Pets/Cricket.hpp"
#include "Pets/Duck.hpp"
#include "Pets/Fish.hpp"
#include "Pets/Horse.hpp"
#include "Pets/LadyBug.hpp"
#include "Pets/Mosquito.hpp"
#include "Pets/ZombieCricket.hpp"


namespace AllPets {

    std::vector<std::pair<int, std::string>> const PET_LIST = {
        {1, "ant"},
        {1, "beaver"},
        {-1, "bee"},
        {1, "beetle"},
        {1, "bluebird"},
        {1, "cricket"},
        {1, "duck"},
        {1, "fish"},
        {1, "horse"},
        {1, "ladybug"},
        {1, "mosquito"},
        {-1, "zombiecricket"},
    };

    Pet* create_new_pet(std::string name, Team* team, Shop* shop);

};


#endif // HEADER_ALL_PETS
