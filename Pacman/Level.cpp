#include "Level.h"

Level::Level(LTexture* food,LTexture* wall)
{
    //ctor
    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            grid[i][j].setPoint(j*32,i*32); //setting points for each grid cell
        }
    }
    this->food = food;
    this->wall = wall;
}

Level::~Level()
{
    //dtor
    std::cout << "Level Destructed" << std::endl;
}
Point Level::getCellPoint(int i, int j)
{
    return grid[i][j].getCellPoint();
}
void Level::generateRandomMaze()
{
    srand(time(NULL));
    //making ghost house
    DrawShape(9,13,GHOST_HOUSE,0);
    //making boundary walls
    for (int i = 0; i < 32; i++)
    {
        grid[0][i].fillCell(wall);
        grid[21][i].fillCell(wall);
    }
    for (int i = 1; i < 21; i++)
    {
        grid[i][0].fillCell(wall);
        grid[i][31].fillCell(wall);
    }
    int num_freeEnds = (rand() %  2) + 1; //1 or 2 free ends
    int* freeEnd_indices = new int(num_freeEnds);
    for (int i = 0; i < num_freeEnds; i++)
    {
        freeEnd_indices[i] = (rand() % 20)+1; //at what index free ends should be
    }
    //restrict the four corners after walls
    grid[1][1].RestrictCell();
    grid[20][1].RestrictCell();
    grid[1][30].RestrictCell();
    grid[20][30].RestrictCell();

    for (int i = 0; i < num_freeEnds; i++) //make free ends
    {
        grid[freeEnd_indices[i]][0].removeFill();
        grid[freeEnd_indices[i]][31].removeFill();
        grid[freeEnd_indices[i]][1].RestrictCell(); //restrict cell just in front of free ends
        grid[freeEnd_indices[i]][30].RestrictCell();
    }
    int random = 0; //random shape
    int ran_dir = 0; //random direction
    for (int i = 4; i < 18; i+=2)
    {
        for (int j = 4; j < 28; j+=2)
        {
            //draw some shape
            //setting random direction and shape
            random = rand() % 4;
            if (random == 0) ran_dir = rand() % 4;
            else if (random == 1) ran_dir = (rand() % 4) + 6;
            else if (random == 2) ran_dir = (rand() % 2) + 4;
            else if (random == 3) ran_dir = 0;
            DrawShape(i,j,random,ran_dir);
        }
    }

    for (int i = 1; i < 21; i++)
    {
        for (int j = 1; j < 31; j++)
        {
            grid[i][j].LoadFoodItem(food,i,j,&target_score); //loading food items in the cells
        }
    }

    delete[] freeEnd_indices;
}
Cell* Level::getCell(int i ,int j)
{
   return &grid[i][j];
}
void Level::FreeLevel()
{
    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            grid[i][j].removeFill();
            grid[i][j].UnRestrictCell();
            grid[i][j].setRestrictFood(false);
            if (grid[i][j].isFoodPresent())
            {
                grid[i][j].deallocateFood();
            }
        }
    }
}
void Level::Draw(long int& frame, SDL_Renderer* gRenderer)
{
    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            grid[i][j].Draw(frame,gRenderer);
        }
    }
}
void Level::DrawShape(int x, int y, int shape, int direction) //draws shape in any direction given an initial cell to start drawing
{
    switch(shape)
    {
        case(T_SHAPE):
            switch(direction)
            {
                case(UP):
                    for (int i = 0; i < 5; i++)
                    {
                        grid[x][y+i].fillCell(wall);
                        if (i == 2)
                        {
                            for (int j = 1; j < 4; j++)
                            {
                                grid[x+j][y+i].fillCell(wall);
                            }
                        }
                    }
                    for (int i = -1; i < 6; i++)
                    {
                        if (i == 2)
                        {
                            grid[x-1][y+i].RestrictCell();
                            grid[x][y-1].RestrictCell();
                            grid[x][y+5].RestrictCell();
                            for (int j = 0; j < 3; j++)
                            {
                                grid[x+2+j][y+i-1].RestrictCell();
                                grid[x+2+j][y+i+1].RestrictCell();
                            }
                            grid[x+4][y+2].RestrictCell();
                        }
                        else
                        {
                            grid[x-1][y+i].RestrictCell();
                            grid[x+1][y+i].RestrictCell();
                        }
                    }
                    break;
                case(DOWN):
                    for (int i = 0; i < 5; i++)
                    {
                        grid[x][y+i].fillCell(wall);
                        if (i == 2)
                        {
                            for (int j = 1; j < 4; j++)
                            {
                                grid[x-j][y+i].fillCell(wall);
                            }
                        }
                    }
                    for (int i = -1; i < 6; i++)
                    {
                        if (i == 2)
                        {
                            grid[x+1][y+i].RestrictCell();
                            grid[x][y-1].RestrictCell();
                            grid[x][y+5].RestrictCell();
                            for (int j = 0; j < 3; j++)
                            {
                                grid[x-2-j][y+i-1].RestrictCell();
                                grid[x-2-j][y+i+1].RestrictCell();
                            }
                            grid[x-4][y+2].RestrictCell();
                        }
                        else
                        {
                            grid[x-1][y+i].RestrictCell();
                            grid[x+1][y+i].RestrictCell();
                        }
                    }
                    break;
                case(LEFT):
                    for (int i = 0; i < 5; i++)
                    {
                        grid[x+i][y].fillCell(wall);
                        if (i == 2)
                        {
                            for (int j = 1; j < 4; j++)
                            {
                                grid[x+i][y+j].fillCell(wall);
                            }
                        }
                    }
                    for (int i = -1; i < 6; i++)
                    {
                        if (i == 2)
                        {
                            grid[x+i][y-1].RestrictCell();
                            grid[x-1][y].RestrictCell();
                            grid[x+5][y].RestrictCell();
                            for (int j = 0; j < 3; j++)
                            {
                                grid[x+i+1][y+2+j].RestrictCell();
                                grid[x+i-1][y+2+j].RestrictCell();
                            }
                            grid[x+2][y+4].RestrictCell();
                        }
                        else
                        {
                            grid[x+i][y-1].RestrictCell();
                            grid[x+i][y+1].RestrictCell();
                        }
                    }
                    break;
                case(RIGHT):
                    for (int i = 0; i < 5; i++)
                    {
                        grid[x+i][y].fillCell(wall);
                        if (i == 2)
                        {
                            for (int j = 1; j < 4; j++)
                            {
                                grid[x+i][y-j].fillCell(wall);
                            }
                        }
                    }
                    for (int i = -1; i < 6; i++)
                    {
                        if (i == 2)
                        {
                            grid[x+i][y+1].RestrictCell();
                            grid[x-1][y].RestrictCell();
                            grid[x+5][y].RestrictCell();
                            for (int j = 0; j < 3; j++)
                            {
                                grid[x+i+1][y-2-j].RestrictCell();
                                grid[x+i-1][y-2-j].RestrictCell();
                            }
                            grid[x+2][y-4].RestrictCell();
                        }
                        else
                        {
                            grid[x+i][y+1].RestrictCell();
                            grid[x+i][y-1].RestrictCell();
                        }
                    }
                    break;
            }
            break;

        case(L_SHAPE):
            switch(direction)
            {
                case(UP_LEFT):
                {
                    int i = 0;
                    for (; i < 4; i++)
                    {
                        grid[x+i][y].fillCell(wall);
                    }
                    i--;
                    grid[x+i][y-1].fillCell(wall);
                    grid[x+i][y-2].fillCell(wall);
                    for (int i = -1; i < 5; i++)
                    {
                        if (i == -1)
                        {
                            grid[x+i][y-1].RestrictCell();
                            grid[x+i][y+1].RestrictCell();
                            grid[x+i][y].RestrictCell();
                        }
                        else if (i == 2)
                        {
                            grid[x+i][y-1].RestrictCell();
                            grid[x+i][y+1].RestrictCell();
                            grid[x+i][y-2].RestrictCell();
                            grid[x+i][y-3].RestrictCell();
                        }
                        else if (i == 3)
                        {
                            grid[x+i][y+1].RestrictCell();
                            grid[x+i][y-3].RestrictCell();
                        }
                        else if (i == 4)
                        {
                            grid[x+i][y+1].RestrictCell();
                            grid[x+i][y].RestrictCell();
                            grid[x+i][y-1].RestrictCell();
                            grid[x+i][y-2].RestrictCell();
                            grid[x+i][y-3].RestrictCell();
                        }
                        else
                        {
                            grid[x+i][y-1].RestrictCell();
                            grid[x+i][y+1].RestrictCell();
                        }
                    }
                    break;
                }
                case(BOTTOM_LEFT):
                    grid[x][y-1].fillCell(wall);
                    grid[x][y-2].fillCell(wall);
                    for (int i = 0; i < 4; i++)
                    {
                        grid[x+i][y].fillCell(wall);
                    }
                    for (int i = -1; i < 5; i++)
                    {
                        if (i == -1)
                        {
                            grid[x+i][y-1].RestrictCell();
                            grid[x+i][y].RestrictCell();
                            grid[x+i][y+1].RestrictCell();
                            grid[x+i][y-2].RestrictCell();
                            grid[x+i][y-3].RestrictCell();
                        }
                        else if (i == 1)
                        {
                            grid[x+i][y-1].RestrictCell();
                            grid[x+i][y+1].RestrictCell();
                            grid[x+i][y-2].RestrictCell();
                            grid[x+i][y-3].RestrictCell();
                        }
                        else if (i == 0)
                        {
                            grid[x+i][y+1].RestrictCell();
                            grid[x+i][y-3].RestrictCell();
                        }
                        else if (i == 4)
                        {
                            grid[x+i][y-1].RestrictCell();
                            grid[x+i][y+1].RestrictCell();
                            grid[x+i][y].RestrictCell();
                        }
                        else
                        {
                            grid[x+i][y-1].RestrictCell();
                            grid[x+i][y+1].RestrictCell();
                        }
                    }
                    break;
                case(UP_RIGHT):
                {
                    int i = 0;
                    for (; i < 4; i++)
                    {
                        grid[x+i][y].fillCell(wall);
                    }
                    i--;
                    grid[x+i][y+1].fillCell(wall);
                    grid[x+i][y+2].fillCell(wall);
                    for (int i = -1; i < 5; i++)
                    {
                        if (i == -1)
                        {
                            grid[x+i][y-1].RestrictCell();
                            grid[x+i][y+1].RestrictCell();
                            grid[x+i][y].RestrictCell();
                        }
                        else if (i == 2)
                        {
                            grid[x+i][y-1].RestrictCell();
                            grid[x+i][y+1].RestrictCell();
                            grid[x+i][y+2].RestrictCell();
                            grid[x+i][y+3].RestrictCell();
                        }
                        else if (i == 3)
                        {
                            grid[x+i][y-1].RestrictCell();
                            grid[x+i][y+3].RestrictCell();
                        }
                        else if (i == 4)
                        {
                            grid[x+i][y-1].RestrictCell();
                            grid[x+i][y].RestrictCell();
                            grid[x+i][y+1].RestrictCell();
                            grid[x+i][y+2].RestrictCell();
                            grid[x+i][y+3].RestrictCell();
                        }
                        else
                        {
                            grid[x+i][y-1].RestrictCell();
                            grid[x+i][y+1].RestrictCell();
                        }
                    }
                    break;
                }
                case(BOTTOM_RIGHT):
                    grid[x][y+1].fillCell(wall);
                    grid[x][y+2].fillCell(wall);
                    for (int i = 0; i < 4; i++)
                    {
                        grid[x+i][y].fillCell(wall);
                    }
                    for (int i = -1; i < 5; i++)
                    {
                        if (i == -1)
                        {
                            grid[x+i][y-1].RestrictCell();
                            grid[x+i][y].RestrictCell();
                            grid[x+i][y+1].RestrictCell();
                            grid[x+i][y+2].RestrictCell();
                            grid[x+i][y+3].RestrictCell();
                        }
                        else if (i == 1)
                        {
                            grid[x+i][y-1].RestrictCell();
                            grid[x+i][y+1].RestrictCell();
                            grid[x+i][y+2].RestrictCell();
                            grid[x+i][y+3].RestrictCell();
                        }
                        else if (i == 0)
                        {
                            grid[x+i][y-1].RestrictCell();
                            grid[x+i][y+3].RestrictCell();
                        }
                        else if (i == 4)
                        {
                            grid[x+i][y-1].RestrictCell();
                            grid[x+i][y+1].RestrictCell();
                            grid[x+i][y].RestrictCell();
                        }
                        else
                        {
                            grid[x+i][y-1].RestrictCell();
                            grid[x+i][y+1].RestrictCell();
                        }
                    }
                    break;
            }
            break;
        case(I_SHAPE):
            switch(direction)
            {
                case(VERTICAL):
                    for (int i = 0; i < 4; i++)
                    {
                        grid[x+i][y].fillCell(wall);
                    }
                    for (int i = -1; i < 2; i++)
                    {
                        if(i == 0)
                        {
                            grid[x-1][y].RestrictCell();
                            grid[x+4][y].RestrictCell();
                        }
                        else
                        {
                            for (int j = -1; j < 5; j++)
                            {
                                grid[x+j][y+i].RestrictCell();
                            }
                        }
                    }
                    break;
                case(HORIZONTAL):
                    for (int i = 0; i < 4; i++)
                    {
                        grid[x][y+i].fillCell(wall);
                    }
                    for (int i = -1; i < 2; i++)
                    {
                        if(i == 0)
                        {
                            grid[x][y-1].RestrictCell();
                            grid[x][y+4].RestrictCell();
                        }
                        else
                        {
                            for (int j = -1; j < 5; j++)
                            {
                                grid[x+i][y+j].RestrictCell();
                            }
                        }
                    }
                    break;
            }
            break;
        case(BOX):
        {
            int i = 0;
            grid[x+1][y].fillCell(wall);
            for (; i < 3; i++)
            {
                grid[x][y+i].fillCell(wall);
                grid[x+2][y+i].fillCell(wall);
            }
            i--;
            grid[x+1][y+i].fillCell(wall);
            for (int j = -1; j < 4; j++)
            {
                grid[x-1][y+j].RestrictCell();
                grid[x+3][y+j].RestrictCell();
            }
            for (int j = -1; j < 4; j++)
            {
                grid[x+j][y-1].RestrictCell();
                grid[x+j][y+3].RestrictCell();
            }
            grid[x+1][y+1].RestrictCell();
            grid[x+1][y+1].setRestrictFood(true);
        }
        break;
        case(GHOST_HOUSE):
        {
            int i = 0;
            grid[x+1][y].fillCell(wall);
            for (; i < 5; i++)
            {
                grid[x][y+i].fillCell(wall);
                grid[x+2][y+i].fillCell(wall);
            }
            i--;
            grid[x+1][y+i].fillCell(wall);
            for (int j = -1; j < 6; j++)
            {
                grid[x-1][y+j].RestrictCell();
                grid[x+3][y+j].RestrictCell();
            }
            for (int j = -1; j < 4; j++)
            {
                grid[x+j][y-1].RestrictCell();
                grid[x+j][y+5].RestrictCell();
            }
            grid[x+1][y+1].RestrictCell();
            grid[x+1][y+2].RestrictCell();
            grid[x+1][y+3].RestrictCell();
            grid[x+1][y+1].setRestrictFood(true);
            grid[x+1][y+2].setRestrictFood(true);
            grid[x+1][y+3].setRestrictFood(true);
            grid[x-1][y+2].setRestrictFood(true);
            grid[x+3][y+2].setRestrictFood(true);
            break;
        }
    }
}
