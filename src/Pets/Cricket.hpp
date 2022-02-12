#ifndef HEADER_CRICKET
#define HEADER_CRICKET

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class Cricket : public Pet {
    public:
        Cricket(Team* team, Shop* shop);
        ~Cricket() override;

        void on_faint() override;
};


#endif // HEADER_CRICKET
