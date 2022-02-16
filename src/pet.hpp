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
        static Pet* create_random_pet(Team* team, Shop* shop, int max_tier, bool strict_tier=false);

        std::string name;
        bool is_tmp;

        Pet(std::string name, Team* team, Shop* shop);
        virtual ~Pet();

        std::string get_repr() const;
        std::string get_object_name() const;
        int get_attack() const;
        int get_xp() const;
        int get_level() const;
        bool is_alive() const;
        std::string disp_stats() const;

        void reset_stats();
        void equip_object(Object* obj);
        void attacks(Pet* other);
        void buff(int buff_attack, int buff_life, bool in_fight);
        void gain_xp(int amount);
        void combine(Pet* const other);


        virtual void on_buy() { };
        virtual void on_sell() { };
        virtual void on_hurt() { };
        virtual void on_faint();
        virtual void on_knockout() { };
        virtual void on_object(Object* obj) { };
        virtual void on_object_bought(size_t index, Object* obj) { };
        virtual void on_level_up() { };
        virtual void on_start_turn() { };
        virtual void on_end_turn() { };
        virtual void on_start_battle() { };
        virtual void on_friend_summoned() { };
        virtual void on_before_attack() { };
        virtual void on_friend_ahead_attacks() { };
        virtual void on_friend_ahead_faints() { };
        virtual void on_friend_sold() { };
        virtual void on_friend_eats_shop() { };

        std::string serialize() const;
        friend std::ostream& operator<<(std::ostream& os, Pet const& pet);

    protected:
        std::string repr;

        Team* team;
        Shop* shop;

        int id;
        int pack;
        int tier;
        int attack;
        int life;
        int xp;
        Object* object;

        int tmp_attack;
        int tmp_life;
        Object* tmp_object;

        std::vector<Pet*>& get_team_pets() const;

    private:
        static std::string get_random_name(int max_tier, bool strict_tier=false);
};


#endif // HEADER_PET
