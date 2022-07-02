#ifndef HEADER_INTERFACE_ENVIRONMENT
#define HEADER_INTERFACE_ENVIRONMENT

#include <array>

#include "game.hpp"


const size_t ACTION_SIZE = 89;
const size_t STATE_SIZE = 0;

using Action = size_t;
using State = int;
using Mask = std::array<bool, ACTION_SIZE>;

class Environment {
    public:
        Environment();
        ~Environment();

        void reset();
        bool is_done() const;
        State get_state() const;
        int step(Action action);

        Mask get_mask() const;

        Game* game;
    private:
};

#endif // HEADER_INTERFACE_ENVIRONMENT
