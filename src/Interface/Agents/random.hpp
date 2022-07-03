#ifndef HEADER_INTERFACE_AGENTS_RANDOM
#define HEADER_INTERFACE_AGENTS_RANDOM

#include "Interface/Agents/agent.hpp"
#include "Interface/environment.hpp"


class RandomAgent : public Agent {
    public:
        RandomAgent(int seed=-1);
        ~RandomAgent();

        Action act(State state, Mask mask) override;
};


#endif // HEADER_INTERFACE_AGENTS_RANDOM
