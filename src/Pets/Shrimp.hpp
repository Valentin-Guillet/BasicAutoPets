#ifndef HEADER_PETS_SHRIMP
#define HEADER_PETS_SHRIMP

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class Shrimp : public Pet {
    public:
        Shrimp(Team* team, Shop* shop);
        ~Shrimp() override;

        void on_friend_sold() override;
};


#endif // HEADER_PETS_SHRIMP
