#ifndef HEADER_TEAM
#define HEADER_TEAM

#include <unordered_map>
#include <utility>
#include <vector>

#include "pet.hpp"
#include "object.hpp"


class Team;
using TeamList = std::unordered_map<int, std::vector<Team*>>;

class Team {
    friend class Pet;
    friend class Object;

    public:
        static std::pair<int, Team*> unserialize(std::string team_str);
        static Team* get_random_team(int turn);
        static void clear_team_list();

        ~Team();

        void begin_turn();
        void order(int order[5]);
        size_t get_nb_pets() const;

        void add(Pet* pet);
        void upgrade(int index, Pet* other_pet);
        int sell(int index);
        void equip_item(int index, Object* item);

        int fight(Team* other_team);
        void disp_fight(Team const* const other_team) const;
        bool is_fighting() const;

        void draw() const;

    private:
        static TeamList team_list;
        static void load_teams();

        bool in_fight = false;

        void reset_pets();
        void _add(Pet* pet);

        std::vector<Pet*> pets;
        std::vector<Pet*> tmp_pets;
};


#endif // HEADER_TEAM
