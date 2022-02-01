#ifndef HEADER_ANT
#define HEADER_ANT

#include "animal.hpp"


class Team;
class Shop;

class Ant : public Animal {
    public:
        Ant(Team* team, Shop* shop);
        ~Ant() override;

        void on_faint() override;
};


#endif // HEADER_ANT
