#include "Shape.h"

bool SHAPE::Rect::draw(Coor pos, Color co )
{
	Coor_f a = convertCoor_f(convertCoor(this->start)), b = convertCoor_f(convertCoor(pos));

	glColor3f(this->co.r, this->co.g, this->co.b);
	glBegin(GL_LINE_LOOP);
		glVertex2f(a.x, a.y);
		glVertex2f(b.x, a.y);
		glVertex2f(b.x, b.y);
		glVertex2f(a.x, b.y);
	glEnd();
	return true;
}

bool SHAPE::Rect::onShape(Coor pos)
{
	Coor a = this->start, b(this->end.x, this->start.y),
			c = this->end, d(this->start.x, this->end.y);

	if (onLine(pos, a, b) || onLine(pos, b, c) || onLine(pos, c, d) || onLine(pos, d, a))
		return true;
	return false;
}