#ifndef HEADER_PETS_SPIDER
#define HEADER_PETS_SPIDER

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class Spider : public Pet {
    public:
        Spider(Team* team, Shop* shop);
        ~Spider() override;

        void on_faint(Pos pos) override;
};


#endif // HEADER_PETS_SPIDER
