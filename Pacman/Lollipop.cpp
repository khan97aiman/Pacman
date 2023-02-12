#include "Lollipop.h"

Lollipop::Lollipop(LTexture* image, int x, int y) : FoodItem(image,x,y)
{
    //ctor
    spriteClips.x = 385;//386;
    spriteClips.y = 93;//98;
    spriteClips.w = 32;//26;
    spriteClips.h = 32;//30;

    widthSheet = spriteClips.w;
    heightSheet = spriteClips.h;
    name = "LOLLIPOP";
}

Lollipop::~Lollipop()
{
    //dtor
    std::cout << "Lollipop destructed" << std::endl;
}
void Lollipop::Render(long int& frame, SDL_Renderer* gRenderer)
{
    if (full_size) //if the lollipop has been rendered with full size start decreasing the size
    {
        scale -= 0.01;
        if (scale < 0.5) //if the size falls below 0.5 mark full_size false
        {
            full_size = false;
        }
    }
    if (!full_size ) //if the lollipop is lesser than 0.5 (not full size) then start incrementing the size
    {
        scale += 0.01;
        if (scale >= 1) //if the size reaches greater than or equal to 1, then mark full_size false
        {
            full_size = true;
        }
    }
    widthSheet = spriteClips.w * scale; //change the width according to the scale
    heightSheet = spriteClips.h * scale; //change the height according to the scale
    spriteSheetTexture->RenderTexture(getGridPixel().x - widthSheet / 2, getGridPixel().y - heightSheet / 2, gRenderer,&spriteClips, SDL_FLIP_NONE,0.0, NULL,scale);
}
