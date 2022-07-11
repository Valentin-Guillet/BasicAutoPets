#ifndef HEADER_PET
#define HEADER_PET

#include <string>
#include <vector>

#include "object.hpp"


class Shop;
class Team;

class Pet {
    friend class UserInterface;
    friend class Environment;

    public:
        static Pet* unserialize(Team* team, Shop* shop, std::string pet_str);
        static Pet* create_random_pet(Team* team, Shop* shop, int max_tier, bool strict_tier=false);
        static Pet* copy_pet(Pet const* pet, Team* team, Shop* shop);

        std::string name;

        Pet(std::string name, Team* team, Shop* shop);
        virtual ~Pet();

        void bind(Team* adv_team);
        void bind(Shop* shop);
        Team* get_adv_team() const;

        int get_attack() const;
        int get_life() const;
        int get_xp() const;
        int get_level() const;
        bool is_alive() const;

        void set_stats(int new_attack, int new_life, int new_xp);
        void reset_stats();

        void equip_object(Object* obj);
        void attacks(Pet* adv_pet) const;
        void take_damage(int value, bool activate_hurt=true);
        void buff(int buff_attack, int buff_life, bool is_tmp);
        void gain_xp(int amount);
        void combine(Pet* const other);
        void kill();

        virtual void on_buy() { };
        virtual void on_sell() { };
        virtual void on_hurt() { };
        virtual void on_faint(size_t index);
        virtual void on_knockout() { };
        virtual void on_object(Object* obj) { };
        virtual void on_object_bought(size_t index, Object* obj) { };
        virtual void on_level_up() { };
        virtual void on_start_turn() { };
        virtual void on_end_turn() { };
        virtual void on_start_battle() { };
        virtual void on_friend_summoned(Pet* new_pet) { };
        virtual void on_before_attack() { };
        virtual void on_friend_ahead_attacks() { };
        virtual void on_friend_ahead_faints() { };
        virtual void on_friend_bought(Pet* new_pet);
        virtual void on_friend_sold() { };
        virtual void on_friend_eats_shop() { };

        std::string serialize() const;

    protected:
        std::string repr;

        Team* team;
        Team* adv_team;
        Shop* shop;

        int id;
        int pack;
        int tier;
        int attack;
        int life;
        int xp;
        Object* object;

        int attack_buff;
        int life_buff;

    private:
        static std::string get_random_name(int max_tier, bool strict_tier=false);
};


#endif // HEADER_PET
