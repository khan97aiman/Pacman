#include "GameLevelScreen.h"

GameLevelScreen::GameLevelScreen(LTexture* bgImage,LTexture* fontSprite, int level_no) : Screen(bgImage,fontSprite)
{
    //ctor
    this->bgImage = bgImage;
    qWidth = 400;
    qHeight = 150;
    position.x = width/2 - qWidth/2;
    position.y = height/2 - qHeight/2;
    words = new Word[2];
    std::string text = "Level " + GlobalFunctions::int_to_string(level_no);
    words[0] = Word("Get Ready!",fontSprite,position.x + qWidth/2,position.y + qHeight/2 - 30);
    words[1] = Word(text,fontSprite,position.x + qWidth/2,position.y + qHeight/2 + 40);

}
void GameLevelScreen::ChangeLevel(int level_no)
{
    std::string text = "Level " + GlobalFunctions::int_to_string(level_no);
    words[1].changeWord(text);
}

GameLevelScreen::~GameLevelScreen()
{
    //dtor
    delete[] words;
    std::cout<<"GameLevel Screen Destroyed"<<std::endl;
}
void GameLevelScreen::Render(long int& frame,SDL_Renderer* gRenderer)
{
    bgImage->RenderTexture( position.x, position.y,gRenderer,NULL,SDL_FLIP_NONE,0.0,NULL,0.5 );
    for (int i = 0; i < 2; i++)
    {
        words[i].Render(gRenderer);
    }

}
