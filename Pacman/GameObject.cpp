#include "GameObject.h"

GameObject::~GameObject()
{
    spriteSheetTexture = NULL;
    printf("GameObject Destroyed\n");
}
GameObject::GameObject(LTexture* image, int i, int j)
{
    spriteSheetTexture = image;
    grid.x = j*32; //sets the grid pixel location according to the grid number
    grid.y = i*32; //sets the grid pixel location according to the grid number
    speedx = 0;
    speedy = 0;
    alive  = true;
}
void GameObject::setGrid(int i,int j)
{
    grid.x = j*32;
    grid.y = i*32;
}
Point GameObject::getGridPixel(int i, int j)
{
    Point p;
    p.x = j*32;
    p.y = i*32;
    return p;
}
Point GameObject::getGrid(Point pixel)
{
    Point p;
    p.x = floor(pixel.y/32);
    p.y = floor(pixel.x/32);
    return p;
}
void GameObject::UpdateGrid(Point p)
{
    setGrid(getGrid(p).x,getGrid(p).y);
}
Point GameObject::GetCenter()
{
	Point p;
	p.x = (GetCurrentObjectPosition().x + GetCurrentObjectPosition().w / 2);
	p.y = (GetCurrentObjectPosition().y + GetCurrentObjectPosition().h / 2);
	return p;
}
bool GameObject::CheckAlive()
{
    return this->alive;
}

SDL_Rect& GameObject::GetCurrentObjectPosition()
{
	currentPostion = { position.x , position.y , widthSheet, heightSheet };
	return currentPostion;
}

