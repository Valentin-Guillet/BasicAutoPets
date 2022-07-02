
#include <iostream>

#include "game.hpp"
#include "Interface/environment.hpp"
#include "Interface/Agents/agent.hpp"
#include "UI/user_interface.hpp"


int main(int argc, char** argv) {
    Environment env;

    UserInterface* ui = UserInterface::create_ui(env.game, true);

    int total_reward = 0;
    Agent* agent = Agent::create_agent("random");
    while (!env.is_done()) {
        State state = env.get_state();
        Mask mask = env.get_mask();
        total_reward += env.step(agent->act(state, mask));

        ui->display_game();
        /* std::cin.get(); */
    }

    std::cout << "Total reward = " << total_reward << std::endl;
    delete agent;
    delete ui;

    return 0;
}
