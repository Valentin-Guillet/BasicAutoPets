#ifndef HEADER_ALL_ANIMALS
#define HEADER_ALL_ANIMALS

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "animal.hpp"

#include "Animals/Ant.hpp"
#include "Animals/Beaver.hpp"


namespace AllAnimals {

    std::vector<std::pair<int, std::string>> const ANIMAL_LIST = {
        {1, "ant"},
        {1, "beaver"},
    };

    Animal* create_new_animal(std::string name, Team* team, Shop* shop) {
        if (name == "ant")
            return new Ant(team, shop);

        else if (name == "beaver")
            return new Beaver(team, shop);

        std::cerr << "No such animal (" << name << "), returning an Ant instead" << std::endl;
        return new Ant(team, shop);
    }
};


#endif // HEADER_ALL_ANIMALS
