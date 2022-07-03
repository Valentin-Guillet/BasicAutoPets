#ifndef HEADER_INTERFACE_AGENTS_RULEBASED
#define HEADER_INTERFACE_AGENTS_RULEBASED

#include "Interface/Agents/agent.hpp"
#include "Interface/environment.hpp"


class RuleBasedAgent : public Agent {
    public:
        RuleBasedAgent(int seed=-1);
        ~RuleBasedAgent();

        Action act(State state, Mask mask) override;

    private:
        int randint(int limit);
};


#endif // HEADER_INTERFACE_AGENTS_RULEBASED
