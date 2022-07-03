#ifndef HEADER_INTERFACE_RANDOMAGENT
#define HEADER_INTERFACE_RANDOMAGENT

#include <random>

#include "Interface/Agents/agent.hpp"
#include "Interface/environment.hpp"


class RandomAgent : public Agent {
    public:
        RandomAgent(int seed=-1);
        ~RandomAgent();

        Action act(State state, Mask mask) override;

    private:
        std::mt19937 rng;
};


#endif // HEADER_INTERFACE_RANDOMAGENT
