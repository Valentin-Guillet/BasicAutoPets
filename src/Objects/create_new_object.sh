#!/bin/bash

name="${1^}"
dst="${2:-./}"

cat > $dst/$name.cpp << EOF

#include "Objects/$name.hpp"


$name::$name(Team* team, Shop* shop) : Object("${name^}", team, shop, ObjType::) {
    id = 0;
    tier = 1;
}

$name::~$name() { }

EOF


cat > $dst/$name.hpp << EOF
#ifndef HEADER_OBJECTS_${name^^}
#define HEADER_OBJECTS_${name^^}

#include "object.hpp"
#include "shop.hpp"
#include "team.hpp"


class $name : public Object {
    public:
        $name(Team* team, Shop* shop);
        ~$name() override;

};


#endif // HEADER_OBJECTS_${name^^}
EOF
