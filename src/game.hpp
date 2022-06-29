#ifndef HEADER_GAME
#define HEADER_GAME

#include <string>

#include "shop.hpp"
#include "team.hpp"


class Game {
    friend class UserInterface;

    public:
        Game();
        ~Game();

        void reset();

        void begin_turn();
        void order(size_t indices[5]);
        void end_turn();
        bool is_over() const;

        void start_fight();
        bool fight_step();
        void end_fight();
        bool in_fight() const;

        void buy_pet(size_t index);
        void combine_shop(size_t index_shop, size_t index_team);
        void combine_team(size_t src_index, size_t dst_index);
        void sell(size_t index);
        void buy_object(size_t index, size_t index_target);
        void roll();
        void freeze_pet(size_t index);
        void freeze_object(size_t index);
        void earn_money(int amount);

        std::string serialize() const;
        void unserialize(std::string game_str);

        void save_state() const;
        void load_state();

        void cheat();

    private:
        int money;
        int life;
        int victories;
        int turn;

        Team* team;
        Shop* shop;

        Team* fighting_team;
        Team* adv_team;
        FIGHT_STATUS fight_status;

        void check_money(std::string action, int amount) const;
};


#endif // HEADER_GAME
