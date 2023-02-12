#include "menuScreen.h"
menuScreen::menuScreen(LTexture* bgImage, LTexture* fontSprite,LTexture* buttonScreen) : Screen(bgImage,fontSprite)
{
    this->bgImage = bgImage;
    this->buttonScreen = buttonScreen;
    std::string ButtonText[3]={"CONTINUE", "NEW GAME","  EXIT  "}; //Text on the buttons
    float posX=(float)width/2;
    float posY=((float)height/2);
    ButtonCount = 3;
    buttons = new Button[3];
    for(int i=0; i<3; i++)
    {
        buttons[i] = Button(fontSprite,ButtonText[i],posX, posY + 50);
        posY+=100;
    }

}

void menuScreen::Render(long int& frame,SDL_Renderer* gRenderer)
{
    bgImage->RenderTexture( 0, 0,gRenderer, NULL);
    buttonScreen->RenderTexture(width/2 - 250,height/2 - 120,gRenderer,NULL);
    for(int i=0; i<ButtonCount; i++)
    {
        buttons[i].Render(gRenderer);
    }
}

menuScreen::~menuScreen()
{
    std::cout<<"Menu Screen Destroyed"<<endl;
}
