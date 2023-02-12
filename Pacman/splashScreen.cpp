#include "splashScreen.h"
splashScreen::splashScreen(LTexture* bgImage,LTexture* fontSprite) : Screen(bgImage,fontSprite)
{
    this->bgImage=bgImage;
}

void splashScreen::Render(long int& frame,SDL_Renderer* gRenderer)
{
     bgImage->RenderTexture( 0, 0,gRenderer,NULL );
}

splashScreen::~splashScreen()
{
    std::cout<<"Splash Screen Destroyed"<<std::endl;
}
