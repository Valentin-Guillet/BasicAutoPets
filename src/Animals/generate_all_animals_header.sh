#!/bin/bash

cat > all_animals.hpp << EOF
#ifndef HEADER_ALL_ANIMALS
#define HEADER_ALL_ANIMALS

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "animal.hpp"

EOF

for file in *.hpp
do
    [ $file = "all_animals.hpp" ] && continue
    echo "#include \"Animals/$file\"" >> all_animals.hpp
done

cat >> all_animals.hpp << EOF


namespace AllAnimals {

    std::vector<std::pair<int, std::string>> const ANIMAL_LIST = {
EOF

for file in *.hpp
do
    [ $file = "all_animals.hpp" ] && continue
    tier=$(sed -n '/tier/p' ${file%.hpp}.cpp)
    tier="${tier:11:-1}"
    name=${file%.hpp}
    name=${name,,}
    echo "        {$tier, \"$name\"}," >> all_animals.hpp
done

cat >> all_animals.hpp << EOF
    };

    Animal* create_new_animal(std::string name, Team* team, Shop* shop) {
EOF

if_else=""
for file in *.hpp
do
    [ $file = "all_animals.hpp" ] && continue
    name=${file%.hpp}
    echo -e "        ${if_else}if (name == \"${name,,}\")" >> all_animals.hpp
    echo -e "            return new $name(team, shop);\n" >> all_animals.hpp
    if_else="else "
done

cat >> all_animals.hpp << EOF
        std::cerr << "No such animal (" << name << "), returning an Ant instead" << std::endl;
        return new Ant(team, shop);
    }
};


#endif // HEADER_ALL_ANIMALS
EOF
