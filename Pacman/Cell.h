#ifndef CELL_H
#define CELL_H
#include "Point.h"
#include <iostream>
#include <SDL.h>
#include <stdlib.h>
#include <time.h>
#include "LTexture.h"
#include "FoodItem.h"
#include "Candy.h"
#include "Lollipop.h"

class Cell
{
    public:
        Cell();
        ~Cell();
        void setPoint(int x,int y); //sets the pixel location of the cell
        Point getCellPoint(); //returns the pixel location of the cell
        bool isFoodPresent() {return food_present;}
        bool get_isCellFilled() {return isCellFilled;}
        bool get_isCellRestricted() {return restricted_fill;}
        FoodItem* getFood() {return food;}
        void deallocateFood(); //frees the food
        void LoadFoodItem(LTexture*, int, int,int*); //loads a new food item randomly (either a candy or lollipop)
        void LoadSavedFood(std::string,LTexture*, int, int); //loads a saved food item
        void fillCell(LTexture*); //fill a cell with a wall
        void removeFill(); //removes the wall from a cekk
        //bool insideCell(Point p); //tells whether an object is inside a cell based on its coordinates
        void Draw(long int& frame, SDL_Renderer*);
        void RestrictCell(); //sets the restricted_fill true
        void UnRestrictCell();//sets the restricted_fill false
        void setRestrictFood(bool);
        std::string GetFoodName(); //returns the name of the food


    protected:

    private:
        Point point; //top left position of the cell
        bool isCellFilled; //indicates whether the cell is filled or not
        bool restricted_fill; //indicated whether a wall can be built on that cell or not
        bool food_present; //tells whether any food is present in the cell or not
        bool restrictFood; //is the food restricted in that cell
        SDL_Rect Rect; //for wall image
        SDL_Rect rect; //for debugging
        FoodItem* food;
        LTexture* image;
        int width;
        int height;
};

#endif // CELL_H
