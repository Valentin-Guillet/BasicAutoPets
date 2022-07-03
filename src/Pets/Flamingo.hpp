#ifndef HEADER_PETS_FLAMINGO
#define HEADER_PETS_FLAMINGO

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class Flamingo : public Pet {
    public:
        Flamingo(Team* team, Shop* shop);
        ~Flamingo() override;

        void on_faint(Pos pos) override;
};


#endif // HEADER_PETS_FLAMINGO
