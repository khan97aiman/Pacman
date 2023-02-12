#pragma once
#include "Screen.h"

class splashScreen:public Screen
{
public:
    splashScreen(LTexture*,LTexture*);
    void Render(long int& frame,SDL_Renderer*);
    virtual ~splashScreen();
};
