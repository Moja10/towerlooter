#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "Object.h"

using std::vector;

class Inventory
{
    public:
        vector<Object> contents;
        Inventory();
        virtual ~Inventory();
    protected:
    private:
};

#endif // INVENTORY_H
