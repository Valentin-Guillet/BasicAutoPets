#ifndef HEADER_PETS_HEDGEHOG
#define HEADER_PETS_HEDGEHOG

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class Hedgehog : public Pet {
    public:
        Hedgehog(Team* team, Shop* shop);
        ~Hedgehog() override;

        void on_faint(Pos pos) override;
};


#endif // HEADER_PETS_HEDGEHOG
