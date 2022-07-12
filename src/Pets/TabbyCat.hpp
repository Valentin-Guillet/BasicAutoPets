#ifndef HEADER_PETS_TABBYCAT
#define HEADER_PETS_TABBYCAT

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class TabbyCat : public Pet {
    public:
        TabbyCat(Team* team, Shop* shop);
        ~TabbyCat() override;

        void on_object(Object* object) override;
};


#endif // HEADER_PETS_TABBYCAT
