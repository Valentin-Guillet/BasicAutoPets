#ifndef HEADER_BEE
#define HEADER_BEE

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class Bee : public Pet {
    public:
        Bee(Team* team, Shop* shop);
        ~Bee() override;
};


#endif // HEADER_BEE
