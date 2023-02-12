#include "Game.h"

Game::Game()
{
    //ctor
    pacman = NULL;
    level = NULL;
    words = NULL;
    for (int i = 0; i < 4; i++)
    {
        ghosts[i] = NULL;
    }
    startingLevel = NULL;
    startingLevelScreen = false;
    level_no = 1;
}
void Game::NewGame(LTexture* pacmanImage,LTexture* pacmanSheet, LTexture* fontSprite, LTexture* cell,LTexture* level_screen)
{
    if (level != NULL)
    {
        Restart();
    }
    else //if the game has not been running previously then make all characters and objects
    {
        level = new Level(pacmanSheet,cell);
        level->generateRandomMaze();
        words = new Word[5];
        std::string Text[2] = {"SCORE","LIVES"};
        for (int i = 0; i < 2; i++)
        {
            words[i] = Word(Text[i],fontSprite,130 + (350*(i+1)) + (80*(i-1)),height-30);
        }
        pacman = new Pacman(pacmanImage,12,15);
        ghosts[0] = new Blinky(pacmanSheet,8,15);
        ghosts[1] = new Inky(pacmanSheet,10,14);
        ghosts[2] = new Pinky(pacmanSheet,10,15);
        ghosts[3] = new Clyde(pacmanSheet,10,16);
        words[2] = Word(GlobalFunctions::int_to_string(pacman->getScore()),fontSprite,words[0].getWidth()+ 440, height-30);
        words[3] = Word(GlobalFunctions::int_to_string(pacman->getLives()),fontSprite,words[1].getWidth()+ 800,height-30);
        words[4] = Word("Going to next level",fontSprite,width/2,height/2);
        startingLevel = new GameLevelScreen(level_screen,fontSprite,level_no);
    }
    startingLevelScreen = true;
}
void Game::LoadGame(LTexture* pacmanImage,LTexture* pacmanSheet, LTexture* fontSprite, LTexture* cell,LTexture* level_screen)
{
    if (level == NULL) //if the game has not been running previously then make all characters and objects
    {
        level = new Level(pacmanSheet,cell);


        words = new Word[5];
        std::string Text[2] = {"SCORE","LIVES"};
        for (int i = 0; i < 2; i++)
        {
            words[i] = Word(Text[i],fontSprite,130 + (350*(i+1)) + (80*(i-1)),height-30);
        }
        pacman = new Pacman(pacmanImage,level->getCellPoint(12,15).x,level->getCellPoint(12,15).y);
        ghosts[0] = new Blinky(pacmanSheet,level->getCellPoint(8,15).x,level->getCellPoint(8,15).y);
        ghosts[1] = new Inky(pacmanSheet,level->getCellPoint(10,14).x,level->getCellPoint(10,14).y);
        ghosts[2] = new Pinky(pacmanSheet,level->getCellPoint(10,15).x,level->getCellPoint(10,15).y);
        ghosts[3] = new Clyde(pacmanSheet,level->getCellPoint(10,16).x,level->getCellPoint(10,16).y);
        words[2] = Word(GlobalFunctions::int_to_string(pacman->getScore()),fontSprite,words[0].getWidth()+ 440, height-30);
        words[3] = Word(GlobalFunctions::int_to_string(pacman->getLives()),fontSprite,words[1].getWidth()+ 800,height-30);
        words[4] = Word("Going to next level",fontSprite,width/2,height/2);
        startingLevel = new GameLevelScreen(level_screen,fontSprite,level_no);
    }
    level->FreeLevel(); //free any previous level
    ifstream file ("GameData.csv");
    string line;
    string line1;
    if (file.is_open())
    {
        getline(file, line);
        level_no = atoi(line.c_str());
        getline(file, line);
        level->setTargetCount(atoi(line.c_str()));
        getline(file, line);
        pacman->setScore(atoi(line.c_str()));
        getline(file, line);
        pacman->SetTargetScore(atoi(line.c_str()));
        getline(file, line);
        pacman->setLives(atoi(line.c_str()));
        getline(file, line);
        getline(file, line1);
        pacman->setGrid(atoi(line.c_str()),atoi(line1.c_str()));
        pacman->setPosition(pacman->getGridPixel());
        getline(file, line);
        pacman->setDirection(atoi(line.c_str()));

        for (int i = 0; i < 4; i++) //also save ghosts states
        {
            getline(file, line);
            getline(file, line1);
            ghosts[i]->setGrid(atoi(line.c_str()),atoi(line1.c_str()));
            ghosts[i]->setPosition(ghosts[i]->getGridPixel());
        }
        for (int i = 0; i < 22; i++)
        {
            for (int j = 0; j< 32; j++)
            {
                getline(file, line,',');
                if ( line == "|_|"  || line == "\n|_|")
                {
                    level->getCell(i,j)->fillCell(cell);

                }
                else if (line == "x")
                {
                    level->getCell(i,j)->RestrictCell();
                    level->getCell(i,j)->setRestrictFood(true);
                }
                else if (line == "*x")
                {
                    level->getCell(i,j)->RestrictCell();
                    level->getCell(i,j)->LoadSavedFood("Candy",pacmanSheet,i,j);
                }
                else if (line == "**x")
                {
                    level->getCell(i,j)->RestrictCell();
                    level->getCell(i,j)->LoadSavedFood("Lollipop",pacmanSheet,i,j);
                }
                else if (line == "*")
                {
                    level->getCell(i,j)->LoadSavedFood("Candy",pacmanSheet,i,j);
                }
                else if (line == "**")
                {
                    level->getCell(i,j)->LoadSavedFood("Lollipop",pacmanSheet,i,j);
                }
            }
        }
        file.close();
        startingLevel->ChangeLevel(level_no);
        startingLevelScreen = true;
    }
    else
    {
        cout << "There is no saved data" << endl;
        exit(-1);
    }

}
void Game::SaveGame()
{
    std::ofstream file;
    file.open("GameData.csv");
    file << level_no << "\n";
    file << level->getTargetCount() << "\n";
    file << pacman->getScore() << "\n";
    file << pacman->getTargetScore() << "\n";
    file << pacman->getLives() << "\n";
    file << pacman->getGrid().x << "\n";
    file << pacman->getGrid().y << "\n";

    file << pacman->getDirection() << "\n";

    for (int i = 0; i < 4; i++) //also save ghosts states
    {
        file << ghosts[i]->getGrid().x << "\n";
        file << ghosts[i]->getGrid().y << "\n";
    }

    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            if (level->getCell(i,j)->isFoodPresent()) //if not food restricted and not filled
            {
                if (level->getCell(i,j)->GetFoodName() == "CANDY")
                {
                    file << "*"; //write * for candy
                }
                else
                {
                    file << "**"; //write ** for lollipop
                }
            }
            else if (level->getCell(i,j)->get_isCellFilled())
            {
                file << "|_|"; //if there is a wall then write "|_|" to the file
            }
            if (level->getCell(i,j)->get_isCellRestricted())
            {
                file << "x"; //write x if the cell has a restriction on wall
            }
            file << ",";
        }
        file << "\n";
    }
    file.close();

}
void Game::StartGame()
{
    startingLevelScreen = false; //to start the game, stop rendering the level screen
    pacman->setEndDeathAnimation(false);
    pacman->setDirection(_RIGHT);
    for (int i = 0; i < 4; i++)
    {
        ghosts[i]->setDirection(_UP);
    }
}
void Game::Render(long int& frame,SDL_Renderer* gRenderer)
{
    for (int i = 0; i < 4; i++)
    {
        words[i].Render(gRenderer);
    }
    level->Draw(frame, gRenderer);
    pacman->Render(frame,gRenderer);
    for (int i = 0; i < 4; i++)
    {
        if (ghosts[i]->getScaredGhost())
        {
            ghosts[i]->Scared_Render(frame,gRenderer);
        }
        else
        {
            ghosts[i]->Render(frame,gRenderer);
        }
    }
    if (startingLevelScreen)
    {
        //render level screen
        startingLevel->Render(frame,gRenderer);
    }
}
void Game::GameLoop(SDL_Renderer* gRenderer,Mix_Chunk* eatCandy, Mix_Chunk* eatGhosts, Mix_Chunk* eatLolli, Mix_Chunk* pacmanDeath,Mix_Chunk* LevelEnd)
{
    pacman->Move(level);
    pacman->eat(level,ghosts,eatCandy,eatLolli);
    words[2].changeWord(GlobalFunctions::int_to_string(pacman->getScore()));
    words[3].changeWord(GlobalFunctions::int_to_string(pacman->getLives()));
    for (int i = 0; i < 4; i++)
    {
        if (pacman->CheckCollision(ghosts[i]) && !ghosts[i]->getScaredGhost()) //if pacman collides with any ghosts
        {
            Mix_PlayChannel( -1, pacmanDeath, 0 );
            pacman->SetAlive(false); //set its life false, so that its life can be decreased
            pacman->setDirection(-1);
            ResetAllGhosts();
        }
        else if (pacman->CheckCollision(ghosts[i]) && ghosts[i]->getScaredGhost())
        {
            Mix_PlayChannel( -1, eatGhosts, 0 );
            pacman->EatGhost(ghosts[i]);
            ghosts[i]->ResetGhost();
            ghosts[i]->setDirection(_UP);
        }
        else
        {
            ghosts[i]->Move(level);
        }
    }
    if (pacman->getTargetScore() == level->getTargetCount())
    {
        Mix_PlayChannel( -1, LevelEnd, 0 );
        NextLevel();
        SDL_Delay(2000);
        SDL_RenderClear(gRenderer);
        SDL_SetRenderDrawColor(gRenderer,0,0,0,0);
        words[4].Render(gRenderer); //render going to next level
        SDL_RenderPresent(gRenderer);
        SDL_Delay(2000); //short delay to give some time to go to the next level.
    }
    if (pacman->GetEndDeathAnimation() || gameOver())
    {
        startingLevelScreen = true;
    }
}
bool Game::gameOver()
{
    return pacman->getLives() < 0;
}
void Game::NextLevel()
{
    pacman->ResetPacman();
    pacman->setLives(pacman->getLives()+1);
    pacman->setScore(0);
    pacman->SetTargetScore(0);
    level->FreeLevel();
    level->generateRandomMaze();
    ///reset ghosts and their positions
    ResetAllGhosts();
    startingLevelScreen = true;
    //scared_ghosts = false;
    level_no++;
    startingLevel->ChangeLevel(level_no);
}
void Game::Restart()
{
    pacman->ResetPacman();
    pacman->setLives(5);
    pacman->setScore(0);
    pacman->SetTargetScore(0);
    level->FreeLevel();
    level->generateRandomMaze();
    ///reset ghosts and their positions
    ResetAllGhosts();
    startingLevelScreen = true;
    //scared_ghosts = false;
    level_no = 1;
    startingLevel->ChangeLevel(level_no);

}
void Game::setPacmanDirection(int direction)
{
    pacman->setDirection(direction);
}
void Game::ResetAllGhosts()
{
    for (int i = 0; i < 4; i++)
    {
        ghosts[i]->ResetGhost();
    }
}

Game::~Game()
{
    for (int i = 0; i < 4; i++)
    {
        delete ghosts[i];
    }
    delete startingLevel;
    delete pacman;
    delete[] words;
    delete level;
    std::cout << "Game Destroyed" << std::endl;
}


