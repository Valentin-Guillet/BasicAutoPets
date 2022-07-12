#ifndef HEADER_PETS_DOG
#define HEADER_PETS_DOG

#include "pet.hpp"
#include "shop.hpp"
#include "team.hpp"


class Dog : public Pet {
    public:
        Dog(Team* team, Shop* shop);
        ~Dog() override;

        void on_friend_bought(Pet* new_pet) override;
        void on_friend_summoned(Pet* new_pet) override;

    private:
        void random_buff();
};


#endif // HEADER_PETS_DOG
