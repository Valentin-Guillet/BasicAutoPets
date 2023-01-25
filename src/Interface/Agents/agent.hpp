#ifndef HEADER_INTERFACE_AGENT
#define HEADER_INTERFACE_AGENT

#include <random>
#include <string>
#include <vector>

#include "Interface/environment.hpp"


class Agent {
    public:
        static Agent* create_agent(std::string name);

        Agent(int seed);
        virtual ~Agent();

        virtual Action act(State state, Mask mask) = 0;

    protected:
        std::mt19937 m_rng;

        size_t choice(std::vector<size_t> vect);
        Action get_random_action(Mask mask);
};


#endif // HEADER_INTERFACE_AGENT
