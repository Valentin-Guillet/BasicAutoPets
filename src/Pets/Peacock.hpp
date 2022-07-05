#ifndef HEADER_PETS_PEACOCK
#define HEADER_PETS_PEACOCK

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class Peacock : public Pet {
    public:
        Peacock(Team* team, Shop* shop);
        ~Peacock() override;

        void on_start_battle() override;
        void on_hurt() override;

    private:
        int remaining_buffs;
};


#endif // HEADER_PETS_PEACOCK
