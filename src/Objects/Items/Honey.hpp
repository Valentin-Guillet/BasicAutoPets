#ifndef HEADER_HONEY
#define HEADER_HONEY

#include "object.hpp"
#include "shop.hpp"
#include "team.hpp"


class Honey : public Object {
    public:
        Honey(Team* team, Shop* shop);
        ~Honey() override;

        void on_faint() override;
};

#endif // HEADER_HONEY
