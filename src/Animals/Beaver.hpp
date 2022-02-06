#ifndef HEADER_BEAVER
#define HEADER_BEAVER

#include "animal.hpp"
#include "shop.hpp"
#include "team.hpp"


class Beaver : public Animal {
    public:
        Beaver(Team* team, Shop* shop);
        ~Beaver() override;

        void on_sell() override;
};


#endif // HEADER_BEAVER
