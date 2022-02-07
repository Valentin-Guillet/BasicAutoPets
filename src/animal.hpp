#ifndef HEADER_ANIMAL
#define HEADER_ANIMAL

#include <iostream>
#include <string>
#include <vector>

#include "object.hpp"


class Shop;
class Team;

class Animal {
    public:
        static Animal* unserialize(Team* team, std::string animal_str);
        static Animal* create_random_animal(Team* team, Shop* shop, int max_tier);

        std::string name;

        Animal(std::string name, Team* team, Shop* shop);
        virtual ~Animal();

        std::string disp_stats() const;

        void give_object(Object* obj);

        void reset_stats();
        int get_xp() const;
        int get_level() const;

        void attacks(Animal* other);
        void buff(int buff_attack, int buff_life, bool in_fight);
        bool is_alive() const;
        bool is_tmp() const;

        virtual void on_buy() { };
        virtual void on_sell() { };
        virtual void on_hurt() { };
        virtual void on_faint() { };
        virtual void on_knockout() { };
        virtual void on_eat() { };
        virtual void on_level_up() { };
        virtual void on_start_turn() { };
        virtual void on_end_turn() { };
        virtual void on_start_battle() { };
        virtual void on_food_bought() { };
        virtual void on_friend_summoned() { };
        virtual void on_before_attack() { };
        virtual void on_friend_ahead_attacks() { };
        virtual void on_friend_ahead_faints() { };
        virtual void on_friend_sold() { };
        virtual void on_friend_eats_shop() { };

        friend std::ostream& operator<<(std::ostream& os, Animal const& animal);

    protected:
        int id;

        int pack;
        int tier;
        int life;
        int attack;
        int xp;
        Object* object;

        bool tmp_animal;
        int tmp_life;
        int tmp_attack;
        Object* tmp_object;

        Team* team;
        Shop* shop;

        std::vector<Animal*> get_team_animals() const;

    private:
        static std::string get_random_name(int max_tier);
};


#endif // HEADER_ANIMAL
