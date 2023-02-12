#ifndef POINT_H
#define POINT_H
#include <iostream>
//#pragma once

struct Point
{
	int x;
	int y;

	Point()
	{
        x = 0;
        y = 0;
	}

	Point(int x, int y)
	{
	    this->x = x;
	    this->y = y;
	}
	Point(const Point& point)
	{
	    x = point.x;
	    y = point.y;
	}
	bool operator == (Point point) //equal to operator
	{
	    return (this->x == point.x && this->y == point.y);
	}
	void operator = (Point point) //assignment operator
	{
	    this->x = point.x;
	    this->y = point.y;
	}
	bool operator != (Point point) //not equal operator
	{
	    return (this->x != point.x || this->y != point.y);
	}
	Point operator /(int divisor) //used to divide both x and y by a number
	{
	    Point p;
	    p.x = y/divisor;
	    p.y = x/divisor;
	    return p;
	}
	Point operator + (int number) //adds a number to both x and y
	{
	    x += number;
	    y += number;
	    return *this;
	}
	Point operator - (int number) //subtracts a number from both x and y
	{
	    x -= number;
	    y -= number;
	    return *this;
	}
};
#endif // POINT_H
