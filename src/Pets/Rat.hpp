#ifndef HEADER_PETS_RAT
#define HEADER_PETS_RAT

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class Rat : public Pet {
    public:
        Rat(Team* team, Shop* shop);
        ~Rat() override;

        void on_faint(Pos pos) override;
};


#endif // HEADER_PETS_RAT
