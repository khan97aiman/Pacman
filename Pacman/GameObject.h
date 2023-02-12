#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#endif // GAMEOBJECT_H
#include <stdio.h>
#include <iostream>
#include "LTexture.h"
#include "Point.h"
#include "GlobalFunctions.h"
#include <string>
#include <math.h>
#include <vector>
#include <SDL_mixer.h>
enum MOTION { _RIGHT, _LEFT, _UP, _DOWN };
class GameObject
{
protected:
    Point position; //Current top-left position of GameObject
    LTexture* spriteSheetTexture; //Loaded image
    int widthSheet, heightSheet; //Width and height of part of image to be loaded
    bool alive;
    float speedx;
    float speedy;
    std::string name = "";
    SDL_Rect currentPostion;
public:
    GameObject(LTexture*, int,int);
    virtual ~GameObject();
    bool CheckAlive();
    Point GetCenter(); //returns the center point
	void SetAlive(bool set) { alive = set; }
    virtual void Render(long int&, SDL_Renderer*) = 0;
    SDL_Rect& GetCurrentObjectPosition();
    std::string getName() {return name;}
    void setGrid(int i,int j); //set the pixel location of an object by its grid location
    Point getGrid(){ Point p = grid/32; return p;} //get the grid location of the object
    Point getGridPixel() {return grid;} //get the pixel location of the object
    Point getGridPixel(int i, int j); //returns the pixel location of an object based on grid location
    void setGridPixel(Point p){grid = p;} //sets the grid pixel location directly
    Point getGrid(Point); //returns the grid location based on any pixel location
    void UpdateGrid(Point);
    void setPosition(Point p){position = p;}
private:
    Point grid; //grid pixel location is private so that pixel location can't be modified. Only grid number can be modified by objects. This is grid pixel

};

