#ifndef HEADER_SHOP
#define HEADER_SHOP

#include <vector>

#include "animal.hpp"
#include "object.hpp"
#include "team.hpp"


class Shop {
    friend class Animal;

    public:
        Shop(Team* team);
        ~Shop();

        Animal* buy_animal(int index);
        Object* buy_object(int index, int index_target);
        void freeze_animal(int index);
        void freeze_object(int index);
        void roll();

        void draw() const;

    private:
        Team* team;

        int nb_turns;
        int max_animals;
        int max_objects;

        std::vector<Animal*> animals;
        std::vector<Object*> objects;
        std::vector<bool> frozen_animals;
        std::vector<bool> frozen_object;

        Animal* create_animal();
        Object* create_object();
};


#endif // HEADER_SHOP
