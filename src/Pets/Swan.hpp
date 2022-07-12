#ifndef HEADER_PETS_SWAN
#define HEADER_PETS_SWAN

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class Swan : public Pet {
    public:
        Swan(Team* team, Shop* shop);
        ~Swan() override;

        void on_start_turn() override;
};


#endif // HEADER_PETS_SWAN
