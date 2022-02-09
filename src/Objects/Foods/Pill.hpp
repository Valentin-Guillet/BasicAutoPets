#ifndef HEADER_PILL
#define HEADER_PILL

#include "object.hpp"
#include "shop.hpp"
#include "team.hpp"


class Pill : public Object {
    public:
        Pill(Team* team, Shop* shop);
        ~Pill() override;

        void on_buy(int index) override;
};


#endif // HEADER_PILL
