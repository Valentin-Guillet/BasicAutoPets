#ifndef HEADER_PETS_LADYBUG
#define HEADER_PETS_LADYBUG

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class LadyBug : public Pet {
    public:
        LadyBug(Team* team, Shop* shop);
        ~LadyBug() override;

        void on_object_bought(size_t index, Object* obj) override;
};


#endif // HEADER_PETS_LADYBUG
