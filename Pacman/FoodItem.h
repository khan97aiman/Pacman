#ifndef FOODITEM_H
#define FOODITEM_H
#include "GameObject.h"


class FoodItem : public GameObject
{
    public:
        FoodItem(LTexture*, int,int);
        virtual ~FoodItem();
        virtual void Render(long int& frame, SDL_Renderer* gRenderer) = 0;

    protected:
        SDL_Rect spriteClips;
};

#endif // FOODITEM_H
