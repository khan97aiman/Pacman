#include "Screen.h"
Screen::Screen(LTexture* bgImage,LTexture* fontSprite)
{
    this->fontSprite = fontSprite;
}
Screen::~Screen()
{
    //deallocating pointer
    if (buttons != NULL)
    {
        delete[] buttons;
        buttons = NULL;
    }
    std::cout <<  "Screen destructed" << std::endl;
}
Button* Screen::getButtons()  //returns array of buttons
{
    return buttons;
}
int Screen::getButtonCount() //return the no. of buttons rendered
{
    return ButtonCount;
}
void Screen::ChangeButtonState(State val, int ind) //changes the state of Button on the index
{
    buttons[ind].changeState(val);
}
void Screen::mouseMotionEvents(int x, int y)
{
    for(int i=0; i < ButtonCount; i++)
    {
        int posX=buttons[i].getPosition().x;
        int posY=buttons[i].getPosition().y;
        //checks if the pointer position lie inside the border of the button
        //then change the state to hover, else to normal
        if((x<=posX+buttons[i].getWidth()/2 && x>=posX-buttons[i].getWidth()/2)&&(y<=posY+buttons[i].getHeight()/2 && y>=posY-buttons[i].getHeight()/2))
        {
            ChangeButtonState(Hover,i);
        }
        else
        {
            ChangeButtonState(Normal,i);
        }
    }
}
void Screen::mouseClickEvents(int x, int y,Mix_Chunk* buttonClick)
{
    for(int i=0; i < ButtonCount; i++) //loop going through each button index
    {
        int posX=buttons[i].getPosition().x;
        int posY=buttons[i].getPosition().y;
        //checks if the pointer position lie inside the border of the button and mouse is clicked
        //then change the state to clicked
        if((x<=posX+buttons[i].getWidth()/2 && x>=posX-buttons[i].getWidth()/2)&&(y<=posY+buttons[i].getHeight()/2 && y>=posY-buttons[i].getHeight()/2))
        {
            Mix_PlayChannel(-1, buttonClick, 0);
            ChangeButtonState(Clicked,i);
        }
    }
}
