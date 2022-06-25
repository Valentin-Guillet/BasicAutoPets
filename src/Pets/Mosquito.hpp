#ifndef HEADER_MOSQUITO
#define HEADER_MOSQUITO

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class Mosquito : public Pet {
    public:
        Mosquito(Team* team, Shop* shop);
        ~Mosquito() override;

        void on_start_battle(Team* adv_team) override;
};


#endif // HEADER_MOSQUITO
