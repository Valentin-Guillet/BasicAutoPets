#ifndef HEADER_INTERFACE_ENVIRONMENT
#define HEADER_INTERFACE_ENVIRONMENT

#include <array>

#include "game.hpp"


using Action = int;

const int ACTION_SIZE = 99;
const int STATE_SIZE = 0;

class Environment {
    public:
        Environment(Game* game);
        ~Environment();

        void get_state() const;
        void take_action(Action action);

    private:
        Game* game;

        std::array<bool, ACTION_SIZE> get_mask() const;
};

#endif // HEADER_INTERFACE_ENVIRONMENT
