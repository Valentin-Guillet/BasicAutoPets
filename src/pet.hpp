#ifndef HEADER_PET
#define HEADER_PET

#include <iostream>
#include <string>
#include <vector>

#include "object.hpp"


class Shop;
class Team;

class Pet {
    public:
        static Pet* unserialize(Team* team, std::string pet_str);
        static Pet* create_random_pet(Team* team, Shop* shop, int max_tier);

        std::string name;
        bool is_tmp;

        Pet(std::string name, Team* team, Shop* shop);
        virtual ~Pet();

        std::string disp_stats() const;

        void give_object(Object* obj);

        void reset_stats();
        int get_attack() const;
        int get_xp() const;
        int get_level() const;
        std::string get_object_name() const;

        void attacks(Pet* other);
        void buff(int buff_attack, int buff_life, bool in_fight);
        void summon(Pet* new_pet);
        bool is_alive() const;

        virtual void on_buy() { };
        virtual void on_sell() { };
        virtual void on_hurt() { };
        virtual void on_faint();
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

        friend std::ostream& operator<<(std::ostream& os, Pet const& pet);

    protected:
        int id;

        int pack;
        int tier;
        int life;
        int attack;
        int xp;
        Object* object;

        int tmp_life;
        int tmp_attack;
        Object* tmp_object;

        Team* team;
        Shop* shop;

        std::vector<Pet*>& get_team_pets() const;

    private:
        static std::string get_random_name(int max_tier);
};


#endif // HEADER_PET
