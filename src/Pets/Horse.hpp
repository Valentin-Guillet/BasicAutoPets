#ifndef HEADER_PETS_HORSE
#define HEADER_PETS_HORSE

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class Horse : public Pet {
    public:
        Horse(Team* team, Shop* shop);
        ~Horse() override;

        void on_friend_summoned(Pet* new_pet) override;
};


#endif // HEADER_PETS_HORSE
