#ifndef HEADER_SHOP
#define HEADER_SHOP

#include <vector>

#include "animal.hpp"
#include "item.hpp"
#include "team.hpp"


class Shop {
    friend class Animal;

    public:
        Shop(Team* team);
        ~Shop();

        Animal* buy_animal(int index);
        Item* buy_item(int index);
        void freeze_animal(int index);
        void freeze_item(int index);
        void roll();

        void draw() const;

    private:
        Team* team;

        int nb_turns;
        int max_animals;
        int max_items;

        std::vector<Animal*> animals;
        std::vector<Item*> items;
        std::vector<bool> frozen_animals;
        std::vector<bool> frozen_item;

        Animal* create_animal();
};


#endif // HEADER_SHOP
