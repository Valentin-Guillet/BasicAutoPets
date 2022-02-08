#!/bin/bash

cat > all_objects.hpp << EOF
#ifndef HEADER_ALL_OBJECTS
#define HEADER_ALL_OBJECTS

#include <string>
#include <utility>
#include <vector>

#include "object.hpp"

EOF

for file in Items/*.hpp
do
    echo "#include \"Objects/$file\"" >> all_objects.hpp
done

for file in Foods/*.hpp
do
    echo "#include \"Objects/$file\"" >> all_objects.hpp
done


cat >> all_objects.hpp << EOF


namespace AllObjects {

    std::vector<std::pair<int, std::string>> const OBJECT_LIST = {
EOF

for file in Items/*.hpp Foods/*.hpp
do
    tier=$(sed -n '/tier/p' ${file%.hpp}.cpp)
    tier="${tier:11:-1}"
    name=$(basename ${file%.hpp})
    name=${name,,}
    echo "        {$tier, \"$name\"}," >> all_objects.hpp
done

cat >> all_objects.hpp << EOF
    };

    Object* create_new_object(std::string name, Team* team, Shop* shop);

};


#endif // HEADER_ALL_OBJECTS
EOF


cat > all_objects.cpp << EOF

#include "Objects/all_objects.hpp"

#include <iostream>


Object* AllObjects::create_new_object(std::string name, Team* team, Shop* shop) {
EOF

if_else=""
for file in Items/*.hpp Foods/*.hpp
do
    name=$(basename ${file%.hpp})
    echo -e "    ${if_else}if (name == \"${name,,}\")" >> all_objects.cpp
    echo -e "        return new $name(team, shop);\n" >> all_objects.cpp
    if_else="else "
done

cat >> all_objects.cpp << EOF
    std::cerr << "No such object (" << name << "), returning an Apple instead" << std::endl;
    return new Apple(team, shop);
}

EOF
