#ifndef HEADER_SHOP
#define HEADER_SHOP

#include <string>
#include <vector>

#include "pet.hpp"
#include "object.hpp"
#include "team.hpp"


class UserInterface;

class Shop {
    friend class Pet;
    friend class UserInterface;

    public:
        static Shop* unserialize(Team* team, std::string shop_str);

        Shop(Team* team);
        ~Shop();

        int get_cost_object(size_t index) const;
        std::string get_pet_name(size_t index) const;

        void begin_turn();
        void roll();
        void create_bonus_pet();

        Pet* buy_pet(size_t index);
        void buy_object(size_t index, size_t index_target);

        void freeze_pet(size_t index);
        void freeze_object(size_t index);

        void upgrade(int attack, int life, bool tmp);

        std::string serialize() const;

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
        void check_size_pets(std::string action, size_t index) const;
        void check_size_objects(std::string action, size_t index) const;

        size_t get_max_pets() const;
        size_t get_max_objects() const;
};


#endif // HEADER_SHOP
