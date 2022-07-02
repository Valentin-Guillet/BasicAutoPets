#ifndef HEADER_PETS_BAT
#define HEADER_PETS_BAT

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class Bat : public Pet {
    public:
        Bat(Team* team, Shop* shop);
        ~Bat() override;

        void on_start_battle(Team* adv_team) override;
};


#endif // HEADER_PETS_BAT
