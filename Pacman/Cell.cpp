#include "Cell.h"
Cell::Cell()
{
    //ctor
    srand(time(NULL));
    isCellFilled = false;
    restricted_fill = false;
    food_present = false;
    food = NULL;
    width = 32;
    height = 32;
    restrictFood = false;
}

Cell::~Cell()
{
    //dtor
    if (food_present)
    {
        delete food;
    }
    //std::cout << "Cell is destructed" << std::endl;
}
void Cell::setPoint(int x, int y)
{
    point.x = x;
    point.y = y;
}
Point Cell::getCellPoint()
{
    return point;
}

std::string Cell::GetFoodName()
{
    if (food_present)
    {
        return food->getName();
    }
    else
    {
        return "";
    }
}
void Cell::deallocateFood()
{
    delete food;
    food = NULL;
    food_present = false;
}
void Cell::fillCell(LTexture* image)
{
    if (!restricted_fill)
    {
        isCellFilled = true;
        this->image = image;

        int random_x = rand() % 8; //randomly pick any of the row from the image containing different cell patterns
        int random_y = rand() % 8; //randomly pick any of the column from the image containing different cell patterns
        Rect.x = random_x*32; //use the above information to form a rect
        Rect.y = random_y*32;
        Rect.w = 32;
        Rect.h = 32;
    }

}
void Cell::removeFill()
{
    isCellFilled = false;

}
void Cell::RestrictCell()
{
    if (!isCellFilled)
    {
        restricted_fill = true;
    }
}
void Cell::LoadFoodItem(LTexture* image, int x, int y,int* target_count)
{
    if (!isCellFilled && !restrictFood)
    {
        int random = rand() % 100;
        if (random < 98) //chances of making a loading a candy are 98%
        {
            food = new Candy(image,x,y);
        }
        else //chances of making a loading a lollipop are 2%
        {
            food = new Lollipop(image,x,y);
        }
        food_present = true;
        *target_count = *target_count + 1;
    }
}
void Cell::LoadSavedFood(std::string foodname,LTexture* image, int x, int y)
{
    food_present = true;
    if (foodname == "Candy")
    {
        food = new Candy(image,x,y);
    }
    else if (foodname == "Lollipop")
    {
        food = new Lollipop(image,x,y);
    }
}
void Cell::setRestrictFood(bool set)
{
    restrictFood = set;
}
void Cell::UnRestrictCell()
{
    restricted_fill = false;
}
void Cell::Draw(long int& frame, SDL_Renderer* gRenderer)
{
    if (isCellFilled && !restricted_fill) //if the cell has a wall
    {
        image->RenderTexture(point.x , point.y , gRenderer,&Rect, SDL_FLIP_NONE,0.0, NULL);
    }
    else ///Render here
    {
        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
        //rect = {point.x, point.y, width, height};
        //SDL_RenderDrawRect( gRenderer, &rect );
        if (food != NULL)
        {
           food->Render(frame, gRenderer);

        }
    }
}
