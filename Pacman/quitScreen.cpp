#include "quitScreen.h"
quitScreen::quitScreen(LTexture* bgImage,LTexture* fontSprite) : Screen(bgImage,fontSprite)
{
    this->bgImage = bgImage;
    qWidth = 800;
    qHeight = 300;
    position.x = width/2 - qWidth/2;
    position.y = height/2 - qHeight/2;
    ButtonCount = 3;
    buttons = new Button[3];
    std::string ButtonText[3] = {" YES ","  NO  ","CANCEL"}; //text on buttons
    int posX = width/2 - 240;
    int posY = position.y + 200;
    for(int i = 0; i<3; i++)
    {
        buttons[i] = Button(fontSprite,ButtonText[i],posX, posY);
        posX += 240;
    }
    word = new Word("Save Game?",fontSprite,position.x + qWidth/2,position.y + qHeight/2 - 50);

}

void quitScreen::Render(long int& frame,SDL_Renderer* gRenderer)
{
    bgImage->RenderTexture( position.x, position.y,gRenderer,NULL );
    for(int i=0; i<ButtonCount; i++)
    {
        buttons[i].Render(gRenderer);
    }
    word->Render(gRenderer);
}

quitScreen::~quitScreen()
{
    std::cout<<"Pause Screen Destroyed"<<std::endl;
}

