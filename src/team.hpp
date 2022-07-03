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

using Pos = size_t;

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

        void bind(Shop* shop) const;

        size_t get_nb_pets() const;
        std::vector<Pet*>& get_pets();
        void can_combine(Pos pos, std::string other_pet) const;
        void can_combine(Pos src_pos, Pos dst_pos) const;

        void begin_turn();
        void move(Pos src_pos, Pos dst_pos);
        void end_turn();
        void reset();

        size_t pos_to_index(Pos pos) const;
        bool has_pet(Pos pos) const;
        void add(Pet* new_pet, Pos pos);
        void combine(Pos pos, Pet* other_pet, bool activate_on_buy=true);
        void combine(Pos src_pos, Pos dst_pos);
        int sell(Pos pos);

        void summon(size_t index, Pet* new_pet);
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
        std::vector<Pos> order;

        void sort();
        void append_pet(Pet* new_pet, Pos pos, bool insert=false);
        void remove_pet(size_t index);
        void remove_dead_pets();
};


#endif // HEADER_TEAM
