#ifndef HEADER_UI_GUI
#define HEADER_UI_GUI

#include <string>

#include "UI/user_interface.hpp"
#include "game.hpp"
#include "object.hpp"
#include "pet.hpp"


enum class UIState { none, buy, sell, freeze, combine, order, fighting };

class GUI : public UserInterface {
    public:
        GUI(Game* game);
        ~GUI();

        bool run() override;
        void display_game() const override;

    private:
        UIState m_state;
        std::string m_status;

        bool play_again() const;
        bool act();

        bool take_action();
        void buy();
        void sell();
        void freeze();
        void combine();
        void move();
        void fight();

        void buy_pet(size_t index);
        void buy_object(size_t index);

        int get_fighting_action();

        void disp_frame() const;
        void disp_game_state() const;
        void disp_pet(Pet const* pet, int x, int y, bool disp_xp, bool in_shop, bool frozen=false) const;
        void disp_object(Object const* obj, int x, int y, bool frozen=false) const;
        void disp_team() const;
        void disp_shop() const;
        void disp_action() const;
        void disp_fight() const;
        void disp_status() const;
        void disp_logs(bool clear=true) const;
        void disp_play_again(bool invalid=false) const;
};


#endif // HEADER_UI_GUI
