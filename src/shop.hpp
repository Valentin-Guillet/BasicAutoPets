#ifndef HEADER_SHOP
#define HEADER_SHOP

#include <vector>

#include "pet.hpp"
#include "object.hpp"
#include "team.hpp"


class Shop {
    friend class Pet;

    public:
        Shop(Team* team);
        ~Shop();

        Pet* buy_pet(int index);
        Object* buy_object(int index, int index_target);
        void freeze_pet(int index);
        void freeze_object(int index);
        void roll();

        void draw() const;

    private:
        Team* team;

        int nb_turns;
        int max_pets;
        int max_objects;

        std::vector<Pet*> pets;
        std::vector<Object*> objects;
        std::vector<bool> frozen_pets;
        std::vector<bool> frozen_object;

        Pet* create_pet();
        Object* create_object();
};


#endif // HEADER_SHOP
