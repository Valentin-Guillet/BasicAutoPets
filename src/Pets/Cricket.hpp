#ifndef HEADER_PETS_CRICKET
#define HEADER_PETS_CRICKET

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class Cricket : public Pet {
    public:
        Cricket(Team* team, Shop* shop);
        ~Cricket() override;

        void on_faint(Pos pos) override;
};


#endif // HEADER_PETS_CRICKET
