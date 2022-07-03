#ifndef HEADER_INTERFACE_ENVIRONMENT
#define HEADER_INTERFACE_ENVIRONMENT

#include <array>

#include "game.hpp"


const size_t ACTION_SIZE = 89;
const size_t STATE_SIZE = 4 + 7 * 5 + 2 + 7 * 7;

using Action = size_t;
using Mask = std::array<bool, ACTION_SIZE>;

struct State {
    int turn;
    int life;
    int victories;
    int money;

    int team_id[5];
    int team_tier[5];
    int team_attack[5];
    int team_attack_buff[5];
    int team_life[5];
    int team_life_buff[5];
    int team_xp[5];

    int shop_attack_buff;
    int shop_life_buff;
    int shop_type[7];
    int shop_id[7];
    int shop_tier[7];
    int shop_attack[7];
    int shop_life[7];
    int shop_cost[7];
    int shop_frozen[7];
};

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
