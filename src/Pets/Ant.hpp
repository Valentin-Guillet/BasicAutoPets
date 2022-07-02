#ifndef HEADER_PETS_ANT
#define HEADER_PETS_ANT

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class Ant : public Pet {
    public:
        Ant(Team* team, Shop* shop);
        ~Ant() override;

        void on_faint(Pos pos) override;
};


#endif // HEADER_PETS_ANT
