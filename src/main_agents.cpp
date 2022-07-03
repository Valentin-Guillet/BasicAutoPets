
#include <iostream>

#include "game.hpp"
#include "Interface/environment.hpp"
#include "Interface/Agents/agent.hpp"
#include "UI/user_interface.hpp"


int main(int argc, char** argv) {
    bool display = false;
    for (int i=1; i<argc; i++) {
        std::string arg(argv[i]);
        if (arg == "-d" || arg == "--display")
            display = true;
    }

    Environment env;
    UserInterface* ui = nullptr;
    if (display)
        ui = UserInterface::create_ui(env.game, true);

    int total_reward = 0;
    Agent* agent = Agent::create_agent("rule_based");

    for (size_t i=0; i<100; i++) {
        while (!env.is_done()) {
            State state = env.get_state();

            Mask mask = env.get_mask();
            Action action = agent->act(state, mask);
            total_reward += env.step(action);

            if (display) {
                ui->display_game();
                std::cin.get();
            }
        }
    env.reset();
    }

    std::cout << "Total reward = " << total_reward << std::endl;
    delete agent;
    delete ui;

    return 0;
}
