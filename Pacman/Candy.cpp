#include "Candy.h"

Candy::Candy(LTexture* image, int x, int y) : FoodItem(image,x,y)
{
    //ctor
    spriteClips.x = 422;
    spriteClips.y = 105;
    spriteClips.w = 14;
    spriteClips.h = 12;

    widthSheet = spriteClips.w*0.5;
    heightSheet = spriteClips.h*0.5;
    name = "CANDY";
}

Candy::~Candy()
{
    //dtor
    std::cout << "Candy destructed" << std::endl;
}
void Candy::Render(long int& frame, SDL_Renderer* gRenderer)
{
    spriteSheetTexture->RenderTexture(getGridPixel().x - widthSheet / 2, getGridPixel().y- heightSheet / 2, gRenderer,&spriteClips, SDL_FLIP_NONE,0.0, NULL,0.5);
}
