#ifndef HEADER_OBJECT
#define HEADER_OBJECT

#define PACK_STANDARD 1
#define PACK_DLC1 2

#include <iostream>
#include <string>
#include <vector>


enum class ObjType { FOOD, ITEM };

class Pet;
class Shop;
class Team;

class Object {
    public:
        static Object* create_new_object(std::string name, Team* team, Shop* shop);
        static Object* create_random_object(Team* team, Shop* shop, int max_tier);

        Object(std::string name, Team* team, Shop* shop, ObjType type);
        virtual ~Object();

        std::string name;
        ObjType type;

        int get_cost() const;
        void set_pet(Pet* pet);

        virtual void on_buy(int index) { };
        virtual void on_faint() { };

        friend std::ostream& operator<<(std::ostream& os, Object const& object);

    protected:
        int id;

        int pack;
        int tier;

        Team* team;
        Shop* shop;
        Pet* attached_pet;

        int cost;

        std::vector<Pet*>& get_team_pets() const;

    private:
        static std::string get_random_name(int max_tier);
};


#endif // HEADER_OBJECT
