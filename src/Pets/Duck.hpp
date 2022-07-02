#ifndef HEADER_PETS_DUCK
#define HEADER_PETS_DUCK

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class Duck : public Pet {
    public:
        Duck(Team* team, Shop* shop);
        ~Duck() override;

        void on_sell() override;
};


#endif // HEADER_PETS_DUCK
