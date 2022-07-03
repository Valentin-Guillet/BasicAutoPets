#ifndef HEADER_PETS_SLOTH
#define HEADER_PETS_SLOTH

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class Sloth : public Pet {
    public:
        Sloth(Team* team, Shop* shop);
        ~Sloth() override;
};


#endif // HEADER_PETS_SLOTH
