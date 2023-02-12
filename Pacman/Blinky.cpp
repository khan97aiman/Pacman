#include "Blinky.h"

Blinky::Blinky(LTexture* image, int x, int y) : Ghost(image,x,y)
{
    //ctor
    spriteClips[0].x = 0;
    spriteClips[0].y = 0;
    spriteClips[0].w = 30;
    spriteClips[0].h = 32;

    spriteClips[1].x = 0;
    spriteClips[1].y = 32;
    spriteClips[1].w = 30;
    spriteClips[1].h = 32;

    spriteClips[2].x = 0;
    spriteClips[2].y = 64;
    spriteClips[2].w = 30;
    spriteClips[2].h = 32;

    spriteClips[3].x = 0;
    spriteClips[3].y = 96;
    spriteClips[3].w = 30;
    spriteClips[3].h = 32;

    widthSheet = spriteClips[0].w;
    heightSheet = spriteClips[0].h;
    direction = -1;
    name = "BLINKY";
}
void Blinky::ResetGhost()
{
    alive = true;
    setGrid(8,15);
    position = getGridPixel();
    direction = -1;
    currentCell = {0,0,0,0};
    scared_ghost = false;
}
Blinky::~Blinky()
{
    //dtor
}
