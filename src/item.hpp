#ifndef HEADER_ITEM
#define HEADER_ITEM

#include <string>


class Item {
    public:
        static Item* create_item(std::string name);
        void on_buy();

    private:

};


#endif // HEADER_ITEM
