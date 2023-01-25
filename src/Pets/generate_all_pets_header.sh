#!/bin/bash

cat > all_pets.hpp << EOF
#ifndef HEADER_PETS_ALLPETS
#define HEADER_PETS_ALLPETS

#include <string>
#include <utility>
#include <vector>

#include "pet.hpp"

EOF

for file in *.hpp
do
    [ $file = "all_pets.hpp" ] && continue
    echo "#include \"Pets/$file\"" >> all_pets.hpp
done

cat >> all_pets.hpp << EOF


namespace AllPets {

    std::vector<std::pair<int, std::string>> const PET_LIST = {
EOF

for file in *.hpp
do
    [ $file = "all_pets.hpp" ] && continue
    tier=$(sed -n '/m_tier = /p' ${file%.hpp}.cpp)
    tier="${tier:13:-1}"
    name=${file%.hpp}
    name=${name,,}
    echo "        {$tier, \"$name\"}," >> all_pets.hpp
done

cat >> all_pets.hpp << EOF
    };

    Pet* create_new_pet(std::string name, Team* team, Shop* shop);

};


#endif // HEADER_PETS_ALLPETS
EOF



cat > all_pets.cpp << EOF

#include "Pets/all_pets.hpp"

#include <iostream>


Pet* AllPets::create_new_pet(std::string name, Team* team, Shop* shop) {
EOF

if_else=""
for file in *.hpp
do
    [ $file = "all_pets.hpp" ] && continue
    name=${file%.hpp}
    echo -e "    ${if_else}if (name == \"${name,,}\")" >> all_pets.cpp
    echo -e "        return new $name(team, shop);\n" >> all_pets.cpp
    if_else="else "
done

cat >> all_pets.cpp << EOF
    std::cerr << "No such pet (" << name << "), returning an Ant instead" << std::endl;
    return new Ant(team, shop);
}

EOF
