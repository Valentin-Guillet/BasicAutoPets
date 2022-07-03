#ifndef HEADER_PETS_ELEPHANT
#define HEADER_PETS_ELEPHANT

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class Elephant : public Pet {
    public:
        Elephant(Team* team, Shop* shop);
        ~Elephant() override;

        void on_before_attack() override;
};


#endif // HEADER_PETS_ELEPHANT
