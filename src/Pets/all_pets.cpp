
#include "Pets/all_pets.hpp"

#include <iostream>


Pet* AllPets::create_new_pet(std::string name, Team* team, Shop* shop) {
    if (name == "ant")
        return new Ant(team, shop);

    else if (name == "beaver")
        return new Beaver(team, shop);

    else if (name == "bee")
        return new Bee(team, shop);

    std::cerr << "No such pet (" << name << "), returning an Ant instead" << std::endl;
    return new Ant(team, shop);
}

