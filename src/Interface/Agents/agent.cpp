
#include "Interface/Agents/agent.hpp"

#include "Interface/Agents/random_agent.hpp"


Agent* Agent::create_agent(std::string name) {
    return new RandomAgent();
}

Agent::Agent() { }

Agent::~Agent() { }
