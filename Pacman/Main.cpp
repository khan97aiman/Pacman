#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "LTexture.h"
#include "word.h"
#include "Button.h"
#include "splashScreen.h"
#include "menuScreen.h"
#include "excerptScreen.h"
#include "gameScreen.h"
#include "pauseScreen.h"
#include "quitScreen.h"
#include "gameOverScreen.h"
#include "GlobalFunctions.h"
#include "GameLevelScreen.h"
#include "Game.h"
#include <time.h>
using namespace std;

bool init();
bool loadMedia();
void close();
void setAlpha();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

const int SCREEN_WIDTH = GlobalFunctions::GetSCREEN_WIDTH();
const int SCREEN_HEIGHT = GlobalFunctions::GetSCREEN_HEIGHT();

///Textures for different images that rendered on the screen
LTexture gFontTexture;
LTexture gExcerpt;
LTexture gSplashTexture;
LTexture gMainMenuTexture;
LTexture gCell;
LTexture gGameOverTexture;
LTexture gQuitTexture;
LTexture gButtonScreen;
LTexture gPacmanTexture;
LTexture gPacman;

//The sound effects that will be used
Mix_Chunk* eatCandy = NULL;
Mix_Chunk* eatLolli = NULL;
Mix_Chunk* eatGhosts = NULL;
Mix_Chunk* pacmanDeath = NULL;
Mix_Chunk* gameBegin = NULL;
Mix_Chunk* LevelEnd = NULL;
Mix_Chunk* buttonClick = NULL;
Mix_Music* game_over = NULL;
//Alpha Modulation component
Uint8 a = 255; //one component is set to full opaque
Uint8 b = 0; //other is full transparent
Uint8 button = 170; //for controlling alpha value of other textures
Uint8 button_screen = 200; //for controlling alpha value of other textures
int main(int argv, char** args)
{
    //Start up SDL and create window
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        //Load media
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            //Main loop flag
            bool quit = false;
            //flags to check which screen is running
            bool splashRunning = true;
            bool menuRunning = false;
            bool excerptRunning = false;
            bool gameRunning = false;
            bool pauseRunning = false;
            bool quitRunning = false;
            bool gameOverRunning = false;
            bool gameOverMusic = true;

            long int frame = 0;

            bool mouseClicked = false; //flag indicating mouse click
            Button* buttons = NULL;   //will hold button(s) on the screen
            int x, y;

            splashScreen splash(&gSplashTexture, &gFontTexture);
            menuScreen mainMenu(&gMainMenuTexture, &gFontTexture, &gButtonScreen);
            excerptScreen Excerpt(&gExcerpt, &gFontTexture);
            gameScreen GameScreen(&gFontTexture);
            gameOverScreen gameOver(&gGameOverTexture, &gFontTexture, &gButtonScreen);
            pauseScreen PauseScreen(&gButtonScreen, &gFontTexture);
            quitScreen QuitScreen(&gQuitTexture, &gFontTexture);
            Game game;
            //Event handler
            SDL_Event e;
            //While application is running
            while (!quit)
            {
                //Handle events on queue
                while (SDL_PollEvent(&e) != 0)
                {
                    //User requests quit
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    SDL_GetMouseState(&x, &y);
                    const Uint8* KeyState = SDL_GetKeyboardState(NULL);
                    if (e.type == SDL_KEYDOWN && !pauseRunning)
                    {
                        if (KeyState[SDL_SCANCODE_UP])
                        {
                            game.setPacmanDirection(_UP);
                        }
                        else if (KeyState[SDL_SCANCODE_DOWN])
                        {
                            game.setPacmanDirection(_DOWN);
                        }
                        else if (KeyState[SDL_SCANCODE_LEFT])
                        {
                            game.setPacmanDirection(_LEFT);
                        }
                        else if (KeyState[SDL_SCANCODE_RIGHT])
                        {
                            game.setPacmanDirection(_RIGHT);
                        }
                        else if (e.type == SDL_KEYDOWN && KeyState[SDL_SCANCODE_ESCAPE] && excerptRunning && !menuRunning)
                        {
                            excerptRunning = false;
                            gameRunning = true;
                        }
                    }
                    if (e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        if (e.button.button == SDL_BUTTON_LEFT)
                            mouseClicked = true;
                    }
                    if (e.type == SDL_MOUSEMOTION) //to handle all mouse motion events for all screens
                    {
                        GameScreen.mouseMotionEvents(x, y);
                        mainMenu.mouseMotionEvents(x, y);
                        PauseScreen.mouseMotionEvents(x, y);
                        QuitScreen.mouseMotionEvents(x, y);
                        gameOver.mouseMotionEvents(x, y);
                    }
                    if (e.type == SDL_MOUSEBUTTONUP && mouseClicked) //tp handle all mouse click events for all screens
                    {

                        GameScreen.mouseClickEvents(x, y, buttonClick);
                        mainMenu.mouseClickEvents(x, y, buttonClick);
                        PauseScreen.mouseClickEvents(x, y, buttonClick);
                        QuitScreen.mouseClickEvents(x, y, buttonClick);
                        gameOver.mouseClickEvents(x, y, buttonClick);
                        mouseClicked = false;
                    }
                    if (menuRunning)
                    {
                        buttons = mainMenu.getButtons();
                        for (int i = 0; i < mainMenu.getButtonCount(); i++)
                        {
                            if (buttons[i].getText() == "NEW GAME" && buttons[i].clicked())
                            {
                                game.NewGame(&gPacman, &gPacmanTexture, &gFontTexture, &gCell, &gQuitTexture);
                                excerptRunning = true;
                                break;
                            }
                            else if (buttons[i].getText() == "CONTINUE" && buttons[i].clicked())
                            {
                                game.LoadGame(&gPacman, &gPacmanTexture, &gFontTexture, &gCell, &gQuitTexture);
                                menuRunning = false;
                                gameRunning = true;
                                break;

                            }
                            else if (buttons[i].getText() == "  EXIT  " && buttons[i].clicked())
                            {
                                quit = true;
                                break;
                            }
                        }
                    }
                    if (gameRunning)
                    {
                        buttons = GameScreen.getButtons();
                        if (buttons[0].clicked())
                        {
                            pauseRunning = true;
                            break;
                        }
                    }
                    if (pauseRunning)
                    {
                        buttons = PauseScreen.getButtons();
                        for (int i = 0; i < PauseScreen.getButtonCount(); i++)   //loop going through each button index
                        {
                            if (buttons[i].getText() == " RESUME " && buttons[i].clicked())
                            {
                                pauseRunning = false;
                                break;
                            }
                            else if (buttons[i].getText() == "RESTART" && buttons[i].clicked())
                            {
                                pauseRunning = false;
                                game.Restart();
                                break;
                            }
                            else if (buttons[i].getText() == "  QUIT  " && buttons[i].clicked())
                            {
                                quitRunning = true;
                                pauseRunning = false;
                                break;
                            }
                        }
                    }
                    if (quitRunning)
                    {
                        buttons = QuitScreen.getButtons();
                        for (int i = 0; i < QuitScreen.getButtonCount(); i++)   //loop going through each button index
                        {
                            if (buttons[i].getText() == " YES " && buttons[i].clicked())
                            {
                                ///save the game
                                game.SaveGame();
                                quitRunning = false;
                                gameRunning = false;
                                menuRunning = true;
                                break;
                            }
                            else if (buttons[i].getText() == "  NO  " && buttons[i].clicked())
                            {
                                ///don't save the game
                                quitRunning = false;
                                gameRunning = false;
                                menuRunning = true;
                                break;
                            }
                            else if (buttons[i].getText() == "CANCEL" && buttons[i].clicked())
                            {
                                quitRunning = false;
                                break;
                            }
                        }
                    }
                    if (gameOverRunning)
                    {
                        buttons = gameOver.getButtons();
                        for (int i = 0; i < gameOver.getButtonCount(); i++)   //loop going through each button index
                        {
                            if (buttons[i].getText() == "MAIN MENU" && buttons[i].clicked())
                            {
                                gameOverRunning = false;
                                menuRunning = true;
                                break;
                            }
                            else if (buttons[i].getText() == "PLAY AGAIN" && buttons[i].clicked())
                            {
                                gameOverRunning = false;
                                gameRunning = true;
                                game.Restart();
                                break;
                            }
                            else if (buttons[i].getText() == "  EXIT  " && buttons[i].clicked())
                            {
                                quit = true;
                                break;
                            }
                        }
                    }
                }
                //Clear screen
                SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
                SDL_RenderClear(gRenderer);


                if (splashRunning)       ///checks if Splash screen is running
                {
                    gSplashTexture.setAlpha(a);     ///Splash Screen fades out with a decreasing
                    splash.Render(frame, gRenderer);       ///Rendering Splash Screen
                    if (a == 0)
                    {
                        //Mix_PlayChannel(-1, screenTransition, 0);
                        splashRunning = false;    ///indicates the end of splash screen run
                        menuRunning = true;
                        a = 255; //reset
                        b = 0; //reset
                    }
                }
                if (menuRunning)     ///checks if Main Menu Screen is running
                {
                    //if transition to excerpt is called, start fading the menuscreen.
                    gFontTexture.setAlpha(button);
                    gButtonScreen.setAlpha(button_screen);
                    gMainMenuTexture.setAlpha(a);
                    if (!excerptRunning)         //checks if transition to Excerpt is not called
                    {
                        a = 255;      //maintains the alpha values
                        b = 0;
                    }
                    else
                    {
                        if (button == 0) //if button screen has on menu has faded out
                        {
                            button = 0; //hold that value and check whether menu screen has faded out
                            button_screen = 0;
                            if (a == 0) //if menu screen has faded out
                            {
                                menuRunning = false; //mark it false
                                a = 255; //reset the values
                                b = 0;
                                button = 170; //reset the valaues
                                button_screen = 200;
                            }
                        }
                        else //if button screen has not faded completely, then fade it more
                        {
                            button -= 2;
                            button_screen -= 2;
                            a = 255;  //maintain high alpha value for menu screen until button screen is there
                            b = 0;
                        }
                    }
                    mainMenu.Render(frame, gRenderer); //render main menu
                }
                if (excerptRunning & !menuRunning) //transition between game and menu screen involves an excerpt, checks if the excerpt has to be rendered
                {
                    gExcerpt.setAlpha(b);
                    Excerpt.Render(frame, gRenderer);
                    if (a == 0) //checks if the menu screen has completely faded and excerpt is rendered with the highest alpha value
                    {
                        SDL_Delay(3000); //keeps the excerpt on screen for 3 seconds
                        gameRunning = true;  //indicates the start of game screen run
                        excerptRunning = false;
                        SDL_RenderClear(gRenderer);
                        a = 255; //reset alpha values
                        b = 0;
                    }
                }
                if (gameRunning) //transition between Game screen and Excerpt
                {
                    gFontTexture.setAlpha(170);
                    if (!game.HasGameStarted()) //if game has not started yet, dim the game textures and render starting level screen to show level no
                    {
                        Mix_PlayChannel(-1, gameBegin, 0);
                        gPacman.setAlpha(100);
                        gCell.setAlpha(100);
                        gPacmanTexture.setAlpha(100);
                        gQuitTexture.setAlpha(230);

                        GameScreen.Render(frame, gRenderer);
                        game.Render(frame, gRenderer);

                        SDL_RenderPresent(gRenderer);
                        SDL_Delay(4000);
                        game.StartGame(); //start the game now, after the level screen has gone
                    }
                    else if (!pauseRunning && !quitRunning)
                    {
                        gPacman.setAlpha(255);
                        gCell.setAlpha(255);
                        gPacmanTexture.setAlpha(255);
                        game.GameLoop(gRenderer, eatCandy, eatGhosts, eatLolli, pacmanDeath, LevelEnd);
                    }
                    if (game.gameOver())
                    {
                        gPacman.setAlpha(a);
                        gCell.setAlpha(a);
                        gPacmanTexture.setAlpha(a);
                        if (a == 0) //if game screen has faded out completely
                        {
                            gameRunning = false;
                            gameOverRunning = true;
                            gameOver.Update(game.getScore(), game.getLevelNo());
                            a = 255;
                            b = 0;
                        }
                    }
                    GameScreen.Render(frame, gRenderer);
                    game.Render(frame, gRenderer);
                }
                if (pauseRunning)
                {
                    gPacman.setAlpha(100);
                    gCell.setAlpha(100);
                    gPacmanTexture.setAlpha(100);
                    gButtonScreen.setAlpha(230);
                    gFontTexture.setAlpha(200);
                    //GameScreen.
                    PauseScreen.Render(frame, gRenderer);
                }
                if (quitRunning)
                {
                    gPacman.setAlpha(100);
                    gCell.setAlpha(100);
                    gPacmanTexture.setAlpha(100);
                    gQuitTexture.setAlpha(230);
                    gFontTexture.setAlpha(200);
                    //GameScreen.
                    QuitScreen.Render(frame, gRenderer);
                }
                if (gameOverRunning)
                {
                    if (gameOverMusic)
                    {
                        Mix_PlayMusic(game_over, 0);
                        gameOverMusic = false; //play game over music only once
                    }
                    if (b > 170)
                    {
                        gButtonScreen.setAlpha(button);
                    }
                    else
                    {
                        gFontTexture.setAlpha(b);
                    }
                    gGameOverTexture.setAlpha(b);
                    gameOver.Render(frame, gRenderer);
                }
                setAlpha(); //to decrement a and increment b
                frame++;
                if (frame % 50 == 0)
                {
                    frame = 0;
                }
                //Update screen
                SDL_RenderPresent(gRenderer);
            }
        }
    }
    //Free resources and close SDL
    close();
    return 0;
}
bool init()
{
    ///Initialization flag
    bool success = true;

    ///Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        ///Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }

        ///Create window
        gWindow = SDL_CreateWindow("PAC-MAN", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }

        else
        {
            ///Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                ///Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
                //Initialize SDL_mixer
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
                    success = false;
                }
            }
        }
    }
    /*if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        success = false;
    }*/
    return success;
}

