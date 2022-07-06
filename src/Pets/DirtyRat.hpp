#ifndef HEADER_PETS_DIRTYRAT
#define HEADER_PETS_DIRTYRAT

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class DirtyRat : public Pet {
    public:
        DirtyRat(Team* team, Shop* shop);
        ~DirtyRat() override;
};


#endif // HEADER_PETS_DIRTYRAT
