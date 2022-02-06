#ifndef HEADER_TEAM
#define HEADER_TEAM

#include <unordered_map>
#include <utility>
#include <vector>

#include "animal.hpp"


class Team;
using TeamList = std::unordered_map<int, std::vector<Team*>>;

class Team {
    friend class Animal;

    public:
        static std::pair<int, Team*> unserialize(std::string team_str);
        static Team* get_random_team(int turn);
        static void clear_team_list();

        ~Team();

        void begin_turn();
        void reset_animals();
        void order(int order[5]);

        void add(Animal* animal);
        void upgrade(int index, Animal* other_animal);
        int sell(int index);

        int fight(Team* other_team);
        void disp_fight(Team const* const other_team) const;
        bool is_fighting() const;

        void draw() const;

    private:
        static TeamList team_list;
        static void load_teams();

        bool in_fight = false;

        void _add(Animal* animal);

        std::vector<Animal*> animals;
        std::vector<Animal*> tmp_animals;
};


#endif // HEADER_TEAM
