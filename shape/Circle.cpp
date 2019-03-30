#include "Shape.h"
#include <math.h>

bool SHAPE::Circle::draw(Coor pos, Color co)
{
	int r = sqrt((this->start.x - this->end.x) * (this->start.x - this->end.x)
				+ (this->start.y - this->end.y) * (this->start.y - this->end.y));

	glColor3f(this->co.r, this->co.g, this->co.b);
	glBegin(GL_LINE_LOOP);
	for (float i = 0.01; i < 2 * PI; i += 0.1)
	{
		Coor_f co = convertCoor_f(convertCoor(Coor(this->start.x + r * cosf(i), this->start.y + r * sinf(i))));
		glVertex2f(co.x, co.y);
	}
	glEnd();

	glFlush();
	return true;
}

bool SHAPE::Circle::onShape(Coor pos)
{
	float diff = (this->start.x - pos.x) * (this->start.x - pos.x)
		+ (this->start.y - pos.y) * (this->start.y - pos.y)
		- (this->start.x - end.x) * (this->start.x - end.x)
		- (this->start.y - end.y) * (this->start.y - end.y);

	if (diff < 400 && diff > -400)
		return true;
	return false;
}