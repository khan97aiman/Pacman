#include "gameOverScreen.h"

gameOverScreen::gameOverScreen(LTexture* bgImage, LTexture* fontSprite,LTexture* buttonScreen) : Screen(bgImage,fontSprite)
{
    this->bgImage = bgImage;
    std::string ButtonText[3]={"MAIN MENU", "PLAY AGAIN","  EXIT  "};          ///Text on the buttons
    float posX=(float)width/2 + (float)width/4 + 50;
    float posY=((float)height/2 - 100);
    ButtonCount = 3;
    buttons = new Button[3];
    for(int i=0; i<3; i++)
    {
        buttons[i] = Button(fontSprite,ButtonText[i],posX, posY + 50);
        posY+=100;
    }
    words = new Word[2];
    std::string text = "Score ";
    words[0] = Word(text,fontSprite,width/2 + 250,height/2 - 250);
    text = "Level ";
    words[1] = Word(text,fontSprite,width/2 + 230,height/2 - 200);

}
void gameOverScreen::Update(int score, int level) //we have to update the game over screen according to the level number last played and the score of that level
{
    std::string text = "Score " +  GlobalFunctions::int_to_string(score);
    words[0].changeWord(text);
    text = "Level " + GlobalFunctions::int_to_string(level);
    words[1].changeWord(text);
}
void gameOverScreen::Render(long int& frame,SDL_Renderer* gRenderer)
{
    bgImage->RenderTexture( 0, 0,gRenderer, NULL);
    for(int i=0; i<ButtonCount; i++)
    {
        buttons[i].Render(gRenderer);
    }
    words[0].Render(gRenderer);
    words[1].Render(gRenderer);
}

gameOverScreen::~gameOverScreen()
{
    delete[] words;
    std::cout<<"Game Over Screen Destroyed"<<endl;
}
