#ifndef HEADER_FISH
#define HEADER_FISH

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class Fish : public Pet {
    public:
        Fish(Team* team, Shop* shop);
        ~Fish() override;

        void on_level_up() override;
};


#endif // HEADER_FISH
