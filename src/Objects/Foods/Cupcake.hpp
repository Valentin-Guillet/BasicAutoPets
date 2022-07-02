#ifndef HEADER_OBJECTS_CUPCAKE
#define HEADER_OBJECTS_CUPCAKE

#include "object.hpp"
#include "shop.hpp"
#include "team.hpp"


class Cupcake : public Object {
    public:
        Cupcake(Team* team, Shop* shop);
        ~Cupcake() override;

        void on_buy(size_t index) override;
};


#endif // HEADER_OBJECTS_CUPCAKE
