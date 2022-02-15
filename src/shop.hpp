#ifndef HEADER_SHOP
#define HEADER_SHOP

#include <string>
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
        std::string get_pet_name(int index) const;

        void begin_turn();
        void roll();

        Pet* buy_pet(int index);
        void buy_object(int index, int index_target);

        void freeze_pet(int index);
        void freeze_object(int index);

        void upgrade(int attack, int life, bool tmp);

        void draw() const;

    private:
        Team* team;

        int turn;
        std::vector<Pet*> pets;
        std::vector<Object*> objects;
        std::vector<bool> frozen_pets;
        std::vector<bool> frozen_objects;
        int buff_attack;
        int buff_life;

        Pet* create_pet();
        Object* create_object();
        void check_size_pets(std::string action, int index) const;
        void check_size_objects(std::string action, int index) const;

        int get_max_pets() const;
        int get_max_objects() const;
};


#endif // HEADER_SHOP
