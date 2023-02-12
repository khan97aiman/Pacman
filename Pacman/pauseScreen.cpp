#include"pauseScreen.h"
pauseScreen::pauseScreen(LTexture* bgImage,LTexture* fontSprite) : Screen(bgImage,fontSprite)
{
    this->bgImage = bgImage;
    pWidth = 500;
    pHeight = 500;
    position.x = width/2 - pWidth/2;
    position.y = height/2 - pHeight/2;
    ButtonCount = 3;
    buttons = new Button[3];
    std::string ButtonText[3] = {" RESUME ","RESTART","  QUIT  "};        //text on buttons
    int posX = width/2;
    int posY = (height/2)-100;
    for(int i=0; i<3; i++)
    {
        buttons[i] = Button(fontSprite,ButtonText[i],posX, posY);
        posY+=100;
    }

}

void pauseScreen::Render(long int& frame,SDL_Renderer* gRenderer)
{
    bgImage->RenderTexture( position.x, position.y,gRenderer,NULL );
    for(int i=0; i<ButtonCount; i++)
    {
        buttons[i].Render(gRenderer);
    }
}

pauseScreen::~pauseScreen()
{
    std::cout<<"Pause Screen Destroyed"<<std::endl;
}
