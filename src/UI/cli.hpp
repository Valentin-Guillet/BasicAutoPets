#ifndef HEADER_UI_CLI
#define HEADER_UI_CLI

#include "UI/abstract_ui.hpp"
#include "game.hpp"
#include "object.hpp"
#include "pet.hpp"


class CLI : public UserInterface {
    public:
        CLI(Game* game);
        ~CLI();

        bool run() override;

    private:
        bool play_again() const;
};


#endif // HEADER_UI_CLI
