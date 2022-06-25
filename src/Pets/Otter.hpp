#ifndef HEADER_OTTER
#define HEADER_OTTER

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class Otter : public Pet {
    public:
        Otter(Team* team, Shop* shop);
        ~Otter() override;

        void on_buy() override;
};


#endif // HEADER_OTTER
