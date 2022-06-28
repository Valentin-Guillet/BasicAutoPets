#ifndef HEADER_PIG
#define HEADER_PIG

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class Pig : public Pet {
    public:
        Pig(Team* team, Shop* shop);
        ~Pig() override;

        void on_sell() override;
};


#endif // HEADER_PIG
