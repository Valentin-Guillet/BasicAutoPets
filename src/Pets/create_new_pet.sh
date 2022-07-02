#!/bin/bash

name="${1^}"

if [ -f "$name.cpp" ]
then
    echo "File $name.cpp already exists, aborting..."
    exit 1
fi

cat > $name.cpp << EOF

#include "Pets/$name.hpp"


$name::$name(Team* team, Shop* shop) : Pet("${name^}", team, shop) {
    id = 0;
    pack = PACK_STANDARD | PACK_DLC1;
    tier = 1;
    attack = 1;
    life = 1;
    reset_stats();
}

$name::~$name() { }

EOF


cat > $name.hpp << EOF
#ifndef HEADER_PETS_${name^^}
#define HEADER_PETS_${name^^}

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class $name : public Pet {
    public:
        $name(Team* team, Shop* shop);
        ~$name() override;

};


#endif // HEADER_PETS_${name^^}
EOF
