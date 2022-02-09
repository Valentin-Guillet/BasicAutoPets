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

        int get_cost_object(int index) const;

        void begin_turn();
        Pet* buy_pet(int index);
        void buy_object(int index, int index_target);
        void freeze_pet(int index);
        void freeze_object(int index);
        void roll();

        void draw() const;

    private:
        Team* team;

        int turns;
        std::vector<Pet*> pets;
        std::vector<Object*> objects;
        std::vector<bool> frozen_pets;
        std::vector<bool> frozen_object;

        Pet* create_pet();
        Object* create_object();

        int get_max_pets() const;
        int get_max_objects() const;
};


#endif // HEADER_SHOP
