#include "Pinky.h"

Pinky::Pinky(LTexture* image, int x, int y) : Ghost(image,x,y)
{
    //ctor
    spriteClips[0].x = 130;
    spriteClips[0].y = 0;
    spriteClips[0].w = 30;
    spriteClips[0].h = 32;

    spriteClips[1].x = 130;
    spriteClips[1].y = 32;
    spriteClips[1].w = 30;
    spriteClips[1].h = 32;

    spriteClips[2].x = 130;
    spriteClips[2].y = 64;
    spriteClips[2].w = 30;
    spriteClips[2].h = 32;

    spriteClips[3].x = 130;
    spriteClips[3].y = 96;
    spriteClips[3].w = 30;
    spriteClips[3].h = 32;

    widthSheet = spriteClips[0].w;
    heightSheet = spriteClips[0].h;

    direction = -1; //direction is set to -1 so that the objects don't start moving as soon as the game screen is rendered. A short delay of is there until the starting screen goes away and then the objects will start moving.
    name = "PINKY";
}
void Pinky::ResetGhost()
{
    alive = true;
    setGrid(10,15); //the initial grid position to be rendered
    position = getGridPixel(); //set the position according to be grid.
    direction = -1;
    currentCell = {0,0,0,0};
    scared_ghost = false;
}
Pinky::~Pinky()
{
    //dtor
}
