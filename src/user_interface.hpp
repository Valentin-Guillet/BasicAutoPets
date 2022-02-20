#ifndef HEADER_USER_INTERFACE
#define HEADER_USER_INTERFACE


#include "game.hpp"
#include "object.hpp"
#include "pet.hpp"


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
        void draw_pet(Pet* pet, int x, int y, bool draw_xp, bool frozen=false) const;
        void draw_object(Object* pet, int x, int y, bool frozen=false) const;
        void draw_team() const;
        void draw_shop() const;
        void draw_action() const;
};



#endif // HEADER_USER_INTERFACE
