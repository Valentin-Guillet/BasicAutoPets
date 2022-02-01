#ifndef HEADER_SHOP
#define HEADER_SHOP

#include <vector>


class Animal;
class Object;
class Team;

class Shop {
    public:
        Shop(Team* team);

        Animal* buy_animal(int index);
        Object* buy_object(int index);
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
};


#endif // HEADER_SHOP
