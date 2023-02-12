#include "Ghost.h"

Ghost::Ghost(LTexture* image, int x, int y) : GameObject(image,x,y)
{
    //ctor
    srand(time(NULL));
        //ctor
    spriteClips_scared[0].x = 385;
    spriteClips_scared[0].y = 0;
    spriteClips_scared[0].w = 30;
    spriteClips_scared[0].h = 32;

    spriteClips_scared[1].x = 385;
    spriteClips_scared[1].y = 32;
    spriteClips_scared[1].w = 30;
    spriteClips_scared[1].h = 32;

    eyes.x = 387;
    eyes.y = 72;
    eyes.w = 25;
    eyes.h = 13;
    currentCell = {0,0,0,0};
    position = getGridPixel();
}

Ghost::~Ghost()
{
    //dtor
}
void Ghost::Render(long int& frame, SDL_Renderer* gRenderer)
{
    SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(gRenderer, 0,0,255, 90);
    SDL_RenderFillRect( gRenderer, &currentCell);
    if (frame % 25 == 0)
    {
        current_frame++; //to control speed of the clips rendering of the ghosts
    }
    if (alive)
    {
        spriteSheetTexture->RenderTexture(position.x, position.y, gRenderer,&spriteClips[current_frame % 4], SDL_FLIP_NONE,0.0, NULL);
    }
    /*else
    {
        spriteSheetTexture->RenderTexture(position.x, position.y , gRenderer,&eyes, SDL_FLIP_NONE,0.0, NULL);
    }*/
    if (current_frame > 4)
    {
        current_frame = 0;
    }
}
void Ghost::Scared_Render(long int& frame, SDL_Renderer* gRenderer)
{
    SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(gRenderer, 0,0,255, 90);
    SDL_RenderFillRect( gRenderer, &currentCell);
    if (frame % 10 == 0)
    {
        scared_frame++; //to control speed of the scared clips
    }
    if (scared_frame >= 40) //if scared frame is greater than or equal to 40, start rendering the white/blue ghosts
    {
        if (scared_frame < 60) //and do that until it is lesser than 60
        {
            spriteSheetTexture->RenderTexture(position.x, position.y , gRenderer,&spriteClips_scared[scared_frame % 2], SDL_FLIP_NONE,0.0, NULL);
        }
        else //otherwise make the scared_ghost false so that normal ghost can be rendered
        {
            scared_frame = 0;
            scared_ghost = false;
        }
    }
    else //if scared frame is lesser than 40 then blue ghost (this means blue ghosts will be rendered for a total of 400 frames
    {
        spriteSheetTexture->RenderTexture(position.x, position.y, gRenderer,&spriteClips_scared[0], SDL_FLIP_NONE,0.0, NULL);
    }

}
void Ghost::setDirection(int direction)
{
    this->direction = direction;
}
void Ghost::Move(Level* level)
{
    //same as that of pacman
	if (direction == _LEFT)
	{
        if (getGrid().y == 0)
        {
            setGrid(getGrid().x,31);
            position.x = GlobalFunctions::GetSCREEN_WIDTH();
        }
	    if (!level->getCell(getGrid().x,getGrid().y-1)->get_isCellFilled())
        {
            speedx = -6;
            position.x += speedx;
		}
		else
        {
            direction = rand() % 4;
            position = getGridPixel();
        }
	}
	if (direction == _RIGHT)
	{
        if (getGrid().y == 31)
        {
            setGrid(getGrid().x,0);
            position.x = 0;
        }
        if (!level->getCell(getGrid().x,getGrid().y+1)->get_isCellFilled())
        {
            speedx = 6;
            position.x += speedx;
		}
		else
        {
            direction = rand() % 4;
            position = getGridPixel();
        }
	}
	if (direction == _UP)
	{
        if (!level->getCell(getGrid().x-1,getGrid().y)->get_isCellFilled() || (getGrid().x-1 == 9 && getGrid().y >= 14 && getGrid().y <= 16))
        {
            speedy = -6;
            position.y += speedy;
		}
		else
        {
            direction = rand() % 4;
            position = getGridPixel();
        }
	}
	if (direction == _DOWN)
	{
        if (!level->getCell(getGrid().x+1,getGrid().y)->get_isCellFilled())
        {
            speedy = 6;
            position.y += speedy;
        }
        else
        {
            direction = rand() % 4;
            position = getGridPixel();
        }
	}
	UpdateGrid(GetCenter());
    currentCell = {getGridPixel().x, getGridPixel().y, 32, 32};

}

