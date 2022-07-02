#ifndef HEADER_INTERFACE_AGENT
#define HEADER_INTERFACE_AGENT

#include <string>

#include "Interface/environment.hpp"


class Agent {
    public:
        static Agent* create_agent(std::string name);

        Agent();
        virtual ~Agent();

        virtual Action act(State state, Mask mask) = 0;
};


#endif // HEADER_INTERFACE_AGENT
