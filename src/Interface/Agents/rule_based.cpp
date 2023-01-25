
#include "Interface/Agents/rule_based.hpp"

#include <vector>


RuleBasedAgent::RuleBasedAgent(int seed) : Agent(seed) { }

RuleBasedAgent::~RuleBasedAgent() { }

Action RuleBasedAgent::act(State state, Mask mask) {
    // End turn
    if (state.money == 0)
        return ACTION_SIZE-1;

    if (state.money < 3) {
        // Roll
        if (randint(2) == 0)
            return 0;

        // Freeze
        std::vector<size_t> slots;
        for (size_t i=0; i<7; i++) {
            if (state.shop_type[i] > 0)
                slots.push_back(i);
        }
        if (!slots.empty())
            return 81 + choice(slots);
        return get_random_action(mask);
    }

    if (state.turn > 8)
        return get_random_action(mask);

    std::vector<size_t> slots;
    for (int i=0; i<5; i++) {
        if (state.team_id[i] > 0)
            slots.push_back(i);
    }

    // Sell pet
    if (slots.size() == 5)
        return 36 + choice(slots);

    int shop_index = -1;
    int highest_life = -1;
    for (size_t i=0; i<7; i++)  {
        if (state.shop_type[i] == 1 && state.shop_life[i] > highest_life) {
            highest_life = state.shop_life[i];
            shop_index = i;
        }
    }

    std::vector<size_t> free_slots;
    for (int i=0; i<5; i++) {
        if (state.team_id[i] == 0)
            free_slots.push_back(i);
    }

    // Buy highest-life pet
    if (shop_index != -1)
        return 1 + 5 * shop_index + choice(free_slots);

    return get_random_action(mask);
}

int RuleBasedAgent::randint(int limit) {
    std::uniform_int_distribution<> distrib(0, limit-1);
    return distrib(m_rng);
}

