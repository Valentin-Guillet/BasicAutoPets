#ifndef HEADER_TEAM
#define HEADER_TEAM

#include <vector>

#include "animal.hpp"


class Team {
    public:
        ~Team();

        void begin_turn();
        void order(int order[5]);

        void add(Animal* animal);
        void upgrade(int index, Animal* other_animal);
        int sell(int index);

        void draw() const;

    private:
        std::vector<Animal*> animals;
};


#endif // HEADER_TEAM
