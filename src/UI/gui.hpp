#ifndef HEADER_UI_GUI
#define HEADER_UI_GUI

#include <string>

#include "UI/abstract_ui.hpp"
#include "game.hpp"
#include "object.hpp"
#include "pet.hpp"


enum class UIState { none, buy, sell, freeze, combine_team, combine_shop, order, fighting };

class GUI : public UserInterface {
    public:
        GUI(Game* game);
        ~GUI();

        bool run() override;

    private:
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
        void fight();

        int get_fighting_action();

        void draw_frame() const;
        void draw_game_state() const;
        void draw_pet(Pet const* pet, int x, int y, bool draw_xp, bool in_shop, bool frozen=false) const;
        void draw_object(Object const* obj, int x, int y, bool frozen=false) const;
        void draw_team() const;
        void draw_shop() const;
        void draw_action() const;
        void draw_fight() const;
        void draw_status() const;
        void draw_logs(bool clear=true) const;
};


#endif // HEADER_UI_GUI
