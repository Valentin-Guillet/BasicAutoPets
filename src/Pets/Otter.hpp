#ifndef HEADER_PETS_OTTER
#define HEADER_PETS_OTTER

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class Otter : public Pet {
    public:
        Otter(Team* team, Shop* shop);
        ~Otter() override;

        void on_buy() override;
};


#endif // HEADER_PETS_OTTER
