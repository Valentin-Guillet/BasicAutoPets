#ifndef HEADER_PETS_BADGER
#define HEADER_PETS_BADGER

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class Badger : public Pet {
    public:
        Badger(Team* team, Shop* shop);
        ~Badger() override;

        void on_faint(Pos pos) override;
};


#endif // HEADER_PETS_BADGER
