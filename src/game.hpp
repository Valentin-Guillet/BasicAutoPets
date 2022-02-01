#ifndef HEADER_GAME
#define HEADER_GAME

#include "shop.hpp"
#include "team.hpp"


enum class Action {
    BUY_ANIMAL, UPGRADE, SELL, BUY_OBJECT, ROLL, FREEZE, END_TURN,
};


class Game {
    public:
        Game();
        ~Game();

        void begin_turn();
        void end_turn();

        void buy_animal(int index);
        void upgrade(int index_shop, int index_team);
        void sell(int index);
        void buy_object(int index);
        void roll();
        void freeze_animal(int index);
        void freeze_object(int index);
        void end_turn(int indices[5]);

        void get_state() const;

        void draw() const;

    private:
        int money;
        int life;
        int victories;
        int turn;

        Team* team;
        Shop* shop;
};



#endif // HEADER_GAME
