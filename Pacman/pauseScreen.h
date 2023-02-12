#pragma once
#include "Screen.h"

class pauseScreen:public Screen
{
private:
    Point position; ///position of the Pause Screen on the whole screen
    int pWidth;
    int pHeight;
public:
    pauseScreen(LTexture*,LTexture*);
    void Render(long int& frame,SDL_Renderer*);
    virtual ~pauseScreen();
};
