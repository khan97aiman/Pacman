#pragma once

#include "Screen.h"

class excerptScreen:public Screen
{
public:
    excerptScreen(LTexture*,LTexture*);
    void Render(long int& frame,SDL_Renderer*);
    virtual ~excerptScreen();
};
