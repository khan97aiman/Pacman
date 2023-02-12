#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include "Screen.h"


class gameOverScreen : public Screen
{
    public:
        gameOverScreen(LTexture*,LTexture*,LTexture*);
        void Render(long int& frame,SDL_Renderer*);
        virtual ~gameOverScreen();
        void Update(int score, int level); //updates the game over screen according to the score of the level and the level no last played when the player loses
    private:
        Word* words;
};

#endif // GAMEOVERSCREEN_H
