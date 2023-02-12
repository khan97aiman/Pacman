#include "Pacman.h"

Pacman::Pacman(LTexture* image, int x, int y) : GameObject(image,x,y)
{
    for (int i = 0; i < 47; i++)
    {
        spriteClipsAlive[i].x = i*32;
        spriteClipsAlive[i].y = 2;
        spriteClipsAlive[i].w = 32;
        spriteClipsAlive[i].h = 32;
    }
    for (int i = 0; i < 23; i++)
    {
        spriteClipsDead[i].x = i*32;
        spriteClipsDead[i].y = 34;
        spriteClipsDead[i].w = 32;
        spriteClipsDead[i].h = 32;
    }

    widthSheet = spriteClipsAlive[0].w;
    heightSheet = spriteClipsAlive[0].h;
    direction = -1;
    angle = 0.0;
    target_x = 0;
    target_y = 0;
    score = 0;
    lives = 5;
    death_frame = 0;
    currentCell = {0,0,0,0};
    targetCell = {0,0,0,0};
    position = getGridPixel();

}

Pacman::~Pacman()
{
    //dtor
    std::cout <<  "Pacman destructed" << std::endl;
}
void Pacman::setDirection(int direction)
{
    this->direction = direction;
    switch(direction)
    {
        case(_UP):
            this->angle = -90.0;
            break;
        case(_DOWN):
            this->angle = 90.0;
            break;
        case(_RIGHT):
            this->angle = 0.0;
            break;
        case(_LEFT):
            this->angle = 180.0;
            break;
    }
}
int Pacman::getDirection()
{
    return direction;
}
void Pacman::SetTargetScore(int score)
{
    targetScore = score;
}
bool Pacman::CheckCollision(Ghost* ghost)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = this->GetCurrentObjectPosition().x;
    rightA = this->GetCurrentObjectPosition().x + this->GetCurrentObjectPosition().w;
    topA = this->GetCurrentObjectPosition().y;
    bottomA = this->GetCurrentObjectPosition().y + this->GetCurrentObjectPosition().h;

    //Calculate the sides of rect B
    leftB = ghost->GetCurrentObjectPosition().x;
    rightB = ghost->GetCurrentObjectPosition().x + ghost->GetCurrentObjectPosition().w;
    topB = ghost->GetCurrentObjectPosition().y;
    bottomB = ghost->GetCurrentObjectPosition().y + ghost->GetCurrentObjectPosition().h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
        return false;
    if( topA >= bottomB )
        return false;
    if( rightA <= leftB )
        return false;
    if( leftA >= rightB )
        return false;
    return true;
}

void Pacman::Render(long int& frame, SDL_Renderer* gRenderer)
{
    SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(gRenderer, 255,0,0, 90);
    SDL_RenderFillRect( gRenderer, &currentCell); //the red cell that specifies the current position of the player
    SDL_SetRenderDrawColor(gRenderer, 255,255,0, 90);
    SDL_RenderFillRect( gRenderer, &targetCell); // the yellow cell that specifies the target cell where the player wants to go
    if (alive)
    {
        spriteSheetTexture->RenderTexture(position.x, position.y, gRenderer,&spriteClipsAlive[frame % 47], SDL_FLIP_NONE,this->angle, NULL);
    }
    else
    {
        if (frame % 3 == 0)
        {
            death_frame++;
        }
        spriteSheetTexture->RenderTexture(position.x, position.y, gRenderer,&spriteClipsDead[death_frame % 23], SDL_FLIP_NONE,0.0, NULL);
        if (death_frame % 23 == 22) //if end of death animation, reset pacman
        {
            ResetPacman();
            endDeathAnimation = true; //mark end of death animation true
        }
    }
    ///FOR DEBUGGING
    /*SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
    SDL_RenderDrawPoint(gRenderer,GetCenter().x,GetCenter().y);
    SDL_Rect rect = { position.x, position.y, widthSheet, heightSheet };
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
    SDL_RenderDrawRect( gRenderer, &rect );*/
}

