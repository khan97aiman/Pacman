#pragma once
#include "Screen.h"
#include <SDL.h>
#include "Level.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Blinky.h"
#include "Pinky.h"
#include "Clyde.h"
#include "Inky.h"
#include "GlobalFunctions.h"

class gameScreen:public Screen
{
public:
    gameScreen(LTexture*);
    void Render(long int& frame,SDL_Renderer*);
    virtual ~gameScreen();
};
