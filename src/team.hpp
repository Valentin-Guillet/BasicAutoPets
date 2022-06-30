#ifndef HEADER_TEAM
#define HEADER_TEAM

#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "pet.hpp"
#include "object.hpp"


class Game;
class Team;
using TeamList = std::unordered_map<int, std::vector<Team*>>;
enum class FIGHT_STATUS { None, Fighting, Win, Loss, Draw };

class Team {
    friend class UserInterface;
    friend class Environment;

    public:
        static Team* unserialize(Game* game, std::string team_str);
        static Team* get_random_team(int turn);
        static Team* copy_team(Team const* team);
        static void clear_team_list();

        static FIGHT_STATUS fight_step(Team* team, Team* adv_team);

        Team(Game* game);
        Team(Team const& team);
        ~Team();

        size_t get_nb_pets() const;
        std::vector<Pet*>& get_pets();
        void can_combine(size_t index, std::string other_pet) const;
        void can_combine(size_t src_index, size_t dst_index) const;

        void begin_turn();
        void move(size_t src_index, size_t dst_index);
        void end_turn();
        void reset();

        void add(Pet* new_pet);
        void combine(size_t index, Pet* other_pet, bool activate_on_buy=true);
        void combine(size_t src_index, size_t dst_index);
        int sell(size_t index);

        void summon(Pet* base_pet, Pet* new_pet);
        void faint(size_t index);

        void give_object(size_t index, Object* obj);
        void earn_money(int amount) const;
        std::tuple<int, std::string, std::string> get_fight_str(Team* other_team);

        std::string serialize() const;

    private:
        static TeamList team_list;
        static void load_teams();
        static std::vector<Pet*> order_pets(Team const* team, Team const* adv_team);
        static FIGHT_STATUS start_of_battle(Team* team, Team* adv_team);
        static FIGHT_STATUS check_end_of_battle(Team const* team, Team const* adv_team);

        Game* game;
        int turn;
        bool in_fight = false;
        std::vector<Pet*> pets;
        std::vector<size_t> order;

        void sort();
        void append_pet(Pet* new_pet);
        void remove_pet(size_t index);
        void check_size(std::string action, size_t index) const;
        void remove_dead_pets();
};


#endif // HEADER_TEAM
