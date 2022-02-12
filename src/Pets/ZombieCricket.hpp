#ifndef HEADER_ZOMBIECRICKET
#define HEADER_ZOMBIECRICKET

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class ZombieCricket : public Pet {
    public:
        ZombieCricket(Team* team, Shop* shop, int lvl=1);
        ~ZombieCricket() override;

};


#endif // HEADER_ZOMBIECRICKET
