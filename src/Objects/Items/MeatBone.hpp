#ifndef HEADER_OBJECTS_MEATBONE
#define HEADER_OBJECTS_MEATBONE

#include "object.hpp"
#include "shop.hpp"
#include "team.hpp"


class MeatBone : public Object {
    public:
        MeatBone(Team* team, Shop* shop);
        ~MeatBone() override;

        int on_attack(int value) override;
};


#endif // HEADER_OBJECTS_MEATBONE
