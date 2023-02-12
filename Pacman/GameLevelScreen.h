#ifndef GAMELEVELSCREEN_H
#define GAMELEVELSCREEN_H

#include "Screen.h"


class GameLevelScreen : public Screen
{
public:
    GameLevelScreen(LTexture*,LTexture*,int);
    void Render(long int& frame,SDL_Renderer*);
    virtual ~GameLevelScreen();
    void ChangeLevel(int); //to update the level number every time
private:
    Word* words;
    Point position;
    int qWidth;
    int qHeight;
};

#endif // GAMELEVELSCREEN_H
