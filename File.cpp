#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "shape/Shape.h"

bool loadShape(const char *name, std::vector<SHAPE::Shape *>& shape)
{
	int type;
	FILE *fin = NULL;
	fopen_s(&fin, name, "rb");
	if (!fin)	return false;
	while (!feof(fin))
	{
		fread(&type, 4, 1, fin);
		switch (type)
		{
		case LINE:
			shape.push_back(new SHAPE::Line());
			break;
		case RECT:
			shape.push_back(new SHAPE::Rect());
			break;
		case CIRCLE:
			shape.push_back(new SHAPE::Circle());
			break;
		default:
			return false;
			break;
		}
		int buf[7] = { 0 };
		fread(buf, 4, 7, fin);
		shape.back()->start.x = buf[0], shape.back()->start.y = buf[1];
		shape.back()->end.x = buf[2], shape.back()->end.y = buf[3];
		shape.back()->co.r = buf[4], shape.back()->co.g = buf[5], shape.back()->co.b = buf[6];
	}
	fclose(fin);
	return true;
}

bool saveShape(const char *name, std::vector<SHAPE::Shape *> shape)
{
	FILE *fout = NULL;
	int buf[8] = { 0 };
	fopen_s(&fout, name, "wb");
	if (!fout)	return false;

	for (auto it = shape.begin(); it != shape.end(); it++)
	{
		buf[0] = (*it)->type, buf[1] = (*it)->start.x, buf[2] = (*it)->start.y;
		buf[3] = (*it)->end.x, buf[4] = (*it)->end.y;
		buf[5] = (*it)->co.r, buf[6] = (*it)->co.g, buf[7] = (*it)->co.b;
		fwrite(buf, 4, 8, fout);
	}

	fclose(fout);
	return true;
}