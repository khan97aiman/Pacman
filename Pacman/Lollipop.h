#ifndef LOLLIPOP_H
#define LOLLIPOP_H

#include "FoodItem.h"


class Lollipop : public FoodItem
{
    public:
        Lollipop(LTexture*, int,int);
        void Render(long int& frame, SDL_Renderer* gRenderer);
        virtual ~Lollipop();
    private:
        float scale = 1; //scale to make lollipop smaller and bigger
        bool full_size = true; //bool to check if the lollipop has attained full size
};

#endif // LOLLIPOP_H
