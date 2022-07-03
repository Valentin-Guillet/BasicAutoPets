#ifndef HEADER_PETS_DROMEDARY
#define HEADER_PETS_DROMEDARY

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class Dromedary : public Pet {
    public:
        Dromedary(Team* team, Shop* shop);
        ~Dromedary() override;

        void on_start_turn() override;
};


#endif // HEADER_PETS_DROMEDARY
