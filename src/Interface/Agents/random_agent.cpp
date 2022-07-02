
#include "Interface/Agents/random_agent.hpp"

#include <vector>


RandomAgent::RandomAgent(int seed) {
    if (seed == -1) {
        std::random_device device;
        rng.seed(device());
    } else {
        rng.seed(seed);
    }
}

RandomAgent::~RandomAgent() { }

Action RandomAgent::act(State state, Mask mask) {
    std::vector<size_t> valid_actions;
    for (size_t i=0; i<ACTION_SIZE; i++) {
        if (mask[i])
            valid_actions.push_back(i);
    }

    std::uniform_int_distribution<> distrib(0, valid_actions.size()-1);
    return valid_actions[distrib(rng)];
}
