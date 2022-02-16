#ifndef HEADER_USER_INTERFACE
#define HEADER_USER_INTERFACE


#include "game.hpp"


class UserInterface {
    public:
        UserInterface(Game* game);
        ~UserInterface();

        bool run();

    private:
        Game* game;

        bool play_again() const;
        bool act();

        void draw_frame() const;
        void draw_game_state() const;
        void draw_team() const;
        void draw_shop() const;
        void draw_action() const;
};



#endif // HEADER_USER_INTERFACE
