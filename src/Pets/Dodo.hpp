#ifndef HEADER_PETS_DODO
#define HEADER_PETS_DODO

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class Dodo : public Pet {
    public:
        Dodo(Team* team, Shop* shop);
        ~Dodo() override;

        void on_start_battle(Team* adv_team) override;
};


#endif // HEADER_PETS_DODO
