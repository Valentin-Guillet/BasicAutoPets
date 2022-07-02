#ifndef HEADER_OBJECTS_HONEY
#define HEADER_OBJECTS_HONEY

#include "object.hpp"
#include "shop.hpp"
#include "team.hpp"


class Honey : public Object {
    public:
        Honey(Team* team, Shop* shop);
        ~Honey() override;

        void on_faint(Pos pos) override;
};

#endif // HEADER_OBJECTS_HONEY
