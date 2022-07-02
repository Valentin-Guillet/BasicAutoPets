#ifndef HEADER_PETS_BEETLE
#define HEADER_PETS_BEETLE

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class Beetle : public Pet {
    public:
        Beetle(Team* team, Shop* shop);
        ~Beetle() override;

        void on_object(Object* object) override;
};


#endif // HEADER_PETS_BEETLE
