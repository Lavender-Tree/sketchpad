#include "Data.h"
#include <math.h>

const int ORIGIN_W_W = 600;
const int ORIGIN_W_H = 600;

int W_WIDTH = ORIGIN_W_W;
int W_HEIGHT = ORIGIN_W_H;

int getWinWidth()
{
    return W_WIDTH;
}

int getWinHeight()
{
    return W_HEIGHT;
}

void setWinSize(int width, int height)
{
    W_WIDTH = width;
    W_HEIGHT = height;
}

Coor convertCoor(Coor coor)
{
    return Coor(coor.x - getWinWidth()/2, -coor.y + getWinHeight()/2);
}

Coor_f convertCoor_f(Coor coor)
{
	return Coor_f(2.0 * coor.x / getWinWidth(), 2.0 * coor.y / getWinHeight());
}

bool operator == (const Coor a, const Coor b)
{
    if(a.x == b.x && a.y == b.y)
        return true;
    else return false;
}

bool operator == (const Color a, const Color b)
{
	if (a.b == b.b && a.g == b.g && a.r == b.r)
		return true;
	return false;
}

int operator * (const VECT a, const VECT b)
{
	return a.x * b.x + a.y * b.y;
}

float M(VECT v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}
bool onLine(Coor pos, Coor start, Coor end)
{
	float diff;
	float k = 2, t;
	if (start.x - end.x != 0)	k = (end.y - start.y) / (end.x - (float)start.x);
	if (k > 1 || k < -1)
	{
		t = (end.x - (float)start.x) / (end.y - start.y);
		diff = t * (pos.y - start.y) + start.x - pos.x;
	}
	else 	diff = k * (pos.x - start.x) + start.y - pos.y;

	if((pos.x > start.x && pos.x < end.x) || (pos.x < start.x && pos.x > end.x)
		|| (pos.y > start.y && pos.y < end.y) || (pos.y < start.y && pos.y > end.y))
		if (diff > -8 && diff <= 8) 
			return true;
	return false;
}