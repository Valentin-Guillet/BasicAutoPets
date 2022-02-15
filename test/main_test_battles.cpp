
#include <iostream>
#include <string>

#include "team.hpp"
#include "utils.hpp"


int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Not enough args to test\nUsage: ./main_test \"$team1\" \"$team2\"" << std::endl;
        return 1;
    }

    bool debug = false;
    int index = 1;
    if (strcmp(argv[1], "--debug") == 0) {
        debug = true;
        index++;
    }

    Team* team1 = Team::unserialize(argv[index++]);
    Team* team2 = Team::unserialize(argv[index++]);

    if (debug) {
        spdlog::set_level(spdlog::level::debug);
        team1->fight(team2);
    } else {
        auto [won, team_str1, team_str2] = team1->get_fight_str(team2);
        std::cout << won << "\n" << team_str1 << "\n" << team_str2 << std::endl;
    }
    return 0;
}
