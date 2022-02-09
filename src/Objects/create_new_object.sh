#!/bin/bash

name="${1^}"
dst="${2:-./}"

cat > $dst/$name.cpp << EOF

#include "Objects/$name.hpp"


$name::$name(Team* team, Shop* shop) : Object("${name,}", team, shop, ObjType::) {
    id = 0;
    pack = PACK_STANDARD | PACK_DLC1;
    tier = 1;
}

$name::~$name() { }

EOF


cat > $dst/$name.hpp << EOF
#ifndef HEADER_${name^^}
#define HEADER_${name^^}

#include "object.hpp"
#include "shop.hpp"
#include "team.hpp"


class $name : public Object {
    public:
        $name(Team* team, Shop* shop);
        ~$name() override;

};


#endif // HEADER_${name^^}
EOF
