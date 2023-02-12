#include "Fruit.h"

Fruit::Fruit(LTexture* image, int x, int y) : FoodItem(image,x,y)
{
    //ctor
    spriteClips.x = 415;
    spriteClips.y = 65;
    spriteClips.w = 30;
    spriteClips.h = 30;

    widthSheet = spriteClips.w;
    heightSheet = spriteClips.h;
    name = "FRUIT";
}

Fruit::~Fruit()
{
    //dtor
    std::cout << "Fruit destructed" << std::endl;
}
