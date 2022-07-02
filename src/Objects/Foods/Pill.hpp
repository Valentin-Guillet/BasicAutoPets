#ifndef HEADER_OBJECTS_PILL
#define HEADER_OBJECTS_PILL

#include "object.hpp"
#include "shop.hpp"
#include "team.hpp"


class Pill : public Object {
    public:
        Pill(Team* team, Shop* shop);
        ~Pill() override;

        void on_buy(size_t index) override;
};


#endif // HEADER_OBJECTS_PILL
