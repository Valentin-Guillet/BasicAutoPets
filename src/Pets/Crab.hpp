#ifndef HEADER_PETS_CRAB
#define HEADER_PETS_CRAB

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class Crab : public Pet {
    public:
        Crab(Team* team, Shop* shop);
        ~Crab() override;

        void on_buy() override;
};


#endif // HEADER_PETS_CRAB
