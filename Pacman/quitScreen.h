#pragma once
#include "Screen.h"

class quitScreen:public Screen
{
private:
    Point position; //position of Quit Screen on the whole screen
    int qWidth;
    int qHeight;
    Word* word;
public:
    quitScreen(LTexture*,LTexture*);
    void Render(long int& frame, SDL_Renderer*);
    virtual ~quitScreen();
};
