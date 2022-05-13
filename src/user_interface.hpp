#ifndef HEADER_USER_INTERFACE
#define HEADER_USER_INTERFACE


#include <string>

#include "game.hpp"
#include "object.hpp"
#include "pet.hpp"


enum class UIState { none, buy, sell, freeze, combine_team, combine_shop, order, fighting };

class UserInterface {
    public:
        UserInterface(Game* game);
        ~UserInterface();

        bool run();

    private:
        Game* game;
        UIState state;
        std::string status;

        bool play_again() const;
        bool act();

        bool take_action();
        void buy();
        void sell();
        void freeze();
        void combine_team();
        void combine_shop();
        void order();
        bool fight();

        void draw_frame() const;
        void draw_game_state() const;
        void draw_pet(Pet* pet, int x, int y, bool draw_xp, bool in_shop, bool frozen=false) const;
        void draw_object(Object* pet, int x, int y, bool frozen=false) const;
        void draw_team() const;
        void draw_shop() const;
        void draw_action() const;
        void draw_fight() const;
        void draw_status() const;
        void draw_log() const;
};



#endif // HEADER_USER_INTERFACE
