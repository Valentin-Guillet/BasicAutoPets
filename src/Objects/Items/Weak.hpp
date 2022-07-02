#ifndef HEADER_OBJECTS_WEAK
#define HEADER_OBJECTS_WEAK

#include "object.hpp"
#include "shop.hpp"
#include "team.hpp"


class Weak : public Object {
    public:
        Weak(Team* team, Shop* shop);
        ~Weak() override;

        int on_damages(int value) override;
};


#endif // HEADER_OBJECTS_WEAK
