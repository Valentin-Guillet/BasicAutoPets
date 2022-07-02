#ifndef HEADER_PETS_FISH
#define HEADER_PETS_FISH

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class Fish : public Pet {
    public:
        Fish(Team* team, Shop* shop);
        ~Fish() override;

        void on_level_up() override;
};


#endif // HEADER_PETS_FISH
