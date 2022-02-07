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
        bool end_turn(int indices[5]);

        int fight();

        void buy_animal(int index);
        void upgrade(int index_shop, int index_team);
        void sell(int index);
        void buy_object(int index, int index_target);
        void roll();
        void freeze_animal(int index);
        void freeze_object(int index);

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
