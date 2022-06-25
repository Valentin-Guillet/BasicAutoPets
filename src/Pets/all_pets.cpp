
#include "Pets/all_pets.hpp"

#include <iostream>


Pet* AllPets::create_new_pet(std::string name, Team* team, Shop* shop) {
    if (name == "ant")
        return new Ant(team, shop);

    else if (name == "beaver")
        return new Beaver(team, shop);

    else if (name == "bee")
        return new Bee(team, shop);

    else if (name == "beetle")
        return new Beetle(team, shop);

    else if (name == "bluebird")
        return new Bluebird(team, shop);

    else if (name == "cricket")
        return new Cricket(team, shop);

    else if (name == "duck")
        return new Duck(team, shop);

    else if (name == "fish")
        return new Fish(team, shop);

    else if (name == "horse")
        return new Horse(team, shop);

    else if (name == "ladybug")
        return new LadyBug(team, shop);

    else if (name == "mosquito")
        return new Mosquito(team, shop);

    else if (name == "otter")
        return new Otter(team, shop);

    else if (name == "zombiecricket")
        return new ZombieCricket(team, shop);

    std::cerr << "No such pet (" << name << "), returning an Ant instead" << std::endl;
    return new Ant(team, shop);
}

