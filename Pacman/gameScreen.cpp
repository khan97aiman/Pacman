#include "gameScreen.h"
gameScreen::gameScreen(LTexture* fontSprite) : Screen(NULL,fontSprite)
{
    ButtonCount = 1;
    buttons = new Button[1];
    buttons[0] = Button (fontSprite,"PAUSE",130,height-30);
}

void gameScreen::Render(long int& frame,SDL_Renderer* gRenderer)
{
    buttons[0].Render(gRenderer);
}
gameScreen::~gameScreen()
{
    std::cout << "Game Screen Destroyed" << std::endl;
}

