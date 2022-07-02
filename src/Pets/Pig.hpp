#ifndef HEADER_PETS_PIG
#define HEADER_PETS_PIG

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class Pig : public Pet {
    public:
        Pig(Team* team, Shop* shop);
        ~Pig() override;

        void on_sell() override;
};


#endif // HEADER_PETS_PIG
