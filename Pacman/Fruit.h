#ifndef FRUIT_H
#define FRUIT_H

#include "FoodItem.h"


class Fruit : public FoodItem
{
    public:
        Fruit(LTexture*, int,int);
        virtual ~Fruit();
};

#endif // FRUIT_H
