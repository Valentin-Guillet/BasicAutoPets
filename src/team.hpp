#ifndef HEADER_TEAM
#define HEADER_TEAM

#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "pet.hpp"
#include "object.hpp"


class UserInterface;
class Team;
using TeamList = std::unordered_map<int, std::vector<Team*>>;

class Team {
    friend class UserInterface;

    public:
        static Team* unserialize(std::string team_str);
        static Team* get_random_team(int turn);
        static void clear_team_list();

        Team();
        ~Team();

        size_t get_nb_pets() const;
        void can_combine(size_t index, std::string other_pet) const;
        void can_combine(size_t src_index, size_t dst_index) const;
        bool is_fighting() const;
        std::vector<Pet*>& get_pets();

        void begin_turn();
        void order(size_t order[5]);
        void end_turn();
        void reset();

        void add(Pet* new_pet);
        void combine(size_t index, Pet* other_pet);
        void combine(size_t src_index, size_t dst_index);
        int sell(size_t index);

        void summon(Pet* base_pet, Pet* new_pet);
        void faint(size_t index);

        void give_object(size_t index, Object* obj);
        int fight(Team* other_team);
        int fight_step(Team* adv_team);
        void disp_fight(Team const* const other_team) const;
        std::tuple<int, std::string, std::string> get_fight_str(Team* other_team);

        std::string serialize(bool tmp=false) const;

    private:
        static TeamList team_list;
        static void load_teams();

        int turn;
        bool in_fight = false;

        std::vector<Pet*> pets;
        std::vector<Pet*> tmp_pets;

        int check_end_of_battle(Team* adv_team) const;
        std::vector<Pet*> order_pets(Team* adv_team) const;

        void check_size(std::string action, size_t index) const;
        void _add(Pet* pet);
};


#endif // HEADER_TEAM
