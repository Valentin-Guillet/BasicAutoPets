#ifndef HEADER_UI_ABSTRACT
#define HEADER_UI_ABSTRACT


#include <string>

#include "game.hpp"
#include "object.hpp"
#include "pet.hpp"


class UserInterface {
    public:
        UserInterface(Game* game);
        virtual ~UserInterface();

        virtual bool run() = 0;

    protected:
        Game* game;

        int get_money() const;
        int get_life() const;
        int get_victories() const;
        int get_turn() const;

        int nb_pets_in_shop() const;
        int nb_objs_in_shop() const;
        Pet const* get_team_pet(size_t index) const;
        Pet const* get_shop_pet(size_t index) const;
        Pet const* get_adv_pet(size_t index) const;
        Object const* get_shop_object(size_t index, bool human_index) const;
        bool is_pet_frozen(size_t index) const;
        bool is_obj_frozen(size_t index) const;

        std::string get_name(Pet const* pet) const;
        std::string get_repr(Pet const* pet) const;
        std::string get_object_repr(Pet const* pet) const;
        bool has_attack_buff(Pet const* pet) const;
        bool has_life_buff(Pet const* pet) const;
        int get_attack(Pet const* pet) const;
        int get_life(Pet const* pet) const;

        std::string get_repr(Object const* obj) const;
        int get_cost(Object const* obj) const;
};


#endif // HEADER_UI_ABSTRACT
