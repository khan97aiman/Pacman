#include "FoodItem.h"

FoodItem::FoodItem(LTexture* image, int x, int y) : GameObject(image,x,y)
{
    setGridPixel(getGridPixel()+16);
}

FoodItem::~FoodItem()
{
    //dtor
    std::cout << "Food Item destructed" << std::endl;
}

