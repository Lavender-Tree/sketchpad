#include "Shape.h"
#include <stdio.h>

using namespace SHAPE;

bool Line::draw(Coor pos, Color co)
{
    Coor_f start = convertCoor_f(convertCoor(this->start)), 
         end = convertCoor_f(convertCoor(pos));

    glBegin(GL_LINE_LOOP);
        glColor3f(this->co.r, this->co.g, this->co.b);
        glVertex2f(start.x, start.y);
        glVertex2f(end.x, end.y);
    glEnd();

    glFlush();
    
    return true;
}

bool Line::onShape(Coor pos)
{
	if (onLine(pos, this->start, this->end))
		return true;
    return false;
}

