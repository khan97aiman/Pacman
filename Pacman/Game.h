#ifndef GAME_H
#define GAME_H
#include "word.h"
#include "Level.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Blinky.h"
#include "Pinky.h"
#include "Clyde.h"
#include "Inky.h"
#include "splashScreen.h"
#include "menuScreen.h"
#include "excerptScreen.h"
#include "gameScreen.h"
#include "pauseScreen.h"
#include "quitScreen.h"
#include "gameOverScreen.h"
#include "GlobalFunctions.h"
#include "GameLevelScreen.h"
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include "LTexture.h"
class Game
{
    public:
        Game();
        void NewGame(LTexture*, LTexture*,LTexture*, LTexture*,LTexture*); //to start a new game
        void SaveGame(); //to save a game
        void LoadGame(LTexture*, LTexture*,LTexture*, LTexture*,LTexture*); //to load a saved game
        void NextLevel(); //to go to next level
        ~Game();
        void Render(long int& frame,SDL_Renderer*);
        void setPacmanDirection(int direction);
        bool gameOver(); //returns whether game has ended or not (i.e player has lost or not)
        void GameLoop(SDL_Renderer*,Mix_Chunk*, Mix_Chunk*, Mix_Chunk*, Mix_Chunk*,Mix_Chunk*); //all the main loop of the game occurs here
        void Restart(); //to restart the game
        void StartGame(); //to start playing a game after the delay
        void ResetAllGhosts(); //to reset all the ghosts to the initial settings (calls reset function of the ghosts)
        int getScore() {return pacman->getScore();} //returns the scores earned by the player so far
        int getLevelNo() {return level_no;} //returns the current level being played
        bool HasGameStarted() {return !startingLevelScreen;} //if starting level screen is true, then game has not started
    private:
        Level* level; //a game contains a level
        Pacman* pacman = NULL;
        Ghost* ghosts[4];
        Word* words;
        int level_no;
        bool startingLevelScreen; //to keep check whether the starting level screen is still on screen or not
        const int width =  GlobalFunctions::GetSCREEN_WIDTH();
        const int height = GlobalFunctions::GetSCREEN_HEIGHT();
        GameLevelScreen* startingLevel; //the starting screen which is  rendered before the game starts (it shows the level no. to be played and tells the player to get ready
};

#endif // GAME_H
