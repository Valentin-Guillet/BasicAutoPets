
#include "Interface/Agents/random.hpp"

#include <vector>


RandomAgent::RandomAgent(int seed) : Agent(seed) { }

RandomAgent::~RandomAgent() { }

Action RandomAgent::act(State state, Mask mask) {
    return get_random_action(mask);
}
