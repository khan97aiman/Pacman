#pragma once
#include "LTexture.h"
#include "Point.h"
#include "word.h"

enum State{Normal, Hover, Clicked};                                 ///Enumerating three states of buttons

class Button
{
    int width;  //width of each of the three parts of the button
    int ButtonWidth; //final width of the Button
    int height; //height of the Button
    std::string text;//Text on the button
    Word* word; //object of word class to be rendered over the button
    SDL_Rect spriteClips[3]; //sprite clips for each state of the button
    LTexture* spriteSheetTexture; //Texture of image consisting of Buttons
    Point position; //Position of the Button
    int state; //current state of the Button

public:
    Button();
    Button(LTexture*,std::string, float, float);
    void Render(SDL_Renderer*);
    ~Button();
    Point getPosition();
    int getWidth();
    int getHeight();
    std::string getText(); //get the text of the button
    void changeState(State); //changes the current state of the button
    void operator = (const Button& cpy); //operator overloading for assignment operator
    bool clicked(); //tells whether button is clicked or not
};
