#ifndef HEADER_ANIMAL
#define HEADER_ANIMAL

#define PACK_STANDARD 1
#define PACK_DLC1 2

#include <string>


class Team;
class Shop;

class Animal {
    public:
        static Animal* create_random_animal(Team* team, Shop* shop, int max_tier);

        std::string name;

        Animal(std::string name, Team* team, Shop* shop);
        virtual ~Animal() { };

        void reset_stats();
        int get_xp() const;

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

        virtual void draw() const;

    protected:
        int id;

        int pack;
        int tier;
        int life;
        int attack;
        int xp;

        int tmp_life;
        int tmp_attack;

        Team* team;
        Shop* shop;
};


#endif // HEADER_ANIMAL
