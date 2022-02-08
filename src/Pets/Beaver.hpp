#ifndef HEADER_BEAVER
#define HEADER_BEAVER

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class Beaver : public Pet {
    public:
        Beaver(Team* team, Shop* shop);
        ~Beaver() override;

        void on_sell() override;
};


#endif // HEADER_BEAVER
