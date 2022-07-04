#ifndef HEADER_PETS_MOSQUITO
#define HEADER_PETS_MOSQUITO

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class Mosquito : public Pet {
    public:
        Mosquito(Team* team, Shop* shop);
        ~Mosquito() override;

        void on_start_battle() override;
};


#endif // HEADER_PETS_MOSQUITO
