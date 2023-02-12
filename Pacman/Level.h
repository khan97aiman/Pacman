#ifndef LEVEL_H
#define LEVEL_H
#include "Cell.h"
#include <ostream>
#include "math.h"
#include "LTexture.h"
enum DIRECTION {UP, DOWN, LEFT, RIGHT, VERTICAL, HORIZONTAL,UP_LEFT, UP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT};
enum SHAPE {T_SHAPE, L_SHAPE, I_SHAPE, BOX, GHOST_HOUSE};
class Level
{
    public:
        Level(LTexture*,LTexture*);
        ~Level();
        void Draw(long int& frame,SDL_Renderer*); //to render the level
        void generateRandomMaze(); //generates a random maze
        void DrawShape(int, int, int, int); //draws shapes of the wall
        Point getCellPoint(int, int); //returns the cell point according to the grid number (x,y grid)
        Cell* getCell(int,int);
        void FreeLevel(); //frees a level of all objects and maze
        int getTargetCount() {return target_score;}
        void setTargetCount(int set) {target_score = set;}
    protected:

    private:
        Cell grid[22][32]; //2d arrays of cells that defines the grid of levels
        LTexture* food; //texture that contains food clips
        LTexture* wall; //texture that contains cell walls
        int target_score = 0; //the target score of a level which is given by the total number of candies and lollipops
};

#endif // LEVEL_H