bool loadMedia()
{
    ///Loading success flag
    bool success = true;
    if (!gFontTexture.LoadFromFile("Images/XiroidFinal2.png", gRenderer))
    {
        printf("Failed to load sprite sheet texture!\n");
        success = false;
    }
    else
    {
        ///Set standard alpha blending
        gFontTexture.setBlendMode(SDL_BLENDMODE_BLEND);
    }
    if (!gExcerpt.LoadFromFile("Images/excerpt4.jpg", gRenderer))
    {
        printf("Failed to load sprite sheet texture!\n");
        success = false;
    }
    else
    {
        ///Set standard alpha blending
        gExcerpt.setBlendMode(SDL_BLENDMODE_BLEND);
    }
    if (!gSplashTexture.LoadFromFile("Images/splash4.png", gRenderer))
    {
        printf("Failed to load sprite sheet texture!\n");
        success = false;
    }
    else
    {
        ///Set standard alpha blending
        gSplashTexture.setBlendMode(SDL_BLENDMODE_BLEND);
    }
    if (!gMainMenuTexture.LoadFromFile("Images/Wiki-background1.jpg", gRenderer))
    {
        printf("Failed to load sprite sheet texture!\n");
        success = false;
    }
    else
    {
        ///Set standard alpha blending
        gMainMenuTexture.setBlendMode(SDL_BLENDMODE_BLEND);
    }
    if (!gPacmanTexture.LoadFromFile("Images/pacman_sheet1.png", gRenderer))
    {
        printf("Failed to load sprite sheet texture!\n");
        success = false;
    }
    if (!gPacman.LoadFromFile("Images/pacman4.png", gRenderer))
    {
        printf("Failed to load sprite sheet texture!\n");
        success = false;
    }
    if (!gCell.LoadFromFile("Images/cell8.png", gRenderer))
    {
        printf("Failed to load sprite sheet texture!\n");
        success = false;
    }
    if (!gGameOverTexture.LoadFromFile("Images/game_over2.png", gRenderer))
    {
        printf("Failed to load sprite sheet texture!\n");
        success = false;
    }
    else
    {
        ///Set standard alpha blending
        gGameOverTexture.setBlendMode(SDL_BLENDMODE_BLEND);
    }
    if (!gQuitTexture.LoadFromFile("Images/QuitScreen1.png", gRenderer))
    {
        printf("Failed to load sprite sheet texture!\n");
        success = false;
    }
    else
    {
        ///Set standard alpha blending
        gQuitTexture.setBlendMode(SDL_BLENDMODE_BLEND);
    }
    if (!gButtonScreen.LoadFromFile("Images/screen2.png", gRenderer))
    {
        printf("Failed to load sprite sheet texture!\n");
        success = false;
    }
    else
    {
        ///Set standard alpha blending
        gButtonScreen.setBlendMode(SDL_BLENDMODE_BLEND);
    }
    //Load sound effects
    eatCandy = Mix_LoadWAV("Sounds/pacman_chomp.wav");
    if (eatCandy == NULL)
    {
        printf("Failed to load eatCandy sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    eatLolli = Mix_LoadWAV("Sounds/pacman_eatLolli.wav");
    if (eatLolli == NULL)
    {
        printf("Failed to load eatLolli sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    eatGhosts = Mix_LoadWAV("Sounds/pacman_eatghost.wav");
    if (eatGhosts == NULL)
    {
        printf("Failed to load eatGhosts sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    pacmanDeath = Mix_LoadWAV("Sounds/pacman_death.wav");
    if (pacmanDeath == NULL)
    {
        printf("Failed to load pacman death sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    gameBegin = Mix_LoadWAV("Sounds/pacman_beginning.wav");
    if (gameBegin == NULL)
    {
        printf("Failed to load pacman beginning sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    LevelEnd = Mix_LoadWAV("Sounds/pacman_intermission.wav");
    if (LevelEnd == NULL)
    {
        printf("Failed to load pacman intermission sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    buttonClick = Mix_LoadWAV("Sounds/button_click.wav");
    if (buttonClick == NULL)
    {
        printf("Failed to load buttonClick sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    game_over = Mix_LoadMUS("Sounds/game_over.wav");
    if (game_over == NULL)
    {
        printf("Failed to load game over sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    return success;
}

void close()
{
    ///Free loaded images
    gFontTexture.Free();
    gExcerpt.Free();
    gSplashTexture.Free();
    gMainMenuTexture.Free();
    gQuitTexture.Free();
    gButtonScreen.Free();
    gPacmanTexture.Free();
    gGameOverTexture.Free();
    gPacman.Free();
    gCell.Free();

    Mix_FreeChunk(eatCandy);
    eatCandy = NULL;
    Mix_FreeChunk(pacmanDeath);
    pacmanDeath = NULL;
    Mix_FreeChunk(eatLolli);
    eatLolli = NULL;
    Mix_FreeChunk(eatGhosts);
    eatGhosts = NULL;
    Mix_FreeChunk(gameBegin);
    gameBegin = NULL;
    Mix_FreeChunk(LevelEnd);
    LevelEnd = NULL;
    Mix_FreeChunk(buttonClick);
    buttonClick = NULL;
    //Free the music
    Mix_FreeMusic(game_over);
    game_over = NULL;

    ///Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    ///Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}
void setAlpha()
{
    ///Cap if below 0
    if (a - 3 < 0)
    {
        a = 0;
    }
    ///Decrement otherwise
    else
    {
        a -= 3;
    }
    ///Cap if above 255
    if (b + 3 > 255)
    {
        b = 255;
    }
    ///Increment otherwise
    else
    {
        b += 3;
    }
}
