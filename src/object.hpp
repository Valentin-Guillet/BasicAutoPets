#ifndef HEADER_OBJECT
#define HEADER_OBJECT

#define PACK_STANDARD 1
#define PACK_DLC1 2

#include <string>
#include <vector>


enum class ObjType { FOOD, ITEM };

class Pet;
class Shop;
class Team;

class Object {
    friend class UserInterface;

    public:
        static Object* create_new_object(std::string name, Team* team, Shop* shop);
        static Object* create_random_object(Team* team, Shop* shop, int max_tier);
        static Object* copy_object(Object const* obj, Team* team, Shop* shop);

        Object(std::string name, Team* team, Shop* shop, ObjType type);
        virtual ~Object();

        std::string name;
        ObjType type;
        bool target_all;

        int get_cost() const;
        void set_pet(Pet* pet);

        virtual void on_buy(size_t index) { };
        virtual void on_faint(size_t index) { };
        virtual int on_damages(int value) { return value; };

    protected:
        std::string repr;

        Team* team;
        Shop* shop;
        Pet* attached_pet;

        int id;
        int tier;
        int cost;

    private:
        static std::string get_random_name(int max_tier);
};


#endif // HEADER_OBJECT
