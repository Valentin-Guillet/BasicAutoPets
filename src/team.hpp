#ifndef HEADER_TEAM
#define HEADER_TEAM

#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "pet.hpp"
#include "object.hpp"


class Team;
using TeamList = std::unordered_map<int, std::vector<Team*>>;

class Team {
    friend class Pet;
    friend class Object;

    public:
        static Team* unserialize(std::string team_str);
        static Team* get_random_team(int turn);
        static void clear_team_list();

        Team();
        ~Team();

        size_t get_nb_pets() const;
        void can_combine(int index, std::string other_pet) const;
        void can_combine(int src_index, int dst_index) const;
        bool is_fighting() const;

        void begin_turn();
        void order(int order[5]);
        void end_turn();

        void add(Pet* pet);
        void combine(int index, Pet* other_pet);
        void combine(int src_index, int dst_index);
        int sell(int index);

        void summon(Pet* base_pet, Pet* new_pet);
        void faint(int index);

        void give_object(int index, Object* obj);
        int fight(Team* other_team);
        void disp_fight(Team const* const other_team) const;
        std::tuple<int, std::string, std::string> get_fight_str(Team* other_team);

        void draw() const;
        std::string serialize(bool tmp=false) const;

    private:
        static TeamList team_list;
        static void load_teams();

        int turn;
        bool in_fight = false;

        std::vector<Pet*> pets;
        std::vector<Pet*> tmp_pets;

        void check_size(std::string action, int index) const;
        void reset();
        void _add(Pet* pet);
};


#endif // HEADER_TEAM
