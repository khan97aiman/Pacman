#pragma once
#include "LTexture.h"
#include "Button.h"
#include "GlobalFunctions.h"
#include <SDL_mixer.h>
class Screen
{
protected:
    LTexture* bgImage;    //background image of the screen
    LTexture* fontSprite;  //image consisting of fonts, and buttons
    int ButtonCount = 0;   //no. of Buttons to be rendered
    Button* buttons = NULL; //pointer of Button class(either kept null or used to create dynamic array of buttons)
    const int width =  GlobalFunctions::GetSCREEN_WIDTH();
    const int height = GlobalFunctions::GetSCREEN_HEIGHT();
public:
    virtual void Render(long int& frame,SDL_Renderer*)=0;  //Render the Screen
    Screen(LTexture* bgImage,LTexture* fontSprite);
    virtual ~Screen();
    Button* getButtons();   //returns array of buttons
    int getButtonCount();   //return the no. of buttons to be rendered
    void ChangeButtonState(State val, int ind); //changes the state of Button on the index
    void mouseMotionEvents(int x, int y); //used to handle mouse motion events on a screen
    void mouseClickEvents(int x, int y,Mix_Chunk* buttonClick); //used to handle mouse click events on a screen
};