void Pacman::ResetPacman()
{
    alive = true;
    lives--;
    setGrid(12,15);
    position = getGridPixel();
    target_x = 0;
    target_y = 0;
    direction = -1;
    angle = 0;
    death_frame = 0;
    currentCell = {0,0,0,0};
    targetCell = {0,0,0,0};
}
void Pacman::Move(Level* level)
{
	if (direction == _LEFT) //if the direction is left
	{
        if (getGrid().y == 0) //if pacman manages to go to the very first column(means there is a free end)
        {
            setGrid(getGrid().x,31); //then set his grid and position towards the extreme right of the screen
            position.x = GlobalFunctions::GetSCREEN_WIDTH(); //so that the player emerges from the other side
        }
	    target_x = getGrid().x; //update the target x_grid location
	    target_y = getGrid().y - 1; //update the target y_grid location
	    if (!level->getCell(target_x,target_y)->get_isCellFilled()) //if the target cell does not have a wall
        {
            speedx = -4;
            position.x += speedx; //make the pacman move
		}
		else
        {
            position = getGridPixel(); //else make his position equal to his grid location so that the position and grid location are always in accordance with each other
        }
	}
	if (direction == _RIGHT)
	{
        if (getGrid().y == 31)
        {
            setGrid(getGrid().x,0);
            position.x = 0;
        }
	    target_x = getGrid().x;
	    target_y = getGrid().y + 1;
        if (!level->getCell(target_x,target_y)->get_isCellFilled())
        {
            speedx = 4;
            position.x += speedx;
		}
		else
        {
            position = getGridPixel();
		}
	}
	if (direction == _UP)
	{
	    target_x = getGrid().x - 1;
	    target_y = getGrid().y;
        if (!level->getCell(target_x,target_y)->get_isCellFilled())
        {
            speedy = -4;
            position.y += speedy;
		}
		else
        {
            position = getGridPixel();
		}
	}
	if (direction == _DOWN)
	{
	    target_x = getGrid().x + 1;
	    target_y = getGrid().y;
        if (!level->getCell(target_x,target_y)->get_isCellFilled())
        {
            speedy = 4;
            position.y += speedy;
        }
        else
        {
            position = getGridPixel();
		}
	}
    UpdateGrid(GetCenter()); //keep uodating pacman's grid location according to his center position
    currentCell = {getGridPixel().x, getGridPixel().y, 32, 32}; //update current cell
    targetCell = {level->getCellPoint(target_x,target_y).x, level->getCellPoint(target_x,target_y).y, 32, 32}; //update target cell
}
void Pacman::eat(Level* level, Ghost** ghosts,Mix_Chunk* eatCandy, Mix_Chunk* eatLolli)
{
    if(level->getCell(getGrid().x,getGrid().y)->isFoodPresent()) //if the cell contains a food item
    {
        if (level->getCell(getGrid().x,getGrid().y)->GetFoodName() == "CANDY") //if the food item is a candy
        {
            Mix_PlayChannel( -1, eatCandy, 0 ); //sound effect for eating candy
            score++;
            targetScore++;
        }
        if (level->getCell(getGrid().x,getGrid().y)->GetFoodName() == "LOLLIPOP") //if the food item is a lollipop
        {
            Mix_PlayChannel( -1, eatLolli, 0 ); //sound effect for eating lollipop
            score++;
            targetScore++;
            //eating lollipops turns all ghosts blue
            for (int i = 0; i < 4; i++)
            {
                ghosts[i]->setScaredGhost(true);
                ghosts[i]->ResetScaredFrame(); //reset the scared frames of the ghosts to start the timer again
                //(the timer is the number of frames for which the blue ghosts are to be rendered until they get back to normal state again)
            }

        }
        level->getCell(getGrid().x,getGrid().y)->deallocateFood(); //deallocate the food item eaten
    }
}
void Pacman::EatGhost(Ghost* ghost)
{
    score += 20; //increase the score (shown on screen) by 20.
}
