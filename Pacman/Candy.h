#ifndef CANDY_H
#define CANDY_H

#include "FoodItem.h"


class Candy : public FoodItem
{
    public:
        Candy(LTexture*, int,int);
        void Render(long int& frame, SDL_Renderer* gRenderer);
        virtual ~Candy();
};

#endif // CANDY_H
