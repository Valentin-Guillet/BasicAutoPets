#ifndef HEADER_PETS_BLUEBIRD
#define HEADER_PETS_BLUEBIRD

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class Bluebird : public Pet {
    public:
        Bluebird(Team* team, Shop* shop);
        ~Bluebird() override;

        void on_end_turn() override;
};


#endif // HEADER_PETS_BLUEBIRD
