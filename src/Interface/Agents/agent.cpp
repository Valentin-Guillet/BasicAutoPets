
#include "Interface/Agents/agent.hpp"

#include "Interface/Agents/random.hpp"
#include "Interface/Agents/rule_based.hpp"


Agent* Agent::create_agent(std::string name) {
    if (name == "rule_based")
        return new RuleBasedAgent();
    return new RandomAgent();
}

Agent::Agent(int seed) {
    if (seed == -1)
        rng.seed(std::random_device()());
    else
        rng.seed(seed);
}

Agent::~Agent() { }


size_t Agent::choice(std::vector<size_t> vect) {
    std::uniform_int_distribution<> distrib(0, vect.size()-1);
    return vect[distrib(rng)];
}

Action Agent::get_random_action(Mask mask) {
    std::vector<size_t> valid_actions;
    for (size_t i=0; i<ACTION_SIZE; i++) {
        if (mask[i])
            valid_actions.push_back(i);
    }
    return choice(valid_actions);
}
