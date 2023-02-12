#include "excerptScreen.h"
excerptScreen::excerptScreen(LTexture* bgImage,LTexture* fontSprite) : Screen(bgImage,fontSprite)
{
    this->bgImage=bgImage;
}

void excerptScreen::Render(long int& frame,SDL_Renderer* gRenderer)
{
     bgImage->RenderTexture( 0, 0,gRenderer,NULL );
}

excerptScreen::~excerptScreen()
{
    std::cout<<"Splash Screen Destroyed"<<std::endl;
}

